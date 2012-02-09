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
		~config_parser();

		bool parse();
	private:
		config_db * config;
		std::string filename;
};

#endif

