#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
//
// player.hpp
//
#include "avatar.hpp"

namespace thornberry
{

    class Player : public Avatar
    {
      public:
        Player(const AvatarImage t_image);
        Player(Player && t_otherPlayer);
        virtual ~Player() override = default;

        void handleEvent(const Context & t_context, const sf::Event & t_event);

      private:
        void updateWalkPosition(const Context & t_context, const float t_elapsedSec) override;
    };

} // namespace thornberry

#endif // PLAYER_HPP_INCLUDED
