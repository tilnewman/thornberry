#ifndef COORDINATOR_HPP_INCLUDED
#define COORDINATOR_HPP_INCLUDED
//
// coordinator.hpp
//
#include "anim-acid-spout.hpp"
#include "anim-lightning.hpp"
#include "anim-plant-trap.hpp"
#include "config.hpp"
#include "context.hpp"
#include "font.hpp"
#include "framerate.hpp"
#include "indirect-level.hpp"
#include "level-file-loader.hpp"
#include "music-particle.hpp"
#include "music-player.hpp"
#include "npc-manager.hpp"
#include "pickup-image-manager.hpp"
#include "player.hpp"
#include "random.hpp"
#include "screen-layout.hpp"
#include "smoke-particle.hpp"
#include "sound-player.hpp"
#include "sparkle-particle.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <memory>

namespace thornberry
{

    class Coordinator
    {
      public:
        Coordinator();
        void run(const Config & t_config);

      private:
        void setup(const Config & t_config);
        void loop();
        void teardown();

        void handleEvents();
        void handleEvent(const sf::Event & t_event);
        void update(const float t_elapsedSec);
        void draw();

        void setupRenderWindow(sf::VideoMode & t_videoMode);

      private:
        Config m_config;
        sf::RenderStates m_renderStates;
        sf::RenderWindow m_renderWindow;
        std::unique_ptr<ScreenLayout> m_screenLayoutUPtr;
        std::unique_ptr<util::Random> m_randomUPtr;
        std::unique_ptr<IndirectLevel> m_levelUPtr;
        std::unique_ptr<LevelFileLoader> m_levelFileLoaderUPtr;
        std::unique_ptr<Player> m_playerUPtr;
        std::unique_ptr<FontManager> m_fontManagerUPtr;
        std::unique_ptr<FrameRateDisplay> m_framerateUPtr;
        std::unique_ptr<util::SoundPlayer> m_soundPlayerUPtr;
        std::unique_ptr<util::MusicPlayer> m_musicPlayerUPtr;
        std::unique_ptr<PickupImageManager> m_pickupImageManagerUPtr;
        std::unique_ptr<SmokeParticleEffects> m_smokeParticleEffectsUPtr;
        std::unique_ptr<SparkleParticleEffects> m_sparkleParticleEffectsUPtr;
        std::unique_ptr<LightningAnimationManager> m_lightningAnimationManagerUPtr;
        std::unique_ptr<MusicParticleManager> m_musicParticleManagerUPtr;
        std::unique_ptr<NpcManager> m_npcManagerUPtr;
        std::unique_ptr<AcidSpoutAnimationManager> m_acidSpoutAnimationManagerUPtr;
        std::unique_ptr<PlantTrapAnimationManager> m_plantTrapAnimationManagerUPtr;
        std::unique_ptr<Context> m_contextUPtr;
    };

} // namespace thornberry

#endif // COORDINATOR_HPP_INCLUDED
