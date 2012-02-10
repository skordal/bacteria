/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "statistics.h"

using namespace std;

extern SDL_Surface * screen;
extern config_db * config;

#ifndef DISABLE_SDLTTF
extern TTF_Font * font;
#endif

statistics::statistics(int bacteria, int food)
	: bacteria(bacteria), food(food), game_over(false), paused(false),
	peak_pop(bacteria), peak_food(food), total_spawn(bacteria),
	food_eaten(food), avg_growth(0), last_pop(bacteria), max_gen(1),
	starting_time(time(0)), running_seconds(0), running_minutes(0),
	running_hours(0)
{
}

void statistics::update()
{
	if(!game_over && !paused)
		running_time = difftime(time(0), starting_time);

	running_seconds = running_time % 60;
	running_minutes = running_time / 60;
	if(running_minutes >= 60)
	{
		running_hours = running_minutes / 60;
		running_minutes = running_minutes % 60;
	}

	calc_avg_growth();
}

void statistics::draw()
{
	SDL_Surface * temp;
	SDL_Rect destination;

#ifndef DISABLE_SDLTTF
	stringstream message_buffer;

	// Upper statistics display:
	message_buffer << "Bacteria: " << setfill('0') << setw(2) << bacteria
		<< " | Food nuggets: " << setw(2) << food
		<< " | Most bacteria: " << setw(2) << peak_pop
		<< " | Most food: " << setw(2) << peak_food
		<< " | Running time: "
			<< setw(3) << running_hours << " h, "
			<< setw(2) << running_minutes << " m, "
			<< setw(2) << running_seconds << " s";

	temp = TTF_RenderText_Solid(font, message_buffer.str().c_str(), STATUS_TEXT_COLOR);
	if(temp == 0)
		cerr << "WARNING: Could not render top text!" << endl;
	else
		SDL_BlitSurface(temp, 0, screen, 0);
	
	if(temp != 0)
		SDL_FreeSurface(temp);

	// Lower statistics display:
	message_buffer.str("Empty");

	// Latest generation:
	message_buffer << "Latest generation: " << setw(4) << max_gen
		<< " | Total bacteria created: " << setw(7) << total_spawn
		<< " | Food nuggets eaten: " << setw(7) << food_eaten
		<< " | dP/dt: " << setprecision(3) << avg_growth;

//	if(game_over)
//		message_buffer << " | SIMULATION ENDED.";

	temp = TTF_RenderText_Solid(font, message_buffer.str().c_str(), STATUS_TEXT_COLOR);
	if(temp == 0)
		cerr << "WARNING: Could not render buttom text!" << endl;
	else {
		destination.x = 0;
		destination.y = config->get_int_value("ScreenHeight") - temp->h;
		SDL_BlitSurface(temp, 0, screen, &destination);
	}

	if(temp != 0)
		SDL_FreeSurface(temp);
#endif
}

// Simply calculated from the current number of bacteria.
void statistics::calc_avg_growth()
{
	static time_t prev_time = time(0);
	time_t dt = difftime(time(0), prev_time);
	int dP = bacteria - last_pop;

	if(dt < config->get_int_value("GrowthRateSamplingInterval"))
		return;

	avg_growth = (avg_growth + ((float) dP / (float) dt)) / 2.0f;

	last_pop = bacteria;
	time(&prev_time);
}

void statistics::remove_food()
{
	food--;
	food_eaten++;
}

void statistics::add_food()
{
	food++;
	if(food > peak_food)
		peak_food = food;
}

void statistics::add_bacteria(int generation)
{
	bacteria++;
	if(bacteria > peak_pop)
		peak_pop = bacteria;
	total_spawn++;
	if(generation > max_gen)
		max_gen = generation;
}

