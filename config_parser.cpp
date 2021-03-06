/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "config_parser.h"

using namespace std;

config_parser::config_parser(const string & filename)
	: filename(filename)
{
	assert(!filename.empty());
}

bool config_parser::parse()
{
	ifstream config_file(filename.c_str(), ios::in);
	string input_line;
	int line_number = 0;

	if(!config_file.good())
	{
		cerr << "ERROR: Could not open configuration file: " << filename << endl;
		return false;
	}

	while(config_file.good() && !config_file.eof())
	{
		size_t equal_sign_index;

		string attribute_name;
		string attribute_value;

		getline(config_file, input_line);
		++line_number;

		// Check for empty lines or comments:
		if(input_line.length() == 0 || input_line.at(0) == '\n' || input_line.at(0) == '\r'
			|| input_line.at(0) == '#')
			continue;

		equal_sign_index = input_line.find_first_of('=');
		if(equal_sign_index == string::npos)
		{
			cerr << "ERROR: Missing assignment on line " << input_line << endl;
			return false;
		}

		size_t name_start = input_line.find_first_not_of(" \t");
		if(name_start == string::npos && input_line[name_start] == '=')
		{
			cerr << "ERROR: Missing attribute name on line " << input_line << endl;
			return false;
		}

		size_t name_end = input_line.find_first_of(" =\t", name_start);
		if(name_end == string::npos)
		{
			cerr << "ERROR: End of attribute name not found on line " << input_line << endl;
			return false;
		}

		attribute_name = input_line.substr(name_start, name_end);

		size_t value_start = input_line.find_first_not_of(" \t", equal_sign_index + 1);
		if(value_start == string::npos)
		{
			cerr << "ERROR: No value found for attribute " << attribute_name << " on line "
				<< input_line << endl;
			return false;
		}

		size_t value_end = input_line.find_first_of("\n\r\t ", value_start);

		attribute_value = input_line.substr(value_start, value_end);

		// Check the name and type of the parsed attribute and value:
		config_type_t type = config_db::get_type(attribute_name);
		if(type == TYPE_INVALID)
		{
			cerr << "ERROR: Unrecognized attribute name: " << attribute_name << " on line "
				<< input_line << endl;
			return false;
		}

		istringstream value_extractor(attribute_value);
		switch(type)
		{
			case TYPE_INTEGER:
				int intval;
				value_extractor >> intval;
				config_db::get().set_value(attribute_name, intval);
				break;
			case TYPE_FLOAT:
				float floatval;
				value_extractor >> floatval;
				config_db::get().set_value(attribute_name, floatval);
				break;
			case TYPE_BOOLEAN:
				transform(attribute_value.begin(), attribute_value.end(),
					attribute_value.begin(), ptr_fun<int, int>(tolower));
				if(attribute_value == "true")
					config_db::get().set_value(attribute_name, true);
				else if(attribute_value == "false")
					config_db::get().set_value(attribute_name, false);
				else {
					cerr << "ERROR: Unrecognized boolean value for attribute " << attribute_name
						<< " on line " << input_line << endl;
					return false;
				}
				break;
			case TYPE_STRING:
				config_db::get().set_value(attribute_name, attribute_value.c_str());
				break;
		}
	}

	config_file.close();
	return true;
}

