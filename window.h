/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <stdexcept>

#include <SDL.h>
#include <SDL_ttf.h>

#include "config.h"
#include "config_db.h"
#include "image.h"

class window
{
	public:
		// Creates the application window and returns a pointer
		// to it. If the window exists or an error occurred, an
		// error message is printed and 0 is returned.
		static window * create(int width, int height);

		// Draws an image to the window:
		void draw(const image & img, int x, int y);

		// Clears the window:
		void clear();
		// Flips the buffers:
		void flip_buffers() { SDL_Flip(screen); }
	private:
		window(int width, int height);
		~window();

		// Clean-up function, destroys the main window object:
		static void cleanup();

		SDL_Surface * screen, * window_icon;
		TTF_Font * font;

		static window * main_window;
};

#endif

