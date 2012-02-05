/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/*************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#include <cstdlib>
#include <cstdio>

#include "statistics.h"
#include "config.h"

class logger
{
	public:
		logger(statistics * stat, const char * filename = DATALOG_FILENAME, int update_interval = LOGGER_UPDATE_INTERVAL);
		~logger();

		void update();
	private:
		float current_time;
		int commit_counter, interval, peak_pop;
		FILE * logfile;
		statistics * stats;
};

#endif

