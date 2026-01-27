#ifndef ANIM_LAYER_LAMP_HPP_INLCUDED
#define ANIM_LAYER_LAMP_HPP_INLCUDED
//
// anim-layer-lamp.hpp
//
#include "anim-layer-base.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace thornberry
{

    struct Context;

    //

    struct AnimLayerLampHanging : public AnimLayerBase
    {
        AnimLayerLampHanging(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampHanging() override = default;
    };

    struct AnimLayerLampGobletLarge : public AnimLayerBase
    {
        AnimLayerLampGobletLarge(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampGobletLarge() override = default;
    };

    struct AnimLayerLampGobletMedium : public AnimLayerBase
    {
        AnimLayerLampGobletMedium(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampGobletMedium() override = default;
    };

    struct AnimLayerLampGobletSmall : public AnimLayerBase
    {
        AnimLayerLampGobletSmall(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampGobletSmall() override = default;
    };

    struct AnimLayerLampSingle : public AnimLayerBase
    {
        AnimLayerLampSingle(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampSingle() override = default;
    };

    struct AnimLayerLampTripple : public AnimLayerBase
    {
        AnimLayerLampTripple(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampTripple() override = default;
    };

    struct AnimLayerLampWide : public AnimLayerBase
    {
        AnimLayerLampWide(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampWide() override = default;
    };

} // namespace thornberry

#endif // ANIM_LAYER_LAMP_HPP_INLCUDED
