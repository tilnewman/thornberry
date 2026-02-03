#ifndef DAY_NIGHT_CYCLE_HPP_INCLUDED
#define DAY_NIGHT_CYCLE_HPP_INCLUDED
//
// day-night-cycle.hpp
//
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace thornberry
{

    struct Config;
    struct Context;

    //
    class DayNightCycle
    {
      public:
        DayNightCycle();

        void setup(const Context & t_context);
        void update(const Context & t_context, const float t_elapsedSec);

        void drawBeforeMap(
            sf::RenderTarget & t_target,
            sf::RenderStates & t_states) const;

        void drawAfterMap(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates & t_states) const;

      private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::RectangleShape m_cycleCoverRectangle;
        sf::RectangleShape m_mapCoverRectangle;
        sf::Color m_dayColor;
        sf::Color m_nightColor;
    };

} // namespace thornberry

#endif // DAY_NIGHT_CYCLE_HPP_INCLUDED
