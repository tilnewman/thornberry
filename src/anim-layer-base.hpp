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

namespace thornberry
{
    struct Context;

    enum class TextureSetting
    {
        Normal,
        Smooth
    };

    //
    class AnimLayerBase : public IIndirectTileLayer
    {
      public:
        AnimLayerBase(
            const sf::FloatRect & t_mapRect,
            const std::size_t t_frameCount,
            const sf::Vector2i & t_cellSize,
            const float t_timeBetweenFramesSec);

        virtual ~AnimLayerBase() override = default;

        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;
        void move(const sf::Vector2f & t_move) override;
        void update(const Context & t_context, const float t_frameTimeSec) override;

        // animation layers have no tiles
        void appendVerts(
            const sf::IntRect &,
            const sf::Vector2i &,
            const sf::Vector2i &,
            const sf::Vector2f &) override
        {}

      protected:
        virtual void setup(
            const Context & t_context,
            const std::filesystem::path & t_path,
            const TextureSetting t_textureSetting);

      private:
        sf::FloatRect m_offscreenRect;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        std::size_t m_frameIndex;
        std::size_t m_frameCount;
        float m_elapsedSec;
        float m_timeBetweenFramesSec;
        sf::Vector2i m_cellSize;
    };

} // namespace mapdisplay

#endif // ANIM_LAYER_BASE_HPP_INCLUDED
