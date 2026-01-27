//
// level-file-loader.cpp
//
#include "level-file-loader.hpp"

#include "anim-layer-campfire.hpp"
#include "anim-layer-candleflame.hpp"
#include "anim-layer-heart.hpp"
#include "check-macros.hpp"
#include "config.hpp"
#include "map-textures.hpp"
#include "screen-layout.hpp"
#include "sfml-util.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace thornberry
{

    LevelFileLoader::LevelFileLoader()
        : m_pathStr()
    {}

    void LevelFileLoader::load(const Context & t_context, const std::string & t_filename)
    {
        const std::filesystem::path path{ t_context.config.media_path / "map" / t_filename };
        M_CHECK(std::filesystem::exists(path), "The level file does not exist: " << path.string());

        m_pathStr = path.string();

        nlohmann::json json;

        {
            std::ifstream iStream(m_pathStr);
            M_CHECK(iStream, "Found but failed to open the level file: \"" << m_pathStr << "\"");
            iStream >> json;
        }

        parseLevelDetails(t_context, t_filename, json);
        parseTilesets(t_context, json);

        // everything else in the level file is saved in "layers"
        // which are parsed in order from back to front
        parseLayers(t_context, json);
    }

    void LevelFileLoader::parseLevelDetails(
        const Context & t_context, const std::string & t_name, const nlohmann::json & t_wholeJson)
    {
        const sf::Vector2i mapTileCount{ t_wholeJson["width"], t_wholeJson["height"] };

        M_CHECK(
            ((mapTileCount.x > 0) && (mapTileCount.y > 0)),
            "The level file had invalid t_context.level.map_tile_count values!");

        const sf::Vector2i textureTileSize{ t_wholeJson["tilewidth"], t_wholeJson["tileheight"] };

        M_CHECK(
            ((textureTileSize.x > 0) && (textureTileSize.y > 0)),
            "The level file had invalid t_context.level.texture_tile_size values!");

        const float scale{ t_context.screen_layout.calScaleBasedOnResolution(
            t_context, t_context.config.map_tile_scale) };

        const sf::Vector2f screenTileSize{ sf::Vector2f{ textureTileSize } * scale };

        t_context.level.setLevelDetails(t_name, mapTileCount, textureTileSize, screenTileSize);
    }

    void LevelFileLoader::parseTilesets(
        const Context & t_context, const nlohmann::json & t_wholeJson)
    {
        for (const nlohmann::json & tilesetJson : t_wholeJson["tilesets"])
        {
            const int gid{ tilesetJson["firstgid"] };
            const std::string imageStr{ tilesetJson.value("image", "") };
            const std::string sourceStr{ tilesetJson.value("source", "") };

            TileImage tileImage{ TileImage::Count };
            std::string transparentColorStr{ "" };

            if (!imageStr.empty())
            {
                parseTilesetAsOrig(tilesetJson, gid, imageStr, tileImage, transparentColorStr);
            }
            else if (!sourceStr.empty())
            {
                parseTilesetAsSeparateFile(
                    t_context, gid, sourceStr, tileImage, transparentColorStr);
            }
            else
            {
                std::cout << "LevelFileLoader::parseTilesets()  While parsing \"" << m_pathStr
                          << "\": Found a tileset (gid=" << gid
                          << ") with no 'image' or 'source' entry.  It will be ingored.\n";
            }

            if (tileImage != TileImage::Count)
            {
                MapTextureManager::instance().setGid(tileImage, gid);

                if (!transparentColorStr.empty())
                {
                    const sf::Color maskColor{ util::hexStringToSfmlColor(transparentColorStr) };
                    MapTextureManager::instance().setTransparentColor(tileImage, maskColor);
                }
            }
        }
    }

    void LevelFileLoader::parseTilesetAsOrig(
        const nlohmann::json & t_tilesetJson,
        const int t_gid,
        const std::string & t_path,
        TileImage & t_tileImageOutParam,
        std::string & t_transparentColorStrOutParam)
    {
        const std::filesystem::path path{ t_path };

        const std::string filenameWithoutExtension{
            path.filename().replace_extension("").string()
        };

        t_tileImageOutParam = tileImageFromString(filenameWithoutExtension);
        if (t_tileImageOutParam == TileImage::Count)
        {
            std::cout << "LevelFileLoader::parseTilesetAsOrig()  While parsing \"" << m_pathStr
                      << "\": Found a tileset (gid=" << t_gid
                      << ") with no valid TileImage filename \"" << t_path
                      << "\".  It will be ingored.\n ";
        }
        else
        {
            t_transparentColorStrOutParam = t_tilesetJson.value("transparentcolor", "");
        }
    }

    void LevelFileLoader::parseTilesetAsSeparateFile(
        const Context & t_context,
        const int t_gid,
        const std::string & t_path,
        TileImage & t_tileImageOutParam,
        std::string & t_transparentColorStrOutParam)
    {
        const std::filesystem::path tilesetPath{ t_context.config.media_path / "map" / t_path };

        M_CHECK(
            std::filesystem::exists(tilesetPath),
            "The tileset file does not exist: " << tilesetPath.string());

        nlohmann::json json;

        {
            std::ifstream iStream(tilesetPath.string());

            M_CHECK(
                iStream,
                "Found but failed to open the tileset file: \"" << tilesetPath.string() << "\"");

            iStream >> json;
        }

        const std::string imagePathStr{ json["image"] };
        const std::filesystem::path imagePath{ imagePathStr };

        const std::string filenameWithoutExtension{
            imagePath.filename().replace_extension("").string()
        };

        t_tileImageOutParam = tileImageFromString(filenameWithoutExtension);
        if (t_tileImageOutParam == TileImage::Count)
        {
            std::cout << "LevelFileLoader::parseTilesetAsSeparateFile()  While parsing \""
                      << m_pathStr << "\": Found a tileset (gid=" << t_gid
                      << ") with no valid TileImage filename \"" << imagePathStr
                      << "\".  It will be ingored.\n ";
        }
        else
        {
            t_transparentColorStrOutParam = json.value("transparentcolor", "");
        }
    }

    void LevelFileLoader::parseTransitionsLayer(
        const Context & t_context, const nlohmann::json & t_layerJson)
    {
        for (const nlohmann::json & objJson : t_layerJson["objects"])
        {
            Transition transition;
            transition.map_rect = parseAndScaleRect(t_context, objJson);

            for (const nlohmann::json & propJson : objJson["properties"])
            {
                const std::string nameStr{ propJson["name"] };
                const std::string valueStr{ propJson["value"] };
                if (nameStr == "type")
                {
                    transition.direction = transitionDirectionFromString(valueStr);
                }
                else if (nameStr == "level")
                {
                    transition.map_filename = valueStr;
                }
                else if (nameStr == "sfx")
                {
                    transition.sfx_name = valueStr;
                }
            }

            t_context.level.transitions().push_back(transition);
        }
    }

    void LevelFileLoader::parseLayers(
        const Context & t_context, const nlohmann::json & jsonWholeFile)
    {
        LayerGroup layerGroup{ LayerGroup::Lower };

        for (const nlohmann::json & layerJson : jsonWholeFile["layers"])
        {
            const std::string layerName{ layerJson["name"] };
            const TileImage tileImage{ tileImageFromString(layerName) };

            if (tileImage != TileImage::Count)
            {
                parseTileLayer(t_context, layerGroup, tileImage, layerJson);
            }
            else if (layerName == "separator")
            {
                // an empty tile layer only for separating what is drawn above or below the avatar
                layerGroup = LayerGroup::Upper;
            }
            else if (layerName == "collision")
            {
                parseRectLayer(t_context, layerJson, t_context.level.collisions());
            }
            else if (layerName == "transition")
            {
                parseTransitionsLayer(t_context, layerJson);
            }
            else if (layerName == "animation")
            {
                parseAnimationLayer(t_context, layerGroup, layerJson);
            }
            else if (layerName == "footstep-sfx")
            {
                parseWalkSoundEffectLayer(t_context, layerJson);
            }
            else if (layerName == "pickup")
            {
                parsePickupLayer(t_context, layerGroup, layerJson);
            }
            else
            {
                std::cout << "LevelFileLoader::parseLayers()  While parsing level file \""
                          << m_pathStr << "\".  Ignored unknown layer named \"" << layerName
                          << "\".\n";
            }
        }
    }

    void LevelFileLoader::parseWalkSoundEffectLayer(
        const Context & t_context, const nlohmann::json & t_layerJson)
    {
        for (const nlohmann::json & objectJson : t_layerJson["objects"])
        {
            WalkSound walkSound;
            walkSound.sfx_name = objectJson["name"];
            walkSound.map_rect = parseAndScaleRect(t_context, objectJson);

            t_context.level.walkSounds().emplace_back(walkSound);
        }
    }

    void LevelFileLoader::parseTileLayer(
        const Context & t_context,
        const LayerGroup t_layerGroup,
        const TileImage image,
        const nlohmann::json & t_json)
    {
        const std::vector<int> indexes = t_json["data"];

        M_CHECK(
            !indexes.empty(),
            "Error Parsing Level File " << m_pathStr << ":  tile layer for image " << image
                                        << " was empty.");

        if (t_layerGroup == LayerGroup::Lower)
        {
            t_context.level.appendToLowerTileLayers(
                std::make_unique<IndirectTileLayer>(t_context, image, indexes));
        }
        else
        {
            t_context.level.appendToUpperTileLayers(
                std::make_unique<IndirectTileLayer>(t_context, image, indexes));
        }
    }

    void LevelFileLoader::parseRectLayer(
        const Context & t_context,
        const nlohmann::json & t_json,
        std::vector<sf::FloatRect> & t_rects)
    {
        t_rects.clear();

        for (const nlohmann::json & collJson : t_json["objects"])
        {
            t_rects.emplace_back(parseAndScaleRect(t_context, collJson));
        }
    }

    const sf::FloatRect
        LevelFileLoader::parseAndScaleRect(const Context & t_context, const nlohmann::json & t_json)
    {
        const sf::IntRect rect{ { t_json["x"], t_json["y"] },
                                { t_json["width"], t_json["height"] } };

        const float scale{ t_context.screen_layout.calScaleBasedOnResolution(
            t_context, t_context.config.map_tile_scale) };

        sf::FloatRect mapRect{ rect };
        mapRect.position.x *= scale;
        mapRect.position.y *= scale;
        mapRect.size.x *= scale;
        mapRect.size.y *= scale;

        return mapRect;
    }

    void LevelFileLoader::parseAnimationLayer(
        const Context & t_context,
        const LayerGroup t_layerGroup,
        const nlohmann::json & t_layerJson)
    {
        for (const nlohmann::json & objJson : t_layerJson["objects"])
        {
            const std::string name{ objJson["name"] };
            const sf::FloatRect rect{ parseAndScaleRect(t_context, objJson) };

            if (name == "campfire")
            {
                appendRectLayer<AnimLayerCampfire>(t_context, t_layerGroup, rect);
            }
            else if (name == "candle-flame-pixel")
            {
                appendRectLayer<AnimLayerCandleflame>(t_context, t_layerGroup, rect);
            }
            else
            {
                std::cout << "LevelFileLoader::parseAnimationLayer()  While parsing level file \""
                          << m_pathStr << "\".  Ignored unknown animation layer named \"" << name
                          << "\".\n";
            }
        }
    }

    void LevelFileLoader::parsePickupLayer(
        const Context & t_context, const LayerGroup layerGroup, const nlohmann::json & t_layerJson)
    {
        for (const nlohmann::json & objJson : t_layerJson["objects"])
        {
            // const std::string name{ objJson["name"] };
            const sf::FloatRect rect{ parseAndScaleRect(t_context, objJson) };

            if (layerGroup == LayerGroup::Lower)
            {
                t_context.level.appendToLowerTileLayers(
                    std::make_unique<AnimLayerHeart>(t_context, rect));
            }
            else
            {
                t_context.level.appendToUpperTileLayers(
                    std::make_unique<AnimLayerHeart>(t_context, rect));
            }
        }
    }

} // namespace thornberry
