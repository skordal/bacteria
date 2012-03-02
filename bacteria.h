/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef BACTERIA_H
#define BACTERIA_H

#include <cassert>
#include <iomanip>
#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "config.h"
#include "config_db.h"
#include "energy_bar.h"
#include "image.h"
#include "vector.h"

class bacteria 
{
	public:
		bacteria(double angle = 0.0f,		// Starting direction
			float init_speed = 0.0f,	// Starting speed
			int ix = 0,			// Starting X coordinate
			int iy = 0,			// Starting Y coordinate
			int init_energy = 0,		// Initial energy
			int gen = 1);			// Which generation typically (parent + 1)

		void draw() const;
		void draw_coords() const;
		void draw_energy(bool graphically = true) const;
		void draw_generation() const;

		bool update(); // Returns false if the bacteria is dead.
		bool is_alive() const { return alive; }

		int feed(); // Returns the energy eaten, used as assignment in food.cpp.
		void release(bool newdir = true);
		void stop() { at_food = true; }

		bool can_reproduce() const { return energy >= config->get_int_value("ReproductionEnergy"); }
		void reproduce();

		const vector & get_vector() const { return speed; }
		int get_generation() const { return generation; }

		void set_destination(coordinate_pair_t destination);
		coordinate_pair_t get_destination() const { return food_loc; }

		bool is_heading_for_food() const { return heading_for_food; }
		static bool does_collide(bacteria * a, bacteria * b);
	private:
		int energy;
		int generation;
		bool alive, heading_for_food, at_food;
		float init_food_dist, prev_food_dist;
		vector speed;
		energy_bar e_bar;
		coordinate_pair_t food_loc;
};

#endif

