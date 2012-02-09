/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "food.h"

extern SDL_Surface * screen;
extern image * food_image;
extern config_db * config;

// This function initializes the food nugget:
food::food(int x, int y)
{
	this->x = x;
	this->y = y;

	anchor_1 = 0;
	anchor_2 = 0;
	anchor_3 = 0;
	anchor_4 = 0;

	energy = FOOD_ENERGY;
}

// This function draws the food nugget:
void food::draw()
{
	SDL_Rect position;
	position.x = x;
	position.y = y;

	SDL_BlitSurface(food_image->get_image(), 0, screen, &position);
}

// This function returns the "anchor point" closes to the specified bacteria.
// It calculates the distance between the bacteria centrum and the various
// anchors on the food nugget, and then it takes the shortest of those
// distances and returns the coordinates of that anchor.
coordinate_pair_t food::closest_anchor(const vector & bacteria_vector)
{
	coordinate_pair_t retval;
	vector this_vector = vector(0, 0, F_ANCHOR_1_X + x, F_ANCHOR_1_Y + y);
	float distance_1, distance_2, distance_3, distance_4, eval_dist;
	std::valarray<float> distances(4);

	if(anchor_1 == 0)
	{
		distance_1 = vector::distance_between(this_vector, bacteria_vector);
		distances[0] = distance_1;
	} else
		distances[0] = INFINITY;

	if(anchor_2 == 0)
	{
		this_vector.set_xy(F_ANCHOR_2_X + x, F_ANCHOR_2_Y + y);
		distance_2 = vector::distance_between(this_vector, bacteria_vector);
		distances[1] = distance_2;
	} else 
		distances[1] = INFINITY;

	if(anchor_3 == 0)
	{
		this_vector.set_xy(F_ANCHOR_3_X + x, F_ANCHOR_3_Y + y);
		distance_3 = vector::distance_between(this_vector, bacteria_vector);
		distances[2] = distance_3;
	} else 
		distances[2] = INFINITY;

	if(anchor_4 == 0)
	{
		this_vector.set_xy(F_ANCHOR_4_X + x, F_ANCHOR_4_Y + y);
		distance_4 = vector::distance_between(this_vector, bacteria_vector);
		distances[3] = distance_4;
	} else
		distances[3] = INFINITY;

	eval_dist = distances.min();

	if(eval_dist == distance_1)
		retval = ANCHOR_1;
	
	if(eval_dist == distance_2)
		retval = ANCHOR_2;

	if(eval_dist == distance_3)
		retval = ANCHOR_3;

	if(eval_dist == distance_4)
		retval = ANCHOR_4;

	return retval;
}

// This function updates the food nugget and feeds the bacteria attached to it:
bool food::update()
{
	if(energy <= 0)
		return false;
	if(anchor_1 != 0)
		energy -= anchor_1->feed();
	
	if(energy <= 0)
		return false;
	if(anchor_2 != 0)
		energy -= anchor_2->feed();
	
	if(energy <= 0)
		return false;
	if(anchor_3 != 0)
		energy -= anchor_3->feed();
	
	if(energy <= 0)
		return false;
	if(anchor_4 != 0)
		energy -= anchor_4->feed();

	return true;
}

// Release the bacteria attached to this food nugget when it is depleted:
void food::release_bacteria()
{
	if(anchor_1 != 0)
		anchor_1 = anchor_1->release();

	if(anchor_2 != 0)
		anchor_2 = anchor_2->release();
	
	if(anchor_3 != 0)
		anchor_3 = anchor_3->release();
	
	if(anchor_4 != 0)
		anchor_4 = anchor_4->release();
}

// This function checks for bacteria to attach to the food nugget.
// This is done here because the bacteria attaches to the food through
// pointers in this class.
void food::check_for_bacteria(std::list<bacteria> & bacteria_list)
{
	std::list<bacteria>::iterator bacteria_iterator;

	vector food_location = vector(0, 0, x + FOOD_CENTER_X, y + FOOD_CENTER_Y);

	// Iterate through the bacteria list:
	for(bacteria_iterator = bacteria_list.begin(); bacteria_iterator != bacteria_list.end(); bacteria_iterator++)
	{
		bacteria & temp = *bacteria_iterator;
		vector temp_center = vector(temp.get_vector());
		coordinate_pair_t bacteria_dest = temp.get_destination();
		temp_center.set_xy(temp_center.get_x() + BACTERIA_CENTER_X, temp_center.get_y() + BACTERIA_CENTER_Y);
		float distance = vector::distance_between(temp_center, food_location);

		// Check if the bacteria is within "smelling distance" of the food:
		if(distance <= config->get_float_value("FoodSmellingDistance")
			&& !temp.is_heading_for_food())
		{
			coordinate_pair_t anchor_temp = this->closest_anchor(temp_center);
			if(!(anchor_temp.x == 0 && anchor_temp.y == 0))
				temp.set_destination(anchor_temp);
		} else if(temp.is_heading_for_food())
		{
			if(CMP_PAIR(bacteria_dest, ANCHOR_1)
				|| CMP_PAIR(bacteria_dest, ANCHOR_2)
				|| CMP_PAIR(bacteria_dest, ANCHOR_3)
				|| CMP_PAIR(bacteria_dest, ANCHOR_4))
			{
				if(AT_DESTINATION(temp_center.get_position(), ANCHOR_1, ACCEPTABLE))
				{
					if(anchor_1 != 0 && anchor_1 != &temp)
						temp.release();
					else {
						anchor_1 = &temp;
						anchor_1->stop();
					}
				}
				if(AT_DESTINATION(temp_center.get_position(), ANCHOR_2, ACCEPTABLE))
				{
					if(anchor_2 != 0 && anchor_2 != &temp)
						temp.release();
					else {
						anchor_2 = &temp;
						anchor_2->stop();
					}
				}
				if(AT_DESTINATION(temp_center.get_position(), ANCHOR_3, ACCEPTABLE))
				{
					if(anchor_3 != 0 && anchor_3 != &temp)
						temp.release();
					else {
						anchor_3 = &temp;
						anchor_3->stop();
					}
				}
				if(AT_DESTINATION(temp_center.get_position(), ANCHOR_4, ACCEPTABLE))
				{
					if(anchor_4 != 0 && anchor_4 != &temp)
						temp.release();
					else {
						anchor_4 = &temp;
						anchor_4->stop();
					}
				}
			}
		}
	}
}

food::~food()
{

}

