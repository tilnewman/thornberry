//
// npc.cpp
//
#include "npc.hpp"

#include "context.hpp"
#include "random.hpp"

namespace thornberry
{

    Npc::Npc() {}

    void Npc::standFacingRandomDirection(const Context & t_context)
    {
        const AvatarDirection direction{ t_context.random.from(
            { AvatarDirection::Up,
              AvatarDirection::Down,
              AvatarDirection::Left,
              AvatarDirection::Right}) };

        m_isAnimating = false;
        m_anim        = AvatarAnim::Walk;
        m_direction   = direction;
        setAnim();
    }

} // namespace thornberry
