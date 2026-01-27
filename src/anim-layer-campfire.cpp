//
// anim-layer-campfire.cpp
//
#include "anim-layer-campfire.hpp"

#include "config.hpp"
#include "context.hpp"

namespace thornberry
{

    AnimLayerCampfire::AnimLayerCampfire(const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerCampfire",
              t_mapRect,
              8,
              { 32, 32 },
              0.05f,
              (t_context.config.media_path / "image" / "animation" / "campfire" / "campfire.png"),
              TextureSetting::Smooth)
    {}

} // namespace thornberry
