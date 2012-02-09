/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <iostream>
#include <string>

#include "config.h"
#include "config_db.h"

class config_parser
{
	public:
		config_parser(config_db * cfg, const std::string & filename);
		~config_parser();

		bool parse();
	private:
		config_db * config;
};

#endif

