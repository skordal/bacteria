/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "config_parser.h"

config_parser::config_parser(config_db * cfg, const char * filename)
{
	assert(filename != NULL);
	assert(cfg != NULL);

	config_file = fopen(filename, "r");
	config = cfg;
}

bool config_parser::parse()
{
	char * in_string, * temp, * delim, * value, * name;
	config_type_t value_type;
	union {
		int int_val;
		float float_val;
		bool bool_val;
		char * string_val;
	};
	int current_line = 1;

	if(config_file == NULL)
	{
		printf("Could not open configuration file!\n");
		return false;
	}

	while(!feof(config_file))
	{
		in_string = new char[CONFIG_LINE_MAXLEN];
		in_string = fgets(in_string, CONFIG_LINE_MAXLEN, config_file);

		if(in_string == NULL)
		{
			delete[] in_string;
			if(!feof(config_file))
			{
				printf("An error occurred while reading line %d of the config file!\n", current_line);
				return false;
			} else
				break;
		}
	
		temp = new char[CONFIG_LINE_MAXLEN];
		int t = 0;

		for(int c = 0; c < strnlen(in_string, CONFIG_LINE_MAXLEN); c++)
		{
			if(!isspace(in_string[c]))
			{
				temp[t] = in_string[c];
				t++;
			}
		}
		delete[] in_string;

		temp[t] = '\0';
		if(strlen(temp) == 0 || temp[0] == '#')
			goto _endline;

		delim = index(temp, '=');

		temp[delim - temp] = '\0';
		name = temp;

		value_type = config_db::get_type(name);
		value = delim + 1;

		switch(value_type)
		{
			case TYPE_INTEGER:
				int_val = atoi(value);
				config->set_value(name, int_val);
				break;
			case TYPE_BOOLEAN:
				if(strncasecmp(value, "true", strlen(value)) == 0)
					bool_val = true;
				else if(strncasecmp(value, "false", strlen(value)) == 0)
					bool_val = false;
				else {
					printf("Line %d: Value is not a boolean!\n", current_line);
					delete[] temp;
					return false;
				}
				config->set_value(name, bool_val);
				break;
			case TYPE_FLOAT:
				float_val = atof(value);
				config->set_value(name, float_val);
				break;
			case TYPE_STRING:
				config->set_value(name, value);
				break;
			default:
				printf("Line %d: Invalid key name \"%s\"\n", current_line, name);
				break;
		}

_endline:
		delete[] temp;
		current_line++;
	}

	return true;
}

bool config_parser::config_file_exists(const char * filename)
{
	assert(filename != NULL);

	if(access(filename, R_OK) != 0)
		return false;
	return true;
}

config_parser::~config_parser()
{
	if(config_file != NULL)
		fclose(config_file);
}

