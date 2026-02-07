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
        sf::VideoMode video_mode{ { 4112u, 2580u }, 32u };
        unsigned framerate_limit{ 0 };
        float map_tile_scale{ 1.0f };
        float avatar_scale{ 1.6f };
        float avatar_walk_speed{ 80.0f };
        float avatar_walk_inner_map_ratio{ 0.4f };
        sf::Color background_color{ 30, 30, 30 };
        sf::Color background_mask_color{ 75, 99, 127 };
        sf::Color map_outline_color{ 127, 127, 127 };
        sf::Color text_button_color{ 0, 0, 0, 127 };
        sf::Color text_button_mouseover_color{ sf::Color::Black };
        sf::Color text_window_focus_off_color{ 127, 127, 127 };
        sf::Color text_window_focus_on_color{ sf::Color::White };
        std::string sound_filename_extension{ ".ogg" };
        float music_volume{ 50.0f }; // 0-100
    };

} // namespace thornberry

#endif // CONFIG_HPP_INCLUDED
