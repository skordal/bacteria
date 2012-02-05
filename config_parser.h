/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/*************************************************/

#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <assert.h>
#include <ctype.h>

#include <unistd.h>

#include "config.h"
#include "config_db.h"

class config_parser
{
	public:
		config_parser(config_db * cfg, const char * filename);
		~config_parser();

		bool parse();
		static bool config_file_exists(const char * filename);
	private:
		FILE * config_file;
		config_db * config;
};

#endif

