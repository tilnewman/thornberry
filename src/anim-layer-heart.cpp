//
// anim-layer-heart.cpp
//
#include "anim-layer-heart.hpp"

#include "config.hpp"
#include "context.hpp"

#include <iostream>

namespace thornberry
{

    AnimLayerHeart::AnimLayerHeart(const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              t_mapRect,
              10,
              { 32, 32 },
              0.15f,
              (t_context.config.media_path / "image" / "animation" / "pickup" / "heart.png"),
              TextureSetting::Smooth)
    {}

    void AnimLayerHeart::dumpInfo() const { std::cout << "\tAnimLayerHeart\n"; }

} // namespace thornberry
