/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "image.h"

using namespace std;

image::image(const string & filename, int alpha)
{
	assert(!filename.empty());

	img = SDL_LoadBMP(filename.c_str());
	if(img == NULL)
	{
		cerr << "ERROR: Could not load file " << filename << "!" << endl;
		throw IMAGE_ERROR_NOT_FOUND;
	}

	SDL_SetColorKey(img, SDL_SRCCOLORKEY, DEFAULT_COLOR_KEY(img));
	SDL_SetAlpha(img, SDL_SRCALPHA, alpha);
}

image::~image()
{
	SDL_FreeSurface(img);
}

