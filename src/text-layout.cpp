// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// text-result.cpp
//
#include "text-layout.hpp"

#include "context.hpp"
#include "sfml-util.hpp"

#include <algorithm>
#include <sstream>

namespace thornberry
{

    const TextLayoutResult
        TextLayout::typeset(const Context & t_context, const TextLayoutSpec & t_spec)
    {
        const FontExtent fontExtent{ t_context.font.extent(t_spec.font_size) };

        // split message into words
        const std::vector<std::string> words{ splitIntoWords(t_spec.text) };

        // transform words into one sf::Text per line of text that fits into rect_inner
        TextLayoutResult result;
        result.rect_outer = t_spec.rect;
        result.rect_inner = util::scaleRectInPlaceCopy(t_spec.rect, (1.0f - t_spec.pad_ratio));

        if (words.empty())
        {
            return result;
        }

        result.texts.reserve(words.size());

        sf::Vector2f pos{ result.rect_inner.position };
        std::string lineStr;
        sf::Text lineText = t_context.font.makeText(t_spec.font_size, "", t_spec.color);
        lineText.setPosition(pos);

        for (auto wordIter = std::begin(words); wordIter != std::end(words); ++wordIter)
        {
            if ("<p>" == *wordIter)
            {
                result.texts.push_back(lineText);
                pos.y += fontExtent.letter_size.y;
                pos.y += fontExtent.letter_size.y;
                lineStr.clear();
                lineText.setString(lineStr);
                util::setOriginToPosition(lineText);
                lineText.setPosition(pos);
                continue;
            }

            std::string tempStr;
            if (lineStr.empty())
            {
                tempStr = *wordIter;
            }
            else
            {
                tempStr = lineStr;
                tempStr += ' ';
                tempStr += *wordIter;
            }

            sf::Text tempText{ lineText };
            tempText.setString(tempStr);
            util::setOriginToPosition(tempText);
            tempText.setPosition(pos);

            if (util::right(tempText) < util::right(result.rect_inner))
            {
                lineText = tempText;
                lineStr  = tempStr;
            }
            else
            {
                result.texts.push_back(lineText);

                pos.y += fontExtent.letter_size.y;
                lineStr = *wordIter;
                lineText.setString(lineStr);
                util::setOriginToPosition(lineText);
                lineText.setPosition(pos);
            }
        }

        result.texts.push_back(lineText);

        if (t_spec.will_center_justify)
        {
            centerTextLines(result);
        }
        else
        {
            centerTextBlock(result);
        }

        return result;
    }

    const std::vector<std::string> TextLayout::splitIntoWords(const std::string & t_text)
    {
        std::vector<std::string> words;
        words.reserve(t_text.size() / 4); // found by experiment to be a good upper bound

        std::istringstream iss{ t_text };

        std::copy(
            std::istream_iterator<std::string>(iss),
            std::istream_iterator<std::string>(),
            std::back_inserter(words));

        return words;
    }

    void TextLayout::centerTextBlock(TextLayoutResult & result)
    {
        if (result.texts.empty())
        {
            return;
        }

        // find the widest line of text
        float width = 0.0f;
        for (const sf::Text & text : result.texts)
        {
            if (text.getGlobalBounds().size.x > width)
            {
                width = text.getGlobalBounds().size.x;
            }
        }

        // center all the text as a block into t_rect
        const float height{ util::bottom(result.texts.back()) -
                            result.texts.front().getGlobalBounds().position.y };

        const sf::Vector2f offset{ (result.rect_inner.size.x - width) * 0.5f,
                                   (result.rect_inner.size.y - height) * 0.5f };

        for (sf::Text & text : result.texts)
        {
            text.move(offset);
        }
    }

    void TextLayout::centerTextLines(TextLayoutResult & result)
    {
        if (result.texts.empty())
        {
            return;
        }

        const float height{ util::bottom(result.texts.back()) -
                            result.texts.front().getGlobalBounds().position.y };

        for (sf::Text & text : result.texts)
        {
            const sf::Vector2f offset{ (result.rect_inner.size.x - text.getGlobalBounds().size.x) *
                                           0.5f,
                                       (result.rect_inner.size.y - height) * 0.5f };

            text.move(offset);
        }
    }

} // namespace thornberry