//
// anim-layer-candleflame.cpp
//
#include "anim-layer-candleflame.hpp"

#include "config.hpp"
#include "context.hpp"

#include <iostream>

namespace thornberry
{

    AnimLayerCandleflame::AnimLayerCandleflame(const sf::FloatRect & t_mapRect)
        : AnimLayerBase(t_mapRect, 8, { 16, 32 }, 0.1f)
    {}

    void AnimLayerCandleflame::postLevelLoadSetup(const Context & t_context)
    {
        setup(
            t_context,
            (t_context.config.media_path / "image" / "animation" / "candle-flame-pixel" /
             "candle-flame-pixel.png"),
            TextureSetting::Smooth);
    }

    void AnimLayerCandleflame::dumpInfo() const
    {
        std::cout << "\tAnimLayerCandleflame\n";
    }

} // namespace thornberry
