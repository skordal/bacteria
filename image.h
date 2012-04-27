/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef IMAGE_H
#define IMAGE_H

#include <cstdlib>
#include <stdexcept>
#include <string>

#include <SDL.h>

#include "config.h"

class image
{
	public:
		// Loads the application images:
		static void load_images() throw(std::runtime_error);

		// Gets the various images:
		static const image & get_bacteria() { return *bacteria_image; }
		static const image & get_food() { return *food_image; }
		static const image & get_red_bar_segment() { return *red_bar_segment; }
		static const image & get_yellow_bar_segment() { return *yellow_bar_segment; }
		static const image & get_green_bar_segment() { return *green_bar_segment; }

		// Gets a pointer to the SDL_Surface containing the image:
		SDL_Surface * get_image() const { return img; }
		operator SDL_Surface* () const { return img; }

		// Gets the dimensions of an image:
		int get_width() const { return img->w; }
		int get_height() const { return img->h; }
	private:
		// Cleans up the globally allocated images:
		static void cleanup();

		// Loads an image from the specified filename and sets its alpha value
		// to the specified value:
		image(const std::string & filename, int alpha = SDL_ALPHA_OPAQUE) throw(std::runtime_error);
		~image();

		SDL_Surface * img;

		// Global image objects, initialized by image::initialize():
		static image * bacteria_image, * food_image;
		static image * red_bar_segment, * yellow_bar_segment, * green_bar_segment;
};

#endif

