#ifndef WINDOW_HPP_INLCUDED
#define WINDOW_HPP_INLCUDED
//
// window.hpp
//
#include "window-image-manager.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

namespace thornberry
{

    struct Context;

    //
    class Window
    {
      public:
        Window();

        void setup(const Context & t_context, const sf::FloatRect & t_rect);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

      private:
        void setupBorder(const Context & t_context, const sf::FloatRect & t_rect);
        void setupBackground(const Context & t_context, const sf::FloatRect & t_rect);

      private:
        std::vector<sf::Sprite> m_sprites;
        sf::RectangleShape m_bgRectangle;
    };

} // namespace thornberry

#endif // WINDOW_HPP_INLCUDED
