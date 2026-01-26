#ifndef FRAMERATE_HPP_INCLUDED
#define FRAMERATE_HPP_INCLUDED
//
// framerate.hpp
//
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace thornberry
{
    struct Context;

    //
    class FrameRateDisplay
    {
      public:
        FrameRateDisplay();

        void setup(const Context & t_context);
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const;

      private:
        sf::Text m_text;
        float m_elapsedSec;
        std::size_t m_frameCount;
    };

} // namespace thornberry

#endif // FRAMERATE_HPP_INCLUDED
