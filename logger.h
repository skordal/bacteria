/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include <ctime>

#include "statistics.h"
#include "config.h"

class logger
{
	public:
		logger(statistics * stats, const std::string & filename = DATALOG_FILENAME,
			int update_interval = LOGGER_UPDATE_INTERVAL);
		~logger();

		void update();
	private:
		float current_time;
		int interval, peak_pop;
		std::ofstream logfile;
		statistics * stats;
};

#endif

