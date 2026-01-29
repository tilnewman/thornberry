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
            const std::size_t npcCount{ 20 };
            m_npcs.reserve(npcCount);

            for (std::size_t counter{ 0 }; counter < npcCount; ++counter)
            {
                const AvatarImage image{ static_cast<AvatarImage>(
                    t_context.random.zeroToOneLessThan(
                        static_cast<std::size_t>(AvatarImage::count))) };

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
            const sf::FloatRect randomRect(
                util::scaleRectInPlaceCopy({ *randomPositionOpt, playerRect.size }, 2.0f));

            // check if random position collides with the player
            if (randomRect.findIntersection(playerRect).has_value())
            {
                continue;
            }

            // check if random position collides with any other NPCs
            bool didAnyNPCsCollide{ false };
            for (const Npc & npc : m_npcs)
            {
                if (randomRect.findIntersection(npc.collisionMapRect()).has_value())
                {
                    didAnyNPCsCollide = true;
                    break;
                }
            }

            if (!didAnyNPCsCollide)
            {
                return *randomPositionOpt;
            }
        }

        std::cerr << "NpcManager::findRandomAvailableSpawnPosition() failed to find a free space "
                     "to place an NPC!\n";

        return {};
    }

} // namespace thornberry
