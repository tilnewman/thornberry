//
// coordinator.cpp
//
#include "coordinator.hpp"

#include "map-textures.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>

#include <algorithm>
#include <iostream>

namespace thornberry
{

    Coordinator::Coordinator()
        : m_config{}
        , m_renderStates{}
        , m_renderWindow{}
        , m_screenLayoutUPtr{}
        , m_randomUPtr{}
        , m_levelUPtr{}
        , m_levelFileLoaderUPtr{}
        , m_playerUPtr{}
        , m_fontManagerUPtr{}
        , m_framerateUPtr{}
        , m_soundPlayerUPtr{}
        , m_musicPlayerUPtr{}
        , m_pickupImageManagerUPtr{}
        , m_smokeParticleEffectsUPtr{}
        , m_sparkleParticleEffectsUPtr{}
        , m_lightningAnimationManagerUPtr{}
        , m_musicParticleManagerUPtr{}
        , m_npcManagerUPtr{}
        , m_contextUPtr{}
    {}

    void Coordinator::run(const Config & t_config)
    {
        setup(t_config);
        loop();
        teardown();
    }

    void Coordinator::setup(const Config & t_config)
    {
        m_config = t_config;

        setupRenderWindow(m_config.video_mode);
        m_renderWindow.setKeyRepeatEnabled(false);

        util::SfmlDefaults::instance().setup();
        MapTextureManager::instance().setup();

        m_randomUPtr                    = std::make_unique<util::Random>();
        m_soundPlayerUPtr               = std::make_unique<util::SoundPlayer>(*m_randomUPtr);
        m_musicPlayerUPtr               = std::make_unique<util::MusicPlayer>();
        m_screenLayoutUPtr              = std::make_unique<ScreenLayout>();
        m_levelUPtr                     = std::make_unique<IndirectLevel>();
        m_levelFileLoaderUPtr           = std::make_unique<LevelFileLoader>();
        m_playerUPtr                    = std::make_unique<Player>();
        m_fontManagerUPtr               = std::make_unique<FontManager>();
        m_framerateUPtr                 = std::make_unique<FrameRateDisplay>();
        m_pickupImageManagerUPtr        = std::make_unique<PickupImageManager>();
        m_smokeParticleEffectsUPtr      = std::make_unique<SmokeParticleEffects>();
        m_sparkleParticleEffectsUPtr    = std::make_unique<SparkleParticleEffects>();
        m_lightningAnimationManagerUPtr = std::make_unique<LightningAnimationManager>();
        m_musicParticleManagerUPtr      = std::make_unique<MusicParticleManager>();
        m_npcManagerUPtr                = std::make_unique<NpcManager>();

        m_contextUPtr = std::make_unique<Context>(
            m_config,
            *m_screenLayoutUPtr,
            *m_randomUPtr,
            *m_levelUPtr,
            *m_levelFileLoaderUPtr,
            *m_playerUPtr,
            *m_fontManagerUPtr,
            *m_soundPlayerUPtr,
            *m_musicPlayerUPtr,
            *m_pickupImageManagerUPtr,
            *m_smokeParticleEffectsUPtr,
            *m_sparkleParticleEffectsUPtr,
            *m_lightningAnimationManagerUPtr,
            *m_musicParticleManagerUPtr,
            *m_npcManagerUPtr);

        m_soundPlayerUPtr->setMediaPath((m_config.media_path / "sfx").string());
        m_soundPlayerUPtr->loadAll();

        m_musicPlayerUPtr->setup((m_config.media_path / "music").string());

        m_musicParticleManagerUPtr->setup(m_config);
        m_lightningAnimationManagerUPtr->setup(m_config);
        m_sparkleParticleEffectsUPtr->setup(m_config);
        m_smokeParticleEffectsUPtr->setup(m_config);
        m_pickupImageManagerUPtr->setup(m_config);
        m_screenLayoutUPtr->setup(m_config);
        m_fontManagerUPtr->setup(m_config);
        m_framerateUPtr->setup(*m_contextUPtr);
        m_playerUPtr->setup(*m_contextUPtr, AvatarImage::puck_female_light);
        
        m_levelUPtr->load(*m_contextUPtr, "house.tmj", "thornberry.tmj");
    }

    void Coordinator::loop()
    {
        sf::Clock frameClock;
        while (m_renderWindow.isOpen())
        {
            handleEvents();
            update(frameClock.restart().asSeconds());
            draw();
        }
    }

    void Coordinator::teardown()
    {
        m_soundPlayerUPtr->stopAll();
        m_musicPlayerUPtr->stopAll();

        if (m_renderWindow.isOpen())
        {
            m_renderWindow.close();
        }

        m_levelUPtr.reset();
        m_levelFileLoaderUPtr.reset();
        m_screenLayoutUPtr.reset();
        m_playerUPtr.reset();
        m_fontManagerUPtr.reset();
        m_framerateUPtr.reset();
        m_soundPlayerUPtr.reset();
        m_musicPlayerUPtr.reset();
        m_pickupImageManagerUPtr.reset();
        m_smokeParticleEffectsUPtr.reset();
        m_sparkleParticleEffectsUPtr.reset();
        m_lightningAnimationManagerUPtr.reset();
        m_musicParticleManagerUPtr.reset();
        m_npcManagerUPtr.reset();

        MapTextureManager::instance().teardown();
        util::SfmlDefaults::instance().teardown();

        m_contextUPtr.reset();
    }

    void Coordinator::handleEvents()
    {
        while (const auto eventOpt = m_renderWindow.pollEvent())
        {
            handleEvent(eventOpt.value());
        }
    }

    void Coordinator::handleEvent(const sf::Event & t_event)
    {
        if (t_event.is<sf::Event::Closed>())
        {
            m_renderWindow.close();
            std::cout << "Exiting because window was closed externally.\n";
        }
        else if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                m_renderWindow.close();
            }
        }

        m_playerUPtr->handleEvent(*m_contextUPtr, t_event);
        m_levelUPtr->handleEvent(*m_contextUPtr, t_event);
    }

    void Coordinator::update(const float t_elapsedSec)
    {
        m_levelUPtr->update(*m_contextUPtr, t_elapsedSec);
        m_playerUPtr->update(*m_contextUPtr, t_elapsedSec);
        m_npcManagerUPtr->update(*m_contextUPtr, t_elapsedSec);
        m_smokeParticleEffectsUPtr->update(*m_contextUPtr, t_elapsedSec);
        m_sparkleParticleEffectsUPtr->update(*m_contextUPtr, t_elapsedSec);
        m_lightningAnimationManagerUPtr->update(*m_contextUPtr, t_elapsedSec);
        m_musicParticleManagerUPtr->update(*m_contextUPtr, t_elapsedSec);
        m_framerateUPtr->update(*m_contextUPtr, t_elapsedSec);
    }

    void Coordinator::draw()
    {
        m_renderWindow.clear(sf::Color(30, 30, 30));

        m_levelUPtr->draw(*m_contextUPtr, m_renderWindow, m_renderStates);
        m_framerateUPtr->draw(m_renderWindow, m_renderStates);

        m_renderWindow.display();
    }

    void Coordinator::setupRenderWindow(sf::VideoMode & t_videoMode)
    {
        std::cout << "Attempting video mode " << t_videoMode << "...";

        if (!m_config.video_mode.isValid())
        {
            std::cout << "but that is not suported.  Valid video modes at "
                      << m_config.video_mode.bitsPerPixel << "bpp:\n"
                      << util::makeSupportedVideoModesString(m_config.video_mode.bitsPerPixel)
                      << '\n';

            t_videoMode = util::findHighestVideoMode(m_config.video_mode.bitsPerPixel);
            setupRenderWindow(t_videoMode);
            return;
        }

        m_renderWindow.create(t_videoMode, "MapDisplay", sf::State::Fullscreen);

        // sometimes the resolution of the window created does not match what was specified
        const unsigned actualWidth  = m_renderWindow.getSize().x;
        const unsigned actualHeight = m_renderWindow.getSize().y;
        if ((m_config.video_mode.size.x == actualWidth) &&
            (m_config.video_mode.size.y == actualHeight))
        {
            std::cout << "Success." << std::endl;
        }
        else
        {
            std::cout << "Failed" << ".  ";

            m_config.video_mode.size.x = actualWidth;
            m_config.video_mode.size.y = actualHeight;

            std::cout << "Using " << m_config.video_mode << " instead." << std::endl;
        }

        if (m_config.framerate_limit > 0)
        {
            m_renderWindow.setFramerateLimit(m_config.framerate_limit);
        }
    }

} // namespace thornberry
