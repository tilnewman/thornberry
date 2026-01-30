#ifndef NPC_HPP_INCLUDED
#define NPC_HPP_INCLUDED
//
// npc.hpp
//
#include "avatar.hpp"

#include <optional>

namespace thornberry
{
    struct Context;

    //
    enum class NpcAction
    {
        Wait,
        Walk,
        Thank,
        Turn
    };

    //
    class Npc : public Avatar
    {
      public:
        Npc(const AvatarImage t_image);
        Npc(Npc && t_otherNpc); // see comment in Avatar.cpp
        virtual ~Npc() override = default;
        void operator=(const Npc & t_otherNpc); // see comment in Avatar.cpp

        void standFacingRandomDirection(const Context & t_context);
        void update(const Context & t_context, const float t_elapsedSec) override;

      private:
        const std::optional<sf::Vector2f> pickRandomWalkTarget(const Context & t_context) const;
        void updateWalkPosition(const Context & t_context, const float t_elapsedSec) override;

      private:
        NpcAction m_action;
        float m_actionElpasedSec;
        float m_timeUntilActionChangeSec;
    };

} // namespace thornberry

#endif // NPC_HPP_INCLUDED
