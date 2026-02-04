//
// window-image-manager.cpp
//
#include "window-image-manager.hpp"

#include "config.hpp"
#include "texture-loader.hpp"

namespace thornberry
{

    WindowImageManager::WindowImageManager()
        : m_backgroundTop{}
        , m_backgroundBot{}
        , m_backgroundLeft{}
        , m_backgroundRight{}
        , m_backgroundTopLeft{}
        , m_backgroundTopRight{}
        , m_backgroundBotLeft{}
        , m_backgroundBotRight{}
        , m_borderTop{}
        , m_borderBot{}
        , m_borderLeft{}
        , m_borderRight{}
        , m_borderTopLeft{}
        , m_borderTopRight{}
        , m_borderBotLeft{}
        , m_borderBotRight{}
    {}

    void WindowImageManager::setup(const Config & t_config)
    {
        const std::filesystem::path path{ t_config.media_path / "image" / "ui" };

        util::TextureLoader::load(m_backgroundTop, path / "menu-bg-top.png");
        util::TextureLoader::load(m_backgroundBot, path / "menu-bg-bottom.png");
        util::TextureLoader::load(m_backgroundLeft, path / "menu-bg-left.png");
        util::TextureLoader::load(m_backgroundRight, path / "menu-bg-right.png");

        util::TextureLoader::load(m_backgroundTopLeft, path / "menu-bg-top-left.png");
        util::TextureLoader::load(m_backgroundTopRight, path / "menu-bg-top-right.png");
        util::TextureLoader::load(m_backgroundBotLeft, path / "menu-bg-bottom-left.png");
        util::TextureLoader::load(m_backgroundBotRight, path / "menu-bg-bottom-right.png");

        //

        util::TextureLoader::load(m_borderTop, path / "small-border-top.png");
        util::TextureLoader::load(m_borderBot, path / "small-border-bottom.png");
        util::TextureLoader::load(m_borderLeft, path / "small-border-left.png");
        util::TextureLoader::load(m_borderRight, path / "small-border-right.png");

        util::TextureLoader::load(m_borderTopLeft, path / "small-border-top-left.png");
        util::TextureLoader::load(m_borderTopRight, path / "small-border-top-right.png");
        util::TextureLoader::load(m_borderBotLeft, path / "small-border-bottom-left.png");
        util::TextureLoader::load(m_borderBotRight, path / "small-border-bottom-right.png");
    }

} // namespace thornberry
