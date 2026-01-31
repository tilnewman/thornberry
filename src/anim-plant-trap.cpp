//
// anim-plant-trap.cpp
//
#include "anim-plant-trap.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "player.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

namespace thornberry
{

    PlantTrapAnimation::PlantTrapAnimation(
        const sf::Texture & t_texture,
        const sf::FloatRect & t_mapRect,
        const sf::Vector2i & m_cellSize)
        : sprite{ t_texture }
        , offscreen_rect{ t_mapRect } // conversion from map to offscreen coordinates happens below
        , state{ PlantTrapState::Ready }
        , elapsed_sec{ 0.0f }
        , frame_index{ 0 }
    {
        sprite.setTextureRect(util::animationCellRect(0, t_texture.getSize(), m_cellSize));
        util::fitAndCenterInside(sprite, t_mapRect);
    }

    //

    PlantTrapAnimationManager::PlantTrapAnimationManager()
        : m_texture{}
        , m_cellSize{ 128, 96 }
        , m_animations{}
    {}

    void PlantTrapAnimationManager::setup(const Config & t_config)
    {
        util::TextureLoader::load(
            m_texture,
            (t_config.media_path / "image" / "animation" / "plant-trap" / "plant-trap.png"),
            true);
    }

    void PlantTrapAnimationManager::postLevelLoadSetup(const Context & t_context)
    {
        move(t_context.level.mapToOffscreenOffset());
    }

    void PlantTrapAnimationManager::move(const sf::Vector2f & t_move)
    {
        for (PlantTrapAnimation & anim : m_animations)
        {
            anim.sprite.move(t_move);
            anim.offscreen_rect.position += t_move;
        }
    }

    void PlantTrapAnimationManager::update(const Context & t_context, const float t_elapsedSec)
    {
        sf::FloatRect playerOffscreenRect{ t_context.player.collisionMapRect() };
        playerOffscreenRect.position += t_context.level.mapToOffscreenOffset();

        const sf::FloatRect mapOffscreenRect{ t_context.level.offscreenRect() };

        for (PlantTrapAnimation & anim : m_animations)
        {
            // only track time and discharge if it's visible
            if (!mapOffscreenRect.findIntersection(anim.offscreen_rect).has_value())
            {
                continue;
            }

            if (PlantTrapState::Delay == anim.state)
            {
                anim.elapsed_sec += t_elapsedSec;
                if (anim.elapsed_sec > 2.0f)
                {
                    anim.elapsed_sec = 0.0f;
                    anim.state       = PlantTrapState::Ready;
                }
            }
            else if (PlantTrapState::Ready == anim.state)
            {
                sf::FloatRect plantOffscreenCollisionRect{ anim.offscreen_rect };

                plantOffscreenCollisionRect.position.y +=
                    (plantOffscreenCollisionRect.size.y * 0.2f);

                plantOffscreenCollisionRect.size.y *= 0.1f;
                util::scaleRectInPlace(plantOffscreenCollisionRect, { 0.3f, 0.5f });

                if (plantOffscreenCollisionRect.findIntersection(playerOffscreenRect).has_value())
                {
                    // TODO actually hurt the player and play sfx
                    t_context.player.startHurtAnimation();

                    anim.state       = PlantTrapState::Snap;
                    anim.frame_index = 0;
                    anim.elapsed_sec = 0.0f;
                }
            }
            else // PlantTrapState::Snap
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
                        anim.state       = PlantTrapState::Delay;
                    }

                    anim.sprite.setTextureRect(
                        util::animationCellRect(anim.frame_index, m_texture.getSize(), m_cellSize));
                }
            }
        }
    }

    void PlantTrapAnimationManager::draw(
        sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const PlantTrapAnimation & anim : m_animations)
        {
            t_target.draw(anim.sprite, t_states);
        }
    }

    void PlantTrapAnimationManager::add(const sf::FloatRect & t_mapRect)
    {
        m_animations.emplace_back(m_texture, t_mapRect, m_cellSize);
    }

} // namespace thornberry
