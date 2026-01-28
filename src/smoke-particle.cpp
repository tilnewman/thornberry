//
// smoke-particle.cpp
//
#include "smoke-particle.hpp"

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

    SmokeParticle::SmokeParticle(
        const Context & t_context,
        const sf::Texture & t_texture,
        const sf::FloatRect & t_offscreenRect,
        const float t_rotationSpeed,
        const float t_ageLimitSec,
        const float t_speed)
        : sprite{ t_texture }
        , speed{ t_speed }
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
        sprite.setRotation(sf::degrees(t_context.random.fromTo(0.0f, 360.0f)));
        const float scale{ t_context.screen_layout.calScaleBasedOnResolution(t_context, 0.4f) };
        sprite.setScale({ scale, scale });

        sf::FloatRect posRect{ util::scaleRectInPlaceCopy(t_offscreenRect, 0.5f) };
        posRect.position.y -= (posRect.size.y * 0.5f);
        sprite.setPosition(posRect.position);

        sprite.move(
            { t_context.random.fromTo(0.0f, posRect.size.x),
              t_context.random.fromTo(0.0f, posRect.size.y) });
    }

    //

    SmokeAnimation::SmokeAnimation(
        const sf::FloatRect & t_offscreenRect, const float t_timeBetwenEmitSec)
        : elapsed_sec{ 0.0f }
        , time_between_emit_sec{ t_timeBetwenEmitSec }
        , offscreen_rect{ t_offscreenRect }
        , particles{}
    {}

    //

    SmokeParticleEffects::SmokeParticleEffects()
        : m_texture{}
        , m_animations{}
    {}

    void SmokeParticleEffects::setup(const Config & t_config)
    {
        util::TextureLoader::load(
            m_texture, (t_config.media_path / "image" / "particle" / "smoke.png"));
    }

    void SmokeParticleEffects::update(const Context & t_context, const float t_elapsedSec)
    {
        for (SmokeAnimation & anim : m_animations)
        {
            anim.elapsed_sec += t_elapsedSec;
            if (anim.elapsed_sec > anim.time_between_emit_sec)
            {
                anim.elapsed_sec -= anim.time_between_emit_sec;
                anim.time_between_emit_sec = t_context.random.fromTo(0.05f, 0.15f);

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

                    const float ageLimitSec{ t_context.random.fromTo(0.75f, 1.5f) };
                    const float speed{ t_context.random.fromTo(50.0f, 100.0f) };

                    anim.particles.emplace_back(
                        t_context,
                        m_texture,
                        anim.offscreen_rect,
                        rotationSpeed,
                        ageLimitSec,
                        speed);
                }
            }

            bool didAnyParticlesDie{ false };
            for (SmokeParticle & particle : anim.particles)
            {
                particle.elapsed_sec += t_elapsedSec;
                if (particle.elapsed_sec > particle.age_limit_sec)
                {
                    particle.is_alive  = false;
                    didAnyParticlesDie = true;
                }
                else
                {
                    particle.sprite.rotate(sf::degrees(particle.rotation_speed * t_elapsedSec));
                    particle.sprite.move({ 0.0f, -(particle.speed * t_elapsedSec) });

                    const float scaleMax{ t_context.screen_layout.calScaleBasedOnResolution(
                        t_context, 0.4f) };

                    const float scaleMin{ 0.2f };

                    const float scale{ util::map(
                        particle.elapsed_sec, 0.0f, particle.age_limit_sec, scaleMax, scaleMin) };

                    particle.sprite.setScale({ scale, scale });

                    const std::uint8_t alpha{ static_cast<std::uint8_t>(
                        util::map(particle.elapsed_sec, 0.0f, particle.age_limit_sec, 64, 0)) };

                    sf::Color color{ sf::Color::White };
                    color.a = alpha;
                    particle.sprite.setColor(color);
                }
            }

            if (didAnyParticlesDie)
            {
                std::erase_if(anim.particles, [](const SmokeParticle & p) { return !p.is_alive; });
            }
        }
    }

    void SmokeParticleEffects::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const SmokeAnimation & anim : m_animations)
        {
            for (const SmokeParticle & particle : anim.particles)
            {
                t_target.draw(particle.sprite, t_states);
            }
        }
    }

    void SmokeParticleEffects::add(const Context &, const sf::FloatRect & t_offscreenRect)
    {
        m_animations.emplace_back(SmokeAnimation(t_offscreenRect, 0.0f));
    }

    void SmokeParticleEffects::move(const sf::Vector2f & t_move)
    {
        for (SmokeAnimation & anim : m_animations)
        {
            anim.offscreen_rect.position += t_move;

            for (SmokeParticle & particle : anim.particles)
            {
                particle.sprite.move(t_move);
            }
        }
    }

    std::size_t SmokeParticleEffects::particleCount() const
    {
        std::size_t count{ 0 };

        for (const SmokeAnimation & anim : m_animations)
        {
            count += anim.particles.size();
        }

        return count;
    }

} // namespace thornberry
