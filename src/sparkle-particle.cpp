//
// sparkle-particle.cpp
//
#include "sparkle-particle.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "random.hpp"
#include "screen-layout.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

#include <algorithm>

namespace thornberry
{

    SparkleParticle::SparkleParticle(
        const Context & t_context,
        const sf::Texture & t_texture,
        const sf::FloatRect & t_offscreenRect,
        const float t_ageLimitSec,
        const float t_rotationSpeed)
        : sprite{ t_texture }
        , elapsed_sec{ 0.0f }
        , age_limit_sec{ t_ageLimitSec }
        , rotation_speed{ t_rotationSpeed }
        , is_alive{ true }
    {
        const int randomImage{ t_context.random.fromTo(1, 4) };
        if (randomImage == 1)
        {
            sprite.setTextureRect({ { 0, 0 }, { 64, 64 } });
        }
        else if (randomImage == 2)
        {
            sprite.setTextureRect({ { 64, 0 }, { 64, 64 } });
        }
        else if (randomImage == 3)
        {
            sprite.setTextureRect({ { 0, 64 }, { 64, 64 } });
        }
        else
        {
            sprite.setTextureRect({ { 64, 64 }, { 64, 64 } });
        }

        util::setOriginToCenter(sprite);

        sf::Color color{ sf::Color::Yellow };
        color.b = static_cast<std::uint8_t>(t_context.random.fromTo(0u, 255u));
        sprite.setColor(color);

        sprite.setRotation(sf::degrees(t_context.random.fromTo(0.0f, 360.0f)));

        sprite.setPosition(t_offscreenRect.position);

        sprite.move(
            { t_context.random.fromTo(0.0f, t_offscreenRect.size.x),
              t_context.random.fromTo(0.0f, t_offscreenRect.size.y) });

        sprite.scale({ 0.0f, 0.0f });
    }

    //

    SparkleAnimation::SparkleAnimation(const sf::FloatRect & t_offscreenRect)
        : offscreen_rect{ t_offscreenRect }
        , elpased_sec{ 0.0f }
        , time_between_emit{ 0.0f }
    {}

    //

    SparkleParticleEffects::SparkleParticleEffects()
        : m_texture{}
        , m_animations{}
    {}

    void SparkleParticleEffects::setup(const Config & t_config)
    {
        util::TextureLoader::load(
            m_texture, (t_config.media_path / "image" / "particle" / "star.png"));
    }

    void SparkleParticleEffects::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_states.blendMode = sf::BlendAdd;

        for (const SparkleAnimation & anim : m_animations)
        {
            for (const SparkleParticle & particle : anim.particles)
            {
                t_target.draw(particle.sprite, t_states);
            }
        }
    }

    void SparkleParticleEffects::update(const Context & t_context, const float t_elapsedSec)
    {
        for (SparkleAnimation & anim : m_animations)
        {
            anim.elpased_sec += t_elapsedSec;
            if (anim.elpased_sec > anim.time_between_emit)
            {
                anim.elpased_sec -= anim.time_between_emit;
                anim.time_between_emit = t_context.random.fromTo(0.2f, 0.8f);

                // only emit particles if they will be visible
                if (t_context.level.offscreenRect()
                        .findIntersection(anim.offscreen_rect)
                        .has_value())
                {
                    float rotationSpeed{ t_context.random.fromTo(50.0f, 100.0f) };
                    if (t_context.random.boolean())
                    {
                        rotationSpeed *= -1.0f;
                    }

                    const float ageLimitSec{ t_context.random.fromTo(0.75f, 1.25f) };

                    anim.particles.emplace_back(
                        t_context, m_texture, anim.offscreen_rect, ageLimitSec, rotationSpeed);
                }
            }

            bool didAnyParticlesDie{ false };
            for (SparkleParticle & particle : anim.particles)
            {
                particle.elapsed_sec += t_elapsedSec;
                if (particle.elapsed_sec < particle.age_limit_sec)
                {
                    particle.sprite.rotate(sf::degrees(particle.rotation_speed * t_elapsedSec));

                    const float scaleMax{ t_context.screen_layout.calScaleBasedOnResolution(
                        t_context, 0.5f) };

                    const float ageLimitHalfSec{ particle.age_limit_sec * 0.5f };
                    if (particle.elapsed_sec < ageLimitHalfSec)
                    {
                        // growing
                        const float scale{ util::map(
                            particle.elapsed_sec, 0.0f, ageLimitHalfSec, 0.0f, scaleMax) };

                        particle.sprite.setScale({ scale, scale });
                    }
                    else
                    {
                        // shrinking
                        const float scale{ util::map(
                            (particle.elapsed_sec - ageLimitHalfSec),
                            0.0f,
                            ageLimitHalfSec,
                            scaleMax,
                            0.0f) };

                        particle.sprite.setScale({ scale, scale });
                    }
                }
                else
                {
                    particle.is_alive  = false;
                    didAnyParticlesDie = true;
                }
            }

            if (didAnyParticlesDie)
            {
                std::erase_if(
                    anim.particles, [](const SparkleParticle & p) { return !p.is_alive; });
            }
        }
    }

    void SparkleParticleEffects::add(const Context &, const sf::FloatRect & t_offscreenRect)
    {
        m_animations.emplace_back(t_offscreenRect);
    }

    void SparkleParticleEffects::postLevelLoadSetup(const Context & t_context)
    {
        for (SparkleAnimation & anim : m_animations)
        {
            anim.offscreen_rect.position += t_context.level.mapToOffscreenOffset();
        }
    }

    void SparkleParticleEffects::move(const sf::Vector2f & t_move)
    {
        for (SparkleAnimation & anim : m_animations)
        {
            anim.offscreen_rect.position += t_move;

            for (SparkleParticle & particle : anim.particles)
            {
                particle.sprite.move(t_move);
            }
        }
    }

} // namespace thornberry
