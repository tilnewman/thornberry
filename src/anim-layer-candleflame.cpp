//
// anim-layer-candleflame.cpp
//
#include "anim-layer-candleflame.hpp"

#include "config.hpp"
#include "context.hpp"

#include <iostream>

namespace thornberry
{

    AnimLayerCandleflame::AnimLayerCandleflame(
        const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerCandleflame",
              t_mapRect,
              8,
              { 16, 32 },
              0.1f,
              (t_context.config.media_path / "image" / "animation" / "candle-flame-pixel" /
               "candle-flame-pixel.png"),
              TextureSetting::Smooth)
    {}

} // namespace thornberry
