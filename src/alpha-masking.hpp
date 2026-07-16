#ifndef ALPHA_MASKING_HPP_INLCUDED
#define ALPHA_MASKING_HPP_INLCUDED
//
// alpha-masking.hpp
//
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>

namespace thornberry
{

    struct Config;

    class AlphaMasking
    {
      public:
        AlphaMasking() = default;

        static void loadAndApplyMasks(
            const Config & t_config,
            sf::Texture & t_texture,
            const sf::Color & t_transparentMask,
            const std::string & t_path,
            const bool t_willApplyShadowMasks);

        static void applyMasks(
            const Config & t_config,
            sf::Image & t_image,
            const sf::Color & t_transparentMask,
            const bool t_willApplyShadowMasks);
    };

} // namespace thornberry

#endif // ALPHA_MASKING_HPP_INLCUDED
