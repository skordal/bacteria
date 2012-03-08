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
		config_parser(const std::string & filename);

		bool parse();
	private:
		std::string filename;
};

#endif

