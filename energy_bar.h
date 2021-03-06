/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef ENERGY_BAR_H
#define ENERGY_BAR_H

#include <cmath>
#include <SDL.h>

#include "image.h"
#include "config_db.h"

class energy_bar
{
	public:
		energy_bar(int energy);

		void set_energy(int energy) { current_energy = energy; }
		void update(int energy = 0) { current_energy += energy; }
		void draw(int x, int y) const;

		energy_bar & operator+=(int energy);

		energy_bar & operator++();
		energy_bar & operator--();
	private:
		int max_energy, current_energy;
};

#endif

