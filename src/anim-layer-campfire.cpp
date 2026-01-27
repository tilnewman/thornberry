//
// anim-layer-campfire.cpp
//
#include "anim-layer-campfire.hpp"

#include "config.hpp"
#include "context.hpp"

#include <iostream>

namespace thornberry
{

    AnimLayerCampfire::AnimLayerCampfire(const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerCampfire",
              t_mapRect,
              40,
              { 64, 64 },
              0.05f,
              (t_context.config.media_path / "image" / "animation" / "campfire" / "campfire.png"),
              TextureSetting::Smooth)
    {}

} // namespace thornberry
