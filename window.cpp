/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "application.h"
#include "window.h"

using namespace std;

// The main window object:
window * window::main_window = 0;

// Creates the application window:
void window::create(int width, int height) throw(runtime_error)
{
	if(main_window != 0)
	{
		cerr << "WARNING: Main window already created!" << endl;
		return;
	}

	// Initialize SDL:
	clog << "Initializing SDL... ";
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) == -1)
	{
		clog << "failed!" << endl;
		throw runtime_error("could not initialize SDL");
	} else
		clog << "ok" << endl;
	atexit(SDL_Quit);

	// Initialize SDL_TTF:
	clog << "Initializing SDL_ttf... ";
	if(TTF_Init() == -1)
	{
		clog << "failed!" << endl;
		throw runtime_error("could not initialize SDL_TTF");
	} else
		clog << "ok" << endl;
	atexit(TTF_Quit);

	// Finally, create the main window, if possible:
	try {
		main_window = new window(width, height);
		atexit(window::cleanup);
	} catch(exception & error)
	{
		cerr << "ERROR: " << error.what() << endl;
		return;
	}
}

// Draws an image to the screen:
void window::draw(const image & img, int x, int y)
{
	SDL_Rect position;

	position.x = x;
	position.y = y;

	SDL_BlitSurface(img.get_image(), 0, screen, &position);
}

// Draws a string to the screen:
void window::draw(const string & text, int x, int y)
{
	SDL_Rect position;
	SDL_Surface * temp = TTF_RenderText_Solid(font, text.c_str(), STATUS_TEXT_COLOR);

	if(temp == 0)
	{
		cerr << "WARNING: Could not render string: \"" << text << "\"" << endl;
		return;
	}

	position.x = x;
	position.y = y;
	SDL_BlitSurface(temp, 0, screen, &position);
	SDL_FreeSurface(temp);
}

window::window(int width, int height) throw(runtime_error)
{
	// Load the font for printing text to the screen:
	font = TTF_OpenFont(STATUS_FONT, STATUS_FONT_SIZE);
	if(font == 0)
		throw runtime_error(string("could not load font from ").append(STATUS_FONT));
	
	// Create the window surface:
	clog << "Creating window (" << config_db::get().get_int_value("ScreenWidth") << " x "
		<< config_db::get().get_int_value("ScreenHeight") << ")...";
	screen = SDL_SetVideoMode(width, height, 0, config_db::get().get_bool_value("Fullscreen")
		? SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN : SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(screen == 0)
	{
		clog << "failed!" << endl;
		throw runtime_error("could not create window");
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

