/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "application.h"
#include "bacteria.h"

using namespace std;

extern image * bacteria_image;

#ifndef DISABLE_SDLTTF
extern TTF_Font * font;
#endif

bacteria::bacteria(double angle, float init_speed, int ix, int iy, int init_energy, int gen)
	: alive(true), generation(gen), heading_for_food(false), at_food(false)
{
	if(init_energy == bacteria::default_starting_energy)
	{
		energy = STARTING_ENERGY;
	} else
		energy = init_energy;

	speed = vector(angle == 0.0f ? (random() % 360) * (M_PI/180) : angle,
		init_speed == 0.0f ? drand48() * (random() % 2) + 1 : init_speed,
		ix == 0 ? random() % (config->get_int_value("ScreenWidth") - bacteria_image->get_width()) : ix,
		iy == 0 ? random() % (config->get_int_value("ScreenHeight") - bacteria_image->get_height()) : iy);

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

	SDL_BlitSurface(bacteria_image->get_image(), 0, 
		application::get()->get_screen(), &position);
}

void bacteria::draw_coords()
{
#ifndef DISABLE_SDLTTF
	SDL_Surface * temp = 0;
	SDL_Rect destination;
	stringstream text;

	text << '(' << (int) speed.get_x() << ',' << (int) speed.get_y() << ')';
	temp = TTF_RenderText_Solid(font, text.str().c_str(), STATUS_TEXT_COLOR);

	assert(temp != 0);

	destination.x = speed.get_x() + bacteria_image->get_width();
	destination.y = speed.get_y();

	SDL_BlitSurface(temp, 0, application::get()->get_screen(), &destination);
	SDL_FreeSurface(temp);
#endif
}

// Draw the energy bar or energy display:
void bacteria::draw_energy(bool graphically)
{
	if(graphically)
		e_bar.draw(speed.get_x() + bacteria_image->get_width(),
			speed.get_y() + ((bacteria_image->get_height() - ENERGY_BAR_HEIGHT) / 2));
#ifndef DISABLE_SDLTTF
	else {
		SDL_Surface * temp = 0;
		SDL_Rect destination;
		stringstream text;

		text << energy;
		temp = TTF_RenderText_Solid(font, text.str().c_str(), STATUS_TEXT_COLOR);

		assert(temp != 0);

		destination.x = speed.get_x() + bacteria_image->get_width();
		destination.y = speed.get_y();

		SDL_BlitSurface(temp, 0, application::get()->get_screen(), &destination);
		SDL_FreeSurface(temp);
	}
#endif
}

// Update the bacteria, return false if dead:
bool bacteria::update()
{
	coordinate_pair_t bacteria_center = {speed.get_x() + bacteria_image->get_width() / 2,
		speed.get_y() + bacteria_image->get_height() / 2};
	float temp_food_dist;

	// Reduce the bacteria's energy supply:
	--energy;
	--e_bar;

	// Check if it died due to lack of energy:
	if(energy <= 0)
		alive = false;

	// Return if we should not move:
	if(at_food || !alive)
		return alive;

	// Update the position of the bacteria:
	speed.set_x(speed.get_x() + (cos(speed.get_angle()) * speed.get_magnitude()));
	speed.set_y(speed.get_y() - (sin(speed.get_angle()) * speed.get_magnitude()));

	// If heading for food, check if there is still food at the discovered food's
	// location:
	if(heading_for_food)
	{
		temp_food_dist = vector::distance_between(bacteria_center, food_loc);
		// If the food is getting closer, store the current position to the
		// food for next time, if not, release the bacteria from this food
		// nugget, making it free to look for other food:
		if(temp_food_dist <= prev_food_dist)
			prev_food_dist = temp_food_dist;
		else
			release(false);
	}

	// Check for collision with the screen edges:
	if(speed.get_x() >= (config->get_int_value("ScreenWidth") - bacteria_image->get_width())
		|| speed.get_x() <= 0.0f)
	{
		speed.set_angle(M_PI - speed.get_angle());
	}

	if(speed.get_y() >= (config->get_int_value("ScreenHeight") - bacteria_image->get_height())
		|| speed.get_y() <= 0.0f)
	{
		speed.set_angle(speed.get_angle() - 2 * speed.get_angle());
	}

	return alive;
}

int bacteria::feed()
{
	energy += config->get_int_value("FeedingEnergy");
	e_bar += config->get_int_value("FeedingEnergy");
	return config->get_int_value("FeedingEnergy");
}

void bacteria::release(bool new_dir)
{
	heading_for_food = false;
	at_food = false;

	if(new_dir)
	{
		speed.set_angle((double) (random() % 360) * (M_PI / 180.0f));
		speed.set_magnitude(drand48() * (random() % 2) + 1);
	}
}

void bacteria::set_destination(coordinate_pair_t destination)
{
	double new_angle;
	float delta_x, delta_y;
	coordinate_pair_t bacteria_center = {speed.get_x() + bacteria_image->get_width() / 2,
		speed.get_y() + bacteria_image->get_height() / 2};

	food_loc = destination;
	heading_for_food = true;

	new_angle = vector::angle_between(bacteria_center, destination);
	assert(new_angle != NAN);

	init_food_dist = vector::distance_between(bacteria_center, food_loc);
	prev_food_dist = init_food_dist;

	speed.set_angle(new_angle);
	speed.set_magnitude(drand48() * (random() % 2) + 1);
}

