#ifndef INDIRECT_LEVEL_HPP_INCLUDED
#define INDIRECT_LEVEL_HPP_INCLUDED
//
// indirect-level.hpp
//
#include "indirect-tile-layer.hpp"
#include "npc.hpp"
#include "sfml-util.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Window/Event.hpp>

#include <string>
#include <vector>

namespace thornberry
{
    struct Context;

    //
    enum class LayerGroup : unsigned char
    {
        Upper,
        Lower
    };

    //
    enum class TransitionDirection : unsigned char
    {
        Entry,
        Exit
    };

    inline const std::string toString(const TransitionDirection t_dir)
    {
        if (t_dir == TransitionDirection::Entry)
        {
            return "entry";
        }
        else
        {
            return "exit";
        }
    }

    inline TransitionDirection transitionDirectionFromString(const std::string & t_dirStr)
    {
        if ((t_dirStr == "entry") || (t_dirStr == "Entry"))
        {
            return TransitionDirection::Entry;
        }
        else
        {
            return TransitionDirection::Exit;
        }
    }

    //
    enum struct Locale : unsigned char
    {
        None,
        Interior,
        Exterior
    };

    inline const std::string toString(const Locale t_music)
    {
        if (t_music == Locale::Interior)
        {
            return "interior";
        }
        else if (t_music == Locale::Exterior)
        {
            return "exterior";
        }
        else
        {
            return "none";
        }
    }

    inline Locale localeFromString(const std::string & t_localeStr)
    {
        if ((t_localeStr == "interior") || (t_localeStr == "Interior"))
        {
            return Locale::Interior;
        }
        else if ((t_localeStr == "exterior") || (t_localeStr == "Exterior"))
        {
            return Locale::Exterior;
        }
        else
        {
            return Locale::None;
        }
    }

    //
    struct Transition
    {
        sf::FloatRect map_rect{};
        std::string map_filename{};
        TransitionDirection direction{};
        std::string sfx_name{};
    };

    //
    struct WalkSound
    {
        std::string sfx_name{};
        sf::FloatRect map_rect{};
    };

    // This class (and many other classes) are called "indirect" because they are not directly drawn
    // to the screen, but rather drawn to an offscreen texture that is then drawn to the screen.
    class IndirectLevel
    {
      public:
        IndirectLevel();

        void load(
            const Context & t_context,
            const std::string & t_filenameFrom,
            const std::string & t_filenameToLoad);

        void update(const Context & t_context, const float t_frameTimeSec);
        void handleEvent(const Context & t_context, const sf::Event & t_event);

        void
            draw(const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states);

        [[nodiscard]] const std::string name() const { return m_name; }
        [[nodiscard]] Locale locale() const { return m_locale; }
        void locale(const Locale t_locale) { m_locale = t_locale; }
        [[nodiscard]] const sf::Vector2i mapTileCount() const { return m_mapTileCount; }
        [[nodiscard]] const sf::Vector2i textureTileSize() const { return m_textureTileSize; }
        [[nodiscard]] const sf::Vector2f screenTileSize() const { return m_screenTileSize; }
        [[nodiscard]] const sf::Vector2f mapScreenPosOffset() const { return m_mapScreenPosOffset; }

        // these return references so that the level loader can populate them
        [[nodiscard]] std::vector<sf::FloatRect> & collisions() { return m_collisions; }
        [[nodiscard]] std::vector<Transition> & transitions() { return m_transitions; }
        [[nodiscard]] std::vector<WalkSound> & walkSounds() { return m_walkSounds; }
        [[nodiscard]] std::vector<sf::FloatRect> & npcWalkBounds() { return m_npcWalkBounds; }

        [[nodiscard]] const sf::FloatRect offscreenRect() const { return m_offscreenDrawRect; }

        void appendToLowerTileLayers(std::unique_ptr<IIndirectTileLayer> t_uptr)
        {
            m_lowerTileLayers.emplace_back(std::move(t_uptr));
        }

        void appendToUpperTileLayers(std::unique_ptr<IIndirectTileLayer> t_uptr)
        {
            m_upperTileLayers.emplace_back(std::move(t_uptr));
        }

        [[nodiscard]] inline const sf::Vector2f mapToOffscreenOffset() const
        {
            return (sf::Vector2f{ m_offscreenTileRange.position } * m_screenTileSize * -1.0f);
        }

        [[nodiscard]] inline const sf::Vector2f mapToScreenOffset() const
        {
            return (m_mapScreenPosOffset + mapToOffscreenOffset());
        }

        // the map loader calls this to set things up very early in the process of loading
        void setLevelDetails(
            const Context & t_context,
            const std::string & t_name,
            const sf::Vector2i & t_mapTileCount,
            const sf::Vector2i & t_textureTileSize);

        // returns true if the avatar will move by t_move amount
        [[nodiscard]] const MoveResultPack playerMove(
            const Context & t_context,
            const sf::FloatRect & t_playerMapRect,
            const sf::Vector2f & t_move);

        void stopWalkSound(const Context & t_context);

        [[nodiscard]] bool isInsideAnyNpcWalkBounds(const sf::FloatRect & t_rect) const;

      private:
        void setupOffscreenTileRange(const Context & t_context, const sf::Vector2f & t_entryPos);
        void reset(const Context & t_context);
        void appendLayerVerts();
        void dumpInfo(const std::string & t_filename) const;
        void drawLowerLayers(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void drawUpperLayers(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void drawToOffscreenTexture(const Context & t_context);
        void drawToOnscreenTexture(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

        [[nodiscard]] bool doesIntersetWithCollision(const sf::FloatRect & t_rect) const;

        [[nodiscard]] const sf::Vector2f
            findEntryTransitionPositionFrom(const std::string & t_fromFilename) const;

        void performPostLoadSetupOnAll(const Context & t_context);

        void moveAllLayers(const sf::Vector2f & t_move);

        [[nodiscard]] const std::optional<Transition>
            findIntersectingExitTransition(const sf::FloatRect & t_rect) const;

        void playWalkSound(const Context & t_context, const sf::FloatRect & t_avatarMapRect);

        void moveAll(const Context & t_context, const sf::Vector2f & t_move);

        void interactWithAll(const Context & t_context, const sf::FloatRect & t_avatarMapRect);

      private:
        std::string m_name;

        Locale m_locale; // determines interiror/exterior (music and whether the sundial is drawn

        sf::Vector2i m_mapTileCount;       // how big is the whole map that was loaded
        sf::Vector2i m_textureTileSize;    // offscreen tile size
        sf::Vector2f m_screenTileSize;     // onscreen tile size
        sf::Vector2f m_mapScreenPosOffset; // where on the screen is the map drawn to

        std::vector<sf::FloatRect> m_collisions;    // in map coordinates
        std::vector<Transition> m_transitions;      // in map coordinates
        std::vector<WalkSound> m_walkSounds;        // in map coordinates
        std::vector<sf::FloatRect> m_npcWalkBounds; // in map coordinates

        // lower layers draw first, then pre anims, then player/nps, then upper layers, post anims
        std::vector<std::unique_ptr<IIndirectTileLayer>> m_lowerTileLayers;
        std::vector<std::unique_ptr<IIndirectTileLayer>> m_upperTileLayers;

        // the offscreen texture
        sf::RenderTexture m_renderTexture;
        sf::RenderStates m_renderStates;

        // which map tiles will be drawn offscreen
        sf::IntRect m_offscreenTileRange;
        sf::FloatRect m_offscreenDrawRect;

        // the onscreen map background (will be visible if m_isMapRectBigEnoughHoriz/Vert)
        sf::RectangleShape m_backgroundRectangle;

        // dirty flag for the offscreen verts, so we don't have to re-append them every frame
        bool m_didOffscreenVertsChange;

        // lots of special cases to handle when the offscreen map fits horiz/vert onscreen
        bool m_isMapRectBigEnoughHoriz;
        bool m_isMapRectBigEnoughVert;

        // these rects trigger movement of the map when the avatar walks on them
        sf::FloatRect m_moveScreenRectLeft;
        sf::FloatRect m_moveScreenRectRight;
        sf::FloatRect m_moveScreenRectUp;
        sf::FloatRect m_moveScreenRectDown;

        // this changes as the player walks on different grasses/dirt/etc.
        std::string m_walkSoundEffectName;
    };

} // namespace thornberry

#endif // INDIRECT_LEVEL_HPP_INCLUDED
