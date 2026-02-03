#ifndef PICKUP_IMAGE_MANAGER_HPP_INCLUDED
#define PICKUP_IMAGE_MANAGER_HPP_INCLUDED
//
// pickup-image-manager.hpp
//
#include "indirect-tile-layer.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <string>
#include <string_view>
#include <vector>

namespace thornberry
{
    struct Config;

    //
    enum class Pickup : unsigned char
    {
        BottleBlue = 0,
        BottleGreen,
        BottlePurple,
        CoinRound,
        CoinSquare,
        CrystalBlue,
        CrystalGreen,
        CrystalPurple,
        CrystalTeal,
        Heart,
        Star,
        Count
    };

    constexpr std::string_view toString(const Pickup t_pickup) noexcept
    {
        // clang-format off
		switch (t_pickup)
		{
			case Pickup::BottleBlue:		{ return "bottle-blue"; }
			case Pickup::BottleGreen:       { return "bottle-green"; }
			case Pickup::BottlePurple:      { return "bottle-purple"; }
			case Pickup::CoinRound:			{ return "coin-round"; }
			case Pickup::CoinSquare:		{ return "coin-square"; }
			case Pickup::CrystalBlue:       { return "crystal-blue"; }
			case Pickup::CrystalGreen:      { return "crystal-green"; }
			case Pickup::CrystalPurple:     { return "crystal-purple"; }
			case Pickup::CrystalTeal:       { return "crystal-teal"; }
			case Pickup::Heart:      		{ return "heart"; }
            case Pickup::Star:      		{ return "star"; }  
            case Pickup::Count:
			default:						{ return "Error_Unknown_Pickup"; }
		}
        // clang-format on
    }

    inline Pickup pickupFromString(const std::string& t_str)
    { 
        // clang-format off
        if (t_str == "bottle-blue")         { return Pickup::BottleBlue; }
        else if (t_str == "bottle-green")   { return Pickup::BottleGreen; }
        else if (t_str == "bottle-purple")  { return Pickup::BottlePurple; }
        else if (t_str == "coin-round")     { return Pickup::CoinRound; }
        else if (t_str == "coin-square")    { return Pickup::CoinSquare; }
        else if (t_str == "crystal-blue")   { return Pickup::CrystalBlue; }
        else if (t_str == "crystal-green")  { return Pickup::CrystalGreen; }
        else if (t_str == "crystal-purple") { return Pickup::CrystalPurple; }
        else if (t_str == "crystal-teal")   { return Pickup::CrystalTeal; }
        else if (t_str == "heart")          { return Pickup::Heart; }
        else if (t_str == "star")           { return Pickup::Star; }
        else                                { return Pickup::Count; }
        // clang-format on
    }

    inline const std::string pickupToFilename(const Pickup t_pickup)
    {
        std::string filename{ toString(t_pickup) };
        filename += ".png";
        return filename;
    }

    //
    class PickupImageManager
    {
      public:
        PickupImageManager();

        void setup(const Config & t_config);
        const sf::Texture & get(const Pickup t_pickup) const;

      private:
        std::vector<sf::Texture> m_textures;
    };

} // namespace thornberry

#endif // PICKUP_IMAGE_MANAGER_HPP_INCLUDED
