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
#include "info_field.h"
#include "vector.h"

class bacteria 
{
	public:
		bacteria(double angle = 0.0f,		// Starting direction
			float init_speed = 0.0f,	// Starting speed
			int ix = 0,			// Starting X coordinate
			int iy = 0,			// Starting Y coordinate
			int init_energy = 0,		// Initial energy
			int gen = 1,			// Which generation typically (parent + 1)
			int ancestor = 0);		// Sets the ancestor of the bacteria

		void draw() const;

		bool update(); // Returns false if the bacteria is dead.
		bool is_alive() const { return alive; }

		int feed(); // Returns the energy eaten, used as assignment in food.cpp.
		void release(bool newdir = true);
		void stop() { at_food = true; }

		bool can_reproduce() const { return energy >= config->get_int_value("ReproductionEnergy"); }
		void reproduce();

		// Returns the speed vector for the bacteria:
		const vector & get_vector() const { return speed; }

		// Gets the generation of the bacteria:
		int get_generation() const { return generation; }

		// Sets the ancestor of the bacteria:
		void set_ancestor(int a) { ancestor = a; }
		// Retrieves the ancestor of the bacteria:
		int get_ancestor() const { return ancestor; }

		// Sets a new destination for a bacteria:
		void set_destination(coordinate_pair_t destination);
		// Retrieves the current destination for a bacteria:
		coordinate_pair_t get_destination() const { return food_loc; }

		// Returns true if the bacteria is currently heading for food:
		bool is_heading_for_food() const { return heading_for_food; }
	private:
		int energy;
		int generation;
		int ancestor;
		bool alive, heading_for_food, at_food;
		float prev_food_dist;

		vector speed;
		coordinate_pair_t food_loc;

		friend class info_field;
};

#endif

