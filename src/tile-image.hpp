#ifndef TILE_IMAGE_HPP_INCLUDED
#define TILE_IMAGE_HPP_INCLUDED
//
// tile-image.hpp
//
#include <ostream>
#include <string_view>

namespace thornberry
{

    enum class TileImage : unsigned char
    {
        BushLarge,
        BushMedium,
        BushSmall,
        Ground,
        GroundOld,
        InteriorDoor,
        InteriorGround,
        InteriorObject,
        InteriorShadow,
        InteriorStairUp,
        InteriorStairDown,
        InteriorWallNormal,
        InteriorWallShoddy,
        MountainShadow,
        Mountain,
        ObjectShadow,
        Object,
        PlantMedium,
        PlantMushroom,
        PlantSmall,
        PlantWood,
        TownDarkRoof,
        TownDark,
        TownLightRoot,
        TownLight,
        TownShadow,
        TownWallShadow,
        TownWall,
        Tree1,
        Tree2_5,
        Tree4,
        Tree6,
        Tree7,
        Tree8,
        Tree9,
        Tree10_13,
        Tree11,
        Tree12,
        Tree13b,
        Tree13c,
        TreeA,
        TreeAb,
        TreeB,
        TreeBaby,
        TreeC,
        TreeDeadCreepy,
        TreeDeadLarge,
        TreeDeadMedium,
        TreeDeadMisc,
        TreeJungle,
        TreeSnow,
        Water,
        Water2,
        Count
    };

    constexpr std::string_view toString(const TileImage t_image) noexcept
    {
        // clang-format off
        switch (t_image)
        {
            case TileImage::BushLarge:              { return "bush-large"; }
            case TileImage::BushMedium:             { return "bush-medium"; }
            case TileImage::BushSmall:              { return "bush-small"; }
            case TileImage::Ground:                 { return "ground"; }
            case TileImage::GroundOld:              { return "ground-old"; }
            case TileImage::InteriorDoor:           { return "interior-door"; }
            case TileImage::InteriorGround:         { return "interior-ground"; }
            case TileImage::InteriorObject:         { return "interior-object"; }
            case TileImage::InteriorShadow:         { return "interior-shadow"; }
            case TileImage::InteriorStairUp:        { return "interior-stair-up"; }
            case TileImage::InteriorStairDown:      { return "interior-stair-down"; }
            case TileImage::InteriorWallNormal:     { return "interior-wall-normal"; }
            case TileImage::InteriorWallShoddy:     { return "interior-wall-shoddy"; }
            case TileImage::MountainShadow:         { return "mountain-shadow"; }
            case TileImage::Mountain:               { return "mountain"; }
            case TileImage::ObjectShadow:           { return "object-shadow"; }
            case TileImage::Object:                 { return "object"; }
            case TileImage::PlantMedium:            { return "plant-medium"; }
            case TileImage::PlantMushroom:          { return "plant-mushroom"; }
            case TileImage::PlantSmall:             { return "plant-small"; }
            case TileImage::PlantWood:              { return "plant-wood"; }
            case TileImage::TownDarkRoof:           { return "town-dark-roof"; }
            case TileImage::TownDark:               { return "town-dark"; }
            case TileImage::TownLightRoot:          { return "town-light-roof"; }
            case TileImage::TownLight:              { return "town-light"; }
            case TileImage::TownShadow:             { return "town-shadow"; }
            case TileImage::TownWallShadow:         { return "town-wall-shadow"; }
            case TileImage::TownWall:               { return "town-wall"; }
            case TileImage::Tree1:                  { return "tree-1"; }
            case TileImage::Tree2_5:                { return "tree-2-5"; }
            case TileImage::Tree4:                  { return "tree-4"; }
            case TileImage::Tree6:                  { return "tree-6"; }
            case TileImage::Tree7:                  { return "tree-7"; }
            case TileImage::Tree8:                  { return "tree-8"; }
            case TileImage::Tree9:                  { return "tree-9"; }
            case TileImage::Tree10_13:              { return "tree-10-13"; }
            case TileImage::Tree11:                 { return "tree-11"; }
            case TileImage::Tree12:                 { return "tree-12"; }
            case TileImage::Tree13b:                { return "tree-13b"; }
            case TileImage::Tree13c:                { return "tree-13c"; }
            case TileImage::TreeA:                  { return "tree-a"; }
            case TileImage::TreeAb:                 { return "tree-ab"; }
            case TileImage::TreeB:                  { return "tree-b"; }
            case TileImage::TreeBaby:               { return "tree-baby"; }
            case TileImage::TreeC:                  { return "tree-c"; }
            case TileImage::TreeDeadCreepy:         { return "tree-dead-creepy"; }
            case TileImage::TreeDeadLarge:          { return "tree-dead-large"; }
            case TileImage::TreeDeadMedium:         { return "tree-dead-medium"; }
            case TileImage::TreeDeadMisc:           { return "tree-dead-misc"; }
            case TileImage::TreeJungle:             { return "tree-jungle"; }
            case TileImage::TreeSnow:               { return "tree-snow"; }
            case TileImage::Water:                  { return "water"; }
            case TileImage::Water2:                 { return "water2"; }
            case TileImage::Count:                  { return "count"; }
            default:                                { return "Error_TileImage_Unknown"; }
        }
        // clang-format on
    }

    inline TileImage tileImageFromString(const std::string & t_filename) noexcept
    {
        // clang-format off
        if (t_filename == "bush-large")                 { return TileImage::BushLarge; }
        else if (t_filename == "bush-medium")           { return TileImage::BushMedium; }
        else if (t_filename == "bush-small")            { return TileImage::BushSmall; }
        else if (t_filename == "ground")                { return TileImage::Ground; }
        else if (t_filename == "ground-old")            { return TileImage::GroundOld; }
        else if (t_filename == "interior-door")         { return TileImage::InteriorDoor; }
        else if (t_filename == "interior-ground")       { return TileImage::InteriorGround; }
        else if (t_filename == "interior-object")       { return TileImage::InteriorObject; }
        else if (t_filename == "interior-shadow")       { return TileImage::InteriorShadow; }
        else if (t_filename == "interior-stair-up")     { return TileImage::InteriorStairUp; }
        else if (t_filename == "interior-stair-down")   { return TileImage::InteriorStairDown; }
        else if (t_filename == "interior-wall-normal")  { return TileImage::InteriorWallNormal; }
        else if (t_filename == "interior-wall-shoddy")  { return TileImage::InteriorWallShoddy; }
        else if (t_filename == "mountain-shadow")       { return TileImage::MountainShadow; }
        else if (t_filename == "mountain")              { return TileImage::Mountain; }
        else if (t_filename == "object-shadow")         { return TileImage::ObjectShadow; }
        else if (t_filename == "object")                { return TileImage::Object; }
        else if (t_filename == "plant-medium")          { return TileImage::PlantMedium; }
        else if (t_filename == "plant-mushroom")        { return TileImage::PlantMushroom; }
        else if (t_filename == "plant-small")           { return TileImage::PlantSmall; }
        else if (t_filename == "plant-wood")            { return TileImage::PlantWood; }
        else if (t_filename == "town-dark-roof")        { return TileImage::TownDarkRoof; }
        else if (t_filename == "town-dark")             { return TileImage::TownDark; }
        else if (t_filename == "town-light-roof")       { return TileImage::TownLightRoot; }
        else if (t_filename == "town-light")            { return TileImage::TownLight; }
        else if (t_filename == "town-shadow")           { return TileImage::TownShadow; }
        else if (t_filename == "town-wall-shadow")      { return TileImage::TownWallShadow; }
        else if (t_filename == "town-wall")             { return TileImage::TownWall; }
        else if (t_filename == "tree-1")                { return TileImage::Tree1; }
        else if (t_filename == "tree-2-5")              { return TileImage::Tree2_5; }
        else if (t_filename == "tree-4")                { return TileImage::Tree4; }
        else if (t_filename == "tree-6")                { return TileImage::Tree6; }
        else if (t_filename == "tree-7")                { return TileImage::Tree7; }
        else if (t_filename == "tree-8")                { return TileImage::Tree8; }
        else if (t_filename == "tree-9")                { return TileImage::Tree9; }
        else if (t_filename == "tree-10-13")            { return TileImage::Tree10_13; }
        else if (t_filename == "tree-11")               { return TileImage::Tree11; }
        else if (t_filename == "tree-12")               { return TileImage::Tree12; }
        else if (t_filename == "tree-13b")              { return TileImage::Tree13b; }
        else if (t_filename == "tree-13c")              { return TileImage::Tree13c; }
        else if (t_filename == "tree-a")                { return TileImage::TreeA; }
        else if (t_filename == "tree-ab")               { return TileImage::TreeAb; }
        else if (t_filename == "tree-b")                { return TileImage::TreeB; }
        else if (t_filename == "tree-baby")             { return TileImage::TreeBaby; }
        else if (t_filename == "tree-c")                { return TileImage::TreeC; }
        else if (t_filename == "tree-dead-creepy")      { return TileImage::TreeDeadCreepy; }
        else if (t_filename == "tree-dead-large")       { return TileImage::TreeDeadLarge; }
        else if (t_filename == "tree-dead-medium")      { return TileImage::TreeDeadMedium; }
        else if (t_filename == "tree-dead-misc")        { return TileImage::TreeDeadMisc; }
        else if (t_filename == "tree-jungle")           { return TileImage::TreeJungle; }
        else if (t_filename == "tree-snow")             { return TileImage::TreeSnow; }
        else if (t_filename == "water")                 { return TileImage::Water; }
        else if (t_filename == "water2")                { return TileImage::Water2; }
        else
        {
            return TileImage::Count;
        }
        // clang-format on
    }

    constexpr bool isTileImageShadow(const TileImage t_image) noexcept
    {
        if ((t_image == TileImage::InteriorShadow) || (t_image == TileImage::MountainShadow) ||
            (t_image == TileImage::ObjectShadow) || (t_image == TileImage::TownShadow) ||
            (t_image == TileImage::TownWallShadow))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    inline std::string toTileImageFilename(const TileImage t_image)
    {
        std::string filename{ toString(t_image) };
        filename += ".png";
        return filename;
    }

    inline std::ostream & operator<<(std::ostream & t_os, const TileImage t_image)
    {
        t_os << toString(t_image);
        return t_os;
    }

} // namespace thornberry

#endif // TILE_IMAGE_HPP_INCLUDED
