//
// anim-layer-fire.cpp
//
#include "anim-layer-fire.hpp"

#include "config.hpp"
#include "context.hpp"

namespace thornberry
{

    AnimLayerFire::AnimLayerFire(const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerFire",
              t_mapRect,
              40,
              { 64, 64 },
              0.05f,
              (t_context.config.media_path / "image" / "animation" / "fire" / "fire.png"),
              TextureSetting::Smooth)
    {}

} // namespace thornberry
