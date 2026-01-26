#ifndef MAPTEXTURES_HPP_INCLUDED
#define MAPTEXTURES_HPP_INCLUDED
//
// map-textures.hpp
//
#include "tile-image.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

namespace thornberry
{

    struct Context;

    //
    struct TileTexture
    {
        std::size_t ref_count{ 0 };
        int gid{ 0 };
        sf::Vector2i size{ 0, 0 };
        sf::Texture texture{};
        sf::Color transparent_color{ sf::Color::Transparent };
    };

    //
    class MapTextureManager
    {
      public:
        MapTextureManager();

        // this class MUST be a singleton because it needs to be accessible in TileLayer destructors
        static MapTextureManager & instance();

        void setup();
        void teardown();

        void acquire(const Context & t_context, const TileImage t_tileImage);
        void release(const TileImage t_tileImage);

        [[nodiscard]] const TileTexture & get(const TileImage t_tileImage) const;
        void setGid(const TileImage t_tileImage, const int t_gid);
        void setTransparentColor(const TileImage t_tileImage, const sf::Color & t_color);

      private:
        std::vector<TileTexture> m_tileTextures;
    };

} // namespace thornberry

#endif // MAPTEXTURES_HPP_INCLUDED
