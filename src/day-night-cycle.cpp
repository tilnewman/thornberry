//
// day-night-cycle.cpp
//
#include "day-night-cycle.hpp"

#include "color-range.hpp"
#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "random.hpp"
#include "screen-layout.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

namespace thornberry
{

    DayNightCycle::DayNightCycle()
        : m_texture{}
        , m_sprite{ m_texture }
        , m_cycleCoverRectangle{}
        , m_mapCoverRectangle{}
        , m_dayColor{ sf::Color::Transparent }
        , m_nightColor{ sf::Color(0, 0, 255, 80) }
    {}

    void DayNightCycle::setup(const Context & t_context)
    {
        util::TextureLoader::load(
            m_texture, (t_context.config.media_path / "image" / "day-night-cycle.png"), true);

        m_sprite.setTexture(m_texture, true);

        const sf::FloatRect mapRect{ t_context.screen_layout.mapRect() };

        m_mapCoverRectangle.setFillColor(m_nightColor);
        m_mapCoverRectangle.setPosition(mapRect.position);
        m_mapCoverRectangle.setSize(mapRect.size);

        sf::FloatRect rect;
        rect.position.x = 0.0f;
        rect.position.y = 0.0f;
        rect.size       = mapRect.position;

        util::fitAndCenterInside(m_sprite, rect);
        util::setOriginToCenter(m_sprite);
        m_sprite.scale({ 0.75f, 0.75f });
        m_sprite.move({ m_sprite.getGlobalBounds().size * 0.5f });
        m_sprite.setRotation(sf::degrees(t_context.random.fromTo(0.0f, 360.0f)));

        m_cycleCoverRectangle.setFillColor(t_context.config.background_color);

        m_cycleCoverRectangle.setPosition(
            { m_sprite.getGlobalBounds().position.x, m_sprite.getPosition().y });

        m_cycleCoverRectangle.setSize(m_sprite.getGlobalBounds().size);
    }

    void DayNightCycle::update(const Context &, const float t_elapsedSec)
    {
        m_sprite.rotate(sf::degrees(t_elapsedSec * 0.5f));
        if (m_sprite.getRotation().asDegrees() > 360.0f)
        {
            m_sprite.setRotation(sf::degrees(0.0f));
        }

        const float degrees{ m_sprite.getRotation().asDegrees() };
        if (degrees < 180.0f)
        {
            const float ratio{ degrees / 180.0f };
            const sf::Color color{ colors::blend(ratio, m_dayColor, m_nightColor) };
            m_mapCoverRectangle.setFillColor(color);
        }
        else
        {
            const float ratio{ (degrees - 180.0f) / 180.0f };
            const sf::Color color{ colors::blend(ratio, m_nightColor, m_dayColor) };
            m_mapCoverRectangle.setFillColor(color);
        }
    }

    void DayNightCycle::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        t_target.draw(m_sprite, t_states);
        t_target.draw(m_cycleCoverRectangle, t_states);

        if (t_context.level.locale() == Locale::Exterior)
        {
            t_target.draw(m_mapCoverRectangle, t_states);
        }
    }

} // namespace thornberry
