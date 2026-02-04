#ifndef NPC_HPP_INCLUDED
#define NPC_HPP_INCLUDED
//
// npc.hpp
//
#include "avatar.hpp"

#include <functional>
#include <optional>
#include <vector>

namespace thornberry
{
    struct Context;

    //
    enum class NpcAction : unsigned char
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
        explicit Npc(const AvatarImage t_image);

        // see comment in Avatar.hpp for why these are required
        Npc(const Npc & t_otherNpc);
        Npc(Npc & t_otherNpc);
        Npc(Npc && t_otherNpc);
        void operator=(const Npc & t_otherNpc);

        virtual ~Npc() override = default;

        void update(const Context & t_context, const float t_elapsedSec) override;

      private:
        const std::optional<sf::Vector2f> pickRandomWalkTarget(const Context & t_context) const;
        void updateWalkPosition(const Context & t_context, const float t_elapsedSec) override;
        bool isMovedPositionValid(const Context & t_context, const sf::Vector2f & t_move) const;

      private:
        NpcAction m_action;
        float m_actionElpasedSec;
        float m_timeUntilActionChangeSec;
        std::vector<AvatarDirection> m_walkDirections;
    };

    using NpcRefOpt_t = std::optional<std::reference_wrapper<Npc>>;

    //
    enum class MoveResult : unsigned char
    {
        Success,
        FailMoveCollision,
        FailTransition,
        FailNpcCollision
    };

    //
    struct MoveResultPack
    {
        MoveResultPack(const MoveResult t_result)
            : result{ t_result }
            , npc_opt{}
        {}

        MoveResultPack(Npc & t_collidingNpc)
            : result{ MoveResult::FailNpcCollision }
            , npc_opt{ t_collidingNpc }
        {}

        // explicit operator bool() const { return (MoveResult::Success == result); }

        MoveResult result;
        NpcRefOpt_t npc_opt;
    };

} // namespace thornberry

#endif // NPC_HPP_INCLUDED
