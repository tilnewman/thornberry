#ifndef ANIM_METAL_TRAP_HPP_INCLUDED
#define ANIM_METAL_TRAP_HPP_INCLUDED
//
// anim-metal-trap.hpp
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
    enum class MetalTrapState
    {
        Delay,
        Ready,
        Snap
    };

    //
    struct MetalTrapAnimation
    {
        MetalTrapAnimation(
            const sf::Texture & t_texture,
            const sf::FloatRect & t_mapRect,
            const sf::Vector2i & m_cellSize);

        sf::Sprite sprite;
        sf::FloatRect offscreen_rect;
        MetalTrapState state;
        float elapsed_sec;
        std::size_t frame_index;

    };

    //
    class MetalTrapAnimationManager
    {
      public:
        MetalTrapAnimationManager();

        void setup(const Config & t_config);
        void postLevelLoadSetup(const Context & t_context);
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void move(const sf::Vector2f & t_move);
        void add(const sf::FloatRect & t_mapRect);
        inline void clear() { m_animations.clear(); }

      private:
        sf::Texture m_texture;
        sf::Vector2i m_cellSize;
        std::vector<MetalTrapAnimation> m_animations;
    };

} // namespace thornberry

#endif // ANIM_METAL_TRAP_HPP_INCLUDED
