//
// smoke-particle.cpp
//
#include "smoke-particle.hpp"

#include "config.hpp"
#include "context.hpp"
#include "random.hpp"
#include "screen-layout.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

#include <algorithm>

namespace thornberry
{

    SmokeParticle::SmokeParticle(
        const Context & t_context, const sf::Texture & t_texture, const sf::Vector2f & t_position)
        : sprite{ t_texture }
        , elapsed_sec{ 0.0f }
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
        sprite.setPosition(t_position);
        sprite.setRotation(sf::degrees(t_context.random.fromTo(0.0f, 360.0f)));
        const float scale{ t_context.screen_layout.calScaleBasedOnResolution(t_context, 1.0f) };
        sprite.setScale({ scale, scale });

        // TODO set randomized scale
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
            m_texture, (t_config.media_path / "image" / "particle" / "smoke.png"), true);
    }

    void SmokeParticleEffects::update(const Context & t_context, const float t_elapsedSec)
    {
        for (SmokeAnimation & anim : m_animations)
        {
            anim.elapsed_sec += t_elapsedSec;
            if (anim.elapsed_sec > anim.time_between_emit_sec)
            {
                anim.elapsed_sec -= anim.time_between_emit_sec;
                anim.time_between_emit_sec = randomTimeBetweenEmit(t_context);

                anim.particles.emplace_back(
                    t_context, m_texture, util::center(anim.offscreen_rect));
            }

            bool didAnyParticlesDie{ false };
            for (SmokeParticle & particle : anim.particles)
            {
                particle.elapsed_sec += t_elapsedSec;
                if (particle.elapsed_sec > 0.8f)
                {
                    particle.is_alive  = false;
                    didAnyParticlesDie = true;
                }
                else
                {
                    particle.sprite.rotate(sf::degrees(20.0f * t_elapsedSec));
                    particle.sprite.move({ 0.0f, -(50.0f * t_elapsedSec) });
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

    void SmokeParticleEffects::add(const Context & t_context, const sf::FloatRect & t_offscreenRect)
    {
        m_animations.emplace_back(
            SmokeAnimation(t_offscreenRect, randomTimeBetweenEmit(t_context)));
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

    float SmokeParticleEffects::randomTimeBetweenEmit(const Context & t_context) const
    {
        return t_context.random.fromTo(0.2f, 0.5f);
    }

} // namespace thornberry
