//
// npc-manager.cpp
//
#include "npc-manager.hpp"

#include "avatar-image.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
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

        const std::vector<sf::FloatRect> & walkBounds{ t_context.level.npcWalkBounds() };
        if (walkBounds.empty())
        {
            return;
        }

        const auto pickRandomSpawnPosition = [&]() {
            const sf::FloatRect spawnMapRect{ t_context.random.from(walkBounds) };

            const sf::Vector2f spawnMapPosition{
                t_context.random.fromTo(
                    spawnMapRect.position.x, (spawnMapRect.position.x + spawnMapRect.size.x)),
                t_context.random.fromTo(
                    spawnMapRect.position.y, (spawnMapRect.position.y + spawnMapRect.size.y))
            };

            return spawnMapPosition;
        };

        const std::string levelName{ t_context.level.name() };
        if (levelName == "house.tmj")
        {
            Npc & npc{ m_npcs.emplace_back() };
            npc.setup(t_context, AvatarImage::leather_corporal2_dark);
            npc.setPosition(pickRandomSpawnPosition());
            npc.standFacingRandomDirection(t_context);
        }
        else if (levelName == "thornberry.tmj")
        {
            const std::size_t npcCount{ 20 };
            m_npcs.reserve(npcCount);

            for (std::size_t counter{ 0 }; counter < npcCount; ++counter)
            {
                Npc & npc{ m_npcs.emplace_back() };

                npc.setup(
                    t_context,
                    static_cast<AvatarImage>(t_context.random.zeroToOneLessThan(
                        static_cast<std::size_t>(AvatarImage::count))));

                npc.setPosition(pickRandomSpawnPosition());
                npc.standFacingRandomDirection(t_context);
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

} // namespace thornberry
