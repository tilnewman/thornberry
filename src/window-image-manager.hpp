#ifndef WINDOW_IMAGE_MANAGER_HPP_INCLUDED
#define WINDOW_IMAGE_MANAGER_HPP_INCLUDED
//
// window-image-manager.hpp
//
#include <SFML/Graphics/Texture.hpp>

namespace thornberry
{
    struct Config;

    //
    class WindowImageManager
    {
      public:
        WindowImageManager();

        void setup(const Config & t_config);

        [[nodiscard]] const sf::Texture & bgTop() const { return m_backgroundTop; }
        [[nodiscard]] const sf::Texture & bgBot() const { return m_backgroundBot; }
        [[nodiscard]] const sf::Texture & bgLeft() const { return m_backgroundLeft; }
        [[nodiscard]] const sf::Texture & bgRight() const { return m_backgroundRight; }

        [[nodiscard]] const sf::Texture & bgTopLeft() const { return m_backgroundTopLeft; }
        [[nodiscard]] const sf::Texture & bgTopRight() const { return m_backgroundTopRight; }
        [[nodiscard]] const sf::Texture & bgBotLeft() const { return m_backgroundBotLeft; }
        [[nodiscard]] const sf::Texture & bgBotRight() const { return m_backgroundBotRight; }

        //

        [[nodiscard]] const sf::Texture & borderTop() const { return m_borderTop; }
        [[nodiscard]] const sf::Texture & borderBot() const { return m_borderBot; }
        [[nodiscard]] const sf::Texture & borderLeft() const { return m_borderLeft; }
        [[nodiscard]] const sf::Texture & borderRight() const { return m_borderRight; }

        [[nodiscard]] const sf::Texture & borderTopLeft() const { return m_borderTopLeft; }
        [[nodiscard]] const sf::Texture & borderTopRight() const { return m_borderTopRight; }
        [[nodiscard]] const sf::Texture & borderBotLeft() const { return m_borderBotLeft; }
        [[nodiscard]] const sf::Texture & borderBotRight() const { return m_borderBotRight; }

      private:
        sf::Texture m_backgroundTop;
        sf::Texture m_backgroundBot;
        sf::Texture m_backgroundLeft;
        sf::Texture m_backgroundRight;
        sf::Texture m_backgroundTopLeft;
        sf::Texture m_backgroundTopRight;
        sf::Texture m_backgroundBotLeft;
        sf::Texture m_backgroundBotRight;
        //
        sf::Texture m_borderTop;
        sf::Texture m_borderBot;
        sf::Texture m_borderLeft;
        sf::Texture m_borderRight;
        sf::Texture m_borderTopLeft;
        sf::Texture m_borderTopRight;
        sf::Texture m_borderBotLeft;
        sf::Texture m_borderBotRight;
    };

} // namespace thornberry

#endif // WINDOW_IMAGE_MANAGER_HPP_INCLUDED
