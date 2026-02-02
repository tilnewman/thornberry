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
        Player() = delete;
        Player(const AvatarImage t_image);
        Player(const Player & t_otherPlayer);         // see comment in Avatar.hpp
        Player(Player & t_otherPlayer);               // see comment in Avatar.hpp
        Player(Player && t_otherPlayer);              // see comment in Avatar.hpp
        void operator=(const Player & t_otherPlayer); // see comment in Avatar.hpp
        void operator=(Player & t_otherPlayer);       // see comment in Avatar.hpp
        void operator=(Player && t_otherPlayer);      // see comment in Avatar.hpp
        virtual ~Player() override = default;

        void handleEvent(const Context & t_context, const sf::Event & t_event);

      private:
        void updateWalkPosition(const Context & t_context, const float t_elapsedSec) override;
    };

} // namespace thornberry

#endif // PLAYER_HPP_INCLUDED
