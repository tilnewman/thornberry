//
// player.cpp
//
#include "player.hpp"

#include "context.hpp"
#include "indirect-level.hpp"
#include "music-particle.hpp"
#include "music-player.hpp"
#include "sound-player.hpp"

namespace thornberry
{

    Player::Player(const AvatarImage t_image)
        : Avatar(t_image)
    {}

    Player::Player(Player && t_otherPlayer)
        : Avatar(std::move(t_otherPlayer))
    {}

    void Player::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
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
                t_context.musical_note.add(t_context, collisionMapRect());
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
        else if (const auto * keyRelPtr = t_event.getIf<sf::Event::KeyReleased>())
        {
            if (keyRelPtr->scancode == scanCodeFromDirection(m_direction))
            {
                m_isAnimating = false;
                m_anim        = AvatarAnim::None;
                setAnim();
                t_context.level.stopWalkSound(t_context);
            }
        }
    }

} // namespace thornberry
