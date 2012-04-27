/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "config.h"
#include "config_db.h"
#include "image.h"

class window
{
	public:
		// Creates the application window:
		static void create(int width, int height) throw(std::runtime_error);

		// Gets the application window:
		static window * get() { return main_window; }
		
		// Draws an image to the window:
		void draw(const image & img, int x, int y);
		void draw(const std::string & text, int x, int y);

		// Returns the height of the font:
		int get_font_height() { return TTF_FontHeight(font); }

		// Clears the window:
		void clear();
		// Flips the buffers:
		void flip_buffers() { SDL_Flip(screen); }
	private:
		window(int width, int height) throw(std::runtime_error);
		~window();

		// Clean-up function, destroys the main window object:
		static void cleanup();

		SDL_Surface * screen, * window_icon;
		TTF_Font * font;

		// The application's main window:
		static window * main_window;
};

#endif

