#ifndef ANIM_LAYER_BASE_HPP_INCLUDED
#define ANIM_LAYER_BASE_HPP_INCLUDED
//
// anim-layer-base.hpp
//
#include "indirect-tile-layer.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <filesystem>
#include <string>

namespace thornberry
{
    struct Context;

    enum class TextureSetting : unsigned char
    {
        Normal,
        Smooth
    };

    //
    class AnimLayerBase : public IIndirectTileLayer
    {
      public:
        AnimLayerBase(
            const std::string & t_name,
            const sf::FloatRect & t_mapRect,
            const std::size_t t_frameCount,
            const sf::Vector2i & t_cellSize,
            const float t_timeBetweenFramesSec,
            const std::filesystem::path & t_texturePath,
            const TextureSetting t_textureSetting);

        virtual ~AnimLayerBase() override = default;

        void postLevelLoadSetup(const Context & t_context) override;
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;
        void move(const sf::Vector2f & t_move) override;
        void update(const Context & t_context, const float t_frameTimeSec) override;
        void dumpInfo() const override;
        void interactWithPlayer(const Context &, const sf::FloatRect &) override {}

        // animation layers have no tiles
        void appendVerts(
            const sf::IntRect &,
            const sf::Vector2i &,
            const sf::Vector2i &,
            const sf::Vector2f &) override
        {}

      protected:
        std::string m_name;
        sf::FloatRect m_offscreenRect;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        std::size_t m_frameIndex;
        std::size_t m_frameCount;
        float m_elapsedSec;
        float m_timeBetweenFramesSec;
        sf::Vector2i m_cellSize;
        std::filesystem::path m_texturePath;
        TextureSetting m_textureSetting;
    };

} // namespace thornberry

#endif // ANIM_LAYER_BASE_HPP_INCLUDED
