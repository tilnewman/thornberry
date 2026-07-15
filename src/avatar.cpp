//
// avatar.cpp
//
#include "avatar.hpp"

#include "alpha-masking.hpp"
#include "avatar-image-manager.hpp"
#include "color-range.hpp"
#include "config.hpp"
#include "context.hpp"
#include "indirect-level.hpp"
#include "music-particle.hpp"
#include "random.hpp"
#include "screen-layout.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "texture-loader.hpp"

#include <iostream>
#include <string>

namespace thornberry
{

    Avatar::Avatar(const AvatarImage t_image)
        : m_image{ t_image }
        , m_anim{ AvatarAnim::None }
        , m_direction{ AvatarDirection::Right }
        , m_isAnimating{ false }
        , m_animCells{}
        , m_animIndex{ 0 }
        , m_elapsedSec{ 0.0f }
        , m_blinkElapsedSec{ 0.0f }
        , m_timeUntilBlinkSec{ 0.0f }
        , m_sprites{ AvatarImageManager::instance().acquire(t_image),
                     AvatarImageManager::instance().shadowTexture() }
        , m_hurtEnableTimerSec{ 0.0f }
        , m_isHurtAnimating{ false }
        , m_hurtColorCycleTimeSec{ 0.0f }
        , m_isHurtColorWhite{ true }
    {}

    Avatar::Avatar(const Avatar & t_otherAvatar)
        : m_image{ t_otherAvatar.m_image }
        , m_anim{ t_otherAvatar.m_anim }
        , m_direction{ t_otherAvatar.m_direction }
        , m_isAnimating{ t_otherAvatar.m_isAnimating }
        , m_animCells{ t_otherAvatar.m_animCells }
        , m_animIndex{ t_otherAvatar.m_animIndex }
        , m_elapsedSec{ t_otherAvatar.m_elapsedSec }
        , m_blinkElapsedSec{ t_otherAvatar.m_blinkElapsedSec }
        , m_timeUntilBlinkSec{ t_otherAvatar.m_timeUntilBlinkSec }
        , m_sprites{ t_otherAvatar.m_sprites }
        , m_hurtEnableTimerSec{ t_otherAvatar.m_hurtEnableTimerSec }
        , m_isHurtAnimating{ t_otherAvatar.m_isHurtAnimating }
        , m_hurtColorCycleTimeSec{ t_otherAvatar.m_hurtColorCycleTimeSec }
        , m_isHurtColorWhite{ t_otherAvatar.m_isHurtColorWhite }
    {
        AvatarImageManager::instance().acquire(m_image);
    }

    Avatar::Avatar(Avatar & t_otherAvatar)
        : m_image{ t_otherAvatar.m_image }
        , m_anim{ t_otherAvatar.m_anim }
        , m_direction{ t_otherAvatar.m_direction }
        , m_isAnimating{ t_otherAvatar.m_isAnimating }
        , m_animCells{ t_otherAvatar.m_animCells }
        , m_animIndex{ t_otherAvatar.m_animIndex }
        , m_elapsedSec{ t_otherAvatar.m_elapsedSec }
        , m_blinkElapsedSec{ t_otherAvatar.m_blinkElapsedSec }
        , m_timeUntilBlinkSec{ t_otherAvatar.m_timeUntilBlinkSec }
        , m_sprites{ t_otherAvatar.m_sprites }
        , m_hurtEnableTimerSec{ t_otherAvatar.m_hurtEnableTimerSec }
        , m_isHurtAnimating{ t_otherAvatar.m_isHurtAnimating }
        , m_hurtColorCycleTimeSec{ t_otherAvatar.m_hurtColorCycleTimeSec }
        , m_isHurtColorWhite{ t_otherAvatar.m_isHurtColorWhite }
    {
        AvatarImageManager::instance().acquire(m_image);
    }

    Avatar::Avatar(Avatar && t_otherAvatar)
        : m_image{ t_otherAvatar.m_image }
        , m_anim{ t_otherAvatar.m_anim }
        , m_direction{ t_otherAvatar.m_direction }
        , m_isAnimating{ t_otherAvatar.m_isAnimating }
        , m_animCells{ t_otherAvatar.m_animCells }
        , m_animIndex{ t_otherAvatar.m_animIndex }
        , m_elapsedSec{ t_otherAvatar.m_elapsedSec }
        , m_blinkElapsedSec{ t_otherAvatar.m_blinkElapsedSec }
        , m_timeUntilBlinkSec{ t_otherAvatar.m_timeUntilBlinkSec }
        , m_sprites{ t_otherAvatar.m_sprites }
        , m_hurtEnableTimerSec{ t_otherAvatar.m_hurtEnableTimerSec }
        , m_isHurtAnimating{ t_otherAvatar.m_isHurtAnimating }
        , m_hurtColorCycleTimeSec{ t_otherAvatar.m_hurtColorCycleTimeSec }
        , m_isHurtColorWhite{ t_otherAvatar.m_isHurtColorWhite }
    {
        AvatarImageManager::instance().acquire(m_image);
    }

    void Avatar::operator=(const Avatar & t_otherAvatar)
    {
        m_image                 = t_otherAvatar.m_image;
        m_anim                  = t_otherAvatar.m_anim;
        m_direction             = t_otherAvatar.m_direction;
        m_isAnimating           = t_otherAvatar.m_isAnimating;
        m_animCells             = t_otherAvatar.m_animCells;
        m_animIndex             = t_otherAvatar.m_animIndex;
        m_elapsedSec            = t_otherAvatar.m_elapsedSec;
        m_blinkElapsedSec       = t_otherAvatar.m_blinkElapsedSec;
        m_timeUntilBlinkSec     = t_otherAvatar.m_timeUntilBlinkSec;
        m_sprites               = t_otherAvatar.m_sprites;
        m_hurtEnableTimerSec    = t_otherAvatar.m_hurtEnableTimerSec;
        m_isHurtAnimating       = t_otherAvatar.m_isHurtAnimating;
        m_hurtColorCycleTimeSec = t_otherAvatar.m_hurtColorCycleTimeSec;
        m_isHurtColorWhite      = t_otherAvatar.m_isHurtColorWhite;
    }

    Avatar::~Avatar() { AvatarImageManager::instance().release(m_image); }

    void Avatar::setup(const Context & t_context)
    {
        // setup the avatar sprite
        util::setOriginToCenter(m_sprites.avatar);

        const float avatarScale{ t_context.screen_layout.scaleBasedOnResolution(
            t_context, t_context.config.avatar_scale) };

        m_sprites.avatar.setScale({ avatarScale, avatarScale });

        setAnim();

        // start the blink timer
        m_timeUntilBlinkSec = timeBetweenBlinks(t_context);

        // setup the shadow sprite
        util::setOriginToCenter(m_sprites.shadow);
        const float shadowScale{ avatarScale * 0.7f };
        m_sprites.shadow.setScale({ shadowScale, shadowScale });
        m_sprites.shadow.setColor(sf::Color(255, 255, 255, 150));

        // position avatar image and shadow image relative to each other
        setPosition({ 0.0f, 0.0f });
    }

    void Avatar::setPosition(const sf::Vector2f & t_position)
    {
        m_sprites.avatar.setPosition(t_position);
        m_sprites.shadow.setPosition(t_position);
        m_sprites.shadow.move({ 0.0f, (m_sprites.avatar.getGlobalBounds().size.y * 0.5f) });
    }

    void Avatar::move(const sf::Vector2f & t_move)
    {
        m_sprites.avatar.move(t_move);
        m_sprites.shadow.move(t_move);
    }

    void Avatar::update(const Context & t_context, const float t_elapsedSec)
    {
        updateBlinking(t_context, t_elapsedSec);

        if (m_isAnimating && (AvatarAnim::Walk == m_anim))
        {
            updateWalkPosition(t_context, t_elapsedSec);
        }

        updateAnimation(t_context, t_elapsedSec);
        updateHurtAnimation(t_context, t_elapsedSec);
    }

    void Avatar::updateHurtAnimation(const Context &, const float t_elapsedSec)
    {
        m_hurtEnableTimerSec += t_elapsedSec;
        if (m_hurtEnableTimerSec > 1.0f)
        {
            m_isHurtAnimating = false;
            m_sprites.avatar.setColor(sf::Color::White);
        }

        if (m_isHurtAnimating)
        {
            m_hurtColorCycleTimeSec += t_elapsedSec;
            const float colorCycleDurationSec{ 0.1f };
            if (m_hurtColorCycleTimeSec < colorCycleDurationSec)
            {
                const float cycleRatio{ m_hurtColorCycleTimeSec / colorCycleDurationSec };
                if (m_isHurtColorWhite)
                {
                    m_sprites.avatar.setColor(
                        colors::blend(cycleRatio, sf::Color::White, sf::Color::Red));
                }
                else
                {
                    m_sprites.avatar.setColor(
                        colors::blend(cycleRatio, sf::Color::Red, sf::Color::White));
                }
            }
            else
            {
                m_hurtColorCycleTimeSec = 0.0f;
                m_isHurtColorWhite      = !m_isHurtColorWhite;
            }
        }
    }

    void Avatar::updateBlinking(const Context & t_context, const float t_elapsedSec)
    {
        m_blinkElapsedSec += t_elapsedSec;
        if (m_blinkElapsedSec > m_timeUntilBlinkSec)
        {
            m_blinkElapsedSec -= m_timeUntilBlinkSec;
            m_timeUntilBlinkSec = timeBetweenBlinks(t_context);

            if (AvatarAnim::None == m_anim)
            {
                m_isAnimating = true;
                m_anim        = AvatarAnim::Blink;
                setAnim();
            }
        }
    }

    void Avatar::updateAnimation(const Context &, const float t_elapsedSec)
    {
        if (!m_isAnimating)
        {
            return;
        }

        m_elapsedSec += t_elapsedSec;
        const float timeBetweenFramesSec{ toTimeBetweenFrames(m_anim) };
        if (m_elapsedSec > timeBetweenFramesSec)
        {
            m_elapsedSec -= timeBetweenFramesSec;

            if (++m_animIndex >= (m_animCells.size() - 1))
            {
                m_animIndex = 0;

                if (AvatarAnim::Walk != m_anim)
                {
                    m_anim        = AvatarAnim::None;
                    m_isAnimating = false;
                    setAnim();
                }
            }

            updateSprite();
        }
    }

    void Avatar::draw(
        const sf::Vector2f & t_mapToOffscreenOffset,
        const sf::FloatRect & t_offscreenDrawRect,
        sf::RenderTarget & t_target,
        sf::RenderStates t_states) const
    {
        sf::Sprite tempAvatarSprite{ m_sprites.avatar };
        tempAvatarSprite.move(t_mapToOffscreenOffset);

        if (!tempAvatarSprite.getGlobalBounds().findIntersection(t_offscreenDrawRect).has_value())
        {
            return;
        }

        sf::Sprite tempShadowSprite{ m_sprites.shadow };
        tempShadowSprite.move(t_mapToOffscreenOffset);

        t_target.draw(tempShadowSprite, t_states);
        t_target.draw(tempAvatarSprite, t_states);
    }

    void Avatar::setAnim()
    {
        m_animCells  = animAndDirectionToCells(m_anim, m_direction);
        m_elapsedSec = 0.0f;
        m_animIndex  = 0;
        updateSprite();
    }

    void Avatar::updateSprite()
    {
        const auto cellIndex{ static_cast<std::size_t>(m_animCells.at(m_animIndex) - 1) };

        m_sprites.avatar.setTextureRect(
            util::animationCellRect(
                cellIndex, m_sprites.avatar.getTexture().getSize(), { 64, 64 }));

        util::setOriginToCenter(m_sprites.avatar);
    }

    float Avatar::timeBetweenBlinks(const Context & t_context) const
    {
        return t_context.random.fromTo(0.3f, 3.0f);
    }

    const sf::FloatRect Avatar::collisionMapRect() const
    {
        sf::FloatRect rect{ m_sprites.avatar.getGlobalBounds() };
        util::scaleRectInPlace(rect, { 0.4f, 0.775f });
        rect.position.y += (rect.size.y * 0.1375f);
        return rect;
    }

    void Avatar::startHurtAnimation()
    {
        m_isHurtAnimating       = true;
        m_hurtEnableTimerSec    = 0.0f;
        m_hurtColorCycleTimeSec = 0.0f;
        m_isHurtColorWhite      = true;
        m_sprites.avatar.setColor(sf::Color::Red);
    }

    void Avatar::standFacingRandomDirection(const Context & t_context)
    {
        standFacing(t_context.random.from(
            { AvatarDirection::Up,
              AvatarDirection::Down,
              AvatarDirection::Left,
              AvatarDirection::Right }));
    }

    void Avatar::standFacingPosition(const sf::Vector2f & t_mapPosition)
    {
        const sf::Vector2f avatarPosition{ util::center(collisionMapRect()) };

        const sf::Vector2f diff{ std::abs(t_mapPosition.x - avatarPosition.x),
                                 std::abs(t_mapPosition.y - avatarPosition.y) };

        if ((t_mapPosition.x < avatarPosition.x) && (diff.x > diff.y))
        {
            standFacing(AvatarDirection::Left);
        }
        else if ((t_mapPosition.x > avatarPosition.x) && (diff.x > diff.y))
        {
            standFacing(AvatarDirection::Right);
        }
        else if ((t_mapPosition.y < avatarPosition.y) && (diff.y > diff.x))
        {
            standFacing(AvatarDirection::Up);
        }
        else
        {
            standFacing(AvatarDirection::Down);
        }
    }

    void Avatar::standFacing(const AvatarDirection t_direction)
    {
        m_isAnimating = false;
        m_anim        = AvatarAnim::Walk;
        m_direction   = t_direction;
        setAnim();
        m_anim = AvatarAnim::None;
    }

} // namespace thornberry
