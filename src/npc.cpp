//
// npc.cpp
//
#include "npc.hpp"

#include "context.hpp"
#include "indirect-level.hpp"
#include "random.hpp"

#include <SFML/Graphics/Rect.hpp>

#include <iostream>
#include <vector>

namespace thornberry
{

    Npc::Npc(const AvatarImage t_image)
        : Avatar(t_image)
        , m_action{ NpcAction::Wait }
        , m_actionElpasedSec{ 0.0f }
        , m_timeUntilActionChangeSec{ 0.0f }
    {}

    Npc::Npc(Npc && t_otherNpc)
        : Avatar(std::move(t_otherNpc))
        , m_action{ t_otherNpc.m_action }
        , m_actionElpasedSec{ t_otherNpc.m_actionElpasedSec }
        , m_timeUntilActionChangeSec{ t_otherNpc.m_timeUntilActionChangeSec }
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

    void Npc::update(const Context & t_context, const float t_elapsedSec)
    {
        Avatar::update(t_context, t_elapsedSec);

        m_actionElpasedSec += t_elapsedSec;
        if (m_actionElpasedSec > m_timeUntilActionChangeSec)
        {
            m_actionElpasedSec -= m_timeUntilActionChangeSec;
            m_timeUntilActionChangeSec = t_context.random.fromTo(3.0f, 7.0f);

            m_action = t_context.random.from(
                { NpcAction::Wait, NpcAction::Walk, NpcAction::Thank, NpcAction::Turn });

            if (NpcAction::Wait == m_action)
            {
                standFacingRandomDirection(t_context);
            }
            else if (NpcAction::Turn == m_action)
            {
                standFacingRandomDirection(t_context);
            }
            else if (NpcAction::Thank == m_action)
            {
                m_isAnimating = true;
                m_anim        = AvatarAnim::Thank;
                setAnim();
            }
            else // Walk
            {
                // TODO
                standFacingRandomDirection(t_context);

                //const auto walkTargetOpt{ pickRandomWalkTarget(t_context) };
                //if (!walkTargetOpt.has_value())
                //{
                //    // if pickRandomTarget() fails, just face a new direction
                //    standFacingRandomDirection(t_context);
                //    return;
                //}
            }
        }
    }

    const std::optional<sf::Vector2f> Npc::pickRandomWalkTarget(const Context & t_context) const
    {
        // all these walk bounds are in map coordinates
        const std::vector<sf::FloatRect> & walkBounds{ t_context.level.npcWalkBounds() };

        std::vector<sf::FloatRect> intersectingWalkBounds;
        intersectingWalkBounds.reserve(8);

        const sf::FloatRect collMapRect{ collisionMapRect() };

        for (const sf::FloatRect & walkBound : walkBounds)
        {
            if (walkBound.findIntersection(collMapRect).has_value())
            {
                intersectingWalkBounds.emplace_back(walkBound);
            }
        }

        if (intersectingWalkBounds.empty())
        {
            std::cerr << "Error: Npc::pickRandomWalkTarget() found no walkbounds to pick a target "
                         "from!\n";

            return {};
        }

        const sf::FloatRect targetRect{ t_context.random.from(intersectingWalkBounds) };

        return sf::Vector2f{ (targetRect.position.x + t_context.random.zeroTo(targetRect.size.x)),
                             (targetRect.position.y + t_context.random.zeroTo(targetRect.size.y)) };
    }

} // namespace thornberry
