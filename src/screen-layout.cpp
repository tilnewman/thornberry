//
// screen-layout.cpp
//
#include "screen-layout.hpp"

#include "config.hpp"
#include "context.hpp"
#include "sfml-util.hpp"

namespace thornberry
{

    ScreenLayout::ScreenLayout()
        : m_screenRect{}
        , m_mapRect{}
    {}

    void ScreenLayout::setup(const Config & t_config)
    {
        m_screenRect = sf::FloatRect{ { 0.0f, 0.0f },
                                      { static_cast<float>(t_config.video_mode.size.x),
                                        static_cast<float>(t_config.video_mode.size.y) } };

        m_mapRect = m_screenRect;
        util::scaleRectInPlace(m_mapRect, 0.45f);
    }

    float ScreenLayout::calScaleBasedOnResolution(
        const Context & t_context, const float t_scale) const
    {
        // This is the resolution on my macbook originally used when starting the game.
        // The values in settings.hpp work as is when this is the resolution.
        const float original{ std::sqrt(2056.0f * 1329.0f) };

        const float current{ std::sqrt(
            static_cast<float>(
                t_context.config.video_mode.size.x * t_context.config.video_mode.size.y)) };

        return ((t_scale * current) / original);
    }

} // namespace thornberry
