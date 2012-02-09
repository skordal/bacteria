/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/*************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <cstdlib>
#include <cstdio>
#include <ctime>

#include <SDL.h>
#include <getopt.h>

#include <list>

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
		application();
		~application();

		bool init(int argc, char * argv[]);
		int run();

		static char * find_file(const char * filename);
	private:
		// Initialization functions:
		bool init_cmd_args(int argc, char * argv[]);
		bool init_config();
		bool init_random();
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
		int option, counter, logging_interval;
		int starting_pop, starting_food;
		char * config_filename;
		bool display_coords, display_energy;
		bool display_stats, graphical_energy_bar;
		bool running;

		logger * data_logger;
		statistics * stats;

		SDL_Surface * window_icon;
		SDL_TimerID refresh_timer, logger_timer;

		std::list<bacteria> spawn_list;
		std::list<bacteria>::iterator bacteria_iterator;
		std::list<food>::iterator food_iterator;
};

#endif

