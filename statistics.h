/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef STATISTICS_H
#define STATISTICS_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "config_db.h"
#include "config.h"

class statistics
{
	public:
		statistics(int bacteria, int food);

		void update();
		void draw() const;

		void set_game_over() { game_over = true; }
		bool get_game_over() const { return game_over; }

		void add_food();
		void remove_food();

		void add_bacteria(int generation = 1);
		void remove_bacteria() { --bacteria; }

		int get_bacteria() const { return bacteria; }
		int get_food() const { return food; }

		// Number of digits for some statistics:
		static const int bacteria_digits = 3;
		static const int food_digits = 3;
		static const int peak_bacteria_digits = 3;
		static const int peak_food_digits = 3;
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

