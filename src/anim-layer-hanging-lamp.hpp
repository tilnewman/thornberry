#ifndef ANIM_LAYER_HANGING_LAMP_LAYER_HPP_INLCUDED
#define ANIM_LAYER_HANGING_LAMP_LAYER_HPP_INLCUDED
//
// anim-layer-hanging-lamp.hpp
//
#include "anim-layer-base.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace thornberry
{

    struct Context;

    //
    class AnimLayerHangingLamp : public AnimLayerBase
    {
      public:
        AnimLayerHangingLamp(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerHangingLamp() override = default;

        void dumpInfo() const override;
    };

} // namespace thornberry

#endif // ANIM_LAYER_HANGING_LAMP_LAYER_HPP_INLCUDED
