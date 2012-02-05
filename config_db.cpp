/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/*************************************************/

#include "config_db.h"

extern config_db * config; // Required for default_config.h
#include "default_config.h"

using namespace std;

config_db::config_db()
{
	for(int c = 0; default_config[c].name != NULL; c++)
	{
		switch(default_config[c].type)
		{
			case TYPE_INTEGER:
				set_value(default_config[c].name, default_config[c].int_val);
				break;
			case TYPE_BOOLEAN:
				set_value(default_config[c].name, default_config[c].bool_val);
				break;
			case TYPE_FLOAT:
				set_value(default_config[c].name, default_config[c].float_val);
				break;
			case TYPE_STRING:
				set_value(default_config[c].name, default_config[c].string_val);
				break;
		}
	}
}

bool config_db::set_value(const string & name, int val)
{
	if(get_type(name) != TYPE_INTEGER)
		return false;

	config_value_t retval;
	retval.int_value = val;
	retval.type = TYPE_INTEGER;

	values[name] = retval;

	return true;
}

bool config_db::set_value(const string & name, bool val)
{
	if(get_type(name) != TYPE_BOOLEAN)
		return false;

	config_value_t retval;
	retval.bool_value = val;
	retval.type = TYPE_BOOLEAN;
	
	values[name] = retval;

	return true;
}

// WARNING: Puts a new (float *) into the map.
bool config_db::set_value(const string & name, float val)
{
	if(get_type(name) != TYPE_FLOAT)
		return false;

	config_value_t retval;
	retval.float_value = val;
	retval.type = TYPE_FLOAT;

	values[name] = retval;

	return true;
}

bool config_db::set_value(const string & name, const char * val)
{
	char * temp = new char[strlen(val) + 1];

	assert(val != NULL);
	if(get_type(name) != TYPE_STRING)
		return false;

	strcpy(temp, val);
	config_value_t retval;
	retval.type = TYPE_STRING;
	retval.string_value = temp;

	values[name] = retval;

	return true;
}

int config_db::get_int_value(const string & key) const
{
	map<string, config_value_t>::const_iterator iterator = values.find(key);
	assert(iterator != values.end());

	config_value_t retval = iterator->second;

	assert(retval.type == TYPE_INTEGER);
	return retval.int_value;
}

bool config_db::get_bool_value(const string & key) const
{
	map<string, config_value_t>::const_iterator iterator = values.find(key);
	assert(iterator != values.end());

	config_value_t retval = iterator->second;

	assert(retval.type == TYPE_BOOLEAN);
	return retval.bool_value;
}

float config_db::get_float_value(const string & key) const
{
	map<string, config_value_t>::const_iterator iterator = values.find(key);
	assert(iterator != values.end());

	config_value_t retval = iterator->second;

	assert(retval.type == TYPE_FLOAT);
	return retval.float_value;
}

const char * config_db::get_string_value(const string & key) const
{
	map<string, config_value_t>::const_iterator iterator = values.find(key);
	assert(iterator != values.end());

	config_value_t retval = iterator->second;

	assert(retval.type == TYPE_STRING);
	return const_cast<const char *>(retval.string_value);
}

config_type_t config_db::get_type(const string & key)
{
	for(int c = 0; default_config[c].name != NULL; c++)
	{
		if(key == default_config[c].name)
			return default_config[c].type;
	}

	return TYPE_INVALID;
}

config_db::~config_db()
{
	// TODO: Free the values that need freeing.
	values.clear();
}

