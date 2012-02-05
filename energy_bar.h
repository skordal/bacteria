/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
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
		energy_bar();

		void set_energy(int energy) { current_energy = energy; }
		void update(int energy = 0) { current_energy += energy; }
		void draw(int x, int y);

		energy_bar & operator+=(int energy);

		void operator++(int);
		void operator--(int);
	private:
		int max_energy, current_energy;
};

#endif

