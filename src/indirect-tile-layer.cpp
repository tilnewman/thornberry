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
        , m_rawIndexes{ t_indexes }
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
            (totalTileCount == m_rawIndexes.size()),
            "raw_index_count=" << m_rawIndexes.size()
                               << " does not equal tile_count=" << totalTileCount);

        // just guesses based on what I know is in the averag map
        const std::size_t reserveCount{ (t_indexes.size() / 4_st) * util::verts_per_quad };
        m_verts.reserve(reserveCount);
        m_mapTiles.reserve(reserveCount);

        createReducedMapTiles(t_context.level.mapTileCount(), t_context.level.textureTileSize());
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
        std::cout << "\tIndirectTileLayer Quads for " << m_image << ": raw=" << m_rawIndexes.size()
                  << ", reduced=" << m_mapTiles.size()
                  << ", actual=" << (m_verts.size() / util::verts_per_quad) << '\n';
    }

    void IndirectTileLayer::appendVerts(
        const sf::IntRect & t_mapTileRange,
        const sf::Vector2i &, // t_mapTileCount
        const sf::Vector2i &, // t_textureTileSize
        const sf::Vector2f & t_screenTileSize)
    {
        appendVertsReduced(t_mapTileRange, t_screenTileSize);
    }

    void IndirectTileLayer::appendVertsRaw(
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
                const int mapTileValue{ m_rawIndexes.at(mapTileIndex++) };
                if (mapTileValue == 0)
                {
                    continue; // zero means no image at this location
                }

                if ((x < t_mapTileRange.position.x) || (x >= util::right(t_mapTileRange)) ||
                    (y < t_mapTileRange.position.y) || (y >= util::bottom(t_mapTileRange)))
                {
                    continue; // only append verts for tiles in range
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

                const sf::FloatRect screenRect{ sf::Vector2f(posX, posY), t_screenTileSize };

                util::appendTriangleVerts(screenRect, textureRect, m_verts);
            }
        }
    }

    void IndirectTileLayer::appendVertsReduced(
        const sf::IntRect & t_mapTileRange,
        const sf::Vector2f & t_screenTileSize)
    {
        m_verts.clear();

        for (const MapTile & mapTile : m_mapTiles)
        {
            if ((mapTile.position.x < t_mapTileRange.position.x) ||
                (mapTile.position.x >= util::right(t_mapTileRange)) ||
                (mapTile.position.y < t_mapTileRange.position.y) ||
                (mapTile.position.y >= util::bottom(t_mapTileRange)))
            {
                continue; // only append verts for tiles in range
            }

            const float posX{ static_cast<float>(mapTile.position.x - t_mapTileRange.position.x) *
                              t_screenTileSize.x };

            const float posY{ static_cast<float>(mapTile.position.y - t_mapTileRange.position.y) *
                              t_screenTileSize.y };

            const sf::FloatRect screenRect{ sf::Vector2f(posX, posY), t_screenTileSize };

            util::appendTriangleVerts(screenRect, mapTile.texture_rect, m_verts);
        }
    }

    void IndirectTileLayer::createReducedMapTiles(
        const sf::Vector2i & t_mapTileCount, const sf::Vector2i & t_textureTileSize)
    {
        m_mapTiles.clear();

        std::size_t mapTileIndex{ 0 };
        for (int y{ 0 }; y < t_mapTileCount.y; ++y)
        {
            for (int x{ 0 }; x < t_mapTileCount.x; ++x)
            {
                const int mapTileValue{ m_rawIndexes.at(mapTileIndex++) };
                if (mapTileValue != 0)
                {
                    const int textureIndex{ (mapTileValue - m_textureGID) };

                    const int texturePosX{ (textureIndex % m_textureTileCount.x) *
                                           t_textureTileSize.x };

                    const int texturePosY{ (textureIndex / m_textureTileCount.x) *
                                           t_textureTileSize.y };

                    const sf::IntRect textureRect{ { texturePosX, texturePosY },
                                                   t_textureTileSize };

                    m_mapTiles.emplace_back(sf::Vector2i(x, y), textureRect);
                }
            }
        }
    }

} // namespace thornberry
