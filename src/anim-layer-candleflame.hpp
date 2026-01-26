#ifndef ANIM_LAYER_CANDLEFLAME_LAYER_HPP_INLCUDED
#define ANIM_LAYER_CANDLEFLAME_LAYER_HPP_INLCUDED
//
// anim-layer-candleflame.hpp
//
#include "anim-layer-base.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace thornberry
{

    struct Context;

    //
    class AnimLayerCandleflame : public AnimLayerBase
    {
      public:
        AnimLayerCandleflame(const sf::FloatRect & t_mapRect);
        virtual ~AnimLayerCandleflame() override = default;

        void postLevelLoadSetup(const Context & t_context) override;
        void dumpInfo() const override;
    };

} // namespace thornberry

#endif // ANIM_LAYER_CANDLEFLAME_LAYER_HPP_INLCUDED
