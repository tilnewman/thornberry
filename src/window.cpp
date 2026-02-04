//
// window.cpp
//
#include "window.hpp"

#include "context.hpp"
#include "sfml-util.hpp"
#include "window-image-manager.hpp"

namespace thornberry
{

    Window::Window()
        : m_sprites{}
        , m_bgRectangle{}
    {}

    void Window::setup(const Context & t_context, const sf::FloatRect & t_rect)
    {
        setupBackground(t_context, t_rect);
        setupBorder(t_context, t_rect);
    }

    void Window::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_bgRectangle, t_states);

        for (const sf::Sprite & sprite : m_sprites)
        {
            t_target.draw(sprite, t_states);
        }
    }

    void Window::setupBorder(const Context & t_context, const sf::FloatRect & t_rect)
    {
        sf::Sprite spriteBorderTopLeft(t_context.window_image.borderTopLeft());
        sf::Sprite spriteBorderTop(t_context.window_image.borderTop());
        sf::Sprite spriteBorderTopRight(t_context.window_image.borderTopRight());

        const float centerWidth{ (t_rect.size.x - spriteBorderTopLeft.getGlobalBounds().size.x) -
                                 spriteBorderTopRight.getGlobalBounds().size.x };

        spriteBorderTopLeft.setPosition(t_rect.position);

        {
            sf::FloatRect r;
            r.position.x = util::right(spriteBorderTopLeft.getGlobalBounds());
            r.position.y = t_rect.position.y;
            r.size.x     = centerWidth;
            r.size.y     = spriteBorderTop.getGlobalBounds().size.y;

            util::scaleAndCenterInside(spriteBorderTop, r);
        }

        spriteBorderTopRight.setPosition({ util::right(spriteBorderTop), t_rect.position.y });

        const float centerHeight{ (t_rect.size.y - spriteBorderTopLeft.getGlobalBounds().size.y) -
                                  spriteBorderTopRight.getGlobalBounds().size.y };

        //
        sf::Sprite spriteBorderLeft(t_context.window_image.borderLeft());

        {
            sf::FloatRect r;
            r.position.x = t_rect.position.x;
            r.position.y = util::bottom(spriteBorderTopLeft);
            r.size.x     = spriteBorderLeft.getGlobalBounds().size.x;
            r.size.y     = centerHeight;

            util::scaleAndCenterInside(spriteBorderLeft, r);
        }

        //
        sf::Sprite spriteBorderRight(t_context.window_image.borderRight());

        {
            sf::FloatRect r;

            r.position.x =
                (util::right(spriteBorderTopRight.getGlobalBounds()) -
                 spriteBorderRight.getGlobalBounds().size.x);

            r.position.y = spriteBorderLeft.getPosition().y;
            r.size.x     = spriteBorderRight.getGlobalBounds().size.x;
            r.size.y     = centerHeight;

            util::scaleAndCenterInside(spriteBorderRight, r);
        }

        //
        sf::Sprite spriteBorderBotLeft(t_context.window_image.borderBotLeft());
        spriteBorderBotLeft.setPosition({ t_rect.position.x, util::bottom(spriteBorderLeft) });

        //
        sf::Sprite spriteBorderBot(t_context.window_image.borderBot());

        {
            sf::FloatRect r;
            r.position.x = util::right(spriteBorderBotLeft);

            r.position.y =
                (util::bottom(spriteBorderBotLeft) - spriteBorderBot.getGlobalBounds().size.y);

            r.size.x = centerWidth;
            r.size.y = spriteBorderBot.getGlobalBounds().size.y;

            util::scaleAndCenterInside(spriteBorderBot, r);
        }

        //
        sf::Sprite spriteBorderBotRight(t_context.window_image.borderBotRight());

        spriteBorderBotRight.setPosition(
            { util::right(spriteBorderBot), spriteBorderBotLeft.getPosition().y });

        //
        m_sprites.emplace_back(spriteBorderTopLeft);
        m_sprites.emplace_back(spriteBorderTop);
        m_sprites.emplace_back(spriteBorderTopRight);
        m_sprites.emplace_back(spriteBorderLeft);
        m_sprites.emplace_back(spriteBorderRight);
        m_sprites.emplace_back(spriteBorderBotLeft);
        m_sprites.emplace_back(spriteBorderBotRight);
        m_sprites.emplace_back(spriteBorderBot);
    }

    void Window::setupBackground(const Context & t_context, const sf::FloatRect & t_rect)
    {
        m_bgRectangle.setFillColor(sf::Color(74, 76, 35));
        m_bgRectangle.setPosition(t_rect.position + sf::Vector2f{ 4.0f, 4.0f });
        m_bgRectangle.setSize(t_rect.size - sf::Vector2f{ 8.0f, 8.0f });

        //
        sf::Sprite spriteBgTopLeft(t_context.window_image.bgTopLeft());
        sf::Sprite spriteBgTop(t_context.window_image.bgTop());
        sf::Sprite spriteBgTopRight(t_context.window_image.bgTopRight());

        const float centerWidth{ ((t_rect.size.x - spriteBgTopLeft.getGlobalBounds().size.x) -
                                  spriteBgTopRight.getGlobalBounds().size.x) -
                                 8.0f };

        spriteBgTopLeft.setPosition(t_rect.position + sf::Vector2f{ 4.0f, 4.0f });

        {
            sf::FloatRect r;
            r.position.x = util::right(spriteBgTopLeft.getGlobalBounds());
            r.position.y = t_rect.position.y + 4.0f;
            r.size.x     = centerWidth;
            r.size.y     = spriteBgTop.getGlobalBounds().size.y;

            util::scaleAndCenterInside(spriteBgTop, r);
        }

        spriteBgTopRight.setPosition({ util::right(spriteBgTop), t_rect.position.y + 4.0f });

        const float centerHeight{ ((t_rect.size.y - spriteBgTopLeft.getGlobalBounds().size.y) -
                                   spriteBgTopRight.getGlobalBounds().size.y) -
                                  3.0f };

        //
        sf::Sprite spriteBgLeft(t_context.window_image.bgLeft());

        {
            sf::FloatRect r;
            r.position.x = t_rect.position.x + 4.0f;
            r.position.y = util::bottom(spriteBgTopLeft);
            r.size.x     = spriteBgLeft.getGlobalBounds().size.x;
            r.size.y     = centerHeight;

            util::scaleAndCenterInside(spriteBgLeft, r);
        }

        //
        sf::Sprite spriteBgRight(t_context.window_image.bgRight());

        {
            sf::FloatRect r;

            r.position.x =
                (util::right(spriteBgTopRight.getGlobalBounds()) -
                 spriteBgRight.getGlobalBounds().size.x);

            r.position.y = spriteBgLeft.getPosition().y;
            r.size.x     = spriteBgRight.getGlobalBounds().size.x;
            r.size.y     = centerHeight;

            util::scaleAndCenterInside(spriteBgRight, r);
        }

        //
        sf::Sprite spriteBgBotLeft(t_context.window_image.bgBotLeft());
        spriteBgBotLeft.setPosition({ (t_rect.position.x + 4.0f), util::bottom(spriteBgLeft) });

        //
        sf::Sprite spriteBgBot(t_context.window_image.bgBot());

        {
            sf::FloatRect r;
            r.position.x = util::right(spriteBgBotLeft);
            r.position.y = (util::bottom(spriteBgBotLeft) - spriteBgBot.getGlobalBounds().size.y);
            r.size.x     = centerWidth;
            r.size.y     = spriteBgBot.getGlobalBounds().size.y;

            util::scaleAndCenterInside(spriteBgBot, r);
        }

        //
        sf::Sprite spriteBgBotRight(t_context.window_image.bgBotRight());

        spriteBgBotRight.setPosition({ util::right(spriteBgBot), spriteBgBotLeft.getPosition().y });

        m_sprites.emplace_back(spriteBgTopLeft);
        m_sprites.emplace_back(spriteBgTop);
        m_sprites.emplace_back(spriteBgTopRight);
        m_sprites.emplace_back(spriteBgLeft);
        m_sprites.emplace_back(spriteBgRight);
        m_sprites.emplace_back(spriteBgBotLeft);
        m_sprites.emplace_back(spriteBgBotRight);
        m_sprites.emplace_back(spriteBgBot);
    }

} // namespace thornberry
