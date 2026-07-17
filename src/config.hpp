#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED
//
// config.hpp
//
#include <filesystem>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace thornberry
{

    struct Config
    {
        std::filesystem::path media_path{};

        unsigned framerate_limit{ 0 };
        sf::VideoMode video_mode{ { 4112u, 2580u }, 32u };

        // minor tweaks to these values are fine, but they should all be scaled together
        float map_tile_scale{ 1.0f };
        float avatar_scale{ 1.6f };
        float avatar_walk_speed{ 80.0f };

        // how close to the edge of the map will the avatar have to be before the map starts moving
        float avatar_walk_moves_map_ratio{ 0.4f };

        sf::Color background_color{ 30, 30, 30 };
        sf::Color map_outline_color{ 127, 127, 127 };

        // Images are PNGs that support transparency, but some are from artists that didn't seem to
        // want to use it and they used these colors as transparent/semi-transparent placeholders.
        sf::Color mask_color_transparent{ 75, 99, 127 };
        sf::Color mask_color_shadow_dark{ 0, 0, 0 };
        sf::Color mask_color_shadow_medium{ 127, 0, 127 };
        sf::Color mask_color_shadow_medium2{ 151, 0, 147 }; // some artists used it...
        sf::Color mask_color_shadow_light{ 255, 0, 255 };
        // ...and here are the actual semi-transparent colors they translate into
        sf::Color shadow_color_dark{ 0, 0, 0, 124 };
        sf::Color shadow_color_medium{ 0, 0, 0, 87 };
        sf::Color shadow_color_light{ 0, 0, 0, 50 };

        sf::Color text_button_color{ 0, 0, 0, 127 };
        sf::Color text_button_mouseover_color{ 0, 0, 0, 192 };
        sf::Color text_window_focus_off_color{ 127, 127, 127 };
        sf::Color text_window_focus_on_color{ sf::Color::White };

        sf::Color night_map_overlay_color{ 0, 0, 255, 80 };

        float music_volume{ 50.0f }; // 0-100
        std::string sound_filename_extension{ ".ogg" };
    };

} // namespace thornberry

#endif // CONFIG_HPP_INCLUDED
