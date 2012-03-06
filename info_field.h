/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef INFO_FIELD_H
#define INFO_FIELD_H

#include <sstream>

#include "energy_bar.h"

// info_field uses the bacteria class and vice-versa:
class bacteria;

class info_field
{
	public:
		typedef enum {
			GENERATION,
			ANCESTOR,
			ENERGY_BAR,
			POSITION,
			NONE
		} mode;

		// Creates an info field belonging to the specified bacteria:
		info_field(const bacteria & owner);

		// Renders the info field:
		void draw() const;
	private:
		const bacteria & owner;
};

#endif

