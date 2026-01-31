//
// anim-metal-trap.cpp
//
#include "anim-metal-trap.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "player.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

namespace thornberry
{

    MetalTrapAnimation::MetalTrapAnimation(
        const sf::Texture & t_texture,
        const sf::FloatRect & t_mapRect,
        const sf::Vector2i & m_cellSize)
        : sprite{ t_texture }
        , offscreen_rect{ t_mapRect } // conversion from map to offscreen coordinates happens below
        , state{ MetalTrapState::Ready }
        , elapsed_sec{ 0.0f }
        , frame_index{ 0 }
    {
        sprite.setTextureRect(util::animationCellRect(0, t_texture.getSize(), m_cellSize));
        util::fitAndCenterInside(sprite, t_mapRect);
    }

    //

    MetalTrapAnimationManager::MetalTrapAnimationManager()
        : m_texture{}
        , m_cellSize{ 128, 64 }
        , m_animations{}
    {}

    void MetalTrapAnimationManager::setup(const Config & t_config)
    {
        util::TextureLoader::load(
            m_texture,
            (t_config.media_path / "image" / "animation" / "metal-trap" / "metal-trap.png"),
            true);
    }

    void MetalTrapAnimationManager::postLevelLoadSetup(const Context & t_context)
    {
        move(t_context.level.mapToOffscreenOffset());
    }

    void MetalTrapAnimationManager::move(const sf::Vector2f & t_move)
    {
        for (MetalTrapAnimation & anim : m_animations)
        {
            anim.sprite.move(t_move);
            anim.offscreen_rect.position += t_move;
        }
    }

    void MetalTrapAnimationManager::update(const Context & t_context, const float t_elapsedSec)
    {
        sf::FloatRect playerOffscreenRect{ t_context.player.collisionMapRect() };
        playerOffscreenRect.position += t_context.level.mapToOffscreenOffset();

        const sf::FloatRect mapOffscreenRect{ t_context.level.offscreenRect() };

        for (MetalTrapAnimation & anim : m_animations)
        {
            // only track time and discharge if it's visible
            if (!mapOffscreenRect.findIntersection(anim.offscreen_rect).has_value())
            {
                continue;
            }

            if (MetalTrapState::Delay == anim.state)
            {
                anim.elapsed_sec += t_elapsedSec;
                if (anim.elapsed_sec > 2.0f)
                {
                    anim.elapsed_sec = 0.0f;
                    anim.state       = MetalTrapState::Ready;
                }
            }
            else if (MetalTrapState::Ready == anim.state)
            {
                sf::FloatRect metalOffscreenCollisionRect{ anim.offscreen_rect };

                metalOffscreenCollisionRect.position.y +=
                    (metalOffscreenCollisionRect.size.y * 0.2f);

                metalOffscreenCollisionRect.size.y *= 0.1f;
                util::scaleRectInPlace(metalOffscreenCollisionRect, { 0.3f, 0.5f });

                if (metalOffscreenCollisionRect.findIntersection(playerOffscreenRect).has_value())
                {
                    // TODO actually hurt the player and play sfx
                    t_context.player.startHurtAnimation();

                    anim.state       = MetalTrapState::Snap;
                    anim.frame_index = 0;
                    anim.elapsed_sec = 0.0f;
                }
            }
            else // MetalTrapState::Snap
            {
                anim.elapsed_sec += t_elapsedSec;
                const float timeBetweenFramesSec{ 0.1f };
                if (anim.elapsed_sec > timeBetweenFramesSec)
                {
                    anim.elapsed_sec -= timeBetweenFramesSec;

                    if (++anim.frame_index >= 6)
                    {
                        anim.frame_index = 0;
                        anim.elapsed_sec = 0.0f;
                        anim.state       = MetalTrapState::Delay;
                    }

                    anim.sprite.setTextureRect(
                        util::animationCellRect(anim.frame_index, m_texture.getSize(), m_cellSize));
                }
            }
        }
    }

    void MetalTrapAnimationManager::draw(
        sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const MetalTrapAnimation & anim : m_animations)
        {
            t_target.draw(anim.sprite, t_states);
        }
    }

    void MetalTrapAnimationManager::add(const sf::FloatRect & t_mapRect)
    {
        m_animations.emplace_back(m_texture, t_mapRect, m_cellSize);
    }

} // namespace thornberry
