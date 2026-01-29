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
        Player();

        void handleEvent(const Context & t_context, const sf::Event & t_event);
    };

} // namespace thornberry

#endif // PLAYER_HPP_INCLUDED
