//
// npc.cpp
//
#include "npc.hpp"

#include "context.hpp"
#include "random.hpp"

namespace thornberry
{

    Npc::Npc(const AvatarImage t_image)
        : Avatar(t_image)
    {}

    Npc::Npc(const Npc && t_otherNpc)
        : Avatar(std::move(t_otherNpc))
    {}

    void Npc::standFacingRandomDirection(const Context & t_context)
    {
        const AvatarDirection direction{ t_context.random.from(
            { AvatarDirection::Up,
              AvatarDirection::Down,
              AvatarDirection::Left,
              AvatarDirection::Right }) };

        m_isAnimating = false;
        m_anim        = AvatarAnim::Walk;
        m_direction   = direction;
        setAnim();
        m_anim = AvatarAnim::None;
    }

} // namespace thornberry
