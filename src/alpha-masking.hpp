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

    class AlphaMasking
    {
      public:
        AlphaMasking() = default;

        static bool loadAndApplyMasks(
            sf::Texture & t_texture,
            const std::string & t_path,
            const sf::Color & t_maskColor,
            const bool t_willApplyShadowMasks);

        static void applyMasks(
            sf::Image & t_image, const sf::Color & t_maskColor, const bool t_willApplyShadowMasks);
    };

} // namespace thornberry

#endif // ALPHA_MASKING_HPP_INLCUDED
