//
// indirect-tile-layer.cpp
//
#include "indirect-tile-layer.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "map-textures.hpp"
#include "sfml-util.hpp"

#include <iostream>

namespace thornberry
{

    IndirectTileLayer::IndirectTileLayer(
        const Context & t_context, const TileImage t_image, const std::vector<int> & t_indexes)
        : m_image{ t_image }
        , m_textureGID{ 0 }
        , m_textureTileCount{}
        , m_indexes{ t_indexes }
        , m_verts{}
    {
        MapTextureManager::instance().acquire(t_context, m_image);

        const TileTexture & tileTexture{ MapTextureManager::instance().get(m_image) };
        m_textureGID       = tileTexture.gid;
        m_textureTileCount = (tileTexture.size / t_context.level.textureTileSize());

        const sf::Vector2i mapTileCount{ t_context.level.mapTileCount() };

        const std::size_t totalTileCount{ static_cast<std::size_t>(mapTileCount.x) *
                                          static_cast<std::size_t>(mapTileCount.y) };

        M_CHECK(
            (totalTileCount == m_indexes.size()),
            "index_count=" << m_indexes.size() << " does not equal tile_count=" << totalTileCount);

        // TODO make this guess exact
        m_verts.reserve((t_indexes.size() / 4_st) * util::verts_per_quad);
    }

    IndirectTileLayer::~IndirectTileLayer() { MapTextureManager::instance().release(m_image); }

    void IndirectTileLayer::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        if (!m_verts.empty())
        {
            t_states.texture = &MapTextureManager::instance().get(m_image).texture;
            t_target.draw(m_verts.data(), m_verts.size(), sf::PrimitiveType::Triangles, t_states);
            t_states.texture = nullptr;
        }
    }

    void IndirectTileLayer::dumpInfo() const
    {
        std::cout << "\tIndirectTileLayer Quads:  " << m_image << ", possible=" << m_indexes.size()
                  << ", actual=" << (m_verts.size() / util::verts_per_quad) << '\n';
    }

    void IndirectTileLayer::appendVerts(
        const sf::IntRect & t_mapTileRange,
        const sf::Vector2i & t_mapTileCount,
        const sf::Vector2i & t_textureTileSize,
        const sf::Vector2f & t_screenTileSize)
    {
        m_verts.clear();

        std::size_t mapTileIndex{ 0 };
        for (int y{ 0 }; y < t_mapTileCount.y; ++y)
        {
            for (int x{ 0 }; x < t_mapTileCount.x; ++x)
            {
                const int mapTileValue{ m_indexes.at(mapTileIndex++) };
                if (mapTileValue == 0)
                {
                    continue; // zero means no image at this location
                }

                if ((x < t_mapTileRange.position.x) || (x >= util::right(t_mapTileRange)) ||
                    (y < t_mapTileRange.position.y) || (y >= util::bottom(t_mapTileRange)))
                {
                    continue; // only draw tiles in range
                }

                const int textureTileIndex{ mapTileValue - m_textureGID };

                const int texturePosX{ (textureTileIndex % m_textureTileCount.x) *
                                       t_textureTileSize.x };

                const int texturePosY{ (textureTileIndex / m_textureTileCount.x) *
                                       t_textureTileSize.y };

                const sf::IntRect textureRect{ { texturePosX, texturePosY }, t_textureTileSize };

                const float posX{ static_cast<float>(x - t_mapTileRange.position.x) *
                                  t_screenTileSize.x };

                const float posY{ static_cast<float>(y - t_mapTileRange.position.y) *
                                  t_screenTileSize.y };

                const sf::Vector2f screenPos{ sf::Vector2f(posX, posY) };
                const sf::FloatRect screenRect{ screenPos, t_screenTileSize };

                util::appendTriangleVerts(screenRect, textureRect, m_verts);
            }
        }
    }

} // namespace thornberry
