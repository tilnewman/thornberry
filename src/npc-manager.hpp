#ifndef NPC_MANAGER_HPP_INCLUDED
#define NPC_MANAGER_HPP_INCLUDED
//
// npc-manager.hpp
//
#include "npc.hpp"

#include <vector>

namespace thornberry
{

    struct Context;

    //
    class NpcManager
    {
      public:
        NpcManager();

        void setup(const Context & t_context);
        void update(const Context & t_context, const float t_elapsedSec);

      private:
        std::vector<Npc> m_npcs;
    };

} // namespace thornberry

#endif // NPC_MANAGER_HPP_INCLUDED
