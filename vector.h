/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

#include "config.h"
#include "macros.h"

#define ACCEPTABLE ACCEPTABLE_TOLERANCE

typedef struct {
	class vector * a;
	class vector * b;
} col_vector_t;

typedef struct {
	float x, y;
} coordinate_pair_t;

class vector
{
	public:
		vector();
		vector(const vector & copy);
		vector(double ang, double magn, float px = 0.0f, float py = 0.0f);

		float get_x() const { return x; }
		float get_y() const { return y; }

		void set_x(float x) { this->x = x; }
		void set_y(float y) { this->y = y; }
		void set_xy(float x, float y) { this->x = x; this->y = y; }

		double get_magnitude() const { return magnitude; }
		double get_angle() const { return angle; }

		void set_angle(double new_angle) { angle = new_angle; }
		void set_magnitude(double new_magnitude) { magnitude = new_magnitude; }

		coordinate_pair_t decompose();
		coordinate_pair_t get_position();

		static float distance_between(vector * a, vector * b);
		static float distance_between(const vector & a, const vector & b);
		static float distance_between(coordinate_pair_t a, coordinate_pair_t b);
		static double angle_between(coordinate_pair_t a, coordinate_pair_t b);
	protected:
		bool moving_sideways();
	private:
		double angle, magnitude;
		float x, y;
};

#endif

