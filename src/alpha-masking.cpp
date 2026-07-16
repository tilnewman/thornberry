//
// alpha-masking.cpp
//
#include "alpha-masking.hpp"

#include "check-macros.hpp"
#include "config.hpp"
#include "texture-loader.hpp"

namespace thornberry
{

    void AlphaMasking::loadAndApplyMasks(
        const Config & t_config,
        sf::Texture & t_texture,
        const sf::Color & t_transparentMask,
        const std::string & t_path,
        const bool t_willApplyShadowMasks)
    {
        sf::Image image;
        const bool loadSuccess{ util::TextureLoader::load(image, t_path) };
        M_CHECK(loadSuccess, "sf::Image::load() failed for image \"" << t_path << "\"");

        applyMasks(t_config, image, t_transparentMask, t_willApplyShadowMasks);

        const bool textureLoadSuccess{ t_texture.loadFromImage(image) };

        M_CHECK(
            textureLoadSuccess,
            "sf::Texture::loadFromImage() failed for image \""
                << t_path << "\" of size " << image.getSize().x << "x" << image.getSize().y);
    }

    void AlphaMasking::applyMasks(
        const Config & t_config,
        sf::Image & t_image,
        const sf::Color & t_transparentMask,
        const bool t_willApplyShadowMasks)
    {
        const sf::Vector2u imageSize{ t_image.getSize() };
        for (unsigned y{ 0 }; y < imageSize.y; ++y)
        {
            for (unsigned x{ 0 }; x < imageSize.x; ++x)
            {
                const sf::Vector2u pixelPos{ x, y };
                const sf::Color color{ t_image.getPixel(pixelPos) };
                if (color == t_transparentMask)
                {
                    t_image.setPixel(pixelPos, sf::Color::Transparent);
                }
                else if (t_willApplyShadowMasks)
                {
                    if (color == t_config.mask_color_shadow_dark)
                    {
                        t_image.setPixel(pixelPos, t_config.shadow_color_dark);
                    }
                    else if (
                        (color == t_config.mask_color_shadow_medium) ||
                        (color == t_config.mask_color_shadow_medium2))
                    {
                        t_image.setPixel(pixelPos, t_config.shadow_color_medium);
                    }
                    else if (color == t_config.mask_color_shadow_light)
                    {
                        t_image.setPixel(pixelPos, t_config.shadow_color_light);
                    }
                }
            }
        }
    }

} // namespace thornberry
