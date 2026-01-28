#ifndef SPARKLE_PARTICLE_HPP_INCLUDED
#define SPARKLE_PARTICLE_HPP_INCLUDED
//
// sparkle-particle.hpp
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
    struct SparkleParticle
    {
        SparkleParticle(
            const Context & t_context,
            const sf::Texture & t_texture,
            const sf::FloatRect & t_offscreenRect,
            const float t_ageLimitSec,
            const float t_rotationSpeed);

        sf::Sprite sprite;
        float elapsed_sec;
        float age_limit_sec;
        float rotation_speed;
        bool is_alive;
    };

    //
    struct SparkleAnimation
    {
        SparkleAnimation(const sf::FloatRect & t_offscreenRect);

        sf::FloatRect offscreen_rect;
        float elpased_sec;
        float time_between_emit;
        std::vector<SparkleParticle> particles;
    };

    //
    class SparkleParticleEffects
    {
      public:
        SparkleParticleEffects();

        void setup(const Config & t_config);
        void postLevelLoadSetup(const Context & t_context);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void update(const Context & t_context, const float t_elapsedSec);
        void add(const Context & t_context, const sf::FloatRect & t_offscreenRect);
        void move(const sf::Vector2f & t_move);
        void clear() { m_animations.clear(); }

      private:
        sf::Texture m_texture;
        std::vector<SparkleAnimation> m_animations;
    };

} // namespace thornberry

#endif // SPARKLE_PARTICLE_HPP_INCLUDED
