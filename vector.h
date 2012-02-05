/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/*************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include "config.h"
#include "macros.h"

#define REFLECT_SIDES true
#define REFLECT_TOP_BOTTOM false

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
		vector(const vector & copyme);
		vector(double ang, double magn, float px = 0.0f, float py = 0.0f);

		float get_x() const { return x; }
		float get_y() const { return y; }

		void set_x(float nx) { x = nx; }
		void set_y(float ny) { y = ny; }
		void set_xy(float nx, float ny) { x = nx; y = ny; }

		double get_magnitude() const { return magnitude; }
		double get_angle() const { return angle; }

		void set_angle(double new_angle) { angle = new_angle; }
		void set_magnitude(double new_magnitude) { magnitude = new_magnitude; }

		void calc_pos();
		void reflect(bool sides = false); // Set to true if colliding with sides.

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

