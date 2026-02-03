//
// alpha-masking.cpp
//
#include "alpha-masking.hpp"

#include "texture-loader.hpp"

namespace thornberry
{

    bool AlphaMasking::loadAndApplyMasks(
        sf::Texture & t_texture,
        const std::string & t_path,
        const sf::Color & t_maskColor,
        const bool t_willApplyShadowMasks)
    {
        sf::Image image;
        if (util::TextureLoader::load(image, t_path))
        {
            applyMasks(image, t_maskColor, t_willApplyShadowMasks);
            return t_texture.loadFromImage(image);
        }
        else
        {
            return false;
        }
    }

    void AlphaMasking::applyMasks(
        sf::Image & t_image, const sf::Color & t_maskColor, const bool t_willApplyShadowMasks)
    {
        const sf::Vector2u imageSize{ t_image.getSize() };
        for (unsigned y{ 0 }; y < imageSize.y; ++y)
        {
            for (unsigned x{ 0 }; x < imageSize.x; ++x)
            {
                const sf::Vector2u pixelPos{ x, y };
                const sf::Color color{ t_image.getPixel(pixelPos) };
                if (color == t_maskColor)
                {
                    t_image.setPixel(pixelPos, sf::Color::Transparent);
                }
                else if (t_willApplyShadowMasks)
                {
                    if (color == sf::Color::Black)
                    {
                        // black is the darkest shadow color
                        t_image.setPixel(pixelPos, sf::Color(0, 0, 0, 124));
                    }
                    else if (color == sf::Color(127, 0, 127))
                    {
                        // this half-magenta color is the medium shadow
                        t_image.setPixel(pixelPos, sf::Color(0, 0, 0, 87));
                    }
                    else if (color == sf::Color(151, 0, 147))
                    {
                        // This half-magenta variant shouldn't be needed, but
                        // until I fix all the shadow images out there that use it...
                        t_image.setPixel(pixelPos, sf::Color(0, 0, 0, 87));
                    }
                    else if (color == sf::Color(255, 0, 255))
                    {
                        // the magenta color is the lightest shadow color
                        t_image.setPixel(pixelPos, sf::Color(0, 0, 0, 50));
                    }
                }
            }
        }
    }

} // namespace thornberry
