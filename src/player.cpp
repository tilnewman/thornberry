//
// player.cpp
//
#include "player.hpp"

#include "context.hpp"
#include "indirect-level.hpp"
#include "music-player.hpp"
#include "npc-manager.hpp"
#include "popup-manager.hpp"
#include "predraw-animations.hpp"
#include "screen-layout.hpp"
#include "sound-player.hpp"

namespace thornberry
{

    Player::Player(const AvatarImage t_image)
        : Avatar(t_image)
    {}

    Player::Player(const Player & t_otherPlayer)
        : Avatar(t_otherPlayer)
    {}

    Player::Player(Player & t_otherPlayer)
        : Avatar(t_otherPlayer)
    {}

    Player::Player(Player && t_otherPlayer)
        : Avatar(std::move(t_otherPlayer))
    {}

    void Player::operator=(const Player & t_otherPlayer) { Avatar::operator=(t_otherPlayer); }

    void Player::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyRelPtr = t_event.getIf<sf::Event::KeyReleased>())
        {
            if (keyRelPtr->scancode == scanCodeFromDirection(m_direction))
            {
                m_isAnimating = false;
                m_anim        = AvatarAnim::None;
                setAnim();
                t_context.level.stopWalkSound(t_context);
            }
        }

        if (t_context.popup.isThereAPopup())
        {
            return;
        }

        if (const auto * keyPressedPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if ((keyPressedPtr->scancode == sf::Keyboard::Scancode::Up) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift))
            {
                m_isAnimating = true;
                m_anim        = AvatarAnim::Walk;
                m_direction   = AvatarDirection::Up;
                setAnim();
            }
            else if (
                (keyPressedPtr->scancode == sf::Keyboard::Scancode::Down) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift))
            {
                m_isAnimating = true;
                m_anim        = AvatarAnim::Walk;
                m_direction   = AvatarDirection::Down;
                setAnim();
            }
            else if (
                (keyPressedPtr->scancode == sf::Keyboard::Scancode::Left) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift))
            {
                m_isAnimating = true;
                m_anim        = AvatarAnim::Walk;
                m_direction   = AvatarDirection::Left;
                setAnim();
            }
            else if (
                (keyPressedPtr->scancode == sf::Keyboard::Scancode::Right) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift))
            {
                m_isAnimating = true;
                m_anim        = AvatarAnim::Walk;
                m_direction   = AvatarDirection::Right;
                setAnim();
            }
            else if (keyPressedPtr->scancode == sf::Keyboard::Scancode::T)
            {
                m_isAnimating = true;
                m_anim        = AvatarAnim::Thank;
                setAnim();
                t_context.level.stopWalkSound(t_context);

                t_context.sfx.play("flute");
                t_context.predraw_anim.music().add(t_context, collisionMapRect());
            }
            else if (keyPressedPtr->scancode == sf::Keyboard::Scancode::D)
            {
                m_isAnimating = true;
                m_anim        = AvatarAnim::Do;
                setAnim();
                t_context.level.stopWalkSound(t_context);
            }
            else if (keyPressedPtr->scancode == sf::Keyboard::Scancode::F)
            {
                m_isAnimating = true;
                m_anim        = AvatarAnim::FistBump;
                setAnim();
                t_context.level.stopWalkSound(t_context);
            }
        }
    }

    void Player::updateWalkPosition(const Context & t_context, const float t_elapsedSec)
    {
        const float walkAmount{ t_context.screen_layout.calScaleBasedOnResolution(
            t_context, (t_context.config.avatar_walk_speed * t_elapsedSec)) };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
        {
            attemptMove(t_context, { 0.0f, -walkAmount });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
        {
            attemptMove(t_context, { 0.0f, walkAmount });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
        {
            attemptMove(t_context, { -walkAmount, 0.0f });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
        {
            attemptMove(t_context, { walkAmount, 0.0f });
        }
    }

    void Player::attemptMove(const Context & t_context, const sf::Vector2f & t_move)
    {
        const MoveResultPack resultPack{ t_context.level.playerMove(
            t_context, collisionMapRect(), t_move) };

        if (resultPack.result == MoveResult::Success)
        {
            Avatar::move(t_move);
        }
        else if (resultPack.npc_opt.has_value())
        {
            m_isAnimating = false;
            m_anim        = AvatarAnim::None;
            setAnim();
            t_context.level.stopWalkSound(t_context);

            resultPack.npc_opt->get().startTalking(t_context, util::center(collisionMapRect()));
        }
    }

} // namespace thornberry
