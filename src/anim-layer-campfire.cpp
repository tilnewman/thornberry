//
// anim-layer-campfire.cpp
//
#include "anim-layer-campfire.hpp"

#include "config.hpp"
#include "context.hpp"

#include <iostream>

namespace thornberry
{

    //
    AnimLayerCampfire::AnimLayerCampfire(const sf::FloatRect & t_mapRect)
        : AnimLayerBase(t_mapRect, 40, { 64, 64 }, 0.05f)
    {}

    void AnimLayerCampfire::postLevelLoadSetup(const Context & t_context)
    {
        setup(
            t_context,
            (t_context.config.media_path / "image" / "animation" / "campfire" / "campfire.png"),
            TextureSetting::Smooth);
    }

    void AnimLayerCampfire::dumpInfo() const { std::cout << "\tAnimLayerCampfire\n"; }

} // namespace thornberry
