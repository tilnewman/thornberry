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
    class Avatar
    {
      public:
        Avatar();

        [[nodiscard]] inline AvatarImage image() const { return m_image; }

        void setup(const Context & t_context);
        void setPosition(const sf::Vector2f & t_position);
        void update(const Context & t_context, const float t_elapsedSec);
        void handleEvent(const Context & t_context, const sf::Event & t_event);

        void draw(
            const sf::Vector2f & t_positionOffset,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const;

      private:
        void updateBlinking(const Context & t_context, const float t_elapsedSec);
        void updateWalkPosition(const Context & t_context, const float t_elapsedSec);
        void updateAnimation(const Context & t_context, const float t_elapsedSec);
        void setAnim();
        void updateSprite();

        [[nodiscard]] static float timeBetweenFrames(const AvatarAnim t_anim);
        [[nodiscard]] float timeBetweenBlinks(const Context & t_context) const;
        [[nodiscard]] const sf::FloatRect collisionRect() const;

        [[nodiscard]] static sf::Keyboard::Scancode
            scanCodeFromDirection(const AvatarDirection t_dir);

        [[nodiscard]] static const std::vector<int>
            animCells(const AvatarAnim t_anim, const AvatarDirection t_direction);

      private:
        AvatarImage m_image;
        AvatarAnim m_anim;
        AvatarDirection m_direction;
        bool m_isAnimating;
        std::vector<int> m_animCells;
        std::size_t m_animIndex;
        float m_elapsedSec;
        float m_blinkElapsedSec;
        float m_timeUntilBlinkSec;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Texture m_shadowTexture;
        sf::Sprite m_shadowSprite;
    };

} // namespace thornberry

#endif // AVATAR_HPP_INCLUDED
