/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "energy_bar.h"

// Initializes the energy bar:
energy_bar::energy_bar(int energy) : current_energy(energy)
{
	max_energy = config_db::get().get_int_value("ReproductionEnergy");
}

// Draws the energy bar at the specified coordinates:
void energy_bar::draw(int x, int y) const
{
	int red_length = ENERGY_BAR_LENGTH * RED_PERCENT;
	int yellow_length = ENERGY_BAR_LENGTH * YELLOW_PERCENT;
	int green_length = ENERGY_BAR_LENGTH - yellow_length - red_length;
	int current_length = ceil(ENERGY_BAR_LENGTH * ((float) current_energy / (float) max_energy));

	// Draw the red bart of the image:
	for(int i = 0; i < red_length && i < current_length; ++i, ++x)
		window::get()->draw(image::get_red_bar_segment(), x, y);

	if(current_length < red_length)
		return;

	// Draw the yellow part of the image:
	for(int i = 0; i < yellow_length && (i + red_length < current_length); ++i, ++x)
		window::get()->draw(image::get_yellow_bar_segment(), x, y);

	if(current_length < red_length + yellow_length)
		return;

	// Draw the green part of the image:
	for(int i = 0; i < green_length && (i + red_length + yellow_length < current_length); ++i, ++x)
		window::get()->draw(image::get_green_bar_segment(), x ,y);
}

energy_bar & energy_bar::operator+=(int energy)
{
	current_energy += energy;
	return *this;
}

energy_bar & energy_bar::operator++()
{
	current_energy++;
	return *this;
}

energy_bar & energy_bar::operator--()
{
	current_energy--;
	return *this;
}

