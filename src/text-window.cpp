//
// text-window.cpp
//
#include "text-window.hpp"

#include "avatar-image-manager.hpp"
#include "config.hpp"
#include "context.hpp"
#include "random.hpp"
#include "screen-layout.hpp"
#include "sfml-defaults.hpp"
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
        , m_imageRect{}
        , m_textRect{}
        , m_layoutResult{}
        , m_buttonText{ util::SfmlDefaults::instance().font() }
        , m_isOpen{ true }
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

        // randomize window position if invalid
        if ((m_spec.position.x < 0.0f) || (m_spec.position.y < 0.0f))
        {
            const sf::FloatRect mapRect{ t_context.screen_layout.mapRect() };
            m_spec.position.x = mapRect.position.x + t_context.random.zeroTo(mapRect.size.x * 0.5f);
            m_spec.position.y = mapRect.position.y + t_context.random.zeroTo(mapRect.size.y * 0.5f);
        }

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

        m_buttonText = t_context.font.makeText(
            FontSize::Medium, "<close>", t_context.config.text_button_color);

        m_buttonText.setStyle(sf::Text::Bold);
        util::setOriginToPosition(m_buttonText);

        // keep trying larger and larger paper image backgrounds until one fits all the text
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
        t_target.draw(m_buttonText, t_states);

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

        // the outer rect that defines where the background image will be
        m_imageRect.position = m_spec.position;
        m_imageRect.size     = sf::Vector2f{ m_bgTexture.getSize() };
        m_imageRect.size *= scale;

        // if the window is partially offscreen then push it back
        const sf::FloatRect screenRect{ t_context.screen_layout.screenRect() };

        if (util::right(m_imageRect) > util::right(screenRect))
        {
            const float offset{ util::right(m_imageRect) - util::right(screenRect) };
            m_imageRect.position.x -= offset;
        }

        if (util::bottom(m_imageRect) > util::bottom(screenRect))
        {
            const float offset{ util::bottom(m_imageRect) - util::bottom(screenRect) };
            m_imageRect.position.y -= offset;
        }

        // the inner rect that defines where the text will be
        const sf::FloatRect innerRectOrig{ backgroundToInnerRect(m_spec.background) };
        m_textRect.position = (m_imageRect.position + (innerRectOrig.position * scale));
        m_textRect.size     = (innerRectOrig.size * scale);

        m_bgSprite.setTexture(m_bgTexture, true);
        util::fitAndCenterInside(m_bgSprite, m_imageRect);

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
                m_avatarSprite.setPosition(m_textRect.position - offset);

                const float pad{ offset.x * 1.5f };
                m_textRect.position.x += pad;
                m_textRect.size.x -= pad;
            }
            else if (TextWindowBackground::PaperLarge == m_spec.background)
            {
                m_avatarSprite.setPosition(
                    { (util::center(m_imageRect).x -
                       (m_avatarSprite.getGlobalBounds().size.x * 0.5f)),
                      m_textRect.position.y });

                m_avatarSprite.move({ 0.0f, -(offset.y * 1.4f) });

                m_textRect.size.y     = (util::bottom(m_textRect) - util::bottom(m_avatarSprite));
                m_textRect.position.y = util::bottom(m_avatarSprite);
            }
        }

        // place button at the bottom
        m_buttonText.setPosition(
            { (util::center(m_imageRect).x - (m_buttonText.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_textRect) - m_buttonText.getGlobalBounds().size.y) });

        // prevent text from overlapping with the button
        m_textRect.size.y -= (m_buttonText.getGlobalBounds().size.y * 1.2f);

        // see if the text fits in the inner rect
        const TextLayoutSpec spec{ m_spec.text, m_textRect, m_spec.font_size, m_spec.text_color };
        m_layoutResult = TextLayout::typeset(t_context, spec);
        return m_layoutResult.didTextFit();
    }

    bool TextWindow::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyReleasedPtr = t_event.getIf<sf::Event::KeyReleased>())
        {
            if (keyReleasedPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                m_isOpen = false;
            }
        }
        else if (const auto * mouseButtonPtr = t_event.getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseButtonPtr->button == sf::Mouse::Button::Left)
            {
                const sf::Vector2f position{ mouseButtonPtr->position };
                if (m_buttonText.getGlobalBounds().contains(position))
                {
                    m_isOpen = false;
                }
            }
        }
        else if (const auto * mouseMovedPtr = t_event.getIf<sf::Event::MouseMoved>())
        {
            const sf::Vector2f position{ mouseMovedPtr->position };
            if (m_buttonText.getGlobalBounds().contains(position))
            {
                m_buttonText.setFillColor(t_context.config.text_button_mouseover_color);
            }
            else
            {
                m_buttonText.setFillColor(t_context.config.text_button_color);
            }
        }

        return !m_isOpen;
    }

    void TextWindow::setFocusOn(const Context & t_context)
    {
        m_bgSprite.setColor(t_context.config.text_window_focus_on_color);
        m_avatarSprite.setColor(t_context.config.text_window_focus_on_color);
    }

    void TextWindow::setFocusOff(const Context & t_context)
    {
        m_bgSprite.setColor(t_context.config.text_window_focus_off_color);
        m_avatarSprite.setColor(t_context.config.text_window_focus_off_color);
    }

} // namespace thornberry
