#ifndef PREDRAW_ANIMATIONS_HPP_INLCUDED
#define PREDRAW_ANIMATIONS_HPP_INLCUDED
//
// predraw-animations.hpp
//
#include "anim-acid-spout.hpp"
#include "anim-lightning.hpp"
#include "anim-metal-trap.hpp"
#include "anim-plant-trap.hpp"
#include "music-particle.hpp"
#include "sparkle-particle.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace thornberry
{
    struct Config;
    struct Context;

    //
    class PredrawAnimations
    {
      public:
        PredrawAnimations();

        AcidSpoutAnimationManager & acidTrap() { return m_acidSpoutAnimationManager; }
        LightningAnimationManager & lightningTrap() { return m_lightningAnimationManager; }
        MetalTrapAnimationManager & metalTrap() { return m_metalTrapAnimationManager; }
        PlantTrapAnimationManager & plantTrap() { return m_plantTrapAnimationManager; }
        MusicParticleManager & music() { return m_musicParticleManager; }
        SparkleParticleEffects & sparkle() { return m_sparkleParticleManager; }

        void setup(const Config & t_config);
        void clear();
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void move(const sf::Vector2f & t_move);
        void postLevelLoadSetup(const Context & t_context);

      private:
        AcidSpoutAnimationManager m_acidSpoutAnimationManager;
        LightningAnimationManager m_lightningAnimationManager;
        MetalTrapAnimationManager m_metalTrapAnimationManager;
        PlantTrapAnimationManager m_plantTrapAnimationManager;
        MusicParticleManager m_musicParticleManager;
        SparkleParticleEffects m_sparkleParticleManager;
    };

} // namespace thornberry

#endif // PREDRAW_ANIMATIONS_HPP_INLCUDED
