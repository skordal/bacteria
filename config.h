/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef CONFIG_H
#define CONFIG_H

#include "macros.h"

// Application version:
#define VERSION_MAJOR 0
#define VERSION_MINOR 1

// Window icon filename:
#define ICON_FILENAME application::find_file("graphics/bacteria.bmp")

// Font filename, font size, maximum text length and font color:
#define STATUS_FONT application::find_file("DejaVuSans.ttf")
#define STATUS_FONT_SIZE 12
#define STATUS_TEXT_COLOR (SDL_Color) {0, 0, 0, 0}

// Window background color:
#define BACKGROUND_R 160
#define BACKGROUND_G 255
#define BACKGROUND_B 255

// Default colour key for all pictures:
#define DEFAULT_COLOR_KEY(image) SDL_MapRGB(image->format, 255, 0, 255)

// Energy bar files and measurements:
#define RED_BAR_SEGMENT		application::find_file("graphics/red.bmp")
#define YELLOW_BAR_SEGMENT	application::find_file("graphics/yellow.bmp")
#define GREEN_BAR_SEGMENT	application::find_file("graphics/green.bmp")
#define RED_PERCENT		15.0f / 100.0f
#define YELLOW_PERCENT		25.0f / 100.0f
#define ENERGY_BAR_LENGTH	30.0f
#define ENERGY_BAR_HEIGHT	10.0f

// Filename and measurements of bacteria:
#define BACTERIA_FILENAME	application::find_file("graphics/bacteria.bmp")
#define BACTERIA_ALPHA		(SDL_ALPHA_OPAQUE - 60)

// Food filename and measurements:
#define FOOD_FILENAME	application::find_file("graphics/food.bmp")
#define FOOD_ALPHA	128

// Starting energy of each bacteria:
#define STARTING_ENERGY	config->get_int_value("FramesPerSecond") * (12 + PM(6))

// Food anchor placements:
#define F_ANCHOR_1_X	0 
#define F_ANCHOR_1_Y	0

#define F_ANCHOR_2_X	18
#define F_ANCHOR_2_Y	0

#define F_ANCHOR_3_X	0
#define F_ANCHOR_3_Y	19

#define F_ANCHOR_4_X	19
#define F_ANCHOR_4_Y	19

#define ANCHOR_1	(coordinate_pair_t) {F_ANCHOR_1_X + x, F_ANCHOR_1_Y + y}
#define ANCHOR_2	(coordinate_pair_t) {F_ANCHOR_2_X + x, F_ANCHOR_2_Y + y}
#define ANCHOR_3	(coordinate_pair_t) {F_ANCHOR_3_X + x, F_ANCHOR_3_Y + y}
#define ANCHOR_4	(coordinate_pair_t) {F_ANCHOR_4_X + x, F_ANCHOR_4_Y + y}

#endif

