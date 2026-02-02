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
    enum class AvatarDirection
    {
        Up,
        Down,
        Left,
        Right
    };

    //
    enum class AvatarAnim
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

        sf::Sprite avatar;
        sf::Sprite shadow;
    };

    //
    class Avatar
    {
      public:
        Avatar() = delete;
        Avatar(const AvatarImage t_image);

        // only including this because it won't be generated since move constructor is user defined
        Avatar(const Avatar & t_otherAvatar);

        // only including this because it won't be generated since move constructor is user defined
        Avatar(Avatar & t_otherAvatar);

        // This might get used by a container like std::vector and the default constructed one won't
        // increment the AvatarImageManager ref_count.
        Avatar(Avatar && t_otherAvatar);

        // only including this because it won't be generated since move constructor is user defined
        void operator=(const Avatar & t_otherAvatar);

        // only including this because it won't be generated since move constructor is user defined
        void operator=(Avatar & t_otherAvatar);

        // only including this because it won't be generated since move constructor is user defined
        void operator=(Avatar && t_otherAvatar);

        Avatar(const Avatar && t_otherAvatar)         = delete;
        void operator=(const Avatar && t_otherAvatar) = delete;

        virtual ~Avatar();

        void startHurtAnimation();
        void setup(const Context & t_context);
        void setPosition(const sf::Vector2f & t_position);

        virtual void update(const Context & t_context, const float t_elapsedSec);

        void draw(
            const sf::Vector2f & t_positionOffset,
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

        [[nodiscard]] const AvatarSprites getSprites() const
        {
            return { m_sprite, m_shadowSprite };
        }

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
        sf::Sprite m_sprite;       // position is in map coordinates
        sf::Sprite m_shadowSprite; // position is in map coordinates
        float m_hurtEnableTimerSec;
        bool m_isHurtAnimating;
        float m_hurtColorCycleTimeSec;
        bool m_isHurtColorWhite;
    };

} // namespace thornberry

#endif // AVATAR_HPP_INCLUDED
