//
// window.cpp
//
#include "window.hpp"

#include "context.hpp"
#include "screen-layout.hpp"
#include "sfml-util.hpp"
#include "window-image-manager.hpp"

namespace thornberry
{

    Window::Window()
        : m_sprites{}
        , m_bgRectangle{}
        , m_bgReColorRectangle{}
        , m_scale{}
        , m_bgOffset{ 4.0f }
    {}

    const sf::FloatRect Window::setup(
        const Context & t_context, const sf::FloatRect & t_rect, const sf::Color & t_color)
    {
        const float scale{ t_context.screen_layout.calScaleBasedOnResolution(t_context, 1.5f) };
        m_scale.x = scale;
        m_scale.y = scale;

        const sf::FloatRect innerRect{ setupBackground(t_context, t_rect, t_color) };
        setupBorder(t_context, t_rect);

        return innerRect;
    }

    void Window::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_bgRectangle, t_states);

        for (const sf::Sprite & sprite : m_sprites)
        {
            t_target.draw(sprite, t_states);
        }

        t_target.draw(m_bgReColorRectangle, t_states);
    }

    void Window::setupBorder(const Context & t_context, const sf::FloatRect & t_rect)
    {
        sf::Sprite spriteTopLeft(t_context.window_image.borderTopLeft());
        spriteTopLeft.setScale(m_scale);

        sf::Sprite spriteTop(t_context.window_image.borderTop());
        spriteTop.setScale(m_scale);

        sf::Sprite spriteTopRight(t_context.window_image.borderTopRight());
        spriteTopRight.setScale(m_scale);

        const float centerWidth{ (t_rect.size.x - spriteTopLeft.getGlobalBounds().size.x) -
                                 spriteTopRight.getGlobalBounds().size.x };

        spriteTopLeft.setPosition(t_rect.position);
        {
            sf::FloatRect r;
            r.position.x = util::right(spriteTopLeft.getGlobalBounds());
            r.position.y = t_rect.position.y;
            r.size.x     = centerWidth;
            r.size.y     = spriteTop.getGlobalBounds().size.y;

            util::scaleAndCenterInside(spriteTop, r);
        }

        spriteTopRight.setPosition({ util::right(spriteTop), t_rect.position.y });

        sf::Sprite spriteBotLeft(t_context.window_image.borderBotLeft());
        spriteBotLeft.setScale(m_scale);

        const float centerHeight{ (t_rect.size.y - spriteTopLeft.getGlobalBounds().size.y) -
                                  spriteBotLeft.getGlobalBounds().size.y };

        //
        sf::Sprite spriteLeft(t_context.window_image.borderLeft());
        spriteLeft.setScale(m_scale);
        {
            sf::FloatRect r;
            r.position.x = t_rect.position.x;
            r.position.y = util::bottom(spriteTopLeft);
            r.size.x     = spriteLeft.getGlobalBounds().size.x;
            r.size.y     = centerHeight;

            util::scaleAndCenterInside(spriteLeft, r);
        }

        //
        sf::Sprite spriteRight(t_context.window_image.borderRight());
        spriteRight.setScale(m_scale);
        {
            sf::FloatRect r;

            r.position.x =
                (util::right(spriteTopRight.getGlobalBounds()) -
                 spriteRight.getGlobalBounds().size.x);

            r.position.y = spriteLeft.getPosition().y;
            r.size.x     = spriteRight.getGlobalBounds().size.x;
            r.size.y     = centerHeight;

            util::scaleAndCenterInside(spriteRight, r);
        }

        //
        spriteBotLeft.setPosition({ t_rect.position.x, util::bottom(spriteLeft) });

        //
        sf::Sprite spriteBot(t_context.window_image.borderBot());
        spriteBot.setScale(m_scale);
        {
            sf::FloatRect r;
            r.position.x = util::right(spriteBotLeft);
            r.position.y = (util::bottom(spriteBotLeft) - spriteBot.getGlobalBounds().size.y);

            r.size.x = centerWidth;
            r.size.y = spriteBot.getGlobalBounds().size.y;

            util::scaleAndCenterInside(spriteBot, r);
        }

        //
        sf::Sprite spriteBotRight(t_context.window_image.borderBotRight());
        spriteBotRight.setScale(m_scale);

        spriteBotRight.setPosition({ util::right(spriteBot), spriteBotLeft.getPosition().y });

        //
        m_sprites.emplace_back(spriteTopLeft);
        m_sprites.emplace_back(spriteTop);
        m_sprites.emplace_back(spriteTopRight);
        m_sprites.emplace_back(spriteLeft);
        m_sprites.emplace_back(spriteRight);
        m_sprites.emplace_back(spriteBotLeft);
        m_sprites.emplace_back(spriteBotRight);
        m_sprites.emplace_back(spriteBot);
    }

    const sf::FloatRect Window::setupBackground(
        const Context & t_context, const sf::FloatRect & t_rect, const sf::Color & t_color)
    {
        m_bgRectangle.setFillColor(sf::Color(75, 75, 75));
        m_bgRectangle.setPosition(t_rect.position + (sf::Vector2f{ m_bgOffset, m_bgOffset }));
        m_bgRectangle.setSize(t_rect.size - (sf::Vector2f{ m_bgOffset, m_bgOffset } * 2.0f));

        sf::Color color{t_color};
        if (sf::Color::Transparent != color)
        {
            color.a = 32;
        }
        m_bgReColorRectangle = m_bgRectangle;
        m_bgReColorRectangle.setFillColor(color);

        //
        sf::Sprite spriteTopLeft(t_context.window_image.bgTopLeft());
        sf::Sprite spriteTop(t_context.window_image.bgTop());
        sf::Sprite spriteTopRight(t_context.window_image.bgTopRight());

        const float centerWidth{ 1.0f +
                                 ((t_rect.size.x - spriteTopLeft.getGlobalBounds().size.x) -
                                  spriteTopRight.getGlobalBounds().size.x) -
                                 (m_bgOffset * 2.0f) };

        spriteTopLeft.setPosition(t_rect.position + (sf::Vector2f{ m_bgOffset, m_bgOffset }));

        {
            sf::FloatRect r;
            r.position.x = util::right(spriteTopLeft.getGlobalBounds());
            r.position.y = (t_rect.position.y + m_bgOffset);
            r.size.x     = centerWidth;
            r.size.y     = spriteTop.getGlobalBounds().size.y;

            util::scaleAndCenterInside(spriteTop, r);
        }

        spriteTopRight.setPosition({ util::right(spriteTop), t_rect.position.y + (m_bgOffset) });

        sf::Sprite spriteBotLeft(t_context.window_image.bgBotLeft());

        const float centerHeight{ ((t_rect.size.y - spriteTopLeft.getGlobalBounds().size.y) -
                                   spriteBotLeft.getGlobalBounds().size.y) -
                                  (m_bgOffset * 2.0f) };

        //
        sf::Sprite spriteLeft(t_context.window_image.bgLeft());
        {
            sf::FloatRect r;
            r.position.x = (t_rect.position.x + m_bgOffset);
            r.position.y = util::bottom(spriteTopLeft);
            r.size.x     = spriteLeft.getGlobalBounds().size.x;
            r.size.y     = centerHeight;

            util::scaleAndCenterInside(spriteLeft, r);
        }

        //
        sf::Sprite spriteRight(t_context.window_image.bgRight());
        {
            sf::FloatRect r;

            r.position.x =
                (util::right(spriteTopRight.getGlobalBounds()) -
                 spriteRight.getGlobalBounds().size.x);

            r.position.y = spriteLeft.getPosition().y;
            r.size.x     = spriteRight.getGlobalBounds().size.x;
            r.size.y     = centerHeight;

            util::scaleAndCenterInside(spriteRight, r);
        }

        //
        spriteBotLeft.setPosition({ (t_rect.position.x + m_bgOffset), util::bottom(spriteLeft) });

        //
        sf::Sprite spriteBot(t_context.window_image.bgBot());
        {
            sf::FloatRect r;
            r.position.x = util::right(spriteBotLeft);
            r.position.y = (util::bottom(spriteBotLeft) - spriteBot.getGlobalBounds().size.y);
            r.size.x     = centerWidth;
            r.size.y     = spriteBot.getGlobalBounds().size.y;

            util::scaleAndCenterInside(spriteBot, r);
        }

        //
        sf::Sprite spriteBotRight(t_context.window_image.bgBotRight());
        spriteBotRight.setPosition({ util::right(spriteBot), spriteBotLeft.getPosition().y });

        m_sprites.emplace_back(spriteTopLeft);
        m_sprites.emplace_back(spriteTop);
        m_sprites.emplace_back(spriteTopRight);
        m_sprites.emplace_back(spriteLeft);
        m_sprites.emplace_back(spriteRight);
        m_sprites.emplace_back(spriteBotLeft);
        m_sprites.emplace_back(spriteBotRight);
        m_sprites.emplace_back(spriteBot);

        sf::FloatRect innerRect(m_bgRectangle.getPosition(), m_bgRectangle.getSize());
        innerRect.position += spriteTopLeft.getGlobalBounds().size;
        innerRect.size -= (spriteTopLeft.getGlobalBounds().size * 2.0f);
        return innerRect;
    }

} // namespace thornberry
