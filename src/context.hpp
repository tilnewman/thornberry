#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED
//
// context.hpp
//
namespace util
{
    class Random;
    class SoundPlayer;
    class MusicPlayer;
} // namespace util

namespace thornberry
{
    struct Config;

    class ScreenLayout;
    class IndirectLevel;
    class LevelFileLoader;
    class Avatar;
    class FontManager;
    class PickupImageManager;
    class SmokeParticleEffects;
    class SparkleParticleEffects;
    class LightningAnimationManager;

    //
    struct Context
    {
        Context(
            const Config & t_config,
            const ScreenLayout & t_screenLayout,
            const util::Random & t_random,
            IndirectLevel & t_level,
            LevelFileLoader & t_levelFileLoader,
            Avatar & t_avatar,
            FontManager & t_fontManager,
            util::SoundPlayer & t_soundPlayer,
            util::MusicPlayer & t_musicPlayer,
            PickupImageManager & t_pickupImageManager,
            SmokeParticleEffects & t_smokeParticleEffects,
            SparkleParticleEffects & t_sparkleParticleEffects,
            LightningAnimationManager & t_lightningAnimationManager)
            : config{ t_config }
            , screen_layout{ t_screenLayout }
            , random{ t_random }
            , level{ t_level }
            , level_loader{ t_levelFileLoader }
            , avatar{ t_avatar }
            , font{ t_fontManager }
            , sfx{ t_soundPlayer }
            , music{ t_musicPlayer }
            , pickup_image{ t_pickupImageManager }
            , smoke{ t_smokeParticleEffects }
            , sparkle{ t_sparkleParticleEffects }
            , lightning{ t_lightningAnimationManager }
        {}

        const Config & config;
        const ScreenLayout & screen_layout;
        const util::Random & random;
        IndirectLevel & level;
        LevelFileLoader & level_loader;
        Avatar & avatar;
        FontManager & font;
        util::SoundPlayer & sfx;
        util::MusicPlayer & music;
        PickupImageManager & pickup_image;
        SmokeParticleEffects & smoke;
        SparkleParticleEffects & sparkle;
        LightningAnimationManager & lightning;
    };

} // namespace thornberry

#endif // CONTEXT_HPP_INCLUDED
