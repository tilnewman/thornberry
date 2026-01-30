//
// anim-acid-spout.cpp
//
#include "anim-acid-spout.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "player.hpp"
#include "random.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

namespace thornberry
{

    AcidSpoutAnimation::AcidSpoutAnimation(
        const sf::FloatRect & t_mapRect,
        const sf::Texture & t_spoutTexture,
        const sf::Texture & t_dropTexture,
        const sf::Texture & t_splatTexture,
        const float t_timeBetweenDropSec,
        const sf::Vector2i & t_spoutCellSize,
        const sf::Vector2i & t_splatCellSize)
        : state{ AcidSpoutState::Wait }
        , offscreen_rect{ t_mapRect }
        , spout_sprite{ t_spoutTexture }
        , drop_sprite{ t_dropTexture }
        , splat_sprite{ t_splatTexture }
        , wait_elapsed_sec{ 0.0f }
        , spout_elapsed_sec{ 0.0f }
        , time_between_drop_sec{ t_timeBetweenDropSec }
        , splat_elapsed_sec{ 0.0f }
        , spout_frame_index{ 0 }
        , splat_frame_index{ 0 }
        , is_spout_animating{ false }
        , drop_speed_initial{ 20.0f }
        , drop_speed{ drop_speed_initial }
        , interact_elapsed_sec{ 0.0f }
    {
        // spout sprite
        spout_sprite.setTextureRect(
            util::cellRect(spout_frame_index, t_spoutTexture.getSize(), t_spoutCellSize));

        util::fitAndCenterInside(spout_sprite, t_mapRect);
        spout_sprite.setPosition({ spout_sprite.getPosition().x, t_mapRect.position.y });

        // drop sprite
        util::fitAndCenterInside(drop_sprite, t_mapRect);
        resetDropSprite();

        // splat sprite
        splat_sprite.setTextureRect(
            util::cellRect(splat_frame_index, t_splatTexture.getSize(), t_splatCellSize));

        sf::FloatRect splatSizeRect{ t_mapRect };
        splatSizeRect.position.x -= (splatSizeRect.size.x * 0.5f);
        splatSizeRect.size.x *= 2.0f;
        util::fitAndCenterInside(splat_sprite, splatSizeRect);

        splat_sprite.setPosition(
            { splat_sprite.getPosition().x,
              (util::bottom(splatSizeRect) - splat_sprite.getGlobalBounds().size.y) });
    }

    void AcidSpoutAnimation::resetDropSprite()
    {
        drop_sprite.setPosition({ drop_sprite.getPosition().x, offscreen_rect.position.y });
    }

    //

    AcidSpoutAnimationManager::AcidSpoutAnimationManager()
        : m_spoutTexture{}
        , m_dropTexture{}
        , m_splatTexture{}
        , m_spoutCellSize{ 32, 64 }
        , m_splatCellSize{ 128, 64 }
        , m_animations{}
    {}

    void AcidSpoutAnimationManager::setup(const Config & t_config)
    {
        util::TextureLoader::load(
            m_spoutTexture,
            (t_config.media_path / "image" / "animation" / "acid-spout" / "acid-spout.png"),
            true);

        util::TextureLoader::load(
            m_dropTexture,
            (t_config.media_path / "image" / "animation" / "acid-spout" / "acid-spout-drop.png"),
            true);

        util::TextureLoader::load(
            m_splatTexture,
            (t_config.media_path / "image" / "animation" / "acid-spout" / "acid-spout-splat.png"),
            true);
    }

    void AcidSpoutAnimationManager::postLevelLoadSetup(const Context & t_context)
    {
        move(t_context.level.mapToOffscreenOffset());
    }

    void AcidSpoutAnimationManager::move(const sf::Vector2f & t_move)
    {
        for (AcidSpoutAnimation & anim : m_animations)
        {
            anim.offscreen_rect.position += t_move;
            anim.spout_sprite.move(t_move);
            anim.drop_sprite.move(t_move);
            anim.splat_sprite.move(t_move);
        }
    }

    void AcidSpoutAnimationManager::update(const Context & t_context, const float t_elapsedSec)
    {
        for (AcidSpoutAnimation & anim : m_animations)
        {
            // only track time and drip if it's visible
            if (!t_context.level.offscreenRect().findIntersection(anim.offscreen_rect).has_value())
            {
                continue;
            }

            if (AcidSpoutState::Wait == anim.state)
            {
                anim.wait_elapsed_sec += t_elapsedSec;
                if (anim.wait_elapsed_sec > anim.time_between_drop_sec)
                {
                    anim.wait_elapsed_sec -= anim.time_between_drop_sec;
                    anim.state              = AcidSpoutState::Drip;
                    anim.spout_elapsed_sec  = 0.0f;
                    anim.spout_frame_index  = 0;
                    anim.is_spout_animating = true;
                }
            }
            else if (AcidSpoutState::Drip == anim.state)
            {
                if (anim.is_spout_animating)
                {
                    anim.spout_elapsed_sec += t_elapsedSec;
                    const float timeBetweenSpoutFramesSec{ 0.15f };
                    if (anim.spout_elapsed_sec > timeBetweenSpoutFramesSec)
                    {
                        anim.spout_elapsed_sec -= timeBetweenSpoutFramesSec;

                        if (++anim.spout_frame_index >= 4)
                        {
                            anim.spout_frame_index  = 0;
                            anim.is_spout_animating = false;
                        }

                        anim.spout_sprite.setTextureRect(
                            util::cellRect(
                                anim.spout_frame_index, m_spoutTexture.getSize(), m_spoutCellSize));
                    }
                }

                anim.drop_sprite.move({ 0.0f, (anim.drop_speed * t_elapsedSec) });
                anim.drop_speed += (10.0f * anim.drop_speed * t_elapsedSec);
                if (util::bottom(anim.drop_sprite) > util::bottom(anim.offscreen_rect))
                {
                    anim.state = AcidSpoutState::Splat;
                    anim.resetDropSprite();
                    anim.drop_speed = anim.drop_speed_initial;
                }
                else
                {
                    anim.interact_elapsed_sec += t_elapsedSec;
                    if (anim.interact_elapsed_sec > 0.5f)
                    {
                        anim.interact_elapsed_sec = 0.0f;
                        interactWithPlayer(t_context, anim.offscreen_rect);
                    }
                }
            }
            else if (AcidSpoutState::Splat == anim.state)
            {
                anim.splat_elapsed_sec += t_elapsedSec;
                const float timeBetweenSplatFramesSec{ 0.1f };
                if (anim.splat_elapsed_sec > timeBetweenSplatFramesSec)
                {
                    anim.splat_elapsed_sec -= timeBetweenSplatFramesSec;

                    if (++anim.splat_frame_index >= 7)
                    {
                        anim.splat_frame_index = 0;
                        anim.state             = AcidSpoutState::Wait;
                        anim.wait_elapsed_sec  = 0.0f;
                    }

                    anim.splat_sprite.setTextureRect(
                        util::cellRect(
                            anim.splat_frame_index, m_splatTexture.getSize(), m_splatCellSize));
                }

                anim.interact_elapsed_sec += t_elapsedSec;
                if (anim.interact_elapsed_sec > 0.5f)
                {
                    anim.interact_elapsed_sec = 0.0f;
                    interactWithPlayer(t_context, anim.offscreen_rect);
                }
            }
        }
    }

    void AcidSpoutAnimationManager::draw(
        sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const AcidSpoutAnimation & anim : m_animations)
        {
            if (AcidSpoutState::Drip == anim.state)
            {
                t_target.draw(anim.drop_sprite, t_states);
            }
            else if (AcidSpoutState::Splat == anim.state)
            {
                t_target.draw(anim.splat_sprite, t_states);
            }

            t_target.draw(anim.spout_sprite, t_states);
        }
    }

    void AcidSpoutAnimationManager::add(const Context & t_context, const sf::FloatRect & t_mapRect)
    {
        m_animations.emplace_back(
            t_mapRect,
            m_spoutTexture,
            m_dropTexture,
            m_splatTexture,
            t_context.random.fromTo(2.75f, 4.5f),
            m_spoutCellSize,
            m_splatCellSize);
    }

    void AcidSpoutAnimationManager::interactWithPlayer(
        const Context & t_context, const sf::FloatRect & t_offscreenRect) const
    {
        sf::FloatRect avatarOffscreenRect{ t_context.player.collisionMapRect() };
        avatarOffscreenRect.position += t_context.level.mapToOffscreenOffset();

        sf::FloatRect acidOffscreenRect{ t_offscreenRect };
        acidOffscreenRect.size.y *= 0.4f;

        if (avatarOffscreenRect.findIntersection(acidOffscreenRect).has_value())
        {
            t_context.player.startHurtAnimation();
            // TODO play hurt sfx and actually hurt the player
        }
    }

} // namespace thornberry
