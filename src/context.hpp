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
            util::MusicPlayer & t_musicPlayer)
            : config{ t_config }
            , screen_layout{ t_screenLayout }
            , random{ t_random }
            , level{ t_level }
            , level_loader{ t_levelFileLoader }
            , avatar{ t_avatar }
            , font{ t_fontManager }
            , sfx{ t_soundPlayer }
            , music{ t_musicPlayer }
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
    };

} // namespace thornberry

#endif // CONTEXT_HPP_INCLUDED
