#ifndef MUSIC_PARTICLE_HPP_INLCUDED
#define MUSIC_PARTICLE_HPP_INLCUDED
//
// music-particle.hpp
//
#include <SFML/Graphics/Color.hpp>
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
    struct MusicParticle
    {
        MusicParticle(
            const Context & t_context,
            const sf::Texture & t_texture,
            const sf::IntRect & t_textureRect,
            const sf::FloatRect & t_offscreenRect,
            const float t_ageLimitSec,
            const float t_speed);

        sf::Sprite sprite;
        float elapsed_sec;
        float age_limit_sec;
        float speed;
        bool is_alive;
    };

    //
    struct MusicAnimation
    {
        MusicAnimation(const sf::FloatRect & t_offscreenRect);

        sf::FloatRect offscreen_rect;
        float emit_elapsed_sec;
        float time_between_emit_sec;
        float age_elapsed_sec;
        std::vector<MusicParticle> particles;
        bool is_alive;
    };

    //
    class MusicParticleManager
    {
      public:
        MusicParticleManager();

        void setup(const Config & t_config);
        void postLevelLoadSetup(const Context &) {}
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void update(const Context & t_context, const float t_elapsedSec);
        void add(const Context & t_context, const sf::FloatRect & t_mapRect);
        void move(const sf::Vector2f & t_move);
        inline void clear() { m_animations.clear(); }

      private:
        const sf::IntRect randomNoteRect(const Context & t_context) const;

      private:
        sf::Texture m_texture;
        std::vector<MusicAnimation> m_animations;
    };

} // namespace thornberry

#endif // MUSIC_PARTICLE_HPP_INLCUDED
