/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include <cstdlib>
#include <assert.h>
#include <climits>
#include <unistd.h>

#include "config.h"

#define IMAGE_ERROR_NOT_FOUND -1

class image
{
	public:
		image(const char * filename, int alpha = SDL_ALPHA_OPAQUE);
		~image();
	
		SDL_Surface * get_image();
	private:
		SDL_Surface * img;
};

#endif

