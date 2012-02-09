/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>

#include "config.h"
#include "config_db.h"

class config_parser
{
	public:
		config_parser(config_db * config, const std::string & filename);

		bool parse();
		static bool config_file_exists(const char * filename);
	private:
		FILE * config_file;
		config_db * config;
		std::string filename;
};

#endif

