//
// anim-layer-pickup.cpp
//
#include "anim-layer-pickup.hpp"

#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "pickup-image-manager.hpp"
#include "random.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"

#include <algorithm>
#include <iostream>

namespace thornberry
{

    PickupOffscreen::PickupOffscreen(
        const Pickup t_pickup,
        const sf::FloatRect & t_offscreenRect,
        const std::size_t t_frameIndex,
        const sf::Texture & t_texture)
        : pickup{ t_pickup }
        , offscreen_rect{ t_offscreenRect }
        , frame_index{ t_frameIndex }
        , elapsed_sec{ 0.0f }
        , sprite{ t_texture }
    {}

    PickupAnimation::PickupAnimation(const sf::Sprite & t_sprite, const sf::Vector2i & t_cellSize)
        : elapsed_sec{ 0.0f }
        , sprite{ t_sprite }
        , is_alive{ true }
        , color{ sf::Color::White }
    {
        sprite.setTextureRect({ { 0, 0 }, t_cellSize });
        util::setOriginToCenter(sprite);

        const sf::Vector2f centerPos{ sprite.getPosition() +
                                      (sprite.getGlobalBounds().size * 0.5f) };

        sprite.setPosition(centerPos);
    }

    AnimLayerPickup::AnimLayerPickup(const std::vector<PickupParse> & t_parsedPickups)
        : m_parsedPickups{ t_parsedPickups }
        , m_frameCount{ 10 }
        , m_timeBetweenFramesSec{ 0.1f }
        , m_cellSize{ 32, 32 }
        , m_pickups{}
        , m_animations{}
    {}

    void AnimLayerPickup::postLevelLoadSetup(const Context & t_context)
    {
        m_pickups.reserve(m_parsedPickups.size());
        m_animations.reserve(8); // just a guess

        for (const PickupParse & parse : m_parsedPickups)
        {
            // convert map coordinates to offscreen coordinates
            sf::FloatRect offscreenRect{ parse.map_rect };
            offscreenRect.position += t_context.level.mapToOffscreenOffset();

            PickupOffscreen & offscreenPickup{ m_pickups.emplace_back(
                parse.pickup,
                offscreenRect,
                t_context.random.zeroToOneLessThan(m_frameCount),
                t_context.pickup_image.get(parse.pickup)) };

            offscreenPickup.sprite.setTextureRect({ { 0, 0 }, m_cellSize });
            util::scaleAndCenterInside(offscreenPickup.sprite, offscreenRect);
        }
    }

    void AnimLayerPickup::dumpInfo() const
    {
        std::cout << "\tAnimLayerPickup x" << m_pickups.size() << "\n";
    }

    void AnimLayerPickup::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const PickupOffscreen & pickup : m_pickups)
        {
            t_target.draw(pickup.sprite, t_states);
        }

        t_states.blendMode = sf::BlendAdd;
        for (const PickupAnimation & animation : m_animations)
        {
            t_target.draw(animation.sprite, t_states);
        }
    }

    void AnimLayerPickup::move(const sf::Vector2f & t_move)
    {
        for (PickupOffscreen & pickup : m_pickups)
        {
            pickup.offscreen_rect.position += t_move;
            pickup.sprite.move(t_move);
        }

        //don't move the animations
    }

    void AnimLayerPickup::update(const Context &, const float t_elapsedSec)
    {
        for (PickupOffscreen & pickup : m_pickups)
        {
            pickup.elapsed_sec += t_elapsedSec;
            if (pickup.elapsed_sec > m_timeBetweenFramesSec)
            {
                pickup.elapsed_sec -= m_timeBetweenFramesSec;

                if (++pickup.frame_index >= m_frameCount)
                {
                    pickup.frame_index = 0;
                }

                pickup.sprite.setTextureRect(
                    util::cellRect(pickup.frame_index, { 320u, 32u }, m_cellSize));
            }
        }

        bool willAnyAnimationsBeRemoved{ false };
        for (PickupAnimation & anim : m_animations)
        {
            anim.elapsed_sec += t_elapsedSec;
            const float durationSec{ 0.5f };
            if (anim.elapsed_sec < durationSec)
            {
                const float scale{ util::map(anim.elapsed_sec, 0.0f, durationSec, 1.0f, 3.0f) };
                anim.sprite.setScale({ scale * scale, scale * scale });

                const std::uint8_t alpha{ static_cast<std::uint8_t>(
                    util::map(anim.elapsed_sec, 0.0f, durationSec, 255, 0)) };

                sf::Color color{ anim.color };
                color.a = alpha;
                anim.sprite.setColor(color);
            }
            else
            {
                willAnyAnimationsBeRemoved = true;
                anim.is_alive              = false;
            }
        }

        if (willAnyAnimationsBeRemoved)
        {
            std::erase_if(
                m_animations, [](const PickupAnimation & anim) { return !anim.is_alive; });
        }
    }

    void AnimLayerPickup::interactWithPlayer(
        const Context & t_context, const sf::FloatRect & t_avatarMapRect)
    {
        // convert from map to offscreen coordinates
        sf::FloatRect avatarOffscreenRect{ t_avatarMapRect };
        avatarOffscreenRect.position += t_context.level.mapToOffscreenOffset();

        bool willAnyBeRemoved{ false };
        for (const PickupOffscreen & pickup : m_pickups)
        {
            if (avatarOffscreenRect.findIntersection(pickup.offscreen_rect).has_value())
            {
                // TODO perform all interactors with player (pickups will be changing things...)
                t_context.sfx.play("pickup");

                // spawn animation
                m_animations.emplace_back(pickup.sprite, m_cellSize);

                // flag that some PickupOffscreens will be erased
                willAnyBeRemoved = true;
            }
        }

        if (willAnyBeRemoved)
        {
            std::erase_if(m_pickups, [&](const PickupOffscreen & pickup) {
                return avatarOffscreenRect.findIntersection(pickup.offscreen_rect).has_value();
            });
        }
    }

} // namespace thornberry
