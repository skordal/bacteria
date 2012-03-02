/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <ctime>
#include <list>
#include <iostream>

#include <SDL.h>
#include <getopt.h>

#include "image.h"
#include "statistics.h"
#include "bacteria.h"
#include "food.h"
#include "logger.h"
#include "config_db.h"
#include "config_parser.h"
#include "config.h"

#ifndef DISABLE_SDLTTF
#include <SDL_ttf.h>
#endif

#define UPDATE_EVENT {SDL_USEREVENT, 0, NULL, NULL}
#define LOGGER_EVENT {SDL_USEREVENT, 1, NULL, NULL}

class application
{
	public:
		static application * init(int argc, char * argv[]);
		static application * get() { return global_app; }
		int run();

		// Finds a file in the application search path:
		static const char * find_file(const char * filename);

		SDL_Surface * get_screen() const { return screen; }
#ifndef DISABLE_SDLTTF
		TTF_Font * get_font() const { return font; }
#endif
	private:
		application();
		~application();

		// Clean up function, called by atexit:
		static void cleanup();

		// Initialization functions:
		bool init_cmd_args(int argc, char * argv[]);
		bool init_config();
		void init_random();
		bool init_sdl();
		bool init_graphics();
		bool init_logging();
		bool init_populations();
		bool init_timers();

		// Functions used for handling events:
		void handle_update();
		void handle_key(SDLKey key);

		void display_help();
		void display_version();

		// Variables:
		int logging_interval;
		int starting_pop, starting_food;
		std::string config_filename;
		bool display_coords, display_energy;
		bool display_stats, graphical_energy_bar;
		bool running;

		logger * data_logger;
		statistics * stats;

		SDL_Surface * window_icon, * screen;
		SDL_TimerID refresh_timer, logger_timer;
#ifndef DISABLE_SDLTTF
		TTF_Font * font;
#endif

		std::list<bacteria>::iterator bacteria_iterator;
		std::list<food>::iterator food_iterator;

		static application * global_app;
};

#endif

