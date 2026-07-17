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

#include <set>

namespace thornberry
{

    Player::Player(const AvatarImage t_image)
        : Avatar(t_image)
        , m_walkDirections{}
    {}

    Player::Player(const Player & t_otherPlayer)
        : Avatar(t_otherPlayer)
        , m_walkDirections{ t_otherPlayer.m_walkDirections }
    {}

    Player::Player(Player & t_otherPlayer)
        : Avatar(t_otherPlayer)
        , m_walkDirections{ t_otherPlayer.m_walkDirections }
    {}

    Player::Player(Player && t_otherPlayer)
        : Avatar(std::move(t_otherPlayer))
        , m_walkDirections{ std::move(t_otherPlayer.m_walkDirections) }
    {}

    void Player::operator=(const Player & t_otherPlayer)
    {
        Avatar::operator=(t_otherPlayer);
        m_walkDirections = t_otherPlayer.m_walkDirections;
    }

    void Player::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        // allow the walk animation to stop even if there is a popup window
        if (const auto * keyRelPtr = t_event.getIf<sf::Event::KeyReleased>())
        {
            if ((keyRelPtr->scancode == sf::Keyboard::Scancode::Up) ||
                (keyRelPtr->scancode == sf::Keyboard::Scancode::Down) ||
                (keyRelPtr->scancode == sf::Keyboard::Scancode::Left) ||
                (keyRelPtr->scancode == sf::Keyboard::Scancode::Right))
            {
                m_walkDirections.erase(fromScanCode(keyRelPtr->scancode));
                updateWalkAnimation(t_context);
            }
        }

        // don't allow any other actions if there is a popup window
        if (t_context.popup.isThereAPopup())
        {
            return;
        }

        if (const auto * keyPressedPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if ((keyPressedPtr->scancode == sf::Keyboard::Scancode::Up) ||
                (keyPressedPtr->scancode == sf::Keyboard::Scancode::Down) ||
                (keyPressedPtr->scancode == sf::Keyboard::Scancode::Left) ||
                (keyPressedPtr->scancode == sf::Keyboard::Scancode::Right))
            {
                m_walkDirections.insert(fromScanCode(keyPressedPtr->scancode));
                updateWalkAnimation(t_context);
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

    void Player::updateWalkAnimation(const Context & t_context)
    {
        // remove opposing directions
        if (m_walkDirections.contains(AvatarDirection::Up) &&
            m_walkDirections.contains(AvatarDirection::Down))
        {
            m_walkDirections.erase(AvatarDirection::Up);
            m_walkDirections.erase(AvatarDirection::Down);
        }

        if (m_walkDirections.contains(AvatarDirection::Left) &&
            m_walkDirections.contains(AvatarDirection::Right))
        {
            m_walkDirections.erase(AvatarDirection::Left);
            m_walkDirections.erase(AvatarDirection::Right);
        }

        // after removing opposing directions, stop and bail if specail case where none left
        if (m_walkDirections.empty())
        {
            stopWalking(t_context);
            return;
        }

        // change direction if needed
        if (m_walkDirections.contains(AvatarDirection::Up))
        {
            startWalkingInDirection(AvatarDirection::Up);
        }
        else if (m_walkDirections.contains(AvatarDirection::Down))
        {
            startWalkingInDirection(AvatarDirection::Down);
        }
        else if (m_walkDirections.contains(AvatarDirection::Left))
        {
            startWalkingInDirection(AvatarDirection::Left);
        }
        else if (m_walkDirections.contains(AvatarDirection::Right))
        {
            startWalkingInDirection(AvatarDirection::Right);
        }
    }

    void Player::startWalkingInDirection(const AvatarDirection t_dir)
    {
        m_isAnimating = true;
        m_anim        = AvatarAnim::Walk;
        m_direction   = t_dir;
        setAnim();
    }

    void Player::stopWalking(const Context & t_context)
    {
        m_isAnimating = false;
        m_anim        = AvatarAnim::None;
        setAnim();
        t_context.level.stopWalkSound(t_context);
    }

    void Player::updateWalkPosition(const Context & t_context, const float t_elapsedSec)
    {
        if (m_isAnimating && (m_anim == AvatarAnim::Walk))
        {
            const float dist{ t_context.screen_layout.scaleBasedOnResolution(
                t_context, (t_context.config.avatar_walk_speed * t_elapsedSec)) };

            if (m_walkDirections.contains(AvatarDirection::Up))
            {
                attemptMove(t_context, { 0.0f, -dist });
            }

            if (m_walkDirections.contains(AvatarDirection::Down))
            {
                attemptMove(t_context, { 0.0f, dist });
            }

            if (m_walkDirections.contains(AvatarDirection::Left))
            {
                attemptMove(t_context, { -dist, 0.0f });
            }

            if (m_walkDirections.contains(AvatarDirection::Right))
            {
                attemptMove(t_context, { dist, 0.0f });
            }
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
