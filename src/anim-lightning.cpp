//
// anim-lightning.cpp
//
#include "anim-lightning.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "player.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "texture-loader.hpp"

namespace thornberry
{

    LightningAnimation::LightningAnimation(
        const Context &,
        const sf::Texture & t_texture,
        const sf::FloatRect & t_offscreenRect,
        const sf::Vector2i & t_cellSize,
        const float t_timeBetweenDischarge)
        : sprite{ t_texture }
        , elapsed_sec{ 0.0f }
        , state{ LightningState::Wait }
        , offscreen_rect{ t_offscreenRect }
        , frame_index{ 0 }
        , time_between_discharge{ t_timeBetweenDischarge }
    {
        sprite.setTextureRect({ { 0, 0 }, t_cellSize });
        util::scaleAndCenterInside(sprite, t_offscreenRect);
    }

    //

    LightningAnimationManager::LightningAnimationManager()
        : m_texture{}
        , m_animations{}
        , m_cellSize{ 64, 128 }
    {}

    void LightningAnimationManager::setup(const Config & t_config)
    {
        util::TextureLoader::load(
            m_texture,
            (t_config.media_path / "image" / "animation" / "lightning" / "lightning.png"),
            true);
    }

    void LightningAnimationManager::postLevelLoadSetup(const Context & t_context)
    {
        move(t_context.level.mapToOffscreenOffset());
    }

    void LightningAnimationManager::draw(
        sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const LightningAnimation & anim : m_animations)
        {
            t_target.draw(anim.sprite, t_states);
        }
    }

    void LightningAnimationManager::update(const Context & t_context, const float t_elapsedSec)
    {
        for (LightningAnimation & anim : m_animations)
        {
            // only track time and discharge if it's visible
            if (!t_context.level.offscreenRect().findIntersection(anim.offscreen_rect).has_value())
            {
                continue;
            }

            anim.elapsed_sec += t_elapsedSec;

            if (LightningState::Wait == anim.state)
            {
                if (anim.elapsed_sec > anim.time_between_discharge)
                {
                    anim.elapsed_sec = 0.0f;
                    anim.state       = LightningState::Discharge;
                    anim.frame_index = 0;
                    anim.sprite.setTextureRect({ { 0, 0 }, m_cellSize });
                    t_context.sfx.play("electricity");
                    interactWithPlayer(t_context, anim.offscreen_rect);
                }
            }
            else
            {
                const float timeBetweenFramesSec{ 0.125f };
                if (anim.elapsed_sec > timeBetweenFramesSec)
                {
                    anim.elapsed_sec -= timeBetweenFramesSec;

                    if (++anim.frame_index >= 8)
                    {
                        anim.elapsed_sec = 0.0f;
                        anim.state       = LightningState::Wait;
                        anim.frame_index = 0;
                    }

                    anim.sprite.setTextureRect(
                        util::cellRect(anim.frame_index, m_texture.getSize(), m_cellSize));
                }
            }
        }
    }

    void LightningAnimationManager::add(
        const Context & t_context, const sf::FloatRect & t_offscreenRect)
    {
        m_animations.emplace_back(
            t_context, m_texture, t_offscreenRect, m_cellSize, t_context.random.fromTo(2.5f, 3.5f));
    }

    void LightningAnimationManager::move(const sf::Vector2f & t_move)
    {
        for (LightningAnimation & anim : m_animations)
        {
            anim.offscreen_rect.position += t_move;
            anim.sprite.move(t_move);
        }
    }

    void LightningAnimationManager::interactWithPlayer(
        const Context & t_context, const sf::FloatRect & t_offscreenRect)
    {
        sf::FloatRect avatarOffscreenRect{ t_context.player.collisionMapRect() };
        avatarOffscreenRect.position += t_context.level.mapToOffscreenOffset();

        sf::FloatRect lightningOffscreenRect{ t_offscreenRect };
        lightningOffscreenRect.size.y *= 0.4f;

        if (avatarOffscreenRect.findIntersection(lightningOffscreenRect).has_value())
        {
            t_context.player.startHurtAnimation();
            // TODO play hurt sfx and actually hurt the player
        }
    }

} // namespace thornberry
