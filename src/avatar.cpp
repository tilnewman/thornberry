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
                     AvatarImageManager ::instance().shadowTexture() }
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

    void Avatar::operator=(Avatar & t_otherAvatar)
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

    void Avatar::operator=(Avatar && t_otherAvatar)
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

        const float avatarScale{ t_context.screen_layout.calScaleBasedOnResolution(
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

        // position both images relative to each other
        setPosition({ 0.0f, 0.0f });
    }

    void Avatar::setPosition(const sf::Vector2f & t_position)
    {
        m_sprites.avatar.setPosition(t_position);
        m_sprites.shadow.setPosition(t_position);
        m_sprites.shadow.move({ 0.0f, (m_sprites.avatar.getGlobalBounds().size.y * 0.5f) });
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
        const float timeBetweenFramesSec{ timeBetweenFrames(m_anim) };
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

    sf::Keyboard::Scancode Avatar::scanCodeFromDirection(const AvatarDirection t_dir)
    {
        // clang-format off
        switch (t_dir)
        {
            case AvatarDirection::Up:       return sf::Keyboard::Scancode ::Up;
            case AvatarDirection::Down:     return sf::Keyboard::Scancode::Down;
            case AvatarDirection::Left:     return sf::Keyboard::Scancode::Left;
            case AvatarDirection::Right:
            default:                        return sf::Keyboard::Scancode::Right;
        }
        // clang-format on
    }

    void Avatar::draw(
        const sf::Vector2f & t_mapToOffscreenOffset,
        const sf::FloatRect & t_offscreenDrawRect,
        sf::RenderTarget & t_target,
        sf::RenderStates t_states) const
    {
        sf::Sprite tempAvatar{ m_sprites.avatar };
        tempAvatar.move(t_mapToOffscreenOffset);

        if (!tempAvatar.getGlobalBounds().findIntersection(t_offscreenDrawRect).has_value())
        {
            return;
        }

        sf::Sprite tempShadow{ m_sprites.shadow };
        tempShadow.move(t_mapToOffscreenOffset);

        t_target.draw(tempShadow, t_states);
        t_target.draw(tempAvatar, t_states);
    }

    void Avatar::setAnim()
    {
        m_animCells  = animCells(m_anim, m_direction);
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

    float Avatar::timeBetweenFrames(const AvatarAnim t_anim)
    {
        // clang-format off
        switch (t_anim)
        {
            case AvatarAnim::Walk:      return 0.1f;
            case AvatarAnim::Do:        return 0.17f;
            case AvatarAnim::Thank:     return 3.0f;
            case AvatarAnim::FistBump:  return 0.75f;

            case AvatarAnim::None:
            case AvatarAnim::Blink:
            default:                    return 0.15f;
        }
        // clang-format on
    }

    float Avatar::timeBetweenBlinks(const Context & t_context) const
    {
        return t_context.random.fromTo(0.3f, 3.0f);
    }

    const std::vector<int>
        Avatar::animCells(const AvatarAnim t_anim, const AvatarDirection t_direction)
    {
        // clang-format off
        switch (t_anim)
        {
            case AvatarAnim::None:
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 1 };
                    case AvatarDirection::Down: return { 17 };
                    case AvatarDirection::Left: return { 9 };
                    case AvatarDirection::Right:
                    default:                    return { 25 };
                }
            }
            case AvatarAnim::Walk:
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 1, 2, 3, 4, 6, 7, 8 };
                    case AvatarDirection::Down: return { 17, 18, 19, 20, 22, 23, 24 };
                    case AvatarDirection::Left: return { 9, 10, 11, 12, 13, 14, 15, 16, 41 };
                    case AvatarDirection::Right:
                    default:                    return { 25, 26, 27, 28, 29, 30, 31, 32, 57 };
                }
            }
            case AvatarAnim::Do:
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 34, 35, 36, 37, 38 };
                    case AvatarDirection::Down: return { 50, 51, 52, 53, 54 };
                    case AvatarDirection::Left: return { 42, 43, 44, 45, 46 };
                    case AvatarDirection::Right:
                    default:                    return { 58, 59, 60, 61, 62 };
                }
            }
            case AvatarAnim::Thank: 
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 40 };
                    case AvatarDirection::Down: return { 56 };
                    case AvatarDirection::Left: return { 48 };
                    case AvatarDirection::Right:
                    default:                    return { 64 };
                }
            }
            case AvatarAnim::FistBump:
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 39 };
                    case AvatarDirection::Down: return { 55 };
                    case AvatarDirection::Left: return { 47 };
                    case AvatarDirection::Right:
                    default:                    return { 63 };
                }
            }
            case AvatarAnim::Blink:
            default: 
            {
                switch (t_direction)
                {
                    case AvatarDirection::Up:   return { 1 };
                    case AvatarDirection::Down: return { 33 };
                    case AvatarDirection::Left: return { 5 };
                    case AvatarDirection::Right:
                    default:                    return { 21 };
                }
            }
        }
        // clang-format on
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

} // namespace thornberry
