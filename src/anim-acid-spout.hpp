#ifndef ANIM_ACID_SPOUT_HPP_INCLUDED
#define ANIM_ACID_SPOUT_HPP_INCLUDED
//
// anim-acid-spout.hpp
//
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

namespace thornberry
{

    struct Config;
    struct Context;

    //
    enum class AcidSpoutState : unsigned char
    {
        Wait,
        Drip,
        Splat
    };

    //
    struct AcidSpoutAnimation
    {
        AcidSpoutAnimation(
            const sf::FloatRect & t_mapRect,
            const sf::Texture & t_spoutTexture,
            const sf::Texture & t_dropTexture,
            const sf::Texture & t_splatTexture,
            const float t_timeBetweenDropSec,
            const sf::Vector2i & t_spoutCellSize,
            const sf::Vector2i & t_splatCellSize);

        void resetDropSprite();

        AcidSpoutState state;
        sf::FloatRect offscreen_rect;
        sf::Sprite spout_sprite;
        sf::Sprite drop_sprite;
        sf::Sprite splat_sprite;
        float wait_elapsed_sec;
        float spout_elapsed_sec;
        float time_between_drop_sec;
        float splat_elapsed_sec;
        std::size_t spout_frame_index;
        std::size_t splat_frame_index;
        bool is_spout_animating;
        float drop_speed_initial;
        float drop_speed;
        float interact_elapsed_sec;
    };

    //
    class AcidSpoutAnimationManager
    {
      public:
        AcidSpoutAnimationManager();

        void setup(const Config & t_config);
        void postLevelLoadSetup(const Context & t_context);
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void add(const Context & t_context, const sf::FloatRect & t_mapRect);
        void move(const sf::Vector2f & t_move);
        inline void clear() { m_animations.clear(); }

      private:
        void interactWithPlayer(
            const Context & t_context, const sf::FloatRect & t_offscreenRect) const;

      private:
        sf::Texture m_spoutTexture;
        sf::Texture m_dropTexture;
        sf::Texture m_splatTexture;
        sf::Vector2i m_spoutCellSize;
        sf::Vector2i m_splatCellSize;
        std::vector<AcidSpoutAnimation> m_animations;
    };

} // namespace thornberry

#endif // ANIM_ACID_SPOUT_HPP_INCLUDED
