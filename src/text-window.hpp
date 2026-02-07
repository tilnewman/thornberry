#ifndef TEXT_WINDOW_HPP_INCLUDED
#define TEXT_WINDOW_HPP_INCLUDED
//
// text-window.hpp
//
#include "avatar-image.hpp"
#include "text-layout.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>
#include <string_view>

namespace thornberry
{

    struct Context;

    //
    enum class TextWindowBackground
    {
        PaperSmall,
        PaperLarge
    };

    constexpr std::string_view toString(const TextWindowBackground bg) noexcept
    {
        if (bg == TextWindowBackground::PaperSmall)
        {
            return "PaperSmall";
        }
        else
        {
            return "PaperLarge";
        }
    }

    inline const sf::FloatRect backgroundToInnerRect(const TextWindowBackground bg) noexcept
    {
        if (bg == TextWindowBackground::PaperSmall)
        {
            return { { 35.0f, 27.0f }, { 440.0f, 270.0f } };
        }
        else
        {
            return { { 36.0f, 36.0f }, { 422.0f, 414.0f } };
        }
    }

    //
    struct TextWindowSpec
    {
        TextWindowSpec()
            : TextWindowSpec(
                  {},
                  TextWindowBackground::PaperSmall,
                  "",
                  sf::Color::Black,
                  FontSize::Small,
                  AvatarImage::count)
        {}

        // use this constrcutor when you know which background you want
        TextWindowSpec(
            const sf::Vector2f & t_position,
            const TextWindowBackground t_background,
            const std::string & t_text,
            const sf::Color & t_textColor = sf::Color(0,0,0,220),
            const FontSize t_fontSize = FontSize::Small,
            const AvatarImage t_avatarImage = AvatarImage::count)
            : position{ t_position }
            , background{ t_background }
            , text{ t_text }
            , font_size{ t_fontSize }
            , text_color{ t_textColor }
            , avatar_image{ t_avatarImage }
        {}

        sf::Vector2f position;
        TextWindowBackground background;
        std::string text;
        FontSize font_size;
        sf::Color text_color;
        AvatarImage avatar_image;
    };

    //
    class TextWindow
    {
      public:
        TextWindow();
        ~TextWindow();

        void setup(const Context & t_context, const TextWindowSpec & t_spec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

      private:
        [[nodiscard]] bool setupSizesAndPositions(const Context & t_context, const float t_baseScale);

      private:
        TextWindowSpec m_spec;
        sf::Texture m_bgTexture;
        sf::Sprite m_bgSprite;
        sf::Texture m_avatarTexture;
        sf::Sprite m_avatarSprite;
        sf::FloatRect m_bgOuterRect;
        sf::FloatRect m_bgInnerRect;
        TextLayoutResult m_layoutResult;
    };

} // namespace thornberry

#endif // TEXT_WINDOW_HPP_INCLUDED
