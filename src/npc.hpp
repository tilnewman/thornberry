#ifndef NPC_HPP_INCLUDED
#define NPC_HPP_INCLUDED
//
// npc.hpp
//
#include "avatar.hpp"

namespace thornberry
{
    struct Context;

    //
    class Npc : public Avatar
    {
      public:
        Npc();

        void standFacingRandomDirection(const Context & t_context);
    };

} // namespace thornberry

#endif // NPC_HPP_INCLUDED
