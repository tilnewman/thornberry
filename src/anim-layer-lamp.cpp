//
// anim-layer-lamp.cpp
//
#include "anim-layer-lamp.hpp"

#include "config.hpp"
#include "context.hpp"

namespace thornberry
{

    AnimLayerLampHanging::AnimLayerLampHanging(
        const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerLampHanging",
              t_mapRect,
              4,
              { 64, 32 },
              0.15f,
              (t_context.config.media_path / "image" / "animation" / "lamp" / "lamp-hanging.png"),
              TextureSetting::Smooth)
    {}

    AnimLayerLampGobletLarge::AnimLayerLampGobletLarge(
        const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerLampGobletLarge",
              t_mapRect,
              4,
              { 40, 64 },
              0.15f,
              (t_context.config.media_path / "image" / "animation" / "lamp" /
               "lamp-goblet-large.png"),
              TextureSetting::Smooth)
    {}

    AnimLayerLampGobletMedium::AnimLayerLampGobletMedium(
        const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerLampGobletMedium",
              t_mapRect,
              4,
              { 32, 56 },
              0.15f,
              (t_context.config.media_path / "image" / "animation" / "lamp" /
               "lamp-goblet-medium.png"),
              TextureSetting::Smooth)
    {}

    AnimLayerLampGobletSmall::AnimLayerLampGobletSmall(
        const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerLampGobletSmall",
              t_mapRect,
              4,
              { 32, 40 },
              0.15f,
              (t_context.config.media_path / "image" / "animation" / "lamp" /
               "lamp-goblet-small.png"),
              TextureSetting::Smooth)
    {}

    AnimLayerLampSingle::AnimLayerLampSingle(
        const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerLampSingle",
              t_mapRect,
              4,
              { 16, 36 },
              0.15f,
              (t_context.config.media_path / "image" / "animation" / "lamp" / "lamp-single.png"),
              TextureSetting::Smooth)
    {}

    AnimLayerLampTripple::AnimLayerLampTripple(
        const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerLampTripple",
              t_mapRect,
              4,
              { 40, 46 },
              0.15f,
              (t_context.config.media_path / "image" / "animation" / "lamp" / "lamp-tripple.png"),
              TextureSetting::Smooth)
    {}

    AnimLayerLampWide::AnimLayerLampWide(
        const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerLampWide",
              t_mapRect,
              4,
              { 32, 48 },
              0.15f,
              (t_context.config.media_path / "image" / "animation" / "lamp" / "lamp-wide.png"),
              TextureSetting::Smooth)
    {}

} // namespace thornberry
