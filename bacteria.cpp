/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/*************************************************/

#include "bacteria.h"

extern SDL_Surface * screen;
extern image * bacteria_image;

#ifndef DISABLE_SDLTTF
extern TTF_Font * font;
#endif

bacteria::bacteria(double angle, float init_speed, int ix, int iy, int init_energy, int gen)
	: alive(true), generation(gen), heading_for_food(false), at_food(false)
{
	if(init_energy == bacteria::default_starting_energy)
	{
		energy = config->get_int_value("BacteriaStartingEnergy");
		if(energy == 0)
			energy = STARTING_ENERGY;
	} else
		energy = init_energy;

	speed = vector(angle == 0.0f ? (random() % 360) * (M_PI/180) : angle,
		init_speed == 0.0f ? drand48() * (random() % 2) + 1 : init_speed,
		ix == 0 ? random() % (config->get_int_value("ScreenWidth") - BACTERIA_WIDTH) : ix,
		iy == 0 ? random() % (config->get_int_value("ScreenHeight") - BACTERIA_HEIGHT) : iy);

	e_bar.set_energy(energy);
}

void bacteria::reproduce()
{
	energy = config->get_int_value("ReproductionEnergy") / 2;
	e_bar.update(-config->get_int_value("ReproductionEnergy") / 2);
}

void bacteria::draw()
{
	SDL_Rect position;
	
	position.x = floorf(speed.get_x());
	position.y = floorf(speed.get_y());

	SDL_BlitSurface(bacteria_image->get_image(), NULL, screen, &position);
}

void bacteria::draw_coords()
{
#ifndef DISABLE_SDLTTF
	char * text = new char[COORDS_MAXLEN + 1];
	SDL_Surface * temp = NULL;
	SDL_Rect destination;

	snprintf(text, COORDS_MAXLEN, "(%.2f, %.2f)", speed.get_x(), speed.get_y());
	temp = TTF_RenderText_Solid(font, text, STATUS_TEXT_COLOR);

	assert(temp != NULL);

	destination.x = speed.get_x() + BACTERIA_WIDTH;
	destination.y = speed.get_y();

	SDL_BlitSurface(temp, NULL, screen, &destination);

	delete[] text;
	if(temp != NULL)
		SDL_FreeSurface(temp);
#endif
}

// Draw the energy bar or energy display:
void bacteria::draw_energy(bool graphically)
{
	if(graphically)
	{
		e_bar.draw(speed.get_x() + BACTERIA_WIDTH, speed.get_y() + ((BACTERIA_HEIGHT - ENERGY_BAR_HEIGHT) / 2));
	} else {
#ifndef DISABLE_SDLTTF
	char * text = new char[COORDS_MAXLEN + 1];
	SDL_Surface * temp = NULL;
	SDL_Rect destination;

	snprintf(text, COORDS_MAXLEN, "%d", energy);
	temp = TTF_RenderText_Solid(font, text, STATUS_TEXT_COLOR);

	assert(temp != NULL);

	destination.x = speed.get_x() + BACTERIA_WIDTH;
	destination.y = speed.get_y();

	SDL_BlitSurface(temp, NULL, screen, &destination);

	delete[] text;
	if(temp != NULL)
		SDL_FreeSurface(temp);
#endif
	}
}

// Update the bacteria, return false if dead:
bool bacteria::update()
{
	coordinate_pair_t bacteria_center = {speed.get_x() + BACTERIA_CENTER_X, speed.get_y() + BACTERIA_CENTER_Y};
	float temp_food_dist;

	energy--;
	e_bar--;
	if(energy <= 0)
		alive = false;

	if(at_food || !alive)
		return alive;

	speed.calc_pos();

	if(heading_for_food)
	{
		temp_food_dist = vector::distance_between(bacteria_center, food_loc);
		if(temp_food_dist <= prev_food_dist)
			prev_food_dist = temp_food_dist;
		else
			release(false);
	}

	if(speed.get_x() >= (config->get_int_value("ScreenWidth") - BACTERIA_WIDTH) || speed.get_x() <= 0.0f)
		speed.reflect(REFLECT_SIDES);
	if(speed.get_y() >= (config->get_int_value("ScreenHeight") - BACTERIA_HEIGHT) || speed.get_y() <= 0.0f)
		speed.reflect(REFLECT_TOP_BOTTOM);

	return alive;
}

int bacteria::feed()
{
	energy += config->get_int_value("FeedingEnergy");
	e_bar += config->get_int_value("FeedingEnergy");
	return config->get_int_value("FeedingEnergy");
}

bacteria * bacteria::release(bool new_dir)
{
	heading_for_food = false;
	at_food = false;

	if(new_dir)
	{
		speed.set_angle((double) (random() % 360) * (M_PI / 180.0f));
		speed.set_magnitude(drand48() * (random() % 2) + 1);
	}

	return NULL;
}

void bacteria::set_destination(coordinate_pair_t destination)
{
	double new_angle;
	float delta_x, delta_y;
	coordinate_pair_t bacteria_center = {speed.get_x() + BACTERIA_CENTER_X, speed.get_y() + BACTERIA_CENTER_Y};

	food_loc = destination;
	heading_for_food = true;

	new_angle = vector::angle_between(bacteria_center, destination);
	assert(new_angle != NAN);

	init_food_dist = vector::distance_between(bacteria_center, food_loc);
	prev_food_dist = init_food_dist;

	speed.set_angle(new_angle);
	speed.set_magnitude(drand48() * (random() % 2) + 1);
}

