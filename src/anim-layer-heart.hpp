#ifndef ANIM_LAYER_HEART_HPP_INCLUDED
#define ANIM_LAYER_HEART_HPP_INCLUDED
//
// anim-layer-heart.hpp
//
#include "anim-layer-base.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace thornberry
{
    struct Context;

    //
    class AnimLayerHeart : public AnimLayerBase
    {
      public:
        AnimLayerHeart(const Context & t_context, const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerHeart() override = default;

        void dumpInfo() const override;
    };

} // namespace thornberry

#endif // ANIM_LAYER_HEART_HPP_INCLUDED
