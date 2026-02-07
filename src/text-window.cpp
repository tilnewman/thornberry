//
// text-window.cpp
//
#include "text-window.hpp"

#include "avatar-image-manager.hpp"
#include "config.hpp"
#include "context.hpp"
#include "screen-layout.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

#include <SFML/Graphics/Text.hpp>

#include <iostream>

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

    TextWindow::~TextWindow()
    {
        if (AvatarImage::count != m_spec.avatar_image)
        {
            AvatarImageManager::instance().release(m_spec.avatar_image);
        }
    }

    void TextWindow::setup(const Context & t_context, const TextWindowSpec & t_spec)
    {
        m_spec = t_spec;

        if (AvatarImage::count != m_spec.avatar_image)
        {
            m_avatarTexture = AvatarImageManager::instance().acquire(m_spec.avatar_image);
        }

        if (TextWindowBackground::PaperSmall == m_spec.background)
        {
            util::TextureLoader::load(
                m_bgTexture, (t_context.config.media_path / "image" / "paper-small.png"), true);
        }
        else if (TextWindowBackground::PaperLarge == m_spec.background)
        {
            util::TextureLoader::load(
                m_bgTexture, (t_context.config.media_path / "image" / "paper-large.png"), true);
        }

        float baseScale{ 0.5f };
        while (!setupSizesAndPositions(t_context, baseScale))
        {
            baseScale += 0.05f;

            if (baseScale > 2.0f)
            {
                std::cout << "Error: TextWindow(background_image=" << toString(m_spec.background)
                          << ", font_size=" << toString(m_spec.font_size)
                          << ") was unable to fit this text=\"" << m_spec.text << "\"\n";

                break;
            }
        }
    }

    void TextWindow::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_bgSprite, t_states);

        if (AvatarImage::count != m_spec.avatar_image)
        {
            t_target.draw(m_avatarSprite, t_states);
        }

        for (const sf::Text & text : m_layoutResult.texts)
        {
            t_target.draw(text, t_states);
        }
    }

    bool TextWindow::setupSizesAndPositions(const Context & t_context, const float t_baseScale)
    {
        const float scale{ t_context.screen_layout.calScaleBasedOnResolution(
            t_context, t_baseScale) };

        m_bgOuterRect.position = m_spec.position;
        m_bgOuterRect.size     = sf::Vector2f{ m_bgTexture.getSize() };
        m_bgOuterRect.size *= scale;

        const sf::FloatRect innerRectOrig{ backgroundToInnerRect(m_spec.background) };
        m_bgInnerRect.position = (m_bgOuterRect.position + (innerRectOrig.position * scale));
        m_bgInnerRect.size     = (innerRectOrig.size * scale);

        m_bgSprite.setTexture(m_bgTexture, true);
        util::fitAndCenterInside(m_bgSprite, m_bgOuterRect);

        if (AvatarImage::count != m_spec.avatar_image)
        {
            m_avatarSprite.setTexture(m_avatarTexture, true);
            m_avatarSprite.setTextureRect({ { 0, 192 }, { 64, 64 } });
            m_avatarSprite.setColor(sf::Color(255, 255, 255, 192));

            const float avatarScale{ t_context.screen_layout.calScaleBasedOnResolution(
                t_context, t_context.config.avatar_scale) };

            m_avatarSprite.setScale({ avatarScale, avatarScale });

            const sf::Vector2f offset{ m_avatarSprite.getGlobalBounds().size *
                                       sf::Vector2f{ 0.3f, 0.2f } };

            if (TextWindowBackground::PaperSmall == m_spec.background)
            {
                m_avatarSprite.setPosition(m_bgInnerRect.position - offset);

                const float pad{ offset.x * 1.5f };
                m_bgInnerRect.position.x += pad;
                m_bgInnerRect.size.x -= pad;
            }
            else if (TextWindowBackground::PaperLarge == m_spec.background)
            {
                m_avatarSprite.setPosition(
                    { (util::center(m_bgOuterRect).x -
                       (m_avatarSprite.getGlobalBounds().size.x * 0.5f)),
                      m_bgInnerRect.position.y });

                m_avatarSprite.move({ 0.0f, -(offset.y * 1.4f) });

                m_bgInnerRect.size.y = (util::bottom(m_bgInnerRect) - util::bottom(m_avatarSprite));
                m_bgInnerRect.position.y = util::bottom(m_avatarSprite);
            }
        }

        const TextLayoutSpec spec{
            m_spec.text, m_bgInnerRect, m_spec.font_size, m_spec.text_color
        };

        m_layoutResult = TextLayout::typeset(t_context, spec);

        return m_layoutResult.didTextFit();
    }

} // namespace thornberry
