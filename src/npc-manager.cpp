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
        , m_drawUpperSprites{}
        , m_drawLowerSprites{}
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

        std::sort(std::begin(m_npcs), std::end(m_npcs), [](const Npc & a, const Npc & b) {
            return (a.getSprites().avatar.getPosition().y < b.getSprites().avatar.getPosition().y);
        });
    }

    void NpcManager::setupDrawOrderVectors(const Context & t_context)
    {
        m_drawUpperSprites.clear();
        m_drawLowerSprites.clear();

        const sf::FloatRect playerRect{ t_context.player.collisionMapRect() };

        for (const Npc & npc : m_npcs)
        {
            if (npc.collisionMapRect().position.y < playerRect.position.y)
            {
                m_drawLowerSprites.emplace_back(npc.getSprites());
            }
            else
            {
                m_drawUpperSprites.emplace_back(npc.getSprites());
            }
        }

        std::sort(
            std::begin(m_drawLowerSprites),
            std::end(m_drawLowerSprites),
            [](const AvatarSprites & a, const AvatarSprites & b) {
                return (a.avatar.getPosition().y < b.avatar.getPosition().y);
            });

        std::sort(
            std::begin(m_drawUpperSprites),
            std::end(m_drawUpperSprites),
            [](const AvatarSprites & a, const AvatarSprites & b) {
                return (a.avatar.getPosition().y < b.avatar.getPosition().y);
            });
    }

    void NpcManager::update(const Context & t_context, const float t_elapsedSec)
    {
        for (Npc & npc : m_npcs)
        {
            npc.update(t_context, t_elapsedSec);
        }

        setupDrawOrderVectors(t_context);
    }

    void NpcManager::drawUpper(
        const sf::Vector2f & t_mapToOffscreenOffset,
        sf::RenderTarget & t_target,
        sf::RenderStates t_states) const
    {
        for (const AvatarSprites & sprites : m_drawUpperSprites)
        {
            sf::Sprite sprite{ sprites.shadow };
            sprite.move(t_mapToOffscreenOffset);
            t_target.draw(sprite, t_states);

            sprite = sprites.avatar;
            sprite.move(t_mapToOffscreenOffset);
            t_target.draw(sprite, t_states);
        }
    }

    void NpcManager::drawLower(
        const sf::Vector2f & t_mapToOffscreenOffset,
        sf::RenderTarget & t_target,
        sf::RenderStates t_states) const
    {
        for (const AvatarSprites & sprites : m_drawLowerSprites)
        {
            sf::Sprite sprite{ sprites.shadow };
            sprite.move(t_mapToOffscreenOffset);
            t_target.draw(sprite, t_states);

            sprite = sprites.avatar;
            sprite.move(t_mapToOffscreenOffset);
            t_target.draw(sprite, t_states);
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

        const sf::FloatRect playerRect{ Avatar::makeAvatarToAvatarCollisionRect(
            t_context.player.collisionMapRect()) };

        // this trying x1000 times was just a guess that is more than ample
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
            util::scaleRectInPlace(randomRect, 1.2f); // this grow seems to help prevent overlap

            // check if random position collides with the player
            if (randomRect.findIntersection(playerRect).has_value())
            {
                continue;
            }

            // ensure the new position is within walk bounds
            if (!t_context.level.isInsideAnyNpcWalkBounds(randomRect))
            {
                continue;
            }

            // check if random position collides with any other NPCs
            if (doesRectCollideWithAny(randomRect))
            {
                continue;
            }

            return *randomPositionOpt;
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
            if (t_mapRect
                    .findIntersection(
                        Avatar::makeAvatarToAvatarCollisionRect(npc.collisionMapRect()))
                    .has_value())
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
            if (&npc == &t_npc)
            {
                continue;
            }

            if (t_mapRect
                    .findIntersection(
                        Avatar::makeAvatarToAvatarCollisionRect(npc.collisionMapRect()))
                    .has_value())
            {
                return true;
            }
        }

        return false;
    }

} // namespace thornberry
