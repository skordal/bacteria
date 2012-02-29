/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef CONFIG_H
#define CONFIG_H

#include "macros.h"

// Completely disable SDL_ttf (causes no statistics to be drawn):
// #define DISABLE_SDLTTF 1

// Config file to read by default (NULL = no file):
#define DEFAULT_CONFIG_FILE "default_config.cfg"

// Application version:
#define VERSION_MAJOR 0
#define VERSION_MINOR 1

// Window icon filename:
#define ICON_FILENAME application::find_file("graphics/bacteria.bmp")

// Frames per second, and the value used for the timer:
#define DEFAULT_FPS 25

// Window dimensions:
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// Maximum length of coordinate message for bacteria:
#define COORDS_MAXLEN 127

// Calculate average growth rate at this rate (sec):
#define AVG_GROWTH_RATE_INT 1

// Font filename, font size, maximum text length and font color:
#define STATUS_FONT application::find_file("DejaVuSans.ttf")
#define STATUS_FONT_SIZE 12
#define STATUS_MAXLEN 512
#define STATUS_TEXT_COLOR (SDL_Color) {0, 0, 0, 0}

// Window background color:
#define BACKGROUND_R 195
#define BACKGROUND_G 255
#define BACKGROUND_B 255

// Default colour key for all pictures:
#define DEFAULT_COLOR_KEY(image) SDL_MapRGB(image->format, 255, 0, 255)

// Energy bar files and measurements:
#define RED_BAR_SEGMENT		application::find_file("graphics/red.bmp")
#define YELLOW_BAR_SEGMENT	application::find_file("graphics/yellow.bmp")
#define GREEN_BAR_SEGMENT	application::find_file("graphics/green.bmp")
#define RED_PERCENT		(float) 15.0f / 100.0f
#define YELLOW_PERCENT		(float) 25.0f / 100.0f
#define ENERGY_BAR_LENGTH	(float) 30.0f
#define ENERGY_BAR_HEIGHT	(float) 10.0f

// Filename and measurements of bacteria:
#define BACTERIA_FILENAME	application::find_file("graphics/bacteria.bmp")
#define BACTERIA_WIDTH		20
#define BACTERIA_HEIGHT		20
#define BACTERIA_CENTER_X	(BACTERIA_WIDTH / 2)
#define BACTERIA_CENTER_Y	(BACTERIA_HEIGHT / 2)
#define BACTERIA_ALPHA		(SDL_ALPHA_OPAQUE - 60)

// Starting population of bacteria:
#define STARTING_POP	10
// Starting amount of food nuggets:
#define STARTING_FOOD	10

// Distance that bacteria can smell food:
#define FOOD_SMELLING_DISTANCE	50.0f

// Food filename and measurements:
#define FOOD_FILENAME	application::find_file("graphics/food.bmp")
#define FOOD_WIDTH	20
#define FOOD_HEIGHT	20
#define FOOD_ALPHA	128
#define FOOD_CENTER_X	FOOD_WIDTH / 2
#define FOOD_CENTER_Y	FOOD_HEIGHT / 2

// Energy contained in each food nugget:
#define FOOD_ENERGY	800
// Starting energy of each bacteria:
#define STARTING_ENERGY	config->get_int_value("FramesPerSecond") * (12 + PM(6))
// Energy required for reproduction (former value: FPS * 20):
#define REPRODUCTION_ENERGY	500

// Food spawning rate (former value: FPS * 2):
#define SPAWNING_RATE	50

// Energy gained from eating:
#define FEEDING_ENERGY	6

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

// Output file for the data logger:
#define DATALOG_FILENAME	"graph_data.dat"
// Interval for data logging:
#define LOGGER_UPDATE_INTERVAL	100
// Flush the data file every x commits:
#define LOGGER_COMMIT_INTERVAL	100

#endif

