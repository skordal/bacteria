/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "application.h"
#include "window.h"

using namespace std;

extern config_db * config;

// The main window object:
window * window::main_window = 0;

// Creates the main window:
window * window::create(int width, int height)
{
	if(main_window == 0)
	{
		cerr << "WARNING: Main window already created!" << endl;
		return 0;
	}

	// Initialize SDL:
	clog << "Initializing SDL... ";
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) == -1)
	{
		clog << "failed!" << endl;
		cerr << "ERROR: Could not initialize SDL!" << endl;
		return 0;
	} else
		clog << "ok" << endl;
	atexit(SDL_Quit);

	// Initialize SDL_TTF:
	clog << "Initializing SDL_ttf... ";
	if(TTF_Init() == -1)
	{
		clog << "failed!" << endl;
		cerr << "ERROR: Could not initialize SDL_TTF!" << endl;
		return 0;
	} else
		clog << "ok" << endl;
	atexit(TTF_Quit);

	// Finally, create the main window, if possible:
	try {
		main_window = new window(width, height);
		atexit(main_window::cleanup);
	} catch(exception & error)
	{
		cerr << "ERROR: " << error.what() << endl;
		return 0;
	}
}

// Draws an image to the screen:
void window::draw(const image & img, int x, int y)
{
	SDL_Rect position;

	position.x = x;
	position.y = y;

	SDL_BlitSurface(image.get_image(), 0, screen, &position);
}

window::window(int width, int height)
{
	// Load the font for printing text to the screen:
	font = TTF_OpenFont(STATUS_FONT, STATUS_FONT_SIZE);
	if(font == 0)
		throw runtime_error(string("Could not load font from ").append(STATUS_FONT));
	
	// Create the window surface:
	clog << "Creating window (" << config->get_int_value("ScreenWidth") << " x "
		<< config->get_int_value("ScreenHeight") << ")...";
	screen = SDL_SetVideoMode(width, height, 0,
		config->get_bool_value("Fullscreen")
		? SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN
		: SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(screen == 0)
	{
		clog << "failed!" << endl;
		throw runtime_error("Could not create window!");
	} else
		clog << "ok" << endl;


	// Set window decoration specifics:
	SDL_WM_SetCaption("Bacteria Simulator", "Bacteria");
	window_icon = SDL_LoadBMP(ICON_FILENAME);
	if(window_icon != 0)
	{
		SDL_SetColorKey(window_icon, SDL_SRCCOLORKEY,
			SDL_MapRGB(window_icon->format, 255, 0, 255));
		SDL_WM_SetIcon(window_icon, 0);
	} else 
		cerr << "WARNING: Could not load icon file: " << ICON_FILENAME << endl;
}

window::~window()
{
	TTF_CloseFont(font);
}

void window::cleanup()
{
	if(main_window != 0)
		delete main_window;
}

// Clears the window:
void window::clear()
{
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B));
}

