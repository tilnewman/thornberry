//
// anim-layer-base.cpp
//
#include "anim-layer-base.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "random.hpp"
#include "texture-loader.hpp"

#include <iostream>

namespace thornberry
{

    AnimLayerBase::AnimLayerBase(
        const std::string & t_name,
        const sf::FloatRect & t_mapRect,
        const std::size_t t_frameCount,
        const sf::Vector2i & t_cellSize,
        const float t_timeBetweenFramesSec,
        const std::filesystem::path & t_texturePath,
        const TextureSetting t_textureSetting)
        : m_name{ t_name }
        , m_offscreenRect{ t_mapRect } // see postLoadSetup() for conversion from map to offscreen
        , m_texture{}
        , m_sprite{ m_texture }
        , m_frameIndex{ 0 }
        , m_frameCount{ t_frameCount }
        , m_elapsedSec{ 0.0f }
        , m_timeBetweenFramesSec{ t_timeBetweenFramesSec }
        , m_cellSize{ t_cellSize }
        , m_texturePath{ t_texturePath }
        , m_textureSetting{ t_textureSetting }
    {}

    void AnimLayerBase::move(const sf::Vector2f & t_move)
    {
        m_offscreenRect.position += t_move;
        m_sprite.move(t_move);
    }

    void AnimLayerBase::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_sprite, t_states);
    }

    void AnimLayerBase::update(const Context &, const float t_elapsedSec)
    {
        m_elapsedSec += t_elapsedSec;
        if (m_elapsedSec > m_timeBetweenFramesSec)
        {
            m_elapsedSec -= m_timeBetweenFramesSec;

            if (++m_frameIndex >= m_frameCount)
            {
                m_frameIndex = 0;
            }

            m_sprite.setTextureRect(util::cellRect(m_frameIndex, m_texture.getSize(), m_cellSize));
        }
    }

    void AnimLayerBase::postLevelLoadSetup(const Context & t_context)
    {
        m_offscreenRect.position += t_context.level.mapToOffscreenOffset();

        util::TextureLoader::load(m_texture, m_texturePath);
        m_texture.setSmooth((m_textureSetting == TextureSetting::Smooth) ? true : false);

        m_sprite.setTexture(m_texture);
        m_sprite.setTextureRect({ { 0, 0 }, m_cellSize });
        util::scaleAndCenterInside(m_sprite, m_offscreenRect);

        m_frameIndex = t_context.random.zeroToOneLessThan(m_frameCount);
    }

    void AnimLayerBase::dumpInfo() const { std::cout << '\t' << m_name << '\n'; }

} // namespace thornberry
