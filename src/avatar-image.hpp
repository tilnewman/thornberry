#ifndef AVATAR_IMAGE_HPP_INCLUDED
#define AVATAR_IMAGE_HPP_INCLUDED
//
// avatar-image.hpp
//
#include <array>
#include <string>
#include <string_view>

namespace thornberry
{

    enum class AvatarImage : std::size_t
    {
        dress_dark_pixie_black = 0,
        dress_dark_pixie_brown,
        dress_dark_pixie_brunette,
        dress_dark_pixie_gray,
        dress_dark_pixie_whiteblonde2,
        dress_dark_shoulderl_black,
        dress_dark_shoulderl_brown,
        dress_dark_shoulderl_brunette,
        dress_dark_shoulderl_gray,
        dress_dark_shoulderl_whiteblonde2,
        dress_dark_shoulderr_black,
        dress_dark_shoulderr_brown,
        dress_dark_shoulderr_brunette,
        dress_dark_shoulderr_gray,
        dress_dark_shoulderr_whiteblonde2,
        dress_dark_swoop_black,
        dress_dark_swoop_brown,
        dress_dark_swoop_brunette,
        dress_dark_swoop_gray,
        dress_dark_swoop_whiteblonde2,
        dress_light_pixie_black,
        dress_light_pixie_blonde2,
        dress_light_pixie_brown,
        dress_light_pixie_brunette,
        dress_light_pixie_brunette2,
        dress_light_pixie_gray,
        dress_light_shoulderl_black,
        dress_light_shoulderl_blonde2,
        dress_light_shoulderl_brown,
        dress_light_shoulderl_brunette,
        dress_light_shoulderl_brunette2,
        dress_light_shoulderl_gray,
        dress_light_shoulderr_black,
        dress_light_shoulderr_blonde2,
        dress_light_shoulderr_brown,
        dress_light_shoulderr_brunette,
        dress_light_shoulderr_brunette2,
        dress_light_shoulderr_gray,
        dress_light_swoop_black,
        dress_light_swoop_blonde2,
        dress_light_swoop_brown,
        dress_light_swoop_brunette,
        dress_light_swoop_brunette2,
        dress_light_swoop_gray,
        girl_dark_loose_black,
        girl_dark_loose_brown,
        girl_dark_loose_brunette,
        girl_dark_loose_brunette2,
        girl_dark_loose_whiteblonde2,
        girl_dark_ponytail2_black,
        girl_dark_ponytail2_brown,
        girl_dark_ponytail2_brunette,
        girl_dark_ponytail2_brunette2,
        girl_dark_ponytail2_whiteblonde2,
        girl_dark_princess_black,
        girl_dark_princess_brown,
        girl_dark_princess_brunette,
        girl_dark_princess_brunette2,
        girl_dark_princess_whiteblonde2,
        girl_dark_unkempt_black,
        girl_dark_unkempt_brown,
        girl_dark_unkempt_brunette,
        girl_dark_unkempt_brunette2,
        girl_dark_unkempt_whiteblonde2,
        girl_light_loose_blonde,
        girl_light_loose_blonde2,
        girl_light_loose_brown,
        girl_light_loose_brunette,
        girl_light_loose_brunette2,
        girl_light_loose_darkblonde,
        girl_light_loose_lightblonde,
        girl_light_loose_lightblonde2,
        girl_light_ponytail2_blonde,
        girl_light_ponytail2_blonde2,
        girl_light_ponytail2_brown,
        girl_light_ponytail2_brunette,
        girl_light_ponytail2_brunette2,
        girl_light_ponytail2_darkblonde,
        girl_light_ponytail2_lightblonde,
        girl_light_ponytail2_lightblonde2,
        girl_light_princess_blonde,
        girl_light_princess_blonde2,
        girl_light_princess_brown,
        girl_light_princess_brunette,
        girl_light_princess_brunette2,
        girl_light_princess_darkblonde,
        girl_light_princess_lightblonde,
        girl_light_princess_lightblonde2,
        girl_light_unkempt_blonde,
        girl_light_unkempt_blonde2,
        girl_light_unkempt_brown,
        girl_light_unkempt_brunette,
        girl_light_unkempt_brunette2,
        girl_light_unkempt_darkblonde,
        girl_light_unkempt_lightblonde,
        girl_light_unkempt_lightblonde2,
        leather_circus1_dark_brunette,
        leather_circus1_dark_raven,
        leather_circus1_dark_white,
        leather_circus1_light_blonde,
        leather_circus1_light_brunette,
        leather_circus1_light_raven,
        leather_circus2_dark_brunette,
        leather_circus2_dark_raven,
        leather_circus2_dark_white,
        leather_circus2_light_blonde,
        leather_circus2_light_brunette,
        leather_circus2_light_raven,
        leather_common1_dark_brunette,
        leather_common1_dark_raven,
        leather_common1_dark_white,
        leather_common1_light_blonde,
        leather_common1_light_brunette,
        leather_common1_light_raven,
        leather_common2_dark_brunette,
        leather_common2_dark_raven,
        leather_common2_dark_white,
        leather_common2_light_blonde,
        leather_common2_light_brunette,
        leather_common2_light_raven,
        leather_common3_dark_brunette,
        leather_common3_dark_raven,
        leather_common3_dark_white,
        leather_common3_light_blonde,
        leather_common3_light_brunette,
        leather_common3_light_raven,
        leather_corporal1_dark,
        leather_corporal1_light,
        leather_corporal2_dark,
        leather_corporal2_light,
        leather_ironarms_dark_brunette,
        leather_ironarms_dark_raven,
        leather_ironarms_dark_white,
        leather_ironarms_light_blonde,
        leather_ironarms_light_brunette,
        leather_ironarms_light_raven,
        leather_ironrich_dark_brunette,
        leather_ironrich_dark_raven,
        leather_ironrich_dark_white,
        leather_ironrich_light_blonde,
        leather_ironrich_light_brunette,
        leather_ironrich_light_raven,
        leather_poor_dark_brunette,
        leather_poor_dark_raven,
        leather_poor_dark_white,
        leather_poor_light_blonde,
        leather_poor_light_brunette,
        leather_poor_light_raven,
        leather_private1_dark_brunette,
        leather_private1_dark_raven,
        leather_private1_dark_white,
        leather_private1_light_blonde,
        leather_private1_light_brunette,
        leather_private1_light_raven,
        leather_private1st1_dark,
        leather_private1st1_light,
        leather_private1st2_dark,
        leather_private1st2_light,
        leather_private1st3_dark,
        leather_private1st3_light,
        leather_private1st4_dark,
        leather_private1st4_light,
        leather_private2_dark_brunette,
        leather_private2_dark_raven,
        leather_private2_dark_white,
        leather_private2_light_blonde,
        leather_private2_light_brunette,
        leather_private2_light_raven,
        leather_private2nd1_dark,
        leather_private2nd1_light,
        leather_private2nd2_dark,
        leather_private2nd2_light,
        leather_private2nd3_dark,
        leather_private2nd3_light,
        leather_private2nd4_dark,
        leather_private2nd4_light,
        leather_private3_dark_brunette,
        leather_private3_dark_raven,
        leather_private3_dark_white,
        leather_private3_light_blonde,
        leather_private3_light_brunette,
        leather_private3_light_raven,
        leather_private4_dark_brunette,
        leather_private4_dark_raven,
        leather_private4_dark_white,
        leather_private4_light_blonde,
        leather_private4_light_brunette,
        leather_private4_light_raven,
        leather_specialist1_dark,
        leather_specialist1_light,
        leather_specialist2_dark,
        leather_specialist2_light,
        leather_thug1_dark_brunette,
        leather_thug1_dark_raven,
        leather_thug1_dark_white,
        leather_thug1_light_blonde,
        leather_thug1_light_brunette,
        leather_thug1_light_raven,
        leather_thug2_dark_brunette,
        leather_thug2_dark_raven,
        leather_thug2_dark_white,
        leather_thug2_light_blonde,
        leather_thug2_light_brunette,
        leather_thug2_light_raven,
        maid_dark_pixie_black,
        maid_dark_pixie_brown,
        maid_dark_pixie_brunette,
        maid_dark_pixie_gray,
        maid_dark_pixie_whiteblonde2,
        maid_dark_shoulderl_black,
        maid_dark_shoulderl_brown,
        maid_dark_shoulderl_brunette,
        maid_dark_shoulderl_gray,
        maid_dark_shoulderl_whiteblonde2,
        maid_dark_shoulderr_black,
        maid_dark_shoulderr_brown,
        maid_dark_shoulderr_brunette,
        maid_dark_shoulderr_gray,
        maid_dark_shoulderr_whiteblonde2,
        maid_dark_swoop_black,
        maid_dark_swoop_brown,
        maid_dark_swoop_brunette,
        maid_dark_swoop_gray,
        maid_dark_swoop_whiteblonde2,
        maid_light_pixie_black,
        maid_light_pixie_blonde2,
        maid_light_pixie_brown,
        maid_light_pixie_brunette,
        maid_light_pixie_brunette2,
        maid_light_shoulderl_black,
        maid_light_shoulderl_blonde2,
        maid_light_shoulderl_brown,
        maid_light_shoulderl_brunette,
        maid_light_shoulderl_brunette2,
        maid_light_shoulderr_black,
        maid_light_shoulderr_blonde2,
        maid_light_shoulderr_brown,
        maid_light_shoulderr_brunette,
        maid_light_shoulderr_brunette2,
        maid_light_swoop_black,
        maid_light_swoop_blonde2,
        maid_light_swoop_brown,
        maid_light_swoop_brunette,
        maid_light_swoop_brunette2,
        metal_female_dark,
        metal_female_light,
        metal_male_dark,
        metal_male_light,
        monk_beltleather_dark_bracer,
        monk_beltleather_dark_nobracer,
        monk_beltleather_tanned2_bracer,
        monk_beltleather_tanned2_nobracer,
        monk_beltnone_dark_bracer,
        monk_beltnone_dark_nobracer,
        monk_beltnone_tanned2_bracer,
        monk_beltnone_tanned2_nobracer,
        monk_beltwhite_dark_bracer,
        monk_beltwhite_dark_nobracer,
        monk_beltwhite_tanned2_bracer,
        monk_beltwhite_tanned2_nobracer,
        monk_shirt_beltnone_dark,
        monk_shirt_beltnone_tanned2,
        monk_shirt_beltwhite_dark,
        monk_shirt_beltwhite_tanned2,
        pants_male_dark_bedhead_brunette,
        pants_male_dark_bedhead_raven,
        pants_male_dark_messy2_brunette,
        pants_male_dark_messy2_raven,
        pants_male_dark_parted_brunette,
        pants_male_dark_parted_raven,
        pants_male_dark_plain_brunette,
        pants_male_dark_plain_raven,
        pants_male_light_bedhead_blonde,
        pants_male_light_bedhead_brunette,
        pants_male_light_bedhead_raven,
        pants_male_light_bedhead_white,
        pants_male_light_messy2_blonde,
        pants_male_light_messy2_brunette,
        pants_male_light_messy2_raven,
        pants_male_light_messy2_white,
        pants_male_light_parted_blonde,
        pants_male_light_parted_brunette,
        pants_male_light_parted_raven,
        pants_male_light_parted_white,
        pants_male_light_plain_blonde,
        pants_male_light_plain_brunette,
        pants_male_light_plain_raven,
        pants_male_light_plain_white,
        plate_gladiator_dark_brunette,
        plate_gladiator_dark_raven,
        plate_gladiator_dark_white,
        plate_gladiator_light_blonde,
        plate_gladiator_light_brunette,
        plate_gladiator_light_raven,
        plate_knight_gold,
        plate_knight,
        plate_major_dark,
        plate_major_light,
        plate_manatarms_dark_brunette,
        plate_manatarms_dark_raven,
        plate_manatarms_dark_white,
        plate_manatarms_light_blonde,
        plate_manatarms_light_brunette,
        plate_manatarms_light_raven,
        plate_sergeant_dark,
        plate_sergeant_light,
        puck_female_dark,
        puck_female_light,
        puck_male_dark,
        puck_male_light,
        rags_female_dark_bangsshort_black,
        rags_female_dark_bangsshort_brown,
        rags_female_dark_bangsshort_brunette,
        rags_female_dark_loose_black,
        rags_female_dark_loose_brown,
        rags_female_dark_loose_brunette,
        rags_female_dark_ponytail_black,
        rags_female_dark_ponytail_brown,
        rags_female_dark_ponytail_brunette,
        rags_female_dark_unkempt_black,
        rags_female_dark_unkempt_brown,
        rags_female_dark_unkempt_brunette,
        rags_female_light_bangsshort_black,
        rags_female_light_bangsshort_blonde2,
        rags_female_light_bangsshort_brown,
        rags_female_light_bangsshort_brunette,
        rags_female_light_bangsshort_brunette2,
        rags_female_light_bangsshort_lightblonde2,
        rags_female_light_loose_black,
        rags_female_light_loose_blonde2,
        rags_female_light_loose_brown,
        rags_female_light_loose_brunette,
        rags_female_light_loose_brunette2,
        rags_female_light_loose_lightblonde2,
        rags_female_light_ponytail_black,
        rags_female_light_ponytail_blonde2,
        rags_female_light_ponytail_brown,
        rags_female_light_ponytail_brunette,
        rags_female_light_ponytail_brunette2,
        rags_female_light_ponytail_lightblonde2,
        rags_female_light_unkempt_black,
        rags_female_light_unkempt_blonde2,
        rags_female_light_unkempt_brown,
        rags_female_light_unkempt_brunette,
        rags_female_light_unkempt_brunette2,
        rags_female_light_unkempt_lightblonde2,
        rags_male_dark_bedhead_brunette,
        rags_male_dark_bedhead_raven,
        rags_male_dark_messy2_brunette,
        rags_male_dark_messy2_raven,
        rags_male_dark_parted_brunette,
        rags_male_dark_parted_raven,
        rags_male_dark_plain_brunette,
        rags_male_dark_plain_raven,
        rags_male_light_bedhead_blonde,
        rags_male_light_bedhead_brunette,
        rags_male_light_bedhead_raven,
        rags_male_light_bedhead_white,
        rags_male_light_messy2_blonde,
        rags_male_light_messy2_brunette,
        rags_male_light_messy2_raven,
        rags_male_light_messy2_white,
        rags_male_light_parted_blonde,
        rags_male_light_parted_brunette,
        rags_male_light_parted_raven,
        rags_male_light_parted_white,
        rags_male_light_plain_blonde,
        rags_male_light_plain_brunette,
        rags_male_light_plain_raven,
        rags_male_light_plain_white,
        robes_male_dark_bedhead_brunette,
        robes_male_dark_bedhead_raven,
        robes_male_dark_messy2_brunette,
        robes_male_dark_messy2_raven,
        robes_male_dark_parted_brunette,
        robes_male_dark_parted_raven,
        robes_male_dark_plain_brunette,
        robes_male_dark_plain_raven,
        robes_male_light_bedhead_blonde,
        robes_male_light_bedhead_brunette,
        robes_male_light_bedhead_raven,
        robes_male_light_bedhead_white,
        robes_male_light_messy2_blonde,
        robes_male_light_messy2_brunette,
        robes_male_light_messy2_raven,
        robes_male_light_messy2_white,
        robes_male_light_parted_blonde,
        robes_male_light_parted_brunette,
        robes_male_light_parted_raven,
        robes_male_light_parted_white,
        robes_male_light_plain_blonde,
        robes_male_light_plain_brunette,
        robes_male_light_plain_raven,
        robes_male_light_plain_white,
        robes_whitebeard,
        sara_bluewhite,
        sara_cyan,
        sara_green,
        sara_white,
        tunic_female_dark_bangsshort_black,
        tunic_female_dark_bangsshort_brown,
        tunic_female_dark_bangsshort_brunette,
        tunic_female_dark_loose_black,
        tunic_female_dark_loose_brown,
        tunic_female_dark_loose_brunette,
        tunic_female_dark_ponytail_black,
        tunic_female_dark_ponytail_brown,
        tunic_female_dark_ponytail_brunette,
        tunic_female_dark_unkempt_black,
        tunic_female_dark_unkempt_brown,
        tunic_female_dark_unkempt_brunette,
        tunic_female_light_bangsshort_black,
        tunic_female_light_bangsshort_blonde2,
        tunic_female_light_bangsshort_brown,
        tunic_female_light_bangsshort_brunette,
        tunic_female_light_bangsshort_brunette2,
        tunic_female_light_bangsshort_lightblonde2,
        tunic_female_light_loose_black,
        tunic_female_light_loose_blonde2,
        tunic_female_light_loose_brown,
        tunic_female_light_loose_brunette,
        tunic_female_light_loose_brunette2,
        tunic_female_light_loose_lightblonde2,
        tunic_female_light_ponytail_black,
        tunic_female_light_ponytail_blonde2,
        tunic_female_light_ponytail_brown,
        tunic_female_light_ponytail_brunette,
        tunic_female_light_ponytail_brunette2,
        tunic_female_light_ponytail_lightblonde2,
        tunic_female_light_unkempt_black,
        tunic_female_light_unkempt_blonde2,
        tunic_female_light_unkempt_brown,
        tunic_female_light_unkempt_brunette,
        tunic_female_light_unkempt_brunette2,
        tunic_female_light_unkempt_lightblonde2,
        count
    };

    constexpr std::string_view toString(const AvatarImage t_avatarImage) noexcept
    {
        // clang-format off
		switch (t_avatarImage)
		{
			case AvatarImage::dress_dark_pixie_black:						{ return "dress-dark-pixie-black"; }
			case AvatarImage::dress_dark_pixie_brown:						{ return "dress-dark-pixie-brown"; }
			case AvatarImage::dress_dark_pixie_brunette:					{ return "dress-dark-pixie-brunette"; }
			case AvatarImage::dress_dark_pixie_gray:						{ return "dress-dark-pixie-gray"; }
			case AvatarImage::dress_dark_pixie_whiteblonde2:				{ return "dress-dark-pixie-whiteblonde2"; }
			case AvatarImage::dress_dark_shoulderl_black:					{ return "dress-dark-shoulderl-black"; }
			case AvatarImage::dress_dark_shoulderl_brown:					{ return "dress-dark-shoulderl-brown"; }
			case AvatarImage::dress_dark_shoulderl_brunette:				{ return "dress-dark-shoulderl-brunette"; }
			case AvatarImage::dress_dark_shoulderl_gray:					{ return "dress-dark-shoulderl-gray"; }
			case AvatarImage::dress_dark_shoulderl_whiteblonde2:			{ return "dress-dark-shoulderl-whiteblonde2"; }
			case AvatarImage::dress_dark_shoulderr_black:					{ return "dress-dark-shoulderr-black"; }
			case AvatarImage::dress_dark_shoulderr_brown:					{ return "dress-dark-shoulderr-brown"; }
			case AvatarImage::dress_dark_shoulderr_brunette:				{ return "dress-dark-shoulderr-brunette"; }
			case AvatarImage::dress_dark_shoulderr_gray:					{ return "dress-dark-shoulderr-gray"; }
			case AvatarImage::dress_dark_shoulderr_whiteblonde2:			{ return "dress-dark-shoulderr-whiteblonde2"; }
			case AvatarImage::dress_dark_swoop_black:						{ return "dress-dark-swoop-black"; }
			case AvatarImage::dress_dark_swoop_brown:						{ return "dress-dark-swoop-brown"; }
			case AvatarImage::dress_dark_swoop_brunette:					{ return "dress-dark-swoop-brunette"; }
			case AvatarImage::dress_dark_swoop_gray:						{ return "dress-dark-swoop-gray"; }
			case AvatarImage::dress_dark_swoop_whiteblonde2:				{ return "dress-dark-swoop-whiteblonde2"; }
			case AvatarImage::dress_light_pixie_black:						{ return "dress-light-pixie-black"; }
			case AvatarImage::dress_light_pixie_blonde2:					{ return "dress-light-pixie-blonde2"; }
			case AvatarImage::dress_light_pixie_brown:						{ return "dress-light-pixie-brown"; }
			case AvatarImage::dress_light_pixie_brunette:					{ return "dress-light-pixie-brunette"; }
			case AvatarImage::dress_light_pixie_brunette2:					{ return "dress-light-pixie-brunette2"; }
			case AvatarImage::dress_light_pixie_gray:						{ return "dress-light-pixie-gray"; }
			case AvatarImage::dress_light_shoulderl_black:					{ return "dress-light-shoulderl-black"; }
			case AvatarImage::dress_light_shoulderl_blonde2:				{ return "dress-light-shoulderl-blonde2"; }
			case AvatarImage::dress_light_shoulderl_brown:					{ return "dress-light-shoulderl-brown"; }
			case AvatarImage::dress_light_shoulderl_brunette:				{ return "dress-light-shoulderl-brunette"; }
			case AvatarImage::dress_light_shoulderl_brunette2:				{ return "dress-light-shoulderl-brunette2"; }
			case AvatarImage::dress_light_shoulderl_gray:					{ return "dress-light-shoulderl-gray"; }
			case AvatarImage::dress_light_shoulderr_black:					{ return "dress-light-shoulderr-black"; }
			case AvatarImage::dress_light_shoulderr_blonde2:				{ return "dress-light-shoulderr-blonde2"; }
			case AvatarImage::dress_light_shoulderr_brown:					{ return "dress-light-shoulderr-brown"; }
			case AvatarImage::dress_light_shoulderr_brunette:				{ return "dress-light-shoulderr-brunette"; }
			case AvatarImage::dress_light_shoulderr_brunette2:				{ return "dress-light-shoulderr-brunette2"; }
			case AvatarImage::dress_light_shoulderr_gray:					{ return "dress-light-shoulderr-gray"; }
			case AvatarImage::dress_light_swoop_black:						{ return "dress-light-swoop-black"; }
			case AvatarImage::dress_light_swoop_blonde2:					{ return "dress-light-swoop-blonde2"; }
			case AvatarImage::dress_light_swoop_brown:						{ return "dress-light-swoop-brown"; }
			case AvatarImage::dress_light_swoop_brunette:					{ return "dress-light-swoop-brunette"; }
			case AvatarImage::dress_light_swoop_brunette2:					{ return "dress-light-swoop-brunette2"; }
			case AvatarImage::dress_light_swoop_gray:						{ return "dress-light-swoop-gray"; }
			case AvatarImage::girl_dark_loose_black:						{ return "girl-dark-loose-black"; }
			case AvatarImage::girl_dark_loose_brown:						{ return "girl-dark-loose-brown"; }
			case AvatarImage::girl_dark_loose_brunette:						{ return "girl-dark-loose-brunette"; }
			case AvatarImage::girl_dark_loose_brunette2:					{ return "girl-dark-loose-brunette2"; }
			case AvatarImage::girl_dark_loose_whiteblonde2:					{ return "girl-dark-loose-whiteblonde2"; }
			case AvatarImage::girl_dark_ponytail2_black:					{ return "girl-dark-ponytail2-black"; }
			case AvatarImage::girl_dark_ponytail2_brown:					{ return "girl-dark-ponytail2-brown"; }
			case AvatarImage::girl_dark_ponytail2_brunette:					{ return "girl-dark-ponytail2-brunette"; }
			case AvatarImage::girl_dark_ponytail2_brunette2:				{ return "girl-dark-ponytail2-brunette2"; }
			case AvatarImage::girl_dark_ponytail2_whiteblonde2:				{ return "girl-dark-ponytail2-whiteblonde2"; }
			case AvatarImage::girl_dark_princess_black:						{ return "girl-dark-princess-black"; }
			case AvatarImage::girl_dark_princess_brown:						{ return "girl-dark-princess-brown"; }
			case AvatarImage::girl_dark_princess_brunette:					{ return "girl-dark-princess-brunette"; }
			case AvatarImage::girl_dark_princess_brunette2:					{ return "girl-dark-princess-brunette2"; }
			case AvatarImage::girl_dark_princess_whiteblonde2:				{ return "girl-dark-princess-whiteblonde2"; }
			case AvatarImage::girl_dark_unkempt_black:						{ return "girl-dark-unkempt-black"; }
			case AvatarImage::girl_dark_unkempt_brown:						{ return "girl-dark-unkempt-brown"; }
			case AvatarImage::girl_dark_unkempt_brunette:					{ return "girl-dark-unkempt-brunette"; }
			case AvatarImage::girl_dark_unkempt_brunette2:					{ return "girl-dark-unkempt-brunette2"; }
			case AvatarImage::girl_dark_unkempt_whiteblonde2:				{ return "girl-dark-unkempt-whiteblonde2"; }
			case AvatarImage::girl_light_loose_blonde:						{ return "girl-light-loose-blonde"; }
			case AvatarImage::girl_light_loose_blonde2:						{ return "girl-light-loose-blonde2"; }
			case AvatarImage::girl_light_loose_brown:						{ return "girl-light-loose-brown"; }
			case AvatarImage::girl_light_loose_brunette:					{ return "girl-light-loose-brunette"; }
			case AvatarImage::girl_light_loose_brunette2:					{ return "girl-light-loose-brunette2"; }
			case AvatarImage::girl_light_loose_darkblonde:					{ return "girl-light-loose-darkblonde"; }
			case AvatarImage::girl_light_loose_lightblonde:					{ return "girl-light-loose-lightblonde"; }
			case AvatarImage::girl_light_loose_lightblonde2:				{ return "girl-light-loose-lightblonde2"; }
			case AvatarImage::girl_light_ponytail2_blonde:					{ return "girl-light-ponytail2-blonde"; }
			case AvatarImage::girl_light_ponytail2_blonde2:					{ return "girl-light-ponytail2-blonde2"; }
			case AvatarImage::girl_light_ponytail2_brown:					{ return "girl-light-ponytail2-brown"; }
			case AvatarImage::girl_light_ponytail2_brunette:				{ return "girl-light-ponytail2-brunette"; }
			case AvatarImage::girl_light_ponytail2_brunette2:				{ return "girl-light-ponytail2-brunette2"; }
			case AvatarImage::girl_light_ponytail2_darkblonde:				{ return "girl-light-ponytail2-darkblonde"; }
			case AvatarImage::girl_light_ponytail2_lightblonde:				{ return "girl-light-ponytail2-lightblonde"; }
			case AvatarImage::girl_light_ponytail2_lightblonde2:			{ return "girl-light-ponytail2-lightblonde2"; }
			case AvatarImage::girl_light_princess_blonde:					{ return "girl-light-princess-blonde"; }
			case AvatarImage::girl_light_princess_blonde2:					{ return "girl-light-princess-blonde2"; }
			case AvatarImage::girl_light_princess_brown:					{ return "girl-light-princess-brown"; }
			case AvatarImage::girl_light_princess_brunette:					{ return "girl-light-princess-brunette"; }
			case AvatarImage::girl_light_princess_brunette2:				{ return "girl-light-princess-brunette2"; }
			case AvatarImage::girl_light_princess_darkblonde:				{ return "girl-light-princess-darkblonde"; }
			case AvatarImage::girl_light_princess_lightblonde:				{ return "girl-light-princess-lightblonde"; }
			case AvatarImage::girl_light_princess_lightblonde2:				{ return "girl-light-princess-lightblonde2"; }
			case AvatarImage::girl_light_unkempt_blonde:					{ return "girl-light-unkempt-blonde"; }
			case AvatarImage::girl_light_unkempt_blonde2:					{ return "girl-light-unkempt-blonde2"; }
			case AvatarImage::girl_light_unkempt_brown:						{ return "girl-light-unkempt-brown"; }
			case AvatarImage::girl_light_unkempt_brunette:					{ return "girl-light-unkempt-brunette"; }
			case AvatarImage::girl_light_unkempt_brunette2:					{ return "girl-light-unkempt-brunette2"; }
			case AvatarImage::girl_light_unkempt_darkblonde:				{ return "girl-light-unkempt-darkblonde"; }
			case AvatarImage::girl_light_unkempt_lightblonde:				{ return "girl-light-unkempt-lightblonde"; }
			case AvatarImage::girl_light_unkempt_lightblonde2:				{ return "girl-light-unkempt-lightblonde2"; }
			case AvatarImage::leather_circus1_dark_brunette:				{ return "leather-circus1-dark-brunette"; }
			case AvatarImage::leather_circus1_dark_raven:					{ return "leather-circus1-dark-raven"; }
			case AvatarImage::leather_circus1_dark_white:					{ return "leather-circus1-dark-white"; }
			case AvatarImage::leather_circus1_light_blonde:					{ return "leather-circus1-light-blonde"; }
			case AvatarImage::leather_circus1_light_brunette:				{ return "leather-circus1-light-brunette"; }
			case AvatarImage::leather_circus1_light_raven:					{ return "leather-circus1-light-raven"; }
			case AvatarImage::leather_circus2_dark_brunette:				{ return "leather-circus2-dark-brunette"; }
			case AvatarImage::leather_circus2_dark_raven:					{ return "leather-circus2-dark-raven"; }
			case AvatarImage::leather_circus2_dark_white:					{ return "leather-circus2-dark-white"; }
			case AvatarImage::leather_circus2_light_blonde:					{ return "leather-circus2-light-blonde"; }
			case AvatarImage::leather_circus2_light_brunette:				{ return "leather-circus2-light-brunette"; }
			case AvatarImage::leather_circus2_light_raven:					{ return "leather-circus2-light-raven"; }
			case AvatarImage::leather_common1_dark_brunette:				{ return "leather-common1-dark-brunette"; }
			case AvatarImage::leather_common1_dark_raven:					{ return "leather-common1-dark-raven"; }
			case AvatarImage::leather_common1_dark_white:					{ return "leather-common1-dark-white"; }
			case AvatarImage::leather_common1_light_blonde:					{ return "leather-common1-light-blonde"; }
			case AvatarImage::leather_common1_light_brunette:				{ return "leather-common1-light-brunette"; }
			case AvatarImage::leather_common1_light_raven:					{ return "leather-common1-light-raven"; }
			case AvatarImage::leather_common2_dark_brunette:				{ return "leather-common2-dark-brunette"; }
			case AvatarImage::leather_common2_dark_raven:					{ return "leather-common2-dark-raven"; }
			case AvatarImage::leather_common2_dark_white:					{ return "leather-common2-dark-white"; }
			case AvatarImage::leather_common2_light_blonde:					{ return "leather-common2-light-blonde"; }
			case AvatarImage::leather_common2_light_brunette:				{ return "leather-common2-light-brunette"; }
			case AvatarImage::leather_common2_light_raven:					{ return "leather-common2-light-raven"; }
			case AvatarImage::leather_common3_dark_brunette:				{ return "leather-common3-dark-brunette"; }
			case AvatarImage::leather_common3_dark_raven:					{ return "leather-common3-dark-raven"; }
			case AvatarImage::leather_common3_dark_white:					{ return "leather-common3-dark-white"; }
			case AvatarImage::leather_common3_light_blonde:					{ return "leather-common3-light-blonde"; }
			case AvatarImage::leather_common3_light_brunette:				{ return "leather-common3-light-brunette"; }
			case AvatarImage::leather_common3_light_raven:					{ return "leather-common3-light-raven"; }
			case AvatarImage::leather_corporal1_dark:						{ return "leather-corporal1-dark"; }
			case AvatarImage::leather_corporal1_light:						{ return "leather-corporal1-light"; }
			case AvatarImage::leather_corporal2_dark:						{ return "leather-corporal2-dark"; }
			case AvatarImage::leather_corporal2_light:						{ return "leather-corporal2-light"; }
			case AvatarImage::leather_ironarms_dark_brunette:				{ return "leather-ironarms-dark-brunette"; }
			case AvatarImage::leather_ironarms_dark_raven:					{ return "leather-ironarms-dark-raven"; }
			case AvatarImage::leather_ironarms_dark_white:					{ return "leather-ironarms-dark-white"; }
			case AvatarImage::leather_ironarms_light_blonde:				{ return "leather-ironarms-light-blonde"; }
			case AvatarImage::leather_ironarms_light_brunette:				{ return "leather-ironarms-light-brunette"; }
			case AvatarImage::leather_ironarms_light_raven:					{ return "leather-ironarms-light-raven"; }
			case AvatarImage::leather_ironrich_dark_brunette:				{ return "leather-ironrich-dark-brunette"; }
			case AvatarImage::leather_ironrich_dark_raven:					{ return "leather-ironrich-dark-raven"; }
			case AvatarImage::leather_ironrich_dark_white:					{ return "leather-ironrich-dark-white"; }
			case AvatarImage::leather_ironrich_light_blonde:				{ return "leather-ironrich-light-blonde"; }
			case AvatarImage::leather_ironrich_light_brunette:				{ return "leather-ironrich-light-brunette"; }
			case AvatarImage::leather_ironrich_light_raven:					{ return "leather-ironrich-light-raven"; }
			case AvatarImage::leather_poor_dark_brunette:					{ return "leather-poor-dark-brunette"; }
			case AvatarImage::leather_poor_dark_raven:						{ return "leather-poor-dark-raven"; }
			case AvatarImage::leather_poor_dark_white:						{ return "leather-poor-dark-white"; }
			case AvatarImage::leather_poor_light_blonde:					{ return "leather-poor-light-blonde"; }
			case AvatarImage::leather_poor_light_brunette:					{ return "leather-poor-light-brunette"; }
			case AvatarImage::leather_poor_light_raven:						{ return "leather-poor-light-raven"; }
			case AvatarImage::leather_private1_dark_brunette:				{ return "leather-private1-dark-brunette"; }
			case AvatarImage::leather_private1_dark_raven:					{ return "leather-private1-dark-raven"; }
			case AvatarImage::leather_private1_dark_white:					{ return "leather-private1-dark-white"; }
			case AvatarImage::leather_private1_light_blonde:				{ return "leather-private1-light-blonde"; }
			case AvatarImage::leather_private1_light_brunette:				{ return "leather-private1-light-brunette"; }
			case AvatarImage::leather_private1_light_raven:					{ return "leather-private1-light-raven"; }
			case AvatarImage::leather_private1st1_dark:						{ return "leather-private1st1-dark"; }
			case AvatarImage::leather_private1st1_light:					{ return "leather-private1st1-light"; }
			case AvatarImage::leather_private1st2_dark:						{ return "leather-private1st2-dark"; }
			case AvatarImage::leather_private1st2_light:					{ return "leather-private1st2-light"; }
			case AvatarImage::leather_private1st3_dark:						{ return "leather-private1st3-dark"; }
			case AvatarImage::leather_private1st3_light:					{ return "leather-private1st3-light"; }
			case AvatarImage::leather_private1st4_dark:						{ return "leather-private1st4-dark"; }
			case AvatarImage::leather_private1st4_light:					{ return "leather-private1st4-light"; }
			case AvatarImage::leather_private2_dark_brunette:				{ return "leather-private2-dark-brunette"; }
			case AvatarImage::leather_private2_dark_raven:					{ return "leather-private2-dark-raven"; }
			case AvatarImage::leather_private2_dark_white:					{ return "leather-private2-dark-white"; }
			case AvatarImage::leather_private2_light_blonde:				{ return "leather-private2-light-blonde"; }
			case AvatarImage::leather_private2_light_brunette:				{ return "leather-private2-light-brunette"; }
			case AvatarImage::leather_private2_light_raven:					{ return "leather-private2-light-raven"; }
			case AvatarImage::leather_private2nd1_dark:						{ return "leather-private2nd1-dark"; }
			case AvatarImage::leather_private2nd1_light:					{ return "leather-private2nd1-light"; }
			case AvatarImage::leather_private2nd2_dark:						{ return "leather-private2nd2-dark"; }
			case AvatarImage::leather_private2nd2_light:					{ return "leather-private2nd2-light"; }
			case AvatarImage::leather_private2nd3_dark:						{ return "leather-private2nd3-dark"; }
			case AvatarImage::leather_private2nd3_light:					{ return "leather-private2nd3-light"; }
			case AvatarImage::leather_private2nd4_dark:						{ return "leather-private2nd4-dark"; }
			case AvatarImage::leather_private2nd4_light:					{ return "leather-private2nd4-light"; }
			case AvatarImage::leather_private3_dark_brunette:				{ return "leather-private3-dark-brunette"; }
			case AvatarImage::leather_private3_dark_raven:					{ return "leather-private3-dark-raven"; }
			case AvatarImage::leather_private3_dark_white:					{ return "leather-private3-dark-white"; }
			case AvatarImage::leather_private3_light_blonde:				{ return "leather-private3-light-blonde"; }
			case AvatarImage::leather_private3_light_brunette:				{ return "leather-private3-light-brunette"; }
			case AvatarImage::leather_private3_light_raven:					{ return "leather-private3-light-raven"; }
			case AvatarImage::leather_private4_dark_brunette:				{ return "leather-private4-dark-brunette"; }
			case AvatarImage::leather_private4_dark_raven:					{ return "leather-private4-dark-raven"; }
			case AvatarImage::leather_private4_dark_white:					{ return "leather-private4-dark-white"; }
			case AvatarImage::leather_private4_light_blonde:				{ return "leather-private4-light-blonde"; }
			case AvatarImage::leather_private4_light_brunette:				{ return "leather-private4-light-brunette"; }
			case AvatarImage::leather_private4_light_raven:					{ return "leather-private4-light-raven"; }
			case AvatarImage::leather_specialist1_dark:						{ return "leather-specialist1-dark"; }
			case AvatarImage::leather_specialist1_light:					{ return "leather-specialist1-light"; }
			case AvatarImage::leather_specialist2_dark:						{ return "leather-specialist2-dark"; }
			case AvatarImage::leather_specialist2_light:					{ return "leather-specialist2-light"; }
			case AvatarImage::leather_thug1_dark_brunette:					{ return "leather-thug1-dark-brunette"; }
			case AvatarImage::leather_thug1_dark_raven:						{ return "leather-thug1-dark-raven"; }
			case AvatarImage::leather_thug1_dark_white:						{ return "leather-thug1-dark-white"; }
			case AvatarImage::leather_thug1_light_blonde:					{ return "leather-thug1-light-blonde"; }
			case AvatarImage::leather_thug1_light_brunette:					{ return "leather-thug1-light-brunette"; }
			case AvatarImage::leather_thug1_light_raven:					{ return "leather-thug1-light-raven"; }
			case AvatarImage::leather_thug2_dark_brunette:					{ return "leather-thug2-dark-brunette"; }
			case AvatarImage::leather_thug2_dark_raven:						{ return "leather-thug2-dark-raven"; }
			case AvatarImage::leather_thug2_dark_white:						{ return "leather-thug2-dark-white"; }
			case AvatarImage::leather_thug2_light_blonde:					{ return "leather-thug2-light-blonde"; }
			case AvatarImage::leather_thug2_light_brunette:					{ return "leather-thug2-light-brunette"; }
			case AvatarImage::leather_thug2_light_raven:					{ return "leather-thug2-light-raven"; }
			case AvatarImage::maid_dark_pixie_black:						{ return "maid-dark-pixie-black"; }
			case AvatarImage::maid_dark_pixie_brown:						{ return "maid-dark-pixie-brown"; }
			case AvatarImage::maid_dark_pixie_brunette:						{ return "maid-dark-pixie-brunette"; }
			case AvatarImage::maid_dark_pixie_gray:							{ return "maid-dark-pixie-gray"; }
			case AvatarImage::maid_dark_pixie_whiteblonde2:					{ return "maid-dark-pixie-whiteblonde2"; }
			case AvatarImage::maid_dark_shoulderl_black:					{ return "maid-dark-shoulderl-black"; }
			case AvatarImage::maid_dark_shoulderl_brown:					{ return "maid-dark-shoulderl-brown"; }
			case AvatarImage::maid_dark_shoulderl_brunette:					{ return "maid-dark-shoulderl-brunette"; }
			case AvatarImage::maid_dark_shoulderl_gray:						{ return "maid-dark-shoulderl-gray"; }
			case AvatarImage::maid_dark_shoulderl_whiteblonde2:				{ return "maid-dark-shoulderl-whiteblonde2"; }
			case AvatarImage::maid_dark_shoulderr_black:					{ return "maid-dark-shoulderr-black"; }
			case AvatarImage::maid_dark_shoulderr_brown:					{ return "maid-dark-shoulderr-brown"; }
			case AvatarImage::maid_dark_shoulderr_brunette:					{ return "maid-dark-shoulderr-brunette"; }
			case AvatarImage::maid_dark_shoulderr_gray:						{ return "maid-dark-shoulderr-gray"; }
			case AvatarImage::maid_dark_shoulderr_whiteblonde2:				{ return "maid-dark-shoulderr-whiteblonde2"; }
			case AvatarImage::maid_dark_swoop_black:						{ return "maid-dark-swoop-black"; }
			case AvatarImage::maid_dark_swoop_brown:						{ return "maid-dark-swoop-brown"; }
			case AvatarImage::maid_dark_swoop_brunette:						{ return "maid-dark-swoop-brunette"; }
			case AvatarImage::maid_dark_swoop_gray:							{ return "maid-dark-swoop-gray"; }
			case AvatarImage::maid_dark_swoop_whiteblonde2:					{ return "maid-dark-swoop-whiteblonde2"; }
			case AvatarImage::maid_light_pixie_black:						{ return "maid-light-pixie-black"; }
			case AvatarImage::maid_light_pixie_blonde2:						{ return "maid-light-pixie-blonde2"; }
			case AvatarImage::maid_light_pixie_brown:						{ return "maid-light-pixie-brown"; }
			case AvatarImage::maid_light_pixie_brunette:					{ return "maid-light-pixie-brunette"; }
			case AvatarImage::maid_light_pixie_brunette2:					{ return "maid-light-pixie-brunette2"; }
			case AvatarImage::maid_light_shoulderl_black:					{ return "maid-light-shoulderl-black"; }
			case AvatarImage::maid_light_shoulderl_blonde2:					{ return "maid-light-shoulderl-blonde2"; }
			case AvatarImage::maid_light_shoulderl_brown:					{ return "maid-light-shoulderl-brown"; }
			case AvatarImage::maid_light_shoulderl_brunette:				{ return "maid-light-shoulderl-brunette"; }
			case AvatarImage::maid_light_shoulderl_brunette2:				{ return "maid-light-shoulderl-brunette2"; }
			case AvatarImage::maid_light_shoulderr_black:					{ return "maid-light-shoulderr-black"; }
			case AvatarImage::maid_light_shoulderr_blonde2:					{ return "maid-light-shoulderr-blonde2"; }
			case AvatarImage::maid_light_shoulderr_brown:					{ return "maid-light-shoulderr-brown"; }
			case AvatarImage::maid_light_shoulderr_brunette:				{ return "maid-light-shoulderr-brunette"; }
			case AvatarImage::maid_light_shoulderr_brunette2:				{ return "maid-light-shoulderr-brunette2"; }
			case AvatarImage::maid_light_swoop_black:						{ return "maid-light-swoop-black"; }
			case AvatarImage::maid_light_swoop_blonde2:						{ return "maid-light-swoop-blonde2"; }
			case AvatarImage::maid_light_swoop_brown:						{ return "maid-light-swoop-brown"; }
			case AvatarImage::maid_light_swoop_brunette:					{ return "maid-light-swoop-brunette"; }
			case AvatarImage::maid_light_swoop_brunette2:					{ return "maid-light-swoop-brunette2"; }
			case AvatarImage::metal_female_dark:							{ return "metal-female-dark"; }
			case AvatarImage::metal_female_light:							{ return "metal-female-light"; }
			case AvatarImage::metal_male_dark:								{ return "metal-male-dark"; }
			case AvatarImage::metal_male_light:								{ return "metal-male-light"; }
			case AvatarImage::monk_beltleather_dark_bracer:					{ return "monk-beltleather-dark-bracer"; }
			case AvatarImage::monk_beltleather_dark_nobracer:				{ return "monk-beltleather-dark-nobracer"; }
			case AvatarImage::monk_beltleather_tanned2_bracer:				{ return "monk-beltleather-tanned2-bracer"; }
			case AvatarImage::monk_beltleather_tanned2_nobracer:			{ return "monk-beltleather-tanned2-nobracer"; }
			case AvatarImage::monk_beltnone_dark_bracer:					{ return "monk-beltnone-dark-bracer"; }
			case AvatarImage::monk_beltnone_dark_nobracer:					{ return "monk-beltnone-dark-nobracer"; }
			case AvatarImage::monk_beltnone_tanned2_bracer:					{ return "monk-beltnone-tanned2-bracer"; }
			case AvatarImage::monk_beltnone_tanned2_nobracer:				{ return "monk-beltnone-tanned2-nobracer"; }
			case AvatarImage::monk_beltwhite_dark_bracer:					{ return "monk-beltwhite-dark-bracer"; }
			case AvatarImage::monk_beltwhite_dark_nobracer:					{ return "monk-beltwhite-dark-nobracer"; }
			case AvatarImage::monk_beltwhite_tanned2_bracer:				{ return "monk-beltwhite-tanned2-bracer"; }
			case AvatarImage::monk_beltwhite_tanned2_nobracer:				{ return "monk-beltwhite-tanned2-nobracer"; }
			case AvatarImage::monk_shirt_beltnone_dark:						{ return "monk-shirt-beltnone-dark"; }
			case AvatarImage::monk_shirt_beltnone_tanned2:					{ return "monk-shirt-beltnone-tanned2"; }
			case AvatarImage::monk_shirt_beltwhite_dark:					{ return "monk-shirt-beltwhite-dark"; }
			case AvatarImage::monk_shirt_beltwhite_tanned2:					{ return "monk-shirt-beltwhite-tanned2"; }
			case AvatarImage::pants_male_dark_bedhead_brunette:				{ return "pants-male-dark-bedhead-brunette"; }
			case AvatarImage::pants_male_dark_bedhead_raven:				{ return "pants-male-dark-bedhead-raven"; }
			case AvatarImage::pants_male_dark_messy2_brunette:				{ return "pants-male-dark-messy2-brunette"; }
			case AvatarImage::pants_male_dark_messy2_raven:					{ return "pants-male-dark-messy2-raven"; }
			case AvatarImage::pants_male_dark_parted_brunette:				{ return "pants-male-dark-parted-brunette"; }
			case AvatarImage::pants_male_dark_parted_raven:					{ return "pants-male-dark-parted-raven"; }
			case AvatarImage::pants_male_dark_plain_brunette:				{ return "pants-male-dark-plain-brunette"; }
			case AvatarImage::pants_male_dark_plain_raven:					{ return "pants-male-dark-plain-raven"; }
			case AvatarImage::pants_male_light_bedhead_blonde:				{ return "pants-male-light-bedhead-blonde"; }
			case AvatarImage::pants_male_light_bedhead_brunette:			{ return "pants-male-light-bedhead-brunette"; }
			case AvatarImage::pants_male_light_bedhead_raven:				{ return "pants-male-light-bedhead-raven"; }
			case AvatarImage::pants_male_light_bedhead_white:				{ return "pants-male-light-bedhead-white"; }
			case AvatarImage::pants_male_light_messy2_blonde:				{ return "pants-male-light-messy2-blonde"; }
			case AvatarImage::pants_male_light_messy2_brunette:				{ return "pants-male-light-messy2-brunette"; }
			case AvatarImage::pants_male_light_messy2_raven:				{ return "pants-male-light-messy2-raven"; }
			case AvatarImage::pants_male_light_messy2_white:				{ return "pants-male-light-messy2-white"; }
			case AvatarImage::pants_male_light_parted_blonde:				{ return "pants-male-light-parted-blonde"; }
			case AvatarImage::pants_male_light_parted_brunette:				{ return "pants-male-light-parted-brunette"; }
			case AvatarImage::pants_male_light_parted_raven:				{ return "pants-male-light-parted-raven"; }
			case AvatarImage::pants_male_light_parted_white:				{ return "pants-male-light-parted-white"; }
			case AvatarImage::pants_male_light_plain_blonde:				{ return "pants-male-light-plain-blonde"; }
			case AvatarImage::pants_male_light_plain_brunette:				{ return "pants-male-light-plain-brunette"; }
			case AvatarImage::pants_male_light_plain_raven:					{ return "pants-male-light-plain-raven"; }
			case AvatarImage::pants_male_light_plain_white:					{ return "pants-male-light-plain-white"; }
			case AvatarImage::plate_gladiator_dark_brunette:				{ return "plate-gladiator-dark-brunette"; }
			case AvatarImage::plate_gladiator_dark_raven:					{ return "plate-gladiator-dark-raven"; }
			case AvatarImage::plate_gladiator_dark_white:					{ return "plate-gladiator-dark-white"; }
			case AvatarImage::plate_gladiator_light_blonde:					{ return "plate-gladiator-light-blonde"; }
			case AvatarImage::plate_gladiator_light_brunette:				{ return "plate-gladiator-light-brunette"; }
			case AvatarImage::plate_gladiator_light_raven:					{ return "plate-gladiator-light-raven"; }
			case AvatarImage::plate_knight_gold:							{ return "plate-knight-gold"; }
			case AvatarImage::plate_knight:									{ return "plate-knight"; }
			case AvatarImage::plate_major_dark:								{ return "plate-major-dark"; }
			case AvatarImage::plate_major_light:							{ return "plate-major-light"; }
			case AvatarImage::plate_manatarms_dark_brunette:				{ return "plate-manatarms-dark-brunette"; }
			case AvatarImage::plate_manatarms_dark_raven:					{ return "plate-manatarms-dark-raven"; }
			case AvatarImage::plate_manatarms_dark_white:					{ return "plate-manatarms-dark-white"; }
			case AvatarImage::plate_manatarms_light_blonde:					{ return "plate-manatarms-light-blonde"; }
			case AvatarImage::plate_manatarms_light_brunette:				{ return "plate-manatarms-light-brunette"; }
			case AvatarImage::plate_manatarms_light_raven:					{ return "plate-manatarms-light-raven"; }
			case AvatarImage::plate_sergeant_dark:							{ return "plate-sergeant-dark"; }
			case AvatarImage::plate_sergeant_light:							{ return "plate-sergeant-light"; }
			case AvatarImage::puck_female_dark:								{ return "puck-female-dark"; }
			case AvatarImage::puck_female_light:							{ return "puck-female-light"; }
			case AvatarImage::puck_male_dark:								{ return "puck-male-dark"; }
			case AvatarImage::puck_male_light:								{ return "puck-male-light"; }
			case AvatarImage::rags_female_dark_bangsshort_black:			{ return "rags-female-dark-bangsshort-black"; }
			case AvatarImage::rags_female_dark_bangsshort_brown:			{ return "rags-female-dark-bangsshort-brown"; }
			case AvatarImage::rags_female_dark_bangsshort_brunette:			{ return "rags-female-dark-bangsshort-brunette"; }
			case AvatarImage::rags_female_dark_loose_black:					{ return "rags-female-dark-loose-black"; }
			case AvatarImage::rags_female_dark_loose_brown:					{ return "rags-female-dark-loose-brown"; }
			case AvatarImage::rags_female_dark_loose_brunette:				{ return "rags-female-dark-loose-brunette"; }
			case AvatarImage::rags_female_dark_ponytail_black:				{ return "rags-female-dark-ponytail-black"; }
			case AvatarImage::rags_female_dark_ponytail_brown:				{ return "rags-female-dark-ponytail-brown"; }
			case AvatarImage::rags_female_dark_ponytail_brunette:			{ return "rags-female-dark-ponytail-brunette"; }
			case AvatarImage::rags_female_dark_unkempt_black:				{ return "rags-female-dark-unkempt-black"; }
			case AvatarImage::rags_female_dark_unkempt_brown:				{ return "rags-female-dark-unkempt-brown"; }
			case AvatarImage::rags_female_dark_unkempt_brunette:			{ return "rags-female-dark-unkempt-brunette"; }
			case AvatarImage::rags_female_light_bangsshort_black:			{ return "rags-female-light-bangsshort-black"; }
			case AvatarImage::rags_female_light_bangsshort_blonde2:			{ return "rags-female-light-bangsshort-blonde2"; }
			case AvatarImage::rags_female_light_bangsshort_brown:			{ return "rags-female-light-bangsshort-brown"; }
			case AvatarImage::rags_female_light_bangsshort_brunette:		{ return "rags-female-light-bangsshort-brunette"; }
			case AvatarImage::rags_female_light_bangsshort_brunette2:		{ return "rags-female-light-bangsshort-brunette2"; }
			case AvatarImage::rags_female_light_bangsshort_lightblonde2:	{ return "rags-female-light-bangsshort-lightblonde2"; }
			case AvatarImage::rags_female_light_loose_black:                { return "rags-female-light-loose-black"; }
			case AvatarImage::rags_female_light_loose_blonde2:              { return "rags-female-light-loose-blonde2"; }
			case AvatarImage::rags_female_light_loose_brown:                { return "rags-female-light-loose-brown"; }
			case AvatarImage::rags_female_light_loose_brunette:             { return "rags-female-light-loose-brunette"; }
			case AvatarImage::rags_female_light_loose_brunette2:            { return "rags-female-light-loose-brunette2"; }
			case AvatarImage::rags_female_light_loose_lightblonde2:         { return "rags-female-light-loose-lightblonde2"; }
			case AvatarImage::rags_female_light_ponytail_black:             { return "rags-female-light-ponytail-black"; }
			case AvatarImage::rags_female_light_ponytail_blonde2:           { return "rags-female-light-ponytail-blonde2"; }
			case AvatarImage::rags_female_light_ponytail_brown:             { return "rags-female-light-ponytail-brown"; }
			case AvatarImage::rags_female_light_ponytail_brunette:          { return "rags-female-light-ponytail-brunette"; }
			case AvatarImage::rags_female_light_ponytail_brunette2:         { return "rags-female-light-ponytail-brunette2"; }
			case AvatarImage::rags_female_light_ponytail_lightblonde2:      { return "rags-female-light-ponytail-lightblonde2"; }
			case AvatarImage::rags_female_light_unkempt_black:				{ return "rags-female-light-unkempt-black"; }
			case AvatarImage::rags_female_light_unkempt_blonde2:			{ return "rags-female-light-unkempt-blonde2"; }
			case AvatarImage::rags_female_light_unkempt_brown:				{ return "rags-female-light-unkempt-brown"; }
			case AvatarImage::rags_female_light_unkempt_brunette:			{ return "rags-female-light-unkempt-brunette"; }
			case AvatarImage::rags_female_light_unkempt_brunette2:			{ return "rags-female-light-unkempt-brunette2"; }
			case AvatarImage::rags_female_light_unkempt_lightblonde2:       { return "rags-female-light-unkempt-lightblonde2"; }
			case AvatarImage::rags_male_dark_bedhead_brunette:				{ return "rags-male-dark-bedhead-brunette"; }
			case AvatarImage::rags_male_dark_bedhead_raven:					{ return "rags-male-dark-bedhead-raven"; }
			case AvatarImage::rags_male_dark_messy2_brunette:				{ return "rags-male-dark-messy2-brunette"; }
			case AvatarImage::rags_male_dark_messy2_raven:					{ return "rags-male-dark-messy2-raven"; }
			case AvatarImage::rags_male_dark_parted_brunette:				{ return "rags-male-dark-parted-brunette"; }
			case AvatarImage::rags_male_dark_parted_raven:					{ return "rags-male-dark-parted-raven"; }
			case AvatarImage::rags_male_dark_plain_brunette:				{ return "rags-male-dark-plain-brunette"; }
			case AvatarImage::rags_male_dark_plain_raven:					{ return "rags-male-dark-plain-raven"; }
			case AvatarImage::rags_male_light_bedhead_blonde:				{ return "rags-male-light-bedhead-blonde"; }
			case AvatarImage::rags_male_light_bedhead_brunette:				{ return "rags-male-light-bedhead-brunette"; }
			case AvatarImage::rags_male_light_bedhead_raven:				{ return "rags-male-light-bedhead-raven"; }
			case AvatarImage::rags_male_light_bedhead_white:				{ return "rags-male-light-bedhead-white"; }
			case AvatarImage::rags_male_light_messy2_blonde:				{ return "rags-male-light-messy2-blonde"; }
			case AvatarImage::rags_male_light_messy2_brunette:				{ return "rags-male-light-messy2-brunette"; }
			case AvatarImage::rags_male_light_messy2_raven:					{ return "rags-male-light-messy2-raven"; }
			case AvatarImage::rags_male_light_messy2_white:					{ return "rags-male-light-messy2-white"; }
			case AvatarImage::rags_male_light_parted_blonde:				{ return "rags-male-light-parted-blonde"; }
			case AvatarImage::rags_male_light_parted_brunette:				{ return "rags-male-light-parted-brunette"; }
			case AvatarImage::rags_male_light_parted_raven:					{ return "rags-male-light-parted-raven"; }
			case AvatarImage::rags_male_light_parted_white:					{ return "rags-male-light-parted-white"; }
			case AvatarImage::rags_male_light_plain_blonde:					{ return "rags-male-light-plain-blonde"; }
			case AvatarImage::rags_male_light_plain_brunette:				{ return "rags-male-light-plain-brunette"; }
			case AvatarImage::rags_male_light_plain_raven:					{ return "rags-male-light-plain-raven"; }
			case AvatarImage::rags_male_light_plain_white:					{ return "rags-male-light-plain-white"; }
			case AvatarImage::robes_male_dark_bedhead_brunette:				{ return "robes-male-dark-bedhead-brunette"; }
			case AvatarImage::robes_male_dark_bedhead_raven:				{ return "robes-male-dark-bedhead-raven"; }
			case AvatarImage::robes_male_dark_messy2_brunette:				{ return "robes-male-dark-messy2-brunette"; }
			case AvatarImage::robes_male_dark_messy2_raven:					{ return "robes-male-dark-messy2-raven"; }
			case AvatarImage::robes_male_dark_parted_brunette:				{ return "robes-male-dark-parted-brunette"; }
			case AvatarImage::robes_male_dark_parted_raven:					{ return "robes-male-dark-parted-raven"; }
			case AvatarImage::robes_male_dark_plain_brunette:				{ return "robes-male-dark-plain-brunette"; }
			case AvatarImage::robes_male_dark_plain_raven:					{ return "robes-male-dark-plain-raven"; }
			case AvatarImage::robes_male_light_bedhead_blonde:				{ return "robes-male-light-bedhead-blonde"; }
			case AvatarImage::robes_male_light_bedhead_brunette:			{ return "robes-male-light-bedhead-brunette"; }
			case AvatarImage::robes_male_light_bedhead_raven:				{ return "robes-male-light-bedhead-raven"; }
			case AvatarImage::robes_male_light_bedhead_white:				{ return "robes-male-light-bedhead-white"; }
			case AvatarImage::robes_male_light_messy2_blonde:				{ return "robes-male-light-messy2-blonde"; }
			case AvatarImage::robes_male_light_messy2_brunette:				{ return "robes-male-light-messy2-brunette"; }
			case AvatarImage::robes_male_light_messy2_raven:				{ return "robes-male-light-messy2-raven"; }
			case AvatarImage::robes_male_light_messy2_white:				{ return "robes-male-light-messy2-white"; }
			case AvatarImage::robes_male_light_parted_blonde:				{ return "robes-male-light-parted-blonde"; }
			case AvatarImage::robes_male_light_parted_brunette:				{ return "robes-male-light-parted-brunette"; }
			case AvatarImage::robes_male_light_parted_raven:				{ return "robes-male-light-parted-raven"; }
			case AvatarImage::robes_male_light_parted_white:				{ return "robes-male-light-parted-white"; }
			case AvatarImage::robes_male_light_plain_blonde:				{ return "robes-male-light-plain-blonde"; }
			case AvatarImage::robes_male_light_plain_brunette:				{ return "robes-male-light-plain-brunette"; }
			case AvatarImage::robes_male_light_plain_raven:					{ return "robes-male-light-plain-raven"; }
			case AvatarImage::robes_male_light_plain_white:					{ return "robes-male-light-plain-white"; }
			case AvatarImage::robes_whitebeard:								{ return "robes-whitebeard"; }
			case AvatarImage::sara_bluewhite:								{ return "sara-bluewhite"; }
			case AvatarImage::sara_cyan:									{ return "sara-cyan"; }
			case AvatarImage::sara_green:									{ return "sara-green"; }
			case AvatarImage::sara_white:									{ return "sara-white"; }
			case AvatarImage::tunic_female_dark_bangsshort_black:			{ return "tunic-female-dark-bangsshort-black"; }
			case AvatarImage::tunic_female_dark_bangsshort_brown:			{ return "tunic-female-dark-bangsshort-brown"; }
			case AvatarImage::tunic_female_dark_bangsshort_brunette:        { return "tunic-female-dark-bangsshort-brunette"; }
			case AvatarImage::tunic_female_dark_loose_black:				{ return "tunic-female-dark-loose-black"; }
			case AvatarImage::tunic_female_dark_loose_brown:				{ return "tunic-female-dark-loose-brown"; }
			case AvatarImage::tunic_female_dark_loose_brunette:				{ return "tunic-female-dark-loose-brunette"; }
			case AvatarImage::tunic_female_dark_ponytail_black:				{ return "tunic-female-dark-ponytail-black"; }
			case AvatarImage::tunic_female_dark_ponytail_brown:				{ return "tunic-female-dark-ponytail-brown"; }
			case AvatarImage::tunic_female_dark_ponytail_brunette:			{ return "tunic-female-dark-ponytail-brunette"; }
			case AvatarImage::tunic_female_dark_unkempt_black:				{ return "tunic-female-dark-unkempt-black"; }
			case AvatarImage::tunic_female_dark_unkempt_brown:				{ return "tunic-female-dark-unkempt-brown"; }
			case AvatarImage::tunic_female_dark_unkempt_brunette:			{ return "tunic-female-dark-unkempt-brunette"; }
			case AvatarImage::tunic_female_light_bangsshort_black:			{ return "tunic-female-light-bangsshort-black"; }
			case AvatarImage::tunic_female_light_bangsshort_blonde2:        { return "tunic-female-light-bangsshort-blonde2"; }
			case AvatarImage::tunic_female_light_bangsshort_brown:			{ return "tunic-female-light-bangsshort-brown"; }
			case AvatarImage::tunic_female_light_bangsshort_brunette:       { return "tunic-female-light-bangsshort-brunette"; }
			case AvatarImage::tunic_female_light_bangsshort_brunette2:      { return "tunic-female-light-bangsshort-brunette2"; }
			case AvatarImage::tunic_female_light_bangsshort_lightblonde2:	{ return "tunic-female-light-bangsshort-lightblonde2"; }
			case AvatarImage::tunic_female_light_loose_black:				{ return "tunic-female-light-loose-black"; }
			case AvatarImage::tunic_female_light_loose_blonde2:				{ return "tunic-female-light-loose-blonde2"; }
			case AvatarImage::tunic_female_light_loose_brown:				{ return "tunic-female-light-loose-brown"; }
			case AvatarImage::tunic_female_light_loose_brunette:			{ return "tunic-female-light-loose-brunette"; }
			case AvatarImage::tunic_female_light_loose_brunette2:			{ return "tunic-female-light-loose-brunette2"; }
			case AvatarImage::tunic_female_light_loose_lightblonde2:        { return "tunic-female-light-loose-lightblonde2"; }
			case AvatarImage::tunic_female_light_ponytail_black:			{ return "tunic-female-light-ponytail-black"; }
			case AvatarImage::tunic_female_light_ponytail_blonde2:          { return "tunic-female-light-ponytail-blonde2"; }
			case AvatarImage::tunic_female_light_ponytail_brown:            { return "tunic-female-light-ponytail-brown"; }
			case AvatarImage::tunic_female_light_ponytail_brunette:         { return "tunic-female-light-ponytail-brunette"; }
			case AvatarImage::tunic_female_light_ponytail_brunette2:        { return "tunic-female-light-ponytail-brunette2"; }
			case AvatarImage::tunic_female_light_ponytail_lightblonde2:		{ return "tunic-female-light-ponytail-lightblonde2"; }
			case AvatarImage::tunic_female_light_unkempt_black:				{ return "tunic-female-light-unkempt-black"; }
			case AvatarImage::tunic_female_light_unkempt_blonde2:			{ return "tunic-female-light-unkempt-blonde2"; }
			case AvatarImage::tunic_female_light_unkempt_brown:				{ return "tunic-female-light-unkempt-brown"; }
			case AvatarImage::tunic_female_light_unkempt_brunette:			{ return "tunic-female-light-unkempt-brunette"; }
			case AvatarImage::tunic_female_light_unkempt_brunette2:			{ return "tunic-female-light-unkempt-brunette2"; }
			case AvatarImage::tunic_female_light_unkempt_lightblonde2:		{ return "tunic-female-light-unkempt-lightblonde2"; }
            case AvatarImage::count:                                        [[fallthrough]];
            default:                                                        { return "Error_AvatarImage_Unknown"; }
		};
        // clang-format on
    }

    constexpr std::array<AvatarImage, 340> getAvatarImagesTownfolk() noexcept
    {
        return { AvatarImage::dress_dark_pixie_black,
                 AvatarImage::dress_dark_pixie_brown,
                 AvatarImage::dress_dark_pixie_brunette,
                 AvatarImage::dress_dark_pixie_gray,
                 AvatarImage::dress_dark_pixie_whiteblonde2,
                 AvatarImage::dress_dark_shoulderl_black,
                 AvatarImage::dress_dark_shoulderl_brown,
                 AvatarImage::dress_dark_shoulderl_brunette,
                 AvatarImage::dress_dark_shoulderl_gray,
                 AvatarImage::dress_dark_shoulderl_whiteblonde2,
                 AvatarImage::dress_dark_shoulderr_black,
                 AvatarImage::dress_dark_shoulderr_brown,
                 AvatarImage::dress_dark_shoulderr_brunette,
                 AvatarImage::dress_dark_shoulderr_gray,
                 AvatarImage::dress_dark_shoulderr_whiteblonde2,
                 AvatarImage::dress_dark_swoop_black,
                 AvatarImage::dress_dark_swoop_brown,
                 AvatarImage::dress_dark_swoop_brunette,
                 AvatarImage::dress_dark_swoop_gray,
                 AvatarImage::dress_dark_swoop_whiteblonde2,
                 AvatarImage::dress_light_pixie_black,
                 AvatarImage::dress_light_pixie_blonde2,
                 AvatarImage::dress_light_pixie_brown,
                 AvatarImage::dress_light_pixie_brunette,
                 AvatarImage::dress_light_pixie_brunette2,
                 AvatarImage::dress_light_pixie_gray,
                 AvatarImage::dress_light_shoulderl_black,
                 AvatarImage::dress_light_shoulderl_blonde2,
                 AvatarImage::dress_light_shoulderl_brown,
                 AvatarImage::dress_light_shoulderl_brunette,
                 AvatarImage::dress_light_shoulderl_brunette2,
                 AvatarImage::dress_light_shoulderl_gray,
                 AvatarImage::dress_light_shoulderr_black,
                 AvatarImage::dress_light_shoulderr_blonde2,
                 AvatarImage::dress_light_shoulderr_brown,
                 AvatarImage::dress_light_shoulderr_brunette,
                 AvatarImage::dress_light_shoulderr_brunette2,
                 AvatarImage::dress_light_shoulderr_gray,
                 AvatarImage::dress_light_swoop_black,
                 AvatarImage::dress_light_swoop_blonde2,
                 AvatarImage::dress_light_swoop_brown,
                 AvatarImage::dress_light_swoop_brunette,
                 AvatarImage::dress_light_swoop_brunette2,
                 AvatarImage::dress_light_swoop_gray,
                 AvatarImage::girl_dark_loose_black,
                 AvatarImage::girl_dark_loose_brown,
                 AvatarImage::girl_dark_loose_brunette,
                 AvatarImage::girl_dark_loose_brunette2,
                 AvatarImage::girl_dark_loose_whiteblonde2,
                 AvatarImage::girl_dark_ponytail2_black,
                 AvatarImage::girl_dark_ponytail2_brown,
                 AvatarImage::girl_dark_ponytail2_brunette,
                 AvatarImage::girl_dark_ponytail2_brunette2,
                 AvatarImage::girl_dark_ponytail2_whiteblonde2,
                 AvatarImage::girl_dark_princess_black,
                 AvatarImage::girl_dark_princess_brown,
                 AvatarImage::girl_dark_princess_brunette,
                 AvatarImage::girl_dark_princess_brunette2,
                 AvatarImage::girl_dark_princess_whiteblonde2,
                 AvatarImage::girl_dark_unkempt_black,
                 AvatarImage::girl_dark_unkempt_brown,
                 AvatarImage::girl_dark_unkempt_brunette,
                 AvatarImage::girl_dark_unkempt_brunette2,
                 AvatarImage::girl_dark_unkempt_whiteblonde2,
                 AvatarImage::girl_light_loose_blonde,
                 AvatarImage::girl_light_loose_blonde2,
                 AvatarImage::girl_light_loose_brown,
                 AvatarImage::girl_light_loose_brunette,
                 AvatarImage::girl_light_loose_brunette2,
                 AvatarImage::girl_light_loose_darkblonde,
                 AvatarImage::girl_light_loose_lightblonde,
                 AvatarImage::girl_light_loose_lightblonde2,
                 AvatarImage::girl_light_ponytail2_blonde,
                 AvatarImage::girl_light_ponytail2_blonde2,
                 AvatarImage::girl_light_ponytail2_brown,
                 AvatarImage::girl_light_ponytail2_brunette,
                 AvatarImage::girl_light_ponytail2_brunette2,
                 AvatarImage::girl_light_ponytail2_darkblonde,
                 AvatarImage::girl_light_ponytail2_lightblonde,
                 AvatarImage::girl_light_ponytail2_lightblonde2,
                 AvatarImage::girl_light_princess_blonde,
                 AvatarImage::girl_light_princess_blonde2,
                 AvatarImage::girl_light_princess_brown,
                 AvatarImage::girl_light_princess_brunette,
                 AvatarImage::girl_light_princess_brunette2,
                 AvatarImage::girl_light_princess_darkblonde,
                 AvatarImage::girl_light_princess_lightblonde,
                 AvatarImage::girl_light_princess_lightblonde2,
                 AvatarImage::girl_light_unkempt_blonde,
                 AvatarImage::girl_light_unkempt_blonde2,
                 AvatarImage::girl_light_unkempt_brown,
                 AvatarImage::girl_light_unkempt_brunette,
                 AvatarImage::girl_light_unkempt_brunette2,
                 AvatarImage::girl_light_unkempt_darkblonde,
                 AvatarImage::girl_light_unkempt_lightblonde,
                 AvatarImage::girl_light_unkempt_lightblonde2,
                 AvatarImage::leather_circus1_dark_brunette,
                 AvatarImage::leather_circus1_dark_raven,
                 AvatarImage::leather_circus1_dark_white,
                 AvatarImage::leather_circus1_light_blonde,
                 AvatarImage::leather_circus1_light_brunette,
                 AvatarImage::leather_circus1_light_raven,
                 AvatarImage::leather_circus2_dark_brunette,
                 AvatarImage::leather_circus2_dark_raven,
                 AvatarImage::leather_circus2_dark_white,
                 AvatarImage::leather_circus2_light_blonde,
                 AvatarImage::leather_circus2_light_brunette,
                 AvatarImage::leather_circus2_light_raven,
                 AvatarImage::leather_common1_dark_brunette,
                 AvatarImage::leather_common1_dark_raven,
                 AvatarImage::leather_common1_dark_white,
                 AvatarImage::leather_common1_light_blonde,
                 AvatarImage::leather_common1_light_brunette,
                 AvatarImage::leather_common1_light_raven,
                 AvatarImage::leather_common2_dark_brunette,
                 AvatarImage::leather_common2_dark_raven,
                 AvatarImage::leather_common2_dark_white,
                 AvatarImage::leather_common2_light_blonde,
                 AvatarImage::leather_common2_light_brunette,
                 AvatarImage::leather_common2_light_raven,
                 AvatarImage::leather_common3_dark_brunette,
                 AvatarImage::leather_common3_dark_raven,
                 AvatarImage::leather_common3_dark_white,
                 AvatarImage::leather_common3_light_blonde,
                 AvatarImage::leather_common3_light_brunette,
                 AvatarImage::leather_common3_light_raven,
                 AvatarImage::leather_ironarms_dark_brunette,
                 AvatarImage::leather_ironarms_dark_raven,
                 AvatarImage::leather_ironarms_dark_white,
                 AvatarImage::leather_ironarms_light_blonde,
                 AvatarImage::leather_ironarms_light_brunette,
                 AvatarImage::leather_ironarms_light_raven,
                 AvatarImage::leather_ironrich_dark_brunette,
                 AvatarImage::leather_ironrich_dark_raven,
                 AvatarImage::leather_ironrich_dark_white,
                 AvatarImage::leather_ironrich_light_blonde,
                 AvatarImage::leather_ironrich_light_brunette,
                 AvatarImage::leather_ironrich_light_raven,
                 AvatarImage::leather_poor_dark_brunette,
                 AvatarImage::leather_poor_dark_raven,
                 AvatarImage::leather_poor_dark_white,
                 AvatarImage::leather_poor_light_blonde,
                 AvatarImage::leather_poor_light_brunette,
                 AvatarImage::leather_poor_light_raven,
                 AvatarImage::leather_private1_dark_brunette,
                 AvatarImage::leather_private1_dark_raven,
                 AvatarImage::leather_private1_dark_white,
                 AvatarImage::leather_private1_light_blonde,
                 AvatarImage::leather_private1_light_brunette,
                 AvatarImage::leather_private1_light_raven,
                 AvatarImage::leather_private2_dark_brunette,
                 AvatarImage::leather_private2_dark_raven,
                 AvatarImage::leather_private2_dark_white,
                 AvatarImage::leather_private2_light_blonde,
                 AvatarImage::leather_private2_light_brunette,
                 AvatarImage::leather_private2_light_raven,
                 AvatarImage::leather_private3_dark_brunette,
                 AvatarImage::leather_private3_dark_raven,
                 AvatarImage::leather_private3_dark_white,
                 AvatarImage::leather_private3_light_blonde,
                 AvatarImage::leather_private3_light_brunette,
                 AvatarImage::leather_private3_light_raven,
                 AvatarImage::leather_private4_dark_brunette,
                 AvatarImage::leather_private4_dark_raven,
                 AvatarImage::leather_private4_dark_white,
                 AvatarImage::leather_private4_light_blonde,
                 AvatarImage::leather_private4_light_brunette,
                 AvatarImage::leather_private4_light_raven,
                 AvatarImage::leather_thug1_dark_brunette,
                 AvatarImage::leather_thug1_dark_raven,
                 AvatarImage::leather_thug1_dark_white,
                 AvatarImage::leather_thug1_light_blonde,
                 AvatarImage::leather_thug1_light_brunette,
                 AvatarImage::leather_thug1_light_raven,
                 AvatarImage::leather_thug2_dark_brunette,
                 AvatarImage::leather_thug2_dark_raven,
                 AvatarImage::leather_thug2_dark_white,
                 AvatarImage::leather_thug2_light_blonde,
                 AvatarImage::leather_thug2_light_brunette,
                 AvatarImage::leather_thug2_light_raven,
                 AvatarImage::maid_dark_pixie_black,
                 AvatarImage::maid_dark_pixie_brown,
                 AvatarImage::maid_dark_pixie_brunette,
                 AvatarImage::maid_dark_pixie_gray,
                 AvatarImage::maid_dark_pixie_whiteblonde2,
                 AvatarImage::maid_dark_shoulderl_black,
                 AvatarImage::maid_dark_shoulderl_brown,
                 AvatarImage::maid_dark_shoulderl_brunette,
                 AvatarImage::maid_dark_shoulderl_gray,
                 AvatarImage::maid_dark_shoulderl_whiteblonde2,
                 AvatarImage::maid_dark_shoulderr_black,
                 AvatarImage::maid_dark_shoulderr_brown,
                 AvatarImage::maid_dark_shoulderr_brunette,
                 AvatarImage::maid_dark_shoulderr_gray,
                 AvatarImage::maid_dark_shoulderr_whiteblonde2,
                 AvatarImage::maid_dark_swoop_black,
                 AvatarImage::maid_dark_swoop_brown,
                 AvatarImage::maid_dark_swoop_brunette,
                 AvatarImage::maid_dark_swoop_gray,
                 AvatarImage::maid_dark_swoop_whiteblonde2,
                 AvatarImage::maid_light_pixie_black,
                 AvatarImage::maid_light_pixie_blonde2,
                 AvatarImage::maid_light_pixie_brown,
                 AvatarImage::maid_light_pixie_brunette,
                 AvatarImage::maid_light_pixie_brunette2,
                 AvatarImage::maid_light_shoulderl_black,
                 AvatarImage::maid_light_shoulderl_blonde2,
                 AvatarImage::maid_light_shoulderl_brown,
                 AvatarImage::maid_light_shoulderl_brunette,
                 AvatarImage::maid_light_shoulderl_brunette2,
                 AvatarImage::maid_light_shoulderr_black,
                 AvatarImage::maid_light_shoulderr_blonde2,
                 AvatarImage::maid_light_shoulderr_brown,
                 AvatarImage::maid_light_shoulderr_brunette,
                 AvatarImage::maid_light_shoulderr_brunette2,
                 AvatarImage::maid_light_swoop_black,
                 AvatarImage::maid_light_swoop_blonde2,
                 AvatarImage::maid_light_swoop_brown,
                 AvatarImage::maid_light_swoop_brunette,
                 AvatarImage::maid_light_swoop_brunette2,
                 AvatarImage::pants_male_dark_bedhead_brunette,
                 AvatarImage::pants_male_dark_bedhead_raven,
                 AvatarImage::pants_male_dark_messy2_brunette,
                 AvatarImage::pants_male_dark_messy2_raven,
                 AvatarImage::pants_male_dark_parted_brunette,
                 AvatarImage::pants_male_dark_parted_raven,
                 AvatarImage::pants_male_dark_plain_brunette,
                 AvatarImage::pants_male_dark_plain_raven,
                 AvatarImage::pants_male_light_bedhead_blonde,
                 AvatarImage::pants_male_light_bedhead_brunette,
                 AvatarImage::pants_male_light_bedhead_raven,
                 AvatarImage::pants_male_light_bedhead_white,
                 AvatarImage::pants_male_light_messy2_blonde,
                 AvatarImage::pants_male_light_messy2_brunette,
                 AvatarImage::pants_male_light_messy2_raven,
                 AvatarImage::pants_male_light_messy2_white,
                 AvatarImage::pants_male_light_parted_blonde,
                 AvatarImage::pants_male_light_parted_brunette,
                 AvatarImage::pants_male_light_parted_raven,
                 AvatarImage::pants_male_light_parted_white,
                 AvatarImage::pants_male_light_plain_blonde,
                 AvatarImage::pants_male_light_plain_brunette,
                 AvatarImage::pants_male_light_plain_raven,
                 AvatarImage::pants_male_light_plain_white,
                 AvatarImage::rags_female_dark_bangsshort_black,
                 AvatarImage::rags_female_dark_bangsshort_brown,
                 AvatarImage::rags_female_dark_bangsshort_brunette,
                 AvatarImage::rags_female_dark_loose_black,
                 AvatarImage::rags_female_dark_loose_brown,
                 AvatarImage::rags_female_dark_loose_brunette,
                 AvatarImage::rags_female_dark_ponytail_black,
                 AvatarImage::rags_female_dark_ponytail_brown,
                 AvatarImage::rags_female_dark_ponytail_brunette,
                 AvatarImage::rags_female_dark_unkempt_black,
                 AvatarImage::rags_female_dark_unkempt_brown,
                 AvatarImage::rags_female_dark_unkempt_brunette,
                 AvatarImage::rags_female_light_bangsshort_black,
                 AvatarImage::rags_female_light_bangsshort_blonde2,
                 AvatarImage::rags_female_light_bangsshort_brown,
                 AvatarImage::rags_female_light_bangsshort_brunette,
                 AvatarImage::rags_female_light_bangsshort_brunette2,
                 AvatarImage::rags_female_light_bangsshort_lightblonde2,
                 AvatarImage::rags_female_light_loose_black,
                 AvatarImage::rags_female_light_loose_blonde2,
                 AvatarImage::rags_female_light_loose_brown,
                 AvatarImage::rags_female_light_loose_brunette,
                 AvatarImage::rags_female_light_loose_brunette2,
                 AvatarImage::rags_female_light_loose_lightblonde2,
                 AvatarImage::rags_female_light_ponytail_black,
                 AvatarImage::rags_female_light_ponytail_blonde2,
                 AvatarImage::rags_female_light_ponytail_brown,
                 AvatarImage::rags_female_light_ponytail_brunette,
                 AvatarImage::rags_female_light_ponytail_brunette2,
                 AvatarImage::rags_female_light_ponytail_lightblonde2,
                 AvatarImage::rags_female_light_unkempt_black,
                 AvatarImage::rags_female_light_unkempt_blonde2,
                 AvatarImage::rags_female_light_unkempt_brown,
                 AvatarImage::rags_female_light_unkempt_brunette,
                 AvatarImage::rags_female_light_unkempt_brunette2,
                 AvatarImage::rags_female_light_unkempt_lightblonde2,
                 AvatarImage::rags_male_dark_bedhead_brunette,
                 AvatarImage::rags_male_dark_bedhead_raven,
                 AvatarImage::rags_male_dark_messy2_brunette,
                 AvatarImage::rags_male_dark_messy2_raven,
                 AvatarImage::rags_male_dark_parted_brunette,
                 AvatarImage::rags_male_dark_parted_raven,
                 AvatarImage::rags_male_dark_plain_brunette,
                 AvatarImage::rags_male_dark_plain_raven,
                 AvatarImage::rags_male_light_bedhead_blonde,
                 AvatarImage::rags_male_light_bedhead_brunette,
                 AvatarImage::rags_male_light_bedhead_raven,
                 AvatarImage::rags_male_light_bedhead_white,
                 AvatarImage::rags_male_light_messy2_blonde,
                 AvatarImage::rags_male_light_messy2_brunette,
                 AvatarImage::rags_male_light_messy2_raven,
                 AvatarImage::rags_male_light_messy2_white,
                 AvatarImage::rags_male_light_parted_blonde,
                 AvatarImage::rags_male_light_parted_brunette,
                 AvatarImage::rags_male_light_parted_raven,
                 AvatarImage::rags_male_light_parted_white,
                 AvatarImage::rags_male_light_plain_blonde,
                 AvatarImage::rags_male_light_plain_brunette,
                 AvatarImage::rags_male_light_plain_raven,
                 AvatarImage::rags_male_light_plain_white,
                 AvatarImage::tunic_female_dark_bangsshort_black,
                 AvatarImage::tunic_female_dark_bangsshort_brown,
                 AvatarImage::tunic_female_dark_bangsshort_brunette,
                 AvatarImage::tunic_female_dark_loose_black,
                 AvatarImage::tunic_female_dark_loose_brown,
                 AvatarImage::tunic_female_dark_loose_brunette,
                 AvatarImage::tunic_female_dark_ponytail_black,
                 AvatarImage::tunic_female_dark_ponytail_brown,
                 AvatarImage::tunic_female_dark_ponytail_brunette,
                 AvatarImage::tunic_female_dark_unkempt_black,
                 AvatarImage::tunic_female_dark_unkempt_brown,
                 AvatarImage::tunic_female_dark_unkempt_brunette,
                 AvatarImage::tunic_female_light_bangsshort_black,
                 AvatarImage::tunic_female_light_bangsshort_blonde2,
                 AvatarImage::tunic_female_light_bangsshort_brown,
                 AvatarImage::tunic_female_light_bangsshort_brunette,
                 AvatarImage::tunic_female_light_bangsshort_brunette2,
                 AvatarImage::tunic_female_light_bangsshort_lightblonde2,
                 AvatarImage::tunic_female_light_loose_black,
                 AvatarImage::tunic_female_light_loose_blonde2,
                 AvatarImage::tunic_female_light_loose_brown,
                 AvatarImage::tunic_female_light_loose_brunette,
                 AvatarImage::tunic_female_light_loose_brunette2,
                 AvatarImage::tunic_female_light_loose_lightblonde2,
                 AvatarImage::tunic_female_light_ponytail_black,
                 AvatarImage::tunic_female_light_ponytail_blonde2,
                 AvatarImage::tunic_female_light_ponytail_brown,
                 AvatarImage::tunic_female_light_ponytail_brunette,
                 AvatarImage::tunic_female_light_ponytail_brunette2,
                 AvatarImage::tunic_female_light_ponytail_lightblonde2,
                 AvatarImage::tunic_female_light_unkempt_black,
                 AvatarImage::tunic_female_light_unkempt_blonde2,
                 AvatarImage::tunic_female_light_unkempt_brown,
                 AvatarImage::tunic_female_light_unkempt_brunette,
                 AvatarImage::tunic_female_light_unkempt_brunette2,
                 AvatarImage::tunic_female_light_unkempt_lightblonde2 };
    }

    constexpr std::array<AvatarImage, 28> getAvatarImagesSoldier() noexcept
    {
        return { AvatarImage::leather_specialist1_dark, AvatarImage::leather_specialist1_light,
                 AvatarImage::leather_specialist2_dark, AvatarImage::leather_specialist2_light,
                 AvatarImage::leather_private2nd1_dark, AvatarImage::leather_private2nd1_light,
                 AvatarImage::leather_private2nd2_dark, AvatarImage::leather_private2nd2_light,
                 AvatarImage::leather_private2nd3_dark, AvatarImage::leather_private2nd3_light,
                 AvatarImage::leather_private2nd4_dark, AvatarImage::leather_private2nd4_light,
                 AvatarImage::leather_private1st1_dark, AvatarImage::leather_private1st1_light,
                 AvatarImage::leather_private1st2_dark, AvatarImage::leather_private1st2_light,
                 AvatarImage::leather_private1st3_dark, AvatarImage::leather_private1st3_light,
                 AvatarImage::leather_private1st4_dark, AvatarImage::leather_private1st4_light,
                 AvatarImage::leather_corporal1_dark,   AvatarImage::leather_corporal1_light,
                 AvatarImage::leather_corporal2_dark,   AvatarImage::leather_corporal2_light,
                 AvatarImage::plate_major_dark,         AvatarImage::plate_major_light,
                 AvatarImage::plate_sergeant_dark,      AvatarImage::plate_sergeant_light };
    }

    constexpr std::array<AvatarImage, 40> getAvatarImagesMonk() noexcept
    {
        return { AvatarImage::monk_beltleather_dark_bracer,
                 AvatarImage::monk_beltleather_dark_nobracer,
                 AvatarImage::monk_beltleather_tanned2_bracer,
                 AvatarImage::monk_beltleather_tanned2_nobracer,
                 AvatarImage::monk_beltnone_dark_bracer,
                 AvatarImage::monk_beltnone_dark_nobracer,
                 AvatarImage::monk_beltnone_tanned2_bracer,
                 AvatarImage::monk_beltnone_tanned2_nobracer,
                 AvatarImage::monk_beltwhite_dark_bracer,
                 AvatarImage::monk_beltwhite_dark_nobracer,
                 AvatarImage::monk_beltwhite_tanned2_bracer,
                 AvatarImage::monk_beltwhite_tanned2_nobracer,
                 AvatarImage::monk_shirt_beltnone_dark,
                 AvatarImage::monk_shirt_beltnone_tanned2,
                 AvatarImage::monk_shirt_beltwhite_dark,
                 AvatarImage::monk_shirt_beltwhite_tanned2,
                 AvatarImage::robes_male_dark_bedhead_brunette,
                 AvatarImage::robes_male_dark_bedhead_raven,
                 AvatarImage::robes_male_dark_messy2_brunette,
                 AvatarImage::robes_male_dark_messy2_raven,
                 AvatarImage::robes_male_dark_parted_brunette,
                 AvatarImage::robes_male_dark_parted_raven,
                 AvatarImage::robes_male_dark_plain_brunette,
                 AvatarImage::robes_male_dark_plain_raven,
                 AvatarImage::robes_male_light_bedhead_blonde,
                 AvatarImage::robes_male_light_bedhead_brunette,
                 AvatarImage::robes_male_light_bedhead_raven,
                 AvatarImage::robes_male_light_bedhead_white,
                 AvatarImage::robes_male_light_messy2_blonde,
                 AvatarImage::robes_male_light_messy2_brunette,
                 AvatarImage::robes_male_light_messy2_raven,
                 AvatarImage::robes_male_light_messy2_white,
                 AvatarImage::robes_male_light_parted_blonde,
                 AvatarImage::robes_male_light_parted_brunette,
                 AvatarImage::robes_male_light_parted_raven,
                 AvatarImage::robes_male_light_parted_white,
                 AvatarImage::robes_male_light_plain_blonde,
                 AvatarImage::robes_male_light_plain_brunette,
                 AvatarImage::robes_male_light_plain_raven,
                 AvatarImage::robes_male_light_plain_white };
    }

    constexpr std::array<AvatarImage, 12> getAvatarImagesPlayer() noexcept
    {
        return { AvatarImage::sara_bluewhite,    AvatarImage::sara_cyan,
                 AvatarImage::sara_green,        AvatarImage::sara_white,
                 AvatarImage::puck_female_dark,  AvatarImage::puck_female_light,
                 AvatarImage::puck_male_dark,    AvatarImage::puck_male_light,
                 AvatarImage::metal_female_dark, AvatarImage::metal_female_light,
                 AvatarImage::metal_male_dark,   AvatarImage::metal_male_light };
    }

    inline const std::string avatarImageToFilename(const AvatarImage t_avatarImage)
    {
        std::string filename{ toString(t_avatarImage) };
        filename += ".png";
        return filename;
    }

} // namespace thornberry

#endif // AVATAR_IMAGE_HPP_INCLUDED
