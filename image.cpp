/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "image.h"

image::image(const char * filename, int alpha)
{
	assert(filename != NULL);

	img = SDL_LoadBMP(filename);
	if(img == NULL)
	{
		printf("ERROR: Could not load file \"%s\"!\n", filename);
		throw IMAGE_ERROR_NOT_FOUND;
	}

	SDL_SetColorKey(img, SDL_SRCCOLORKEY, DEFAULT_COLOR_KEY(img));
	SDL_SetAlpha(img, SDL_SRCALPHA, alpha);

	delete[] filename;
}

SDL_Surface * image::get_image()
{
	return img;
}

image::~image()
{
	SDL_FreeSurface(img);
}

