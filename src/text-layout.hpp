#ifndef TEXT_LAYOUT_HPP_INCLUDED
#define TEXT_LAYOUT_HPP_INCLUDED
//
// text-layout.hpp
//
#include "font.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>
#include <vector>

namespace thornberry
{

    struct Context;

    //
    struct TextLayoutSpec
    {
        TextLayoutSpec(
            const std::string & t_text,
            const sf::FloatRect & t_rect,
            const FontSize & t_fontSize,
            const sf::Color & t_color      = sf::Color::White,
            const float t_padRatio         = 0.0f,
            const bool t_willCenterJustify = true)
            : text{ t_text }
            , rect{ t_rect }
            , font_size{ t_fontSize }
            , pad_ratio{ t_padRatio }
            , will_center_justify{ t_willCenterJustify }
            , color{ t_color }
        {}

        std::string text;
        sf::FloatRect rect;
        FontSize font_size;
        float pad_ratio;
        bool will_center_justify;
        sf::Color color;
    };

    //
    struct TextLayoutResult
    {
        sf::FloatRect rect_pad{}; // the original from TextLayoutSpec with pad_ratio applied
        sf::FloatRect rect_actual{}; // the actual rect containing the text
        std::vector<sf::Text> texts{};
        bool didTextFit() const;
    };

    //
    class TextLayout
    {
      public:
        [[nodiscard]] static const TextLayoutResult
            typeset(const Context & t_context, const TextLayoutSpec & t_spec);

      private:
        [[nodiscard]] static const std::vector<std::string>
            splitIntoWords(const std::string & t_text);

        static void centerTextBlock(TextLayoutResult & layout);
        static void centerTextLines(TextLayoutResult & layout);
    };

} // namespace thornberry

#endif // TEXT_LAYOUT_HPP_INCLUDED
