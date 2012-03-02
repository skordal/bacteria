/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <ctime>
#include <list>
#include <iostream>

#include <getopt.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "bacteria.h"
#include "config.h"
#include "config_db.h"
#include "config_parser.h"
#include "food.h"
#include "image.h"
#include "logger.h"
#include "statistics.h"
#include "window.h"

#define UPDATE_EVENT {SDL_USEREVENT, 0, NULL, NULL}
#define LOGGER_EVENT {SDL_USEREVENT, 1, NULL, NULL}

class application
{
	public:
		static application * init(int argc, char * argv[]);
		static application * get() { return global_app; }

		// Runs the simulator:
		int run();

		// Finds a file in the application search path:
		static const char * find_file(const char * filename);
	private:
		application();
		~application();

		// Clean up function, called by atexit:
		static void cleanup();

		// Initialization functions:
		bool init_cmd_args(int argc, char * argv[]);
		bool init_config();
		void init_random();
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

		window * main_window;
		SDL_TimerID refresh_timer, logger_timer;

		std::list<bacteria>::iterator bacteria_iterator;
		std::list<food>::iterator food_iterator;

		static application * global_app;
};

#endif

