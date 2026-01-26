//
// framerate.cpp
//
#include "framerate.hpp"

#include "avatar.hpp"
#include "context.hpp"
#include "font.hpp"
#include "indirect-level.hpp"
#include "screen-layout.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"

#include <string>

namespace thornberry
{

    FrameRateDisplay::FrameRateDisplay()
        : m_text{ util::SfmlDefaults::instance().font() }
        , m_elapsedSec{ 0.0f }
        , m_frameCount{ 0 }
    {}

    void FrameRateDisplay::setup(const Context & t_context)
    {
        m_text = t_context.font.makeText(FontSize::Medium, "");
    }

    void FrameRateDisplay::update(const Context & t_context, const float t_elapsedSec)
    {
        ++m_frameCount;
        m_elapsedSec += t_elapsedSec;
        if (m_elapsedSec > 1.0f)
        {
            const float framesPerSec{ static_cast<float>(m_frameCount) / m_elapsedSec };

            m_frameCount = 0;
            m_elapsedSec -= 1.0f;

            std::string str{ "fps: " };
            str += std::to_string(static_cast<int>(framesPerSec));
            str += ", ";
            str += t_context.level.name();
            str += ", ";
            str += toString(t_context.avatar.image());

            m_text.setString(str);
            util::setOriginToPosition(m_text);

            m_text.setPosition(
                { 0.0f,
                  (t_context.screen_layout.screenRect().size.y -
                   m_text.getGlobalBounds().size.y) });
        }
    }

    void FrameRateDisplay::draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        t_target.draw(m_text, t_states);
    }

} // namespace thornberry
