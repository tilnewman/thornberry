#ifndef LEVEL_FILE_LOADER_HPP_INCLUDED
#define LEVEL_FILE_LOADER_HPP_INCLUDED
//
// level-file-loader.hpp
//
#include "context.hpp"
#include "indirect-level.hpp"
#include "indirect-tile-layer.hpp"
#include "json-wrapper.hpp"
#include "tile-image.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <string>
#include <vector>

namespace thornberry
{

    class LevelFileLoader
    {
      public:
        LevelFileLoader();

        void load(const Context & t_context, const std::string & t_filename);

      private:
        void parseLevelDetails(
            const Context & t_context, const std::string & t_name, const nlohmann::json & t_json);

        void parseTilesets(const Context & t_context, const nlohmann::json & t_json);

        void parseTilesetAsOrig(
            const nlohmann::json & t_json,
            const int t_gid,
            const std::string & t_path,
            TileImage & t_tileImageOutParam,
            std::string & t_transparentColorStrOutParam);

        void parseTilesetAsSeparateFile(
            const Context & t_context,
            const int t_gid,
            const std::string & t_path,
            TileImage & t_tileImageOutParam,
            std::string & t_transparentColorStrOutParam);

        void parseLayers(const Context & t_context, const nlohmann::json & t_json);
        void parseTransitionsLayer(const Context & t_context, const nlohmann::json & t_json);

        void parseWalkSoundEffectLayer(
            const Context & t_context, const nlohmann::json & t_layerJson);

        void parseTileLayer(
            const Context & t_context,
            const LayerGroup t_layerGroup,
            const TileImage image,
            const nlohmann::json & t_json);

        void parseRectLayer(
            const Context & t_context,
            const nlohmann::json & t_json,
            std::vector<sf::FloatRect> & t_rects);

        [[nodiscard]] const sf::FloatRect
            parseAndScaleRect(const Context & t_context, const nlohmann::json & t_json);

        void parseAnimationLayer(
            const Context & t_context,
            const LayerGroup layerGroup,
            const nlohmann::json & t_layerJson);

        template <typename Layer_t>
        void appendRectLayer(
            const Context & t_context, const LayerGroup layerGroup, const sf::FloatRect & t_rect)
        {
            if (layerGroup == LayerGroup::Lower)
            {
                t_context.level.appendToLowerTileLayers(std::make_unique<Layer_t>(t_rect));
            }
            else
            {
                t_context.level.appendToUpperTileLayers(std::make_unique<Layer_t>(t_rect));
            }
        }

      private:
        std::string m_pathStr;
    };

} // namespace thornberry

#endif // LEVEL_FILE_LOADER_HPP_INCLUDED
