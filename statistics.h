/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef STATISTICS_H
#define STATISTICS_H

#include <iomanip>
#include <iostream>
#include <sstream>

#include <ctime>

#include <SDL.h>

#include "config_db.h"
#include "config.h"

#ifndef DISABLE_SDLTTF
#include <SDL_ttf.h>
#endif

class statistics
{
	public:
		statistics(int bacteria = STARTING_POP, int food = STARTING_FOOD);

		void update();
		void draw();

		void set_game_over() { game_over = true; }
		bool get_game_over() const { return game_over; }

		void add_food();
		void remove_food();

		void add_bacteria(int generation = 1);
		void remove_bacteria() { --bacteria; }

		int get_bacteria() const { return bacteria; }
		int get_food() const { return food; }
	private:
		void calc_avg_growth();

		bool game_over, paused;
		int bacteria, food, peak_pop, peak_food, max_gen;
		int last_pop;
		int running_seconds, running_minutes;
		int running_hours;
		float avg_growth;
		long long int total_spawn, food_eaten;
		time_t starting_time, running_time;
};

#endif

