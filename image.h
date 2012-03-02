/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <stdexcept>
#include <string>

#include <SDL.h>

#include "config.h"

class image
{
	public:
		image(const std::string & filename, int alpha = SDL_ALPHA_OPAQUE);
		~image();
	
		SDL_Surface * get_image() const { return img; }

		int get_width() const { return img->w; }
		int get_height() const { return img->h; }
	private:
		SDL_Surface * img;
};

#endif

