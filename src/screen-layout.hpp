#ifndef SCREEN_LAYOUT_HPP_INCLUDED
#define SCREEN_LAYOUT_HPP_INCLUDED
//
// screen-layout.hpp
//
#include "config.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace thornberry
{

    struct Context;

    //
    class ScreenLayout
    {
      public:
        ScreenLayout();

        void setup(const Config & t_config);

        [[nodiscard]] const sf::FloatRect & screenRect() const noexcept { return m_screenRect; }
        [[nodiscard]] const sf::FloatRect & mapRect() const noexcept { return m_mapRect; }

        float calScaleBasedOnResolution(const Context & t_context, const float t_scale) const;

      private:
        sf::FloatRect m_screenRect;
        sf::FloatRect m_mapRect;
    };

} // namespace thornberry

#endif // SCREEN_LAYOUT_HPP_INCLUDED
