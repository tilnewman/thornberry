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

namespace thornberry
{

    struct Context;

    //
    enum class TextWindowBackground
    {
        // Auto, // either PaperSmall or PaperLarge will be auto selected
        PaperSmall,
        PaperLarge
    };

    //
    struct TextWindowSpec
    {
        TextWindowSpec()
            : TextWindowSpec(
                  {},
                  TextWindowBackground::PaperSmall,
                  "",
                  FontSize::Small,
                  sf::Color::Black,
                  AvatarImage::count)
        {}

        // use this constrcutor when you DON'T know which background you want (auto)
        // TextWindowSpec(
        //    const TextLayoutSpec & t_layoutSpec,
        //    const AvatarImage t_avatarImage = AvatarImage::count)
        //    : background{ TextWindowBackground::Auto }
        //    , layout_spec{ t_layoutSpec }
        //    , avatar_image{ t_avatarImage }
        //{}

        // use this constrcutor when you know which background you want
        TextWindowSpec(
            const sf::Vector2f & t_position,
            const TextWindowBackground t_background,
            const std::string & t_text,
            const FontSize t_fontSize,
            const sf::Color & t_textColor,
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

        void setup(const Context & t_context, const TextWindowSpec & t_spec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

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
