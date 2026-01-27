#ifndef ANIM_LAYER_PICKUP_HPP_INCLUDED
#define ANIM_LAYER_PICKUP_HPP_INCLUDED
//
// anim-layer-pickup.hpp
//
#include "indirect-tile-layer.hpp"
#include "pickup-image-manager.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace thornberry
{
    struct Context;

    //
    class AnimLayerPickup : public IIndirectTileLayer
    {
      public:
        AnimLayerPickup(const Pickup t_pickup, const sf::FloatRect & t_mapRect);

        virtual ~AnimLayerPickup() override = default;

        void postLevelLoadSetup(const Context & t_context) override;
        void dumpInfo() const override;
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;
        void move(const sf::Vector2f & t_move) override;
        void update(const Context & t_context, const float t_elapsedSec) override;

        // animation layers have no tiles
        void appendVerts(
            const sf::IntRect &,
            const sf::Vector2i &,
            const sf::Vector2i &,
            const sf::Vector2f &) override
        {}

      private:
        Pickup m_pickup;
        sf::FloatRect m_offscreenRect;
        sf::Sprite m_sprite;
        std::size_t m_frameIndex;
        std::size_t m_frameCount;
        float m_elapsedSec;
        float m_timeBetweenFramesSec;
        sf::Vector2i m_cellSize;
    };

} // namespace thornberry

#endif // ANIM_LAYER_PICKUP_HPP_INCLUDED
