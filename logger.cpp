/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "logger.h"

logger::logger(statistics * stat, const char * filename, int update_interval)
{
	time_t now = time(NULL);

	logfile = fopen(filename, "w");
	assert(logfile != NULL);

	stats = stat;
	current_time = 0.0f;
	commit_counter = 0;
	interval = update_interval;

	fprintf(logfile, "# Bacteria population log\n");
	fprintf(logfile, "# Generated automatically on %s", ctime(&now));
	fprintf(logfile, "# Time (s)\tBacteria\tFood\n");
}

void logger::update()
{
	if(stats->get_game_over())
		return;

	current_time += (float) interval / 1000.0f;
	int current_bacteria = stats->get_bacteria();
	int current_food = stats->get_food();

	fprintf(logfile, "%.3f\t%d\t%d\n", current_time, current_bacteria, current_food);

	if(commit_counter >= LOGGER_COMMIT_INTERVAL)
	{
		fflush(logfile);
		commit_counter = 0;
	} else
		commit_counter ++;
}

logger::~logger()
{
	if(logfile != NULL)
		fclose(logfile);
}

