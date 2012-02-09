/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef CONFIG_DB_H
#define CONFIG_DB_H

#include <cstring>
#include <cstdio>
#include <inttypes.h>
#include <assert.h>

#include <string>
#include <map>

#include "config.h"

class config_db;
extern config_db * config;

typedef enum {
	TYPE_INTEGER, TYPE_BOOLEAN, TYPE_FLOAT, TYPE_STRING, TYPE_INVALID
} config_type_t;

typedef struct {
	union {
		int int_value;
		bool bool_value;
		float float_value;
		char * string_value;
	};
	config_type_t type;
} config_value_t;

class config_db
{
	public:
		config_db();
		~config_db();

		// Returns false if wrong type:
		bool set_value(const std::string & name, int value);
		bool set_value(const std::string & name, bool value);
		bool set_value(const std::string & name, float value);
		bool set_value(const std::string & name, const char * value);

		int get_int_value(const std::string & name) const;
		bool get_bool_value(const std::string & name) const;
		float get_float_value(const std::string & name) const;
		const char * get_string_value(const std::string & name) const;

		static config_type_t get_type(const std::string & name);
	private:
		std::map<std::string, config_value_t> values;
};

#endif

