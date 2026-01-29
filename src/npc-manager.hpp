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

        void draw(
            const sf::Vector2f & t_mapToOffscreenOffset,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const;

      private:
        const std::optional<sf::Vector2f> pickRandomSpawnPosition(const Context & t_context) const;

        const std::optional<sf::Vector2f>
            findRandomAvailableSpawnPosition(const Context & t_context) const;

      private:
        std::vector<Npc> m_npcs;
    };

} // namespace thornberry

#endif // NPC_MANAGER_HPP_INCLUDED
