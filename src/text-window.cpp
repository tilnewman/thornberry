//
// text-window.cpp
//
#include "text-window.hpp"

#include "config.hpp"
#include "context.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

#include <SFML/Graphics/Text.hpp>

namespace thornberry
{

    TextWindow::TextWindow()
        : m_spec{}
        , m_bgTexture{}
        , m_bgSprite{ m_bgTexture }
        , m_avatarTexture{}
        , m_avatarSprite{ m_avatarTexture }
        , m_bgOuterRect{}
        , m_bgInnerRect{}
        , m_layoutResult{}
    {}

    void TextWindow::setup(const Context & t_context, const TextWindowSpec & t_spec)
    {
        m_spec = t_spec;

        if (TextWindowBackground::PaperSmall == m_spec.background)
        {
            util::TextureLoader::load(
                m_bgTexture, (t_context.config.media_path / "image" / "paper-small.png"), true);

            m_bgInnerRect = { { 35.0f, 27.0f }, { 440.0f, 270.0f } };
        }
        else if (TextWindowBackground::PaperLarge == m_spec.background)
        {
            util::TextureLoader::load(
                m_bgTexture, (t_context.config.media_path / "image" / "paper-large.png"), true);

            m_bgInnerRect = { { 36.0f, 36.0f }, { 424.0f, 414.0f } };
        }

        m_bgOuterRect.position = m_spec.position;
        m_bgOuterRect.size     = sf::Vector2f{ m_bgTexture.getSize() };

        m_bgInnerRect.position += m_bgOuterRect.position;

        m_bgSprite.setTexture(m_bgTexture, true);
        util::fitAndCenterInside(m_bgSprite, m_bgOuterRect);

        const TextLayoutSpec layoutSpec(
            m_spec.text, m_bgInnerRect, m_spec.font_size, m_spec.text_color);

        m_layoutResult = TextLayout::typeset(t_context, layoutSpec);
    }

    void TextWindow::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_bgSprite, t_states);

        for (const sf::Text & text : m_layoutResult.texts)
        {
            t_target.draw(text, t_states);
        }
    }

} // namespace thornberry
