/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "application.h"
#include "image.h"

using namespace std;

// The bacteria and food images:
image * image::bacteria_image = 0, * image::food_image = 0;
// The energy bar segment images:
image * image::red_bar_segment = 0, * image::yellow_bar_segment = 0;
image * image::green_bar_segment = 0;

// Loads the application images:
void image::load_images() throw(runtime_error)
{
	atexit(image::cleanup);

	bacteria_image = new image(BACTERIA_FILENAME, BACTERIA_ALPHA);
	food_image = new image(FOOD_FILENAME, FOOD_ALPHA);

	red_bar_segment = new image(RED_BAR_SEGMENT);
	yellow_bar_segment = new image(YELLOW_BAR_SEGMENT);
	green_bar_segment = new image(GREEN_BAR_SEGMENT);
}

// Cleans up the globally allocated images:
void image::cleanup()
{
	if(bacteria_image != 0)
		delete bacteria_image;
	if(food_image != 0)
		delete food_image;
	if(red_bar_segment != 0)
		delete red_bar_segment;
	if(yellow_bar_segment != 0)
		delete yellow_bar_segment;
	if(green_bar_segment != 0)
		delete green_bar_segment;
}

image::image(const string & filename, int alpha) throw(runtime_error)
{
	assert(!filename.empty());

	img = SDL_LoadBMP(filename.c_str());
	if(img == NULL)
		throw runtime_error(string("could not load file ").append(filename));

	SDL_SetColorKey(img, SDL_SRCCOLORKEY, DEFAULT_COLOR_KEY(img));
	SDL_SetAlpha(img, SDL_SRCALPHA, alpha);
}

image::~image()
{
	SDL_FreeSurface(img);
}

