/**************************************************/
/* Bacteria -- The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/**************************************************/

#ifndef FOOD_H
#define FOOD_H

#include <cmath>
#include <assert.h>
#include <SDL.h>

#include <list>
#include <valarray>

#include "bacteria.h"
#include "vector.h"
#include "image.h"
#include "config_db.h"
#include "config.h"

class food
{
	public:
		food(int ix = 0, int iy = 0);
		~food();

		bool update();
		void draw();

		void release_bacteria();
		void check_for_bacteria(std::list<bacteria> & bacteria_list);

		bool anchor_busy(int anchor);

		coordinate_pair_t closest_anchor(const vector & bacteria_vector);
	private:
		int x, y;
		float energy;

		// Anchors for hungry bacteria:
		bacteria * anchor_1, * anchor_2, * anchor_3, * anchor_4;
};

#endif

