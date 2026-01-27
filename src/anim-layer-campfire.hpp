#ifndef ANIM_LAYER_CAMPFIRE_HPP_INLCUDED
#define ANIM_LAYER_CAMPFIRE_HPP_INLCUDED
//
// anim-layer-campfire.hpp
//
#include "anim-layer-base.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace thornberry
{

    struct Context;

    //
    struct AnimLayerCampfire : public AnimLayerBase
    {
        AnimLayerCampfire(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerCampfire() override = default;
    };

} // namespace thornberry

#endif // ANIM_LAYER_CAMPFIRE_HPP_INLCUDED
