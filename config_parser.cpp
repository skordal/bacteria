/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "config_parser.h"

using namespace std;

config_parser::config_parser(config_db * cfg, const string & filename)
{
	assert(!filename.empty());
	assert(cfg != NULL);
}

bool config_parser::parse()
{
	return true;
}

config_parser::~config_parser()
{
}

