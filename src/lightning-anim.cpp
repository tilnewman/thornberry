//
// lightning-anim.cpp
//
#include "lightning-anim.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "texture-loader.hpp"

namespace thornberry
{

    LightningAnimation::LightningAnimation(
        const Context &,
        const sf::Texture & t_texture,
        const sf::FloatRect & t_offscreenRect)
        : sprite{ t_texture }
        , elapsed_sec{ 0.0f }
        , state{ LightningState::Wait }
        , offscreen_rect{ t_offscreenRect }
    {
        // TODO this is temp for testing purposes, show some lightning to test size
        sprite.setTextureRect({ { 64, 128 }, { 64, 128 } });

        util::scaleAndCenterInside(sprite, t_offscreenRect);
    }

    //

    LightningAnimationManager::LightningAnimationManager()
        : m_texture{}
        , m_animations{}
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
            // TODO?
            // Check if anim.offscreen_rect intersects with the offscreen texture
            // to prevent drawing particles that are not visible.

            t_target.draw(anim.sprite, t_states);
        }
    }

    void LightningAnimationManager::update(const Context &, const float)
    {

    }

    void LightningAnimationManager::add(
        const Context & t_context, const sf::FloatRect & t_offscreenRect)
    {
        m_animations.emplace_back(t_context, m_texture, t_offscreenRect);
    }

    void LightningAnimationManager::move(const sf::Vector2f & t_move)
    {
        for (LightningAnimation & anim : m_animations)
        {
            anim.offscreen_rect.position += t_move;
            anim.sprite.move(t_move);
        }
    }

} // namespace thornberry
