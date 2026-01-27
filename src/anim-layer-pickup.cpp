//
// anim-layer-pickup.cpp
//
#include "anim-layer-pickup.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "pickup-image-manager.hpp"
#include "random.hpp"
#include "sfml-defaults.hpp"

#include <iostream>

namespace thornberry
{

    AnimLayerPickup::AnimLayerPickup(const Pickup t_pickup, const sf::FloatRect & t_mapRect)
        : m_pickup{ t_pickup }
        , m_offscreenRect{ t_mapRect }
        , m_sprite{ util::SfmlDefaults::instance().texture() }
        , m_frameIndex{ 0 }
        , m_frameCount{ 10 }
        , m_elapsedSec{ 0.0f }
        , m_timeBetweenFramesSec{ 0.125f }
        , m_cellSize{ 32, 32 }
    {}

    void AnimLayerPickup::postLevelLoadSetup(const Context & t_context)
    {
        m_offscreenRect.position += t_context.level.mapToOffscreenOffset();

        const sf::Texture & texture{ t_context.pickup_image.get(m_pickup) };

        m_sprite.setTexture(texture);
        m_sprite.setTextureRect({ { 0, 0 }, m_cellSize });
        util::scaleAndCenterInside(m_sprite, m_offscreenRect);

        m_frameIndex = t_context.random.zeroToOneLessThan(m_frameCount);
    }

    void AnimLayerPickup::dumpInfo() const
    {
        std::cout << "\tAnimLayerPickup " << toString(m_pickup) << "\n";
    }

    void AnimLayerPickup::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_sprite, t_states);
    }

    void AnimLayerPickup::move(const sf::Vector2f & t_move)
    {
        m_offscreenRect.position += t_move;
        m_sprite.move(t_move);
    }

    void AnimLayerPickup::update(const Context &, const float t_elapsedSec)
    {
        m_elapsedSec += t_elapsedSec;
        if (m_elapsedSec > m_timeBetweenFramesSec)
        {
            m_elapsedSec -= m_timeBetweenFramesSec;

            if (++m_frameIndex >= m_frameCount)
            {
                m_frameIndex = 0;
            }

            m_sprite.setTextureRect(util::cellRect(m_frameIndex, { 320u, 32u }, m_cellSize));
        }
    }

} // namespace thornberry
