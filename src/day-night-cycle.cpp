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
        , m_animalCapLeftTexture{}
        , m_animalCapMiddleTexture{}
        , m_animalCapRightTexture{}
        , m_animalCapLeftSprite{ m_animalCapLeftTexture }
        , m_animalCapMiddleSprite{ m_animalCapMiddleTexture }
        , m_animalCapRightSprite{ m_animalCapRightTexture }
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
        m_sprite.scale({ 0.65f, 0.65f });
        m_sprite.setRotation(sf::degrees(t_context.random.fromTo(0.0f, 360.0f)));

        m_sprite.setPosition(
            { (mapRect.position.x + (mapRect.size.x * 0.5f)), mapRect.position.y * 0.9f });

        m_cycleCoverRectangle.setFillColor(t_context.config.background_color);

        m_cycleCoverRectangle.setPosition(
            { m_sprite.getGlobalBounds().position.x, m_sprite.getPosition().y });

        m_cycleCoverRectangle.setSize(
            { m_sprite.getGlobalBounds().size.x, (m_sprite.getGlobalBounds().size.y * 0.5f) });

        util::TextureLoader::load(
            m_animalCapLeftTexture,
            (t_context.config.media_path / "image" / "animal-cap" / "animal-cap-left.png"),
            true);

        util::TextureLoader::load(
            m_animalCapMiddleTexture,
            (t_context.config.media_path / "image" / "animal-cap" / "animal-cap-middle.png"),
            true);

        util::TextureLoader::load(
            m_animalCapRightTexture,
            (t_context.config.media_path / "image" / "animal-cap" / "animal-cap-right.png"),
            true);

        m_animalCapLeftSprite.setTexture(m_animalCapLeftTexture, true);
        m_animalCapMiddleSprite.setTexture(m_animalCapMiddleTexture, true);
        m_animalCapRightSprite.setTexture(m_animalCapRightTexture, true);

        const sf::Color animalCapColor{ 192, 192, 192 };
        m_animalCapLeftSprite.setColor(animalCapColor);
        m_animalCapMiddleSprite.setColor(animalCapColor);
        m_animalCapRightSprite.setColor(animalCapColor);

        const float animalCapScale{ t_context.screen_layout.calScaleBasedOnResolution(
            t_context, 0.2f) };

        m_animalCapLeftSprite.setScale({ animalCapScale, animalCapScale });
        m_animalCapMiddleSprite.setScale({ animalCapScale, animalCapScale });
        m_animalCapRightSprite.setScale({ animalCapScale, animalCapScale });

        sf::FloatRect animalCapMiddleRect;
        animalCapMiddleRect.position = m_cycleCoverRectangle.getPosition();
        animalCapMiddleRect.size.x   = m_cycleCoverRectangle.getGlobalBounds().size.x;
        animalCapMiddleRect.size.y   = m_animalCapMiddleSprite.getGlobalBounds().size.y;
        util::scaleAndCenterInside(m_animalCapMiddleSprite, animalCapMiddleRect);

        m_animalCapLeftSprite.setPosition(
            { (m_animalCapMiddleSprite.getPosition().x -
               (m_animalCapLeftSprite.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_animalCapMiddleSprite) -
               m_animalCapLeftSprite.getGlobalBounds().size.y) });

        m_animalCapRightSprite.setPosition(
            { (util::right(m_animalCapMiddleSprite) -
               (m_animalCapRightSprite.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_animalCapMiddleSprite) -
               m_animalCapLeftSprite.getGlobalBounds().size.y) });
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

    void DayNightCycle::drawBeforeMap(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        if (t_context.level.locale() == Locale::Exterior)
        {
            t_target.draw(m_sprite, t_states);
            t_target.draw(m_cycleCoverRectangle, t_states);
            t_target.draw(m_animalCapLeftSprite, t_states);
            t_target.draw(m_animalCapMiddleSprite, t_states);
            t_target.draw(m_animalCapRightSprite, t_states);
        }
    }

    void DayNightCycle::drawAfterMap(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        if (t_context.level.locale() == Locale::Exterior)
        {
            t_target.draw(m_mapCoverRectangle, t_states);
        }
    }

} // namespace thornberry
