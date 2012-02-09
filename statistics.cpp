/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "statistics.h"

extern SDL_Surface * screen;
extern config_db * config;

#ifndef DISABLE_SDLTTF
extern TTF_Font * font;
#endif

statistics::statistics(int bacteria, int food)
	: bacteria(bacteria), food(food), game_over(false), paused(false),
	peak_pop(bacteria), peak_food(food), total_spawn(bacteria),
	food_eaten(food), avg_growth(0), last_pop(bacteria), max_gen(1),
	starting_time(time(NULL)), running_seconds(0), running_minutes(0),
	running_hours(0)
{
	message_buffer = new char[STATUS_MAXLEN];
}

void statistics::update()
{
	if(!game_over && !paused)
		running_time = difftime(time(NULL), starting_time);

	running_seconds = running_time % 60;
	running_minutes = (running_time - (running_time % 60)) / 60;
	if(running_minutes >= 60)
	{
		running_hours = (running_minutes - (running_minutes % 60)) / 60;
		running_minutes = running_minutes % 60;
	}

	calc_avg_growth();
}

void statistics::draw()
{
	SDL_Surface * temp;
	SDL_Rect destination;

#ifndef DISABLE_SDLTTF
// Upper statistics display:
	snprintf(message_buffer, STATUS_MAXLEN,
		"Bacteria: %.2d | " \
		"Food nuggets: %.2d | " \
		"Most bacteria: %.2d | " \
		"Most food: %.2d | " \
		"Running time: %.3d h, %.2d m, %.2d s",
		bacteria, food, peak_pop, peak_food, running_hours,
		running_minutes, running_seconds);

	temp = TTF_RenderText_Solid(font, message_buffer, STATUS_TEXT_COLOR);
	if(temp == NULL)
		printf("WARNING: Could not render top text!\n");
	else
		SDL_BlitSurface(temp, NULL, screen, NULL);
	
	if(temp != NULL)
		SDL_FreeSurface(temp);

// Lower statistics display:
	snprintf(message_buffer, STATUS_MAXLEN,
		"Latest generation: %.3d | " \
		"Total bacteria created: %.7lld | " \
		"Food nuggets eaten: %.7lld | dP/dt: %.2f",
		max_gen, total_spawn, food_eaten, avg_growth);

	if(game_over)
		strcat(message_buffer, " | SIMULATION ENDED.");

	temp = TTF_RenderText_Solid(font, message_buffer, STATUS_TEXT_COLOR);
	if(temp == NULL)
		printf("WARNING: Could not render bottom text!\n");
	else {
		destination.x = 0;
		destination.y = config->get_int_value("ScreenHeight") - temp->h;
		SDL_BlitSurface(temp, NULL, screen, &destination);
	}

	if(temp != NULL)
		SDL_FreeSurface(temp);
#endif
}

// Simply calculated from the current number of bacteria.
void statistics::calc_avg_growth()
{
	static time_t prev_time = time(NULL);
	time_t dt = difftime(time(NULL), prev_time);
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

statistics::~statistics()
{
	delete[] message_buffer;
}

