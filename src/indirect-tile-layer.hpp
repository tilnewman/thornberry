#ifndef INDIRECT_TILE_LAYER_HPP_INCLUDED
#define INDIRECT_TILE_LAYER_HPP_INCLUDED
//
// indirect-tile-layer.hpp
//
#include "tile-image.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

namespace thornberry
{
    struct Context;

    //
    struct IIndirectTileLayer
    {
        virtual ~IIndirectTileLayer() = default;

        virtual void postLevelLoadSetup(const Context & t_context)                      = 0;
        virtual void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const = 0;
        virtual void move(const sf::Vector2f & t_move)                                  = 0;
        virtual void dumpInfo() const                                                   = 0;
        virtual void update(const Context & t_context, const float t_elapsedSec)        = 0;

        virtual void appendVerts(
            const sf::IntRect & t_mapTileRange,
            const sf::Vector2i & t_mapTileCount,
            const sf::Vector2i & t_textureTileSize,
            const sf::Vector2f & t_screenTileSize) = 0;
    };

    //
    class IndirectTileLayer : public IIndirectTileLayer
    {
      public:
        IndirectTileLayer(
            const Context & t_context, const TileImage t_image, const std::vector<int> & t_indexes);

        virtual ~IndirectTileLayer() override;

        void postLevelLoadSetup(const Context &) override {}
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;
        void dumpInfo() const override;
        void update(const Context &, const float) override {}

        void appendVerts(
            const sf::IntRect & t_mapTileRange,
            const sf::Vector2i & t_mapTileCount,
            const sf::Vector2i & t_textureTileSize,
            const sf::Vector2f & t_screenTileSize) override;

        // tile layers don't need to move thier verts, see indirect-level.cpp
        void move(const sf::Vector2f &) override {}

      private:
        TileImage m_image;
        int m_textureGID;
        sf::Vector2i m_textureTileCount;
        std::vector<int> m_indexes;
        std::vector<sf::Vertex> m_verts;
    };

} // namespace thornberry

#endif // INDIRECT_TILE_LAYER_HPP_INCLUDED
