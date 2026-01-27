#ifndef ANIM_LAYER_FIRE_HPP_INLCUDED
#define ANIM_LAYER_FIRE_HPP_INLCUDED
//
// anim-layer-fire.hpp
//
#include "anim-layer-base.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace thornberry
{

    struct Context;

    //
    struct AnimLayerFire : public AnimLayerBase
    {
        AnimLayerFire(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerFire() override = default;
    };

} // namespace thornberry

#endif // ANIM_LAYER_FIRE_HPP_INLCUDED
