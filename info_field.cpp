/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "application.h"
#include "info_field.h"

using namespace std;

extern image * bacteria_image;

info_field::info_field(const bacteria & owner) : owner(owner)
{

}

void info_field::draw() const
{
	stringstream text;
	energy_bar ebar(owner.energy);

	switch(application::get()->get_info_mode())
	{
		case NONE:
			return;
		case ANCESTOR:
			text << owner.ancestor;
			break;
		case GENERATION:
			text << owner.generation;
			break;
		case ENERGY_BAR:
			ebar.draw(owner.speed.get_x() + bacteria_image->get_width(),
				owner.speed.get_y() + (bacteria_image->get_height() - ENERGY_BAR_HEIGHT) / 2);
			return;
		case POSITION:
			text << '(' << (int) owner.speed.get_x() << ", " << (int) owner.speed.get_y() << ')';
			break;
	}
	window::get()->draw(text.str(), owner.speed.get_x() + bacteria_image->get_width(), owner.speed.get_y());
}

