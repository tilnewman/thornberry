#ifndef SMOKE_PARTICLE_HPP_INCLUDED
#define SMOKE_PARTICLE_HPP_INCLUDED
//
// smoke-particle.hpp
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
    struct SmokeParticle
    {
        SmokeParticle(
            const Context & t_context,
            const sf::Texture & t_texture,
            const sf::Vector2f & t_position);

        sf::Sprite sprite;
        float elapsed_sec;
        bool is_alive;
    };

    //
    struct SmokeAnimation
    {
        SmokeAnimation(const sf::FloatRect & t_offscreenRect, const float t_timeBetwenEmitSec);

        float elapsed_sec;
        float time_between_emit_sec;
        sf::FloatRect offscreen_rect{};
        std::vector<SmokeParticle> particles;
    };

    //
    class SmokeParticleEffects
    {
      public:
        SmokeParticleEffects();

        void setup(const Config & t_config);
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void add(const Context & t_context, const sf::FloatRect & t_offscreenRect);
        void move(const sf::Vector2f & t_move);

      private:
        float randomTimeBetweenEmit(const Context & t_context) const;

      private:
        sf::Texture m_texture;
        std::vector<SmokeAnimation> m_animations;
    };

} // namespace thornberry

#endif // SMOKE_PARTICLE_HPP_INCLUDED
