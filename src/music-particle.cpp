//
// music-particle.cpp
//
#include "music-particle.hpp"

#include "color-range.hpp"
#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "random.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

#include <algorithm>

namespace thornberry
{

    MusicParticle::MusicParticle(
        const Context & t_context,
        const sf::Texture & t_texture,
        const sf::IntRect & t_textureRect,
        const sf::FloatRect & t_offscreenRect,
        const float t_ageLimitSec,
        const float t_speed)
        : sprite{ t_texture }
        , elapsed_sec{ 0.0f }
        , age_limit_sec{ t_ageLimitSec }
        , speed{ t_speed }
        , is_alive{ true }
    {
        sprite.setTextureRect(t_textureRect);
        sprite.setColor(colors::randomVibrant(t_context.random));
        util::setOriginToCenter(sprite);

        const sf::FloatRect spawnRect{ util::scaleRectInPlaceCopy(t_offscreenRect, 0.75f) };
        sprite.setPosition(spawnRect.position);

        sprite.move(
            { t_context.random.fromTo(0.0f, spawnRect.size.x),
              t_context.random.fromTo(0.0f, spawnRect.size.y) });
    }

    MusicAnimation::MusicAnimation(const sf::FloatRect & t_offscreenRect)
        : offscreen_rect{ t_offscreenRect }
        , elapsed_sec{ 0.0f }
        , time_between_emit_sec{ 0.0f }
        , particles{}
    {}

    MusicParticleManager::MusicParticleManager()
        : m_texture{}
        , m_animations{}
    {}

    void MusicParticleManager::setup(const Config & t_config)
    {
        util::TextureLoader::load(
            m_texture, (t_config.media_path / "image" / "particle" / "musical-note.png"));
    }

    void MusicParticleManager::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_states.blendMode = sf::BlendAdd;

        for (const MusicAnimation & anim : m_animations)
        {
            for (const MusicParticle & particle : anim.particles)
            {
                t_target.draw(particle.sprite, t_states);
            }
        }
    }

    void MusicParticleManager::update(const Context & t_context, const float t_elapsedSec)
    {
        for (MusicAnimation & anim : m_animations)
        {
            anim.elapsed_sec += t_elapsedSec;
            if (anim.elapsed_sec > anim.time_between_emit_sec)
            {
                anim.elapsed_sec -= anim.time_between_emit_sec;
                anim.time_between_emit_sec = t_context.random.fromTo(0.1f, 0.3f);

                anim.particles.emplace_back(
                    t_context,
                    m_texture,
                    randomNoteRect(t_context),
                    anim.offscreen_rect,
                    t_context.random.fromTo(1.0f, 2.0f),
                    t_context.random.fromTo(100.0f, 200.0f));
            }

            bool didAnyParticlesDie{ false };
            for (MusicParticle & particle : anim.particles)
            {
                particle.elapsed_sec += t_elapsedSec;
                if (particle.elapsed_sec > particle.age_limit_sec)
                {
                    didAnyParticlesDie = true;
                    particle.is_alive  = false;
                }
                else
                {
                    particle.sprite.move({ 0.0f, -(particle.speed * t_elapsedSec) });
                }
            }

            if (didAnyParticlesDie)
            {
                std::erase_if(anim.particles, [](const MusicParticle & p) { return !p.is_alive; });
            }
        }
    }

    void MusicParticleManager::add(const Context & t_context, const sf::FloatRect & t_mapRect)
    {
        sf::FloatRect offscreenRect{ t_mapRect };
        offscreenRect.position += t_context.level.mapToOffscreenOffset();

        m_animations.emplace_back(offscreenRect);
    }

    const sf::IntRect MusicParticleManager::randomNoteRect(const Context & t_context) const
    {
        const int index{ t_context.random.fromTo(0, 4) };

        // clang-format off
        switch (index)
        {
            case 0:     { return {{   0,   0 }, {  84, 126 }}; }
            case 1:     { return {{  87,   0 }, {  76, 128 }}; }
            case 2:     { return {{ 192,   0 }, {  64, 128 }}; }
            case 3:     { return {{   8, 128 }, { 120, 128 }}; }
            default:    { return {{ 136, 144 }, { 112,  96 }}; }
        }
        // clang-format on
    }

} // namespace thornberry
