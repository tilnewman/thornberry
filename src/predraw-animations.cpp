//
// predraw-animations.cpp
//
#include "predraw-animations.hpp"

namespace thornberry
{

    PredrawAnimations::PredrawAnimations()
        : m_acidSpoutAnimationManager{}
        , m_lightningAnimationManager{}
        , m_metalTrapAnimationManager{}
        , m_plantTrapAnimationManager{}
        , m_musicParticleManager{}
        , m_sparkleParticleManager{}
    {}

    void PredrawAnimations::setup(const Config & t_config)
    {
        m_acidSpoutAnimationManager.setup(t_config);
        m_lightningAnimationManager.setup(t_config);
        m_metalTrapAnimationManager.setup(t_config);
        m_plantTrapAnimationManager.setup(t_config);
        m_musicParticleManager.setup(t_config);
        m_sparkleParticleManager.setup(t_config);
    }

    void PredrawAnimations::clear()
    {
        m_acidSpoutAnimationManager.clear();
        m_lightningAnimationManager.clear();
        m_metalTrapAnimationManager.clear();
        m_plantTrapAnimationManager.clear();
        m_musicParticleManager.clear();
        m_sparkleParticleManager.clear();
    }

    void PredrawAnimations::update(const Context & t_context, const float t_elapsedSec)
    {
        m_acidSpoutAnimationManager.update(t_context, t_elapsedSec);
        m_lightningAnimationManager.update(t_context, t_elapsedSec);
        m_metalTrapAnimationManager.update(t_context, t_elapsedSec);
        m_plantTrapAnimationManager.update(t_context, t_elapsedSec);
        m_musicParticleManager.update(t_context, t_elapsedSec);
        m_sparkleParticleManager.update(t_context, t_elapsedSec);
    }

    void PredrawAnimations::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        m_acidSpoutAnimationManager.draw(t_target, t_states);
        m_lightningAnimationManager.draw(t_target, t_states);
        m_metalTrapAnimationManager.draw(t_target, t_states);
        m_plantTrapAnimationManager.draw(t_target, t_states);
        m_musicParticleManager.draw(t_target, t_states);
        m_sparkleParticleManager.draw(t_target, t_states);
    }

    void PredrawAnimations::move(const sf::Vector2f & t_move)
    {
        m_acidSpoutAnimationManager.move(t_move);
        m_lightningAnimationManager.move(t_move);
        m_metalTrapAnimationManager.move(t_move);
        m_plantTrapAnimationManager.move(t_move);
        m_musicParticleManager.move(t_move);
        m_sparkleParticleManager.move(t_move);
    }

    void PredrawAnimations::postLevelLoadSetup(const Context & t_context)
    {
        m_acidSpoutAnimationManager.postLevelLoadSetup(t_context);
        m_lightningAnimationManager.postLevelLoadSetup(t_context);
        m_metalTrapAnimationManager.postLevelLoadSetup(t_context);
        m_plantTrapAnimationManager.postLevelLoadSetup(t_context);
        m_musicParticleManager.postLevelLoadSetup(t_context);
        m_sparkleParticleManager.postLevelLoadSetup(t_context);
    }

} // namespace thornberry
