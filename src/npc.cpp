//
// npc.cpp
//
#include "npc.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "npc-manager.hpp"
#include "player.hpp"
#include "popup-manager.hpp"
#include "random.hpp"
#include "screen-layout.hpp"

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
        , m_walkDirections{}
        , m_isTalkingWithPlayer{ false }
    {}

    Npc::Npc(const Npc & t_otherNpc)
        : Avatar(t_otherNpc)
        , m_action{ t_otherNpc.m_action }
        , m_actionElpasedSec{ t_otherNpc.m_actionElpasedSec }
        , m_timeUntilActionChangeSec{ t_otherNpc.m_timeUntilActionChangeSec }
        , m_walkDirections{ t_otherNpc.m_walkDirections }
        , m_isTalkingWithPlayer{ t_otherNpc.m_isTalkingWithPlayer }
    {}

    Npc::Npc(Npc & t_otherNpc)
        : Avatar(t_otherNpc)
        , m_action{ t_otherNpc.m_action }
        , m_actionElpasedSec{ t_otherNpc.m_actionElpasedSec }
        , m_timeUntilActionChangeSec{ t_otherNpc.m_timeUntilActionChangeSec }
        , m_walkDirections{ t_otherNpc.m_walkDirections }
        , m_isTalkingWithPlayer{ t_otherNpc.m_isTalkingWithPlayer }
    {}

    Npc::Npc(Npc && t_otherNpc)
        : Avatar(std::move(t_otherNpc))
        , m_action{ t_otherNpc.m_action }
        , m_actionElpasedSec{ t_otherNpc.m_actionElpasedSec }
        , m_timeUntilActionChangeSec{ t_otherNpc.m_timeUntilActionChangeSec }
        , m_walkDirections{ t_otherNpc.m_walkDirections }
        , m_isTalkingWithPlayer{ t_otherNpc.m_isTalkingWithPlayer }
    {}

    void Npc::operator=(const Npc & t_otherNpc)
    {
        Avatar::operator=(t_otherNpc);
        m_action                   = t_otherNpc.m_action;
        m_actionElpasedSec         = t_otherNpc.m_actionElpasedSec;
        m_timeUntilActionChangeSec = t_otherNpc.m_timeUntilActionChangeSec;
        m_walkDirections           = t_otherNpc.m_walkDirections;
        m_isTalkingWithPlayer      = t_otherNpc.m_isTalkingWithPlayer;
    }

    void Npc::update(const Context & t_context, const float t_elapsedSec)
    {
        Avatar::update(t_context, t_elapsedSec);
        updateAction(t_context, t_elapsedSec);
    }

    void Npc::updateAction(const Context & t_context, const float t_elapsedSec)
    {
        if (m_isTalkingWithPlayer)
        {
            return;
        }

        m_actionElpasedSec += t_elapsedSec;
        if (m_actionElpasedSec < m_timeUntilActionChangeSec)
        {
            return;
        }

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
            const auto walkTargetOpt{ pickRandomWalkTarget(t_context) };
            if (walkTargetOpt.has_value())
            {
                // only walk for a short amount of time
                m_timeUntilActionChangeSec = t_context.random.fromTo(0.3f, 2.0f);

                const sf::Vector2f npcPosition{ util::center(collisionMapRect()) };
                m_walkDirections.clear();
                if (walkTargetOpt->x < npcPosition.x)
                {
                    m_walkDirections.push_back(AvatarDirection::Left);
                }
                else if (walkTargetOpt->x > npcPosition.x)
                {
                    m_walkDirections.push_back(AvatarDirection::Right);
                }

                if (walkTargetOpt->y < npcPosition.y)
                {
                    m_walkDirections.push_back(AvatarDirection::Up);
                }
                else if (walkTargetOpt->y < npcPosition.y)
                {
                    m_walkDirections.push_back(AvatarDirection::Down);
                }

                if (m_walkDirections.empty())
                {
                    m_walkDirections.push_back(AvatarDirection::Left);
                }

                t_context.random.shuffle(m_walkDirections);

                m_isAnimating = true;
                m_anim        = AvatarAnim::Walk;
                m_direction   = m_walkDirections.front();
                setAnim();
            }
            else
            {
                // if pickRandomTarget() fails, just face a new direction
                standFacingRandomDirection(t_context);
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

    void Npc::updateWalkPosition(const Context & t_context, const float t_elapsedSec)
    {
        const float walkAmount{ t_context.screen_layout.calScaleBasedOnResolution(
            t_context, (t_context.config.avatar_walk_speed * t_elapsedSec)) };

        const auto isWalkingInDirection = [&](const AvatarDirection dir) {
            return (
                std::find(std::begin(m_walkDirections), std::end(m_walkDirections), dir) !=
                std::end(m_walkDirections));
        };

        if (isWalkingInDirection(AvatarDirection::Up))
        {
            const sf::Vector2f move{ 0.0f, -walkAmount };
            if (isMovedPositionValid(t_context, move))
            {
                Avatar::move(move);
            }
        }

        if (isWalkingInDirection(AvatarDirection::Down))
        {
            const sf::Vector2f move{ 0.0f, walkAmount };
            if (isMovedPositionValid(t_context, move))
            {
                Avatar::move(move);
            }
        }

        if (isWalkingInDirection(AvatarDirection::Left))
        {
            const sf::Vector2f move{ -walkAmount, 0.0f };
            if (isMovedPositionValid(t_context, move))
            {
                Avatar::move(move);
            }
        }

        if (isWalkingInDirection(AvatarDirection::Right))
        {
            const sf::Vector2f move{ walkAmount, 0.0f };
            if (isMovedPositionValid(t_context, move))
            {
                Avatar::move(move);
            }
        }
    }

    bool Npc::isMovedPositionValid(const Context & t_context, const sf::Vector2f & t_move) const
    {
        // everything in this function is in map coordinates

        sf::FloatRect movedRect{ Avatar::makeAvatarToAvatarCollisionRect(collisionMapRect()) };
        movedRect.position += t_move;

        // check for collision with player
        const sf::FloatRect playerRect{ Avatar::makeAvatarToAvatarCollisionRect(
            t_context.player.collisionMapRect()) };

        if (movedRect.findIntersection(playerRect).has_value())
        {
            return false;
        }

        // ensure the new position is within walk bounds
        if (!t_context.level.isInsideAnyNpcWalkBounds(movedRect))
        {
            return false;
        }

        // check for collision with other NPCs
        return !t_context.npc.doesRectCollideWithAnyExcept(movedRect, *this);
    }

    bool Npc::startTalking(const Context & t_context, const sf::Vector2f & t_playerPosition)
    {
        if (m_isTalkingWithPlayer)
        {
            return false;
        }

        m_isTalkingWithPlayer = true;
        Avatar::standFacingPosition(t_playerPosition);

        t_context.popup.add(
            t_context,
            TextWindowSpec{ randomGreeting(t_context), TextWindowBackground::PaperSmall, m_image });

        return true;
    }

    const std::string Npc::randomGreeting(const Context& t_context) const
    { 
        std::string str;
        str.reserve(32);

        if (t_context.random.boolean())
        {
            if (t_context.random.zeroTo(2) == 0)
            {
                str += "Oh. ";
            }

            // clang-format off
            switch (t_context.random.zeroTo(3))
            {
                case 0: { str += "Hi"; break; }
                case 1: { str += "Hiya"; break; }
                case 2: { str += "Hello"; break; }
                default: { str += "Howdy"; break; }
            }
            // clang-format on

            if (t_context.random.zeroTo(3) == 0)
            {
                str += " there";
            }

            if (t_context.random.boolean())
            {
                str += '.';
            }
            else
            {
                str += '!';
            }
        }
        else
        {
            // clang-format off
            switch (t_context.random.zeroTo(6))
            {
                case 0: { str += "Greetings."; break; }
                case 1: { str += "Greetings!"; break; }
                case 2: { str += "Salutations."; break; }
                case 3: { str += "Salutations!"; break; }
                case 4: { str += "Welcome to Thornberry."; break; }
                case 5: { str += "I'm listening."; break; }
                default: { str += "Shh. I'm thinking."; break; }
            }
            // clang-format on
        }

        return str;
    }

} // namespace thornberry
