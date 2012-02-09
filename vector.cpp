/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "vector.h"

// Blank constructor, sets all variables to 0:
vector::vector()
{
	angle = 0;
	magnitude = 0;
	x = 0;
	y = 0;
}

// Copy constructor:
vector::vector(const vector & copyme)
{
	angle = copyme.get_angle();
	magnitude = copyme.get_magnitude();
	x = copyme.get_x();
	y = copyme.get_y();
}

vector::vector(double ang, double magn, float px, float py)
{
	angle = ang;
	magnitude = magn;

	x = px;
	y = py;
}

// Returns the x and y components of the vector as a coordinate pair:
coordinate_pair_t vector::decompose()
{
	coordinate_pair_t retval;
	retval.x = cos(angle) * magnitude;
	retval.y = sin(angle) * magnitude;

	return retval;
}

// Returns the x and y coordinates of the vector as a coordinate pair:
coordinate_pair_t vector::get_position()
{
	coordinate_pair_t retval;
	retval.x = x;
	retval.y = y;
	
	return retval;
}

// The three following functions returns the distance between the origin
// of vector a and vector b:
float vector::distance_between(vector * a, vector * b)
{
	float delta_x, delta_y;

	delta_x = fabsf(a->get_x() - b->get_x());
	delta_y = fabsf(a->get_y() - b->get_y());

	return hypotf(delta_x, delta_y);
}

float vector::distance_between(const vector & a, const vector & b)
{
	float delta_x, delta_y;

	delta_x = fabsf(a.get_x() - b.get_x());
	delta_y = fabsf(a.get_y() - b.get_y());

	return hypotf(delta_x, delta_y);
}

float vector::distance_between(coordinate_pair_t a, coordinate_pair_t b)
{
	float delta_x, delta_y;

	delta_x = fabsf(a.x - b.x);
	delta_y = fabsf(a.y - b.y);

	return hypotf(delta_x, delta_y);
}

// This function returns the angle between two coordinate pairs:
double vector::angle_between(coordinate_pair_t a, coordinate_pair_t b)
{
	double delta_x, delta_y;

	delta_x = b.x - a.x;
	delta_y = a.y - b.y;

	return atan2(delta_y, delta_x);
}

