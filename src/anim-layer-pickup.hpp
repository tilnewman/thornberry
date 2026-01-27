#ifndef ANIM_LAYER_PICKUP_HPP_INCLUDED
#define ANIM_LAYER_PICKUP_HPP_INCLUDED
//
// anim-layer-pickup.hpp
//
#include "indirect-tile-layer.hpp"
#include "pickup-image-manager.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

namespace thornberry
{
    struct Context;

    //
    struct PickupParse
    {
        Pickup pickup{};
        sf::FloatRect map_rect{};
    };

    //
    struct PickupOffscreen
    {
        PickupOffscreen(
            const Pickup t_pickup,
            const sf::FloatRect & t_offscreenRect,
            const std::size_t t_frameIndex,
            const sf::Texture & t_texture);

        Pickup pickup;
        sf::FloatRect offscreen_rect;
        std::size_t frame_index;
        float elapsed_sec;
        sf::Sprite sprite;
    };

    //
    class AnimLayerPickup : public IIndirectTileLayer
    {
      public:
        AnimLayerPickup(const std::vector<PickupParse> & t_parsedPickups);

        virtual ~AnimLayerPickup() override = default;

        void postLevelLoadSetup(const Context & t_context) override;
        void dumpInfo() const override;
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;
        void move(const sf::Vector2f & t_move) override;
        void update(const Context & t_context, const float t_elapsedSec) override;

        void interactWithPlayer(
            const Context & t_context, const sf::FloatRect & t_avatarMapRect) override;

        // animation layers have no tiles
        void appendVerts(
            const sf::IntRect &,
            const sf::Vector2i &,
            const sf::Vector2i &,
            const sf::Vector2f &) override
        {}

      private:
        std::vector<PickupParse> m_parsedPickups;
        std::size_t m_frameCount;
        float m_timeBetweenFramesSec;
        sf::Vector2i m_cellSize;
        std::vector<PickupOffscreen> m_pickups;
    };

} // namespace thornberry

#endif // ANIM_LAYER_PICKUP_HPP_INCLUDED
