#ifndef NPC_MANAGER_HPP_INCLUDED
#define NPC_MANAGER_HPP_INCLUDED
//
// npc-manager.hpp
//
#include "npc.hpp"

#include <optional>
#include <vector>

namespace thornberry
{

    struct Context;

    //
    class NpcManager
    {
      public:
        NpcManager();

        void postLevelLoadSetup(const Context & t_context);
        void update(const Context & t_context, const float t_elapsedSec);
        void clear() { m_npcs.clear(); }

        void drawUpper(
            const sf::Vector2f & t_mapToOffscreenOffset,
            const sf::FloatRect & t_offscreenDrawRect,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const;

        void drawLower(
            const sf::Vector2f & t_mapToOffscreenOffset,
            const sf::FloatRect & t_offscreenDrawRect,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const;

        [[nodiscard]] bool doesRectCollideWithAny(const sf::FloatRect & t_mapRect) const;

        [[nodiscard]] bool
            doesRectCollideWithAnyExcept(const sf::FloatRect & t_mapRect, const Npc & t_npc) const;

        void setupDrawOrderVectors(const Context & t_context);

      private:
        [[nodiscard]] const std::optional<sf::Vector2f>
            pickRandomSpawnPosition(const Context & t_context) const;

        [[nodiscard]] const std::optional<sf::Vector2f>
            findRandomAvailableSpawnPosition(const Context & t_context) const;

      private:
        std::vector<Npc> m_npcs;

        // these vectors hold copes of the sprites in m_npcs
        std::vector<AvatarSprites> m_drawUpperSprites;
        std::vector<AvatarSprites> m_drawLowerSprites;
    };

} // namespace thornberry

#endif // NPC_MANAGER_HPP_INCLUDED
