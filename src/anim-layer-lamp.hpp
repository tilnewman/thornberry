#ifndef ANIM_LAYER_LAMP_LAYER_HPP_INLCUDED
#define ANIM_LAYER_LAMP_LAYER_HPP_INLCUDED
//
// anim-layer-lamp.hpp
//
#include "anim-layer-base.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace thornberry
{

    struct Context;

    //
    class AnimLayerLampHanging : public AnimLayerBase
    {
      public:
        AnimLayerLampHanging(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampHanging() override = default;
    };

    //
    class AnimLayerLampGobletLarge : public AnimLayerBase
    {
      public:
        AnimLayerLampGobletLarge(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampGobletLarge() override = default;
    };

    //
    class AnimLayerLampGobletMedium : public AnimLayerBase
    {
      public:
        AnimLayerLampGobletMedium(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampGobletMedium() override = default;
    };

    //
    class AnimLayerLampGobletSmall : public AnimLayerBase
    {
      public:
        AnimLayerLampGobletSmall(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampGobletSmall() override = default;
    };

    //
    class AnimLayerLampSingle : public AnimLayerBase
    {
      public:
        AnimLayerLampSingle(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampSingle() override = default;
    };

    //
    class AnimLayerLampTripple : public AnimLayerBase
    {
      public:
        AnimLayerLampTripple(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampTripple() override = default;
    };

    //
    class AnimLayerLampWide : public AnimLayerBase
    {
      public:
        AnimLayerLampWide(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampWide() override = default;
    };

} // namespace thornberry

#endif // ANIM_LAYER_LAMP_LAYER_HPP_INLCUDED
