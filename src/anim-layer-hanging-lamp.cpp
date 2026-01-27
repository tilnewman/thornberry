//
// anim-layer-hanging-lamp.cpp
//
#include "anim-layer-hanging-lamp.hpp"

#include "config.hpp"
#include "context.hpp"

namespace thornberry
{

    AnimLayerHangingLamp::AnimLayerHangingLamp(
        const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerHangingLamp",
              t_mapRect,
              4,
              { 64, 32 },
              0.15f,
              (t_context.config.media_path / "image" / "animation" / "lamp" / "lamp-hanging.png"),
              TextureSetting::Smooth)
    {}

    

} // namespace thornberry
