#ifndef TEXTURE_LOADER_HPP_INCLUDED
#define TEXTURE_LOADER_HPP_INCLUDED
//
// texture-loader.hpp
//
#include <filesystem>
#include <map>
#include <string>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace thornberry
{
    struct Context;
}

namespace util
{

    struct TextureRecord
    {
        std::size_t loads{ 0 };
        sf::Vector2u size{};
    };

    //

    class TextureLoader
    {
      public:
        static inline bool load(
            sf::Texture & t_texture,
            const std::filesystem::path & t_path,
            const bool t_willSmooth = false)
        {
            return load(t_texture, t_path.string(), t_willSmooth);
        }

        static bool load(
            sf::Texture & t_texture,
            const std::string & t_pathStr,
            const bool t_willSmooth = false);

        static inline bool load(
            sf::Image & t_image,
            const std::filesystem::path & t_path)
        {
            return load(t_image, t_path.string());
        }

        static bool load(
            sf::Image & t_image,
            const std::string & t_pathStr);

        static void dumpInfo(const thornberry::Context & t_context);

      private:
        static inline std::map<std::string, TextureRecord> m_pathRecordtMap;
    };

} // namespace util

#endif // TEXTURE_LOADER_HPP_INCLUDED
