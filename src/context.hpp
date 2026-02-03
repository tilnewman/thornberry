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
    class Player;
    class FontManager;
    class PickupImageManager;
    class SmokeParticleEffects;
    class NpcManager;
    class PredrawAnimations;
    class DayNightCycle;

    //
    struct Context
    {
        Context(
            const Config & t_config,
            const ScreenLayout & t_screenLayout,
            const util::Random & t_random,
            IndirectLevel & t_level,
            LevelFileLoader & t_levelFileLoader,
            Player & t_player,
            FontManager & t_fontManager,
            util::SoundPlayer & t_soundPlayer,
            util::MusicPlayer & t_musicPlayer,
            PickupImageManager & t_pickupImageManager,
            SmokeParticleEffects & t_smokeParticleEffects,
            NpcManager & t_npcManager,
            PredrawAnimations & t_predrawAnimations,
            DayNightCycle & t_dayNightCycle)
            : config{ t_config }
            , screen_layout{ t_screenLayout }
            , random{ t_random }
            , level{ t_level }
            , level_loader{ t_levelFileLoader }
            , player{ t_player }
            , font{ t_fontManager }
            , sfx{ t_soundPlayer }
            , music{ t_musicPlayer }
            , pickup_image{ t_pickupImageManager }
            , smoke{ t_smokeParticleEffects }
            , npc{ t_npcManager }
            , predraw_anim{ t_predrawAnimations }
            , time{ t_dayNightCycle }
        {}

        const Config & config;
        const ScreenLayout & screen_layout;
        const util::Random & random;
        IndirectLevel & level;
        LevelFileLoader & level_loader;
        Player & player;
        FontManager & font;
        util::SoundPlayer & sfx;
        util::MusicPlayer & music;
        PickupImageManager & pickup_image;
        SmokeParticleEffects & smoke;
        NpcManager & npc;
        PredrawAnimations & predraw_anim;
        DayNightCycle & time;
    };

} // namespace thornberry

#endif // CONTEXT_HPP_INCLUDED
