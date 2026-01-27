//
// anim-layer-campfire.cpp
//
#include "anim-layer-campfire.hpp"

#include "config.hpp"
#include "context.hpp"
#include "smoke-particle.hpp"

namespace thornberry
{

    AnimLayerCampfire::AnimLayerCampfire(const Context & t_context, const sf::FloatRect & t_mapRect)
        : AnimLayerBase(
              "AnimLayerCampfire",
              t_mapRect,
              8,
              { 32, 32 },
              0.05f,
              (t_context.config.media_path / "image" / "animation" / "campfire" / "campfire.png"),
              TextureSetting::Smooth)
    {}

    void AnimLayerCampfire::postLevelLoadSetup(const Context & t_context)
    {
        AnimLayerBase::postLevelLoadSetup(t_context);
        t_context.smoke.add(t_context, m_offscreenRect);
    }

} // namespace thornberry
