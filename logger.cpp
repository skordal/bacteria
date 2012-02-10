/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "logger.h"

using namespace std;

logger::logger(statistics * stats, const string & filename, int update_interval)
	: logfile(filename.c_str()), stats(stats), current_time(0.0f), interval(update_interval)
{
	time_t now = time(0);

	if(logfile.good())
	{
		logfile << "# Bacteria population log" << endl;
		logfile << "# Generated automatically on " << ctime(&now) << endl;
		logfile << "# Time (s)\tBacteria\tFood" << endl;
	} else
		cerr << "WARNING: Cannot write to log file!" << endl;
}

void logger::update()
{
	if(stats->get_game_over())
		return;

	current_time += (float) interval / 1000.0f;
	int current_bacteria = stats->get_bacteria();
	int current_food = stats->get_food();

	if(logfile.good())
		logfile << setprecision(3) << current_time << "\t"
			<< current_bacteria << "\t" << current_food << endl;
}

logger::~logger()
{
	if(logfile.is_open())
		logfile.close();
}

