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

        // implement all constructors to make sure we call AvatarImageManager::acquire()
        Avatar(const Avatar & t_otherAvatar);
        Avatar(Avatar & t_otherAvatar);
        Avatar(Avatar && t_otherAvatar);

        // only including this because it won't be generated since move constructor is defined above
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
            makeAvatarToAvatarCollisionRect(const sf::FloatRect & t_rect)
        {
            sf::FloatRect rect{ t_rect };
            rect.size.y *= 0.2f;
            return rect;
        }

        [[nodiscard]] const AvatarSprites & getSprites() const { return m_sprites; }

        void standFacingRandomDirection(const Context & t_context);

      protected:
        void updateBlinking(const Context & t_context, const float t_elapsedSec);
        void updateAnimation(const Context & t_context, const float t_elapsedSec);
        void updateHurtAnimation(const Context & t_context, const float t_elapsedSec);
        void setAnim();
        void updateSprite();
        virtual void updateWalkPosition(const Context & t_context, const float t_elapsedSec) = 0;

        [[nodiscard]] float timeBetweenBlinks(const Context & t_context) const;
        [[nodiscard]] static float timeBetweenFrames(const AvatarAnim t_anim);

        [[nodiscard]] static sf::Keyboard::Scancode
            scanCodeFromDirection(const AvatarDirection t_dir);

        [[nodiscard]] static const std::vector<int>
            animCells(const AvatarAnim t_anim, const AvatarDirection t_direction);

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
