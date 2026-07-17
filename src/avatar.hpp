#ifndef AVATAR_HPP_INCLUDED
#define AVATAR_HPP_INCLUDED
//
// avatar.hpp
//
#include "avatar-image.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <vector>

namespace thornberry
{

    struct Context;

    //
    enum class AvatarDirection : unsigned char
    {
        Up,
        Down,
        Left,
        Right
    };

    [[nodiscard]] constexpr sf::Keyboard::Scancode toScanCode(const AvatarDirection t_dir) noexcept
    {
        // clang-format off
        switch (t_dir)
        {
            case AvatarDirection::Up:       return sf::Keyboard::Scancode ::Up;
            case AvatarDirection::Down:     return sf::Keyboard::Scancode::Down;
            case AvatarDirection::Left:     return sf::Keyboard::Scancode::Left;
            case AvatarDirection::Right:
            default:                        return sf::Keyboard::Scancode::Right;
        }
        // clang-format on}
    }

    //
    enum class AvatarAnim : unsigned char
    {
        None,
        Walk,
        Do,
        Thank,
        FistBump,
        Blink
    };

    // each animation has its own speed because they have different number of frames
    [[nodiscard]] constexpr float toTimeBetweenFrames(const AvatarAnim t_anim) noexcept
    {
        // clang-format off
        switch (t_anim)
        {
            case AvatarAnim::Walk:      return 0.1f;
            case AvatarAnim::Do:        return 0.17f;
            case AvatarAnim::Thank:     return 3.0f;
            case AvatarAnim::FistBump:  return 0.75f;

            case AvatarAnim::None:
            case AvatarAnim::Blink:
            default:                    return 0.15f;
        }
        // clang-format on
    }

    // animation frames, in order
    [[nodiscard]] inline const std::vector<int>
        animAndDirectionToCells(const AvatarAnim t_anim, const AvatarDirection t_direction)
    {
        // clang-format off
        switch (t_anim)
        {
            case AvatarAnim::None:
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 1 };
                    case AvatarDirection::Down: return { 17 };
                    case AvatarDirection::Left: return { 9 };
                    case AvatarDirection::Right:
                    default:                    return { 25 };
                }
            }
            case AvatarAnim::Walk:
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 1, 2, 3, 4, 6, 7, 8 };
                    case AvatarDirection::Down: return { 17, 18, 19, 20, 22, 23, 24 };
                    case AvatarDirection::Left: return { 9, 10, 11, 12, 13, 14, 15, 16, 41 };
                    case AvatarDirection::Right:
                    default:                    return { 25, 26, 27, 28, 29, 30, 31, 32, 57 };
                }
            }
            case AvatarAnim::Do:
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 34, 35, 36, 37, 38 };
                    case AvatarDirection::Down: return { 50, 51, 52, 53, 54 };
                    case AvatarDirection::Left: return { 42, 43, 44, 45, 46 };
                    case AvatarDirection::Right:
                    default:                    return { 58, 59, 60, 61, 62 };
                }
            }
            case AvatarAnim::Thank: 
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 40 };
                    case AvatarDirection::Down: return { 56 };
                    case AvatarDirection::Left: return { 48 };
                    case AvatarDirection::Right:
                    default:                    return { 64 };
                }
            }
            case AvatarAnim::FistBump:
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 39 };
                    case AvatarDirection::Down: return { 55 };
                    case AvatarDirection::Left: return { 47 };
                    case AvatarDirection::Right:
                    default:                    return { 63 };
                }
            }
            case AvatarAnim::Blink:
            default: 
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 1 };
                    case AvatarDirection::Down: return { 33 };
                    case AvatarDirection::Left: return { 5 };
                    case AvatarDirection::Right:
                    default:                    return { 21 };
                }
            }
        }
        // clang-format on
    }

    //
    struct AvatarSprites
    {
        AvatarSprites(const sf::Sprite t_avatarSprite, const sf::Sprite t_shadowSprite)
            : avatar{ t_avatarSprite }
            , shadow{ t_shadowSprite }
        {}

        AvatarSprites(const sf::Texture & t_avatarTexture, const sf::Texture & t_shadowTexture)
            : avatar{ t_avatarTexture }
            , shadow{ t_shadowTexture }
        {}

        sf::Sprite avatar;
        sf::Sprite shadow;
    };

    //
    class Avatar
    {
      public:
        explicit Avatar(const AvatarImage t_image);

        // implement all constructors to make sure we call AvatarImageManager::acquire() once
        Avatar(const Avatar & t_otherAvatar);
        Avatar(Avatar & t_otherAvatar);
        Avatar(Avatar && t_otherAvatar);

        // only included because it won't be generated since move constructor is defined above
        void operator=(const Avatar & t_otherAvatar);

        virtual ~Avatar();

        void startHurtAnimation();
        void setup(const Context & t_context);
        void setPosition(const sf::Vector2f & t_position);
        void move(const sf::Vector2f & t_move);

        virtual void update(const Context & t_context, const float t_elapsedSec);

        void draw(
            const sf::Vector2f & t_mapToOffscreenOffset,
            const sf::FloatRect & t_offscreenDrawRect,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const;

        [[nodiscard]] const sf::FloatRect collisionMapRect() const;
        [[nodiscard]] inline AvatarImage image() const noexcept { return m_image; }

        [[nodiscard]] static inline const sf::FloatRect
            makeAvatarToAvatarCollisionRect(const sf::FloatRect & t_rect) noexcept
        {
            sf::FloatRect rect{ t_rect };
            rect.size.y *= 0.2f;
            return rect;
        }

        [[nodiscard]] static inline const sf::FloatRect
            makeFootstepRect(const sf::FloatRect & t_avatarRect) noexcept
        {
            sf::FloatRect footstepRect{ t_avatarRect };

            const float adjustment{ footstepRect.size.y * 0.85f };
            footstepRect.size.y -= adjustment;
            footstepRect.position.y += adjustment;

            return footstepRect;
        }

        [[nodiscard]] const AvatarSprites & getSprites() const noexcept { return m_sprites; }

        void standFacingRandomDirection(const Context & t_context);
        void standFacingPosition(const sf::Vector2f & t_mapPosition);

      protected:
        void standFacing(const AvatarDirection t_direction);
        void updateBlinking(const Context & t_context, const float t_elapsedSec);
        void updateAnimation(const Context & t_context, const float t_elapsedSec);
        void updateHurtAnimation(const Context & t_context, const float t_elapsedSec);
        void setAnim();
        void updateSprite();
        virtual void updateWalkPosition(const Context & t_context, const float t_elapsedSec) = 0;

        [[nodiscard]] float timeBetweenBlinks(const Context & t_context) const;

      protected:
        AvatarImage m_image;
        AvatarAnim m_anim;
        AvatarDirection m_direction;
        bool m_isAnimating;
        std::vector<int> m_animCells;
        std::size_t m_animIndex;
        float m_elapsedSec;
        float m_blinkElapsedSec;
        float m_timeUntilBlinkSec;
        AvatarSprites m_sprites;
        float m_hurtEnableTimerSec;
        bool m_isHurtAnimating;
        float m_hurtColorCycleTimeSec;
        bool m_isHurtColorWhite;
    };

} // namespace thornberry

#endif // AVATAR_HPP_INCLUDED
