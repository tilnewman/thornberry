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
        : m_discTexture{}
        , m_discSprite{ m_discTexture }
        , m_discCoverRectangle{}
        , m_mapCoverRectangle{}
        , m_dayColor{ sf::Color::Transparent }
        , m_nightColor{}
        , m_animalCapLeftTexture{}
        , m_animalCapMiddleTexture{}
        , m_animalCapRightTexture{}
        , m_animalCapLeftSprite{ m_animalCapLeftTexture }
        , m_animalCapMiddleSprite{ m_animalCapMiddleTexture }
        , m_animalCapRightSprite{ m_animalCapRightTexture }
    {}

    void DayNightCycle::setup(const Context & t_context)
    {
        m_nightColor = t_context.config.night_map_overlay_color;

        // setup the day/night map overlay rectangle
        const sf::FloatRect mapRect{ t_context.screen_layout.mapRect() };
        m_mapCoverRectangle.setFillColor(m_nightColor);
        m_mapCoverRectangle.setPosition(mapRect.position);
        m_mapCoverRectangle.setSize(mapRect.size);

        // setup the disc image (except for random starting rotation, see comment below)
        util::TextureLoader::load(
            m_discTexture,
            (t_context.config.media_path / "image" / "day-night-cycle" / "disc.png"),
            true);

        m_discSprite.setTexture(m_discTexture, true);

        const float discScale{ t_context.screen_layout.scaleBasedOnResolution(t_context, 0.5f) };
        util::setOriginToCenter(m_discSprite);
        m_discSprite.scale({ discScale, discScale });
        
        m_discSprite.setPosition(
            { (mapRect.position.x + (mapRect.size.x * 0.5f)), mapRect.position.y * 0.9f });

        // setup the rectangle that covers up the bottom half of the disc
        m_discCoverRectangle.setFillColor(t_context.config.background_color);

        m_discCoverRectangle.setPosition(
            { m_discSprite.getGlobalBounds().position.x, m_discSprite.getPosition().y });

        m_discCoverRectangle.setSize(
            { m_discSprite.getGlobalBounds().size.x,
              (m_discSprite.getGlobalBounds().size.y * 0.5f) });

        // setup the platform and animal statue endcaps
        util::TextureLoader::load(
            m_animalCapLeftTexture,
            (t_context.config.media_path / "image" / "day-night-cycle" / "animal-cap-left.png"),
            true);

        util::TextureLoader::load(
            m_animalCapMiddleTexture,
            (t_context.config.media_path / "image" / "day-night-cycle" / "animal-cap-middle.png"),
            true);

        util::TextureLoader::load(
            m_animalCapRightTexture,
            (t_context.config.media_path / "image" / "day-night-cycle" / "animal-cap-right.png"),
            true);

        m_animalCapLeftSprite.setTexture(m_animalCapLeftTexture, true);
        m_animalCapMiddleSprite.setTexture(m_animalCapMiddleTexture, true);
        m_animalCapRightSprite.setTexture(m_animalCapRightTexture, true);

        const sf::Color animalCapColor{ 192, 192, 192 };
        m_animalCapLeftSprite.setColor(animalCapColor);
        m_animalCapMiddleSprite.setColor(animalCapColor);
        m_animalCapRightSprite.setColor(animalCapColor);

        const float animalCapScale{ t_context.screen_layout.scaleBasedOnResolution(
            t_context, 0.2f) };

        m_animalCapLeftSprite.setScale({ animalCapScale, animalCapScale });
        m_animalCapMiddleSprite.setScale({ animalCapScale, animalCapScale });
        m_animalCapRightSprite.setScale({ animalCapScale, animalCapScale });

        sf::FloatRect animalCapMiddleRect;
        animalCapMiddleRect.position = m_discCoverRectangle.getPosition();
        animalCapMiddleRect.size.x   = m_discCoverRectangle.getGlobalBounds().size.x;
        animalCapMiddleRect.size.y   = m_animalCapMiddleSprite.getGlobalBounds().size.y;
        util::scaleAndCenterInside(m_animalCapMiddleSprite, animalCapMiddleRect);

        m_animalCapLeftSprite.setPosition(
            { m_animalCapMiddleSprite.getPosition().x,
              (util::bottom(m_animalCapMiddleSprite) -
               m_animalCapLeftSprite.getGlobalBounds().size.y) });

        m_animalCapLeftSprite.move(
            { -(m_animalCapLeftSprite.getGlobalBounds().size.x * 0.5f), 0.0f });

        m_animalCapRightSprite.setPosition(
            { util::right(m_animalCapMiddleSprite),
              (util::bottom(m_animalCapMiddleSprite) -
               m_animalCapLeftSprite.getGlobalBounds().size.y) });

        m_animalCapRightSprite.move(
            { -(m_animalCapRightSprite.getGlobalBounds().size.x * 0.5f), 0.0f });

        // the discSprite width needs to be used in several calculations but those will be wrong if
        // we rotate the disc first, espcially at random, so rotate last
        m_discSprite.setRotation(sf::degrees(t_context.random.fromTo(0.0f, 360.0f)));
    }

    void DayNightCycle::update(const Context &, const float t_elapsedSec)
    {
        m_discSprite.rotate(sf::degrees(t_elapsedSec * 0.5f));
        if (m_discSprite.getRotation().asDegrees() > 360.0f)
        {
            m_discSprite.setRotation(sf::degrees(0.0f));
        }

        const float degrees{ m_discSprite.getRotation().asDegrees() };
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
            t_target.draw(m_discSprite, t_states);
            t_target.draw(m_discCoverRectangle, t_states);
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
