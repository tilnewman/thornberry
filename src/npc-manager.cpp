//
// npc-manager.cpp
//
#include "npc-manager.hpp"

#include "avatar-image.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "player.hpp"
#include "random.hpp"
#include "sfml-util.hpp"

#include <SFML/Graphics/Rect.hpp>

#include <algorithm>
#include <iostream>
#include <string>

namespace thornberry
{

    NpcManager::NpcManager()
        : m_npcs{}
    {}

    void NpcManager::postLevelLoadSetup(const Context & t_context)
    {
        m_npcs.clear();

        // if the map artist didn't lay down any walk bounds then we can't place any NPCs
        if (t_context.level.npcWalkBounds().empty())
        {
            return;
        }

        const std::string levelName{ t_context.level.name() };
        if (levelName == "house.tmj")
        {
            const auto randomPositionOpt{ findRandomAvailableSpawnPosition(t_context) };
            if (randomPositionOpt.has_value())
            {
                Npc & npc{ m_npcs.emplace_back(AvatarImage::leather_corporal2_dark) };
                npc.setup(t_context);
                npc.standFacingRandomDirection(t_context);
                npc.setPosition(*randomPositionOpt);
            }
        }
        else if (levelName == "thornberry.tmj")
        {
            const std::size_t npcCount{ 10 };
            m_npcs.reserve(npcCount);

            const auto townFolkImages{ getAvatarImagesTownfolk() };

            for (std::size_t counter{ 0 }; counter < npcCount; ++counter)
            {
                const AvatarImage image{ t_context.random.from(townFolkImages) };
                const auto randomPositionOpt{ findRandomAvailableSpawnPosition(t_context) };
                if (randomPositionOpt.has_value())
                {
                    Npc & npc{ m_npcs.emplace_back(image) };
                    npc.setup(t_context);
                    npc.standFacingRandomDirection(t_context);
                    npc.setPosition(*randomPositionOpt);
                }
            }
        }
    }

    void NpcManager::update(const Context & t_context, const float t_elapsedSec)
    {
        for (Npc & npc : m_npcs)
        {
            npc.update(t_context, t_elapsedSec);
        }
    }

    void NpcManager::draw(
        const sf::Vector2f & t_mapToOffscreenOffset,
        sf::RenderTarget & t_target,
        sf::RenderStates t_states) const
    {
        for (const Npc & npc : m_npcs)
        {
            npc.draw(t_mapToOffscreenOffset, t_target, t_states);
        }
    }

    const std::optional<sf::Vector2f>
        NpcManager::pickRandomSpawnPosition(const Context & t_context) const
    {
        // all of this function is in map coordinates

        const std::vector<sf::FloatRect> & walkBounds{ t_context.level.npcWalkBounds() };
        if (walkBounds.empty())
        {
            return {};
        }

        const sf::FloatRect spawnMapRect{ t_context.random.from(walkBounds) };

        return sf::Vector2f{
            t_context.random.fromTo(
                spawnMapRect.position.x, (spawnMapRect.position.x + spawnMapRect.size.x)),
            t_context.random.fromTo(
                spawnMapRect.position.y, (spawnMapRect.position.y + spawnMapRect.size.y))
        };
    }

    const std::optional<sf::Vector2f>
        NpcManager::findRandomAvailableSpawnPosition(const Context & t_context) const
    {
        // all of this function is in map coordinates

        const sf::FloatRect playerRect{ t_context.player.collisionMapRect() };

        for (std::size_t counter{ 0 }; counter < 1000; ++counter)
        {
            const auto randomPositionOpt{ pickRandomSpawnPosition(t_context) };
            if (!randomPositionOpt.has_value())
            {
                break;
            }

            // all NPCs and the player are the same size so steal the player's size to make this
            sf::FloatRect randomRect({ *randomPositionOpt, playerRect.size });
            randomRect.position -= (playerRect.size * 0.5f); // because sprite origin is centered
            // randomRect.size.y *= 0.3f;                // a third looks good so keep this magic
            util::scaleRectInPlace(randomRect, 1.2f); // this grow seems to help prevent overlap

            // check if random position collides with the player
            if (randomRect.findIntersection(playerRect).has_value())
            {
                continue;
            }

            // ensure the new position is within walk bounds
            const std::vector<sf::FloatRect> & walkBounds{ t_context.level.npcWalkBounds() };
            bool didAllFourCornersFitInAnyWalkBound{ false };
            for (const sf::FloatRect & walkBound : walkBounds)
            {
                const sf::Vector2f topLeft{ randomRect.position };
                const sf::Vector2f topRight{ util::right(randomRect), randomRect.position.y };
                const sf::Vector2f botLeft{ randomRect.position.x, util::bottom(randomRect) };
                const sf::Vector2f botRight{ util::right(randomRect), util::bottom(randomRect) };

                if (walkBound.contains(topLeft) && walkBound.contains(topRight) &&
                    walkBound.contains(botLeft) && walkBound.contains(botRight))
                {
                    didAllFourCornersFitInAnyWalkBound = true;
                    break;
                }
            }

            if (!didAllFourCornersFitInAnyWalkBound)
            {
                continue;
            }

            // check if random position collides with any other NPCs
            if (!doesRectCollideWithAny(randomRect))
            {
                return *randomPositionOpt;
            }
        }

        std::cerr << "NpcManager::findRandomAvailableSpawnPosition() failed to find a free space "
                     "to place an NPC!\n";

        return {};
    }

    bool NpcManager::doesRectCollideWithAny(const sf::FloatRect & t_mapRect) const
    {
        // all of this function is in map coordinates

        for (const Npc & npc : m_npcs)
        {
            if (t_mapRect.findIntersection(npc.collisionMapRect()).has_value())
            {
                return true;
            }
        }

        return false;
    }

    bool NpcManager::doesRectCollideWithAnyExcept(
        const sf::FloatRect & t_mapRect, const Npc & t_npc) const
    {
        // all of this function is in map coordinates

        for (const Npc & npc : m_npcs)
        {
            // check if npc == t_npc (not perfect but close enough)
            if (npc.collisionMapRect() == t_npc.collisionMapRect())
            {
                continue;
            }

            if (t_mapRect.findIntersection(npc.collisionMapRect()).has_value())
            {
                return true;
            }
        }

        return false;
    }

} // namespace thornberry
