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

    struct AnimLayerLampHanging final : public AnimLayerBase
    {
        AnimLayerLampHanging(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampHanging() final = default;
    };

    struct AnimLayerLampGobletLarge final : public AnimLayerBase
    {
        AnimLayerLampGobletLarge(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampGobletLarge() final = default;
    };

    struct AnimLayerLampGobletMedium final : public AnimLayerBase
    {
        AnimLayerLampGobletMedium(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampGobletMedium() final = default;
    };

    struct AnimLayerLampGobletSmall final : public AnimLayerBase
    {
        AnimLayerLampGobletSmall(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampGobletSmall() final = default;
    };

    struct AnimLayerLampSingle final : public AnimLayerBase
    {
        AnimLayerLampSingle(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampSingle() final = default;
    };

    struct AnimLayerLampTripple final : public AnimLayerBase
    {
        AnimLayerLampTripple(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampTripple() final = default;
    };

    struct AnimLayerLampWide final : public AnimLayerBase
    {
        AnimLayerLampWide(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerLampWide() final = default;
    };

} // namespace thornberry

#endif // ANIM_LAYER_LAMP_HPP_INLCUDED
