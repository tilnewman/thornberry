//
// anim-acid-spout.cpp
//
#include "anim-acid-spout.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
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
        const sf::Vector2i & t_spoutCellSize)
        : state{ AcidSpoutState::Wait }
        , map_rect{ t_mapRect }
        , spout_sprite{ t_spoutTexture }
        , drop_sprite{ t_dropTexture }
        , splat_sprite{ t_splatTexture }
        , wait_elapsed_sec{ 0.0f }
        , spout_elapsed_sec{ 0.0f }
        , time_between_drop_sec{ t_timeBetweenDropSec }
        , splat_elapsed_sec{ 0.0f }
        , spout_frame_index{ 0 }
        , is_spout_animating{ false }
    {
        spout_sprite.setTextureRect(
            util::cellRect(spout_frame_index, t_spoutTexture.getSize(), t_spoutCellSize));

        util::fitAndCenterInside(spout_sprite, t_mapRect);
        spout_sprite.setPosition({ spout_sprite.getPosition().x, t_mapRect.position.y });
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
            anim.map_rect.position += t_move;
            anim.spout_sprite.move(t_move);
            anim.drop_sprite.move(t_move);
            anim.splat_sprite.move(t_move);
        }
    }

    void AcidSpoutAnimationManager::update(const Context &, const float t_elapsedSec)
    {
        for (AcidSpoutAnimation & anim : m_animations)
        {
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

                            // TODO remove after testing
                            anim.state = AcidSpoutState::Wait;
                        }

                        anim.spout_sprite.setTextureRect(
                            util::cellRect(
                                anim.spout_frame_index, m_spoutTexture.getSize(), m_spoutCellSize));
                    }
                }

                // move the drop sprite
                // TODO
            }
            else if (AcidSpoutState::Splat == anim.state)
            {
                // TODO
                anim.wait_elapsed_sec = 0.0f;
            }
        }
    }

    void AcidSpoutAnimationManager::draw(
        sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const AcidSpoutAnimation & anim : m_animations)
        {
            t_target.draw(anim.spout_sprite, t_states);

            if (AcidSpoutState::Drip == anim.state)
            {
                t_target.draw(anim.drop_sprite, t_states);
            }
            else if (AcidSpoutState::Splat == anim.state)
            {
                t_target.draw(anim.splat_sprite, t_states);
            }
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
            m_spoutCellSize);
    }

} // namespace thornberry
