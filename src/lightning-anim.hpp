#ifndef LIGHTNING_ANIM_HPP_INLCUDED
#define LIGHTNING_ANIM_HPP_INLCUDED
//
// lightning-anim.hpp
//
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
    enum class LightningState
    {
        Wait,
        Discharge
    };

    //
    struct LightningAnimation
    {
        LightningAnimation(
            const Context & t_context,
            const sf::Texture & t_texture,
            const sf::FloatRect & t_offscreenRect,
            const sf::Vector2i & t_cellSize);

        sf::Sprite sprite;
        float elapsed_sec;
        LightningState state;
        sf::FloatRect offscreen_rect;
        std::size_t frame_index;
    };

    //
    class LightningAnimationManager
    {
      public:
        LightningAnimationManager();

        void setup(const Config & t_config);
        void postLevelLoadSetup(const Context & t_context);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void update(const Context & t_context, const float t_elapsedSec);
        void add(const Context & t_context, const sf::FloatRect & t_offscreenRect);
        inline void clear() { m_animations.clear(); }
        void move(const sf::Vector2f & t_move);

      private:
        void interactWithPlayer(const Context & t_context, const sf::FloatRect & t_offscreenRect);

      private:
        sf::Texture m_texture;
        std::vector<LightningAnimation> m_animations;
        sf::Vector2i m_cellSize;
    };

} // namespace thornberry

#endif // LIGHTNING_ANIM_HPP_INLCUDED
