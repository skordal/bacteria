/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "application.h"

using namespace std;

// Global image variables:
image * bacteria_image, * food_image;
image * red_bar_segment, * yellow_bar_segment, * green_bar_segment;

// Lists of organisms:
list<bacteria> bacteria_list;
list<food> food_list;

// Global application object:
application * application::global_app = 0;

// Timer callback functions:
Uint32 timer_callback(Uint32 interval, void * unused __attribute((unused)));
Uint32 logger_timer_cb(Uint32 interval, void * logger_object);

// Search path for finding image files:
const char * image_search_path[] = {
	"/usr/share/bacteria/",
	"/usr/local/share/bacteria/",
	"/opt/local/share/bacteria/",
	"./",
	0
};

const char * opt_string = "b:c:f:i:x:y:hv";
static struct option cmd_options[] = {
{"bacteria", required_argument, 0, 'b'},
{"config", required_argument, 0, 'c'},
{"food", required_argument, 0, 'f'},
{"interval", required_argument, 0, 'i'},
{"help", no_argument, 0, 'h'},
{"version", no_argument, 0, 'v'},
{0, 0, 0, 0}
};

application::application()
	: config_filename(""), info_mode(info_field::NONE), running(true), display_stats(true)
{
}

// This function initializes the application by running
// all the other initialization functions:
application * application::init(int argc, char * argv[])
{
	bool retval = true;
	global_app = new application();

	srand(time(0));

	if(!global_app->init_config())
	{
		retval = false;
		goto _skip_init;
	}

	if(!global_app->init_cmd_args(argc, argv))
	{
		retval = false;
		goto _skip_init;
	}

	global_app->main_window = window::create(config_db::get().get_int_value("ScreenWidth"),
		config_db::get().get_int_value("ScreenHeight"));
	if(global_app->main_window == 0)
	{
		retval = false;
		goto _skip_init;
	}

	if(!global_app->init_graphics())
	{
		retval = false;
		goto _skip_init;
	}
	
	if(!global_app->init_logging())
	{
		retval = false;
		goto _skip_init;
	}

	if(!global_app->init_populations())
	{
		retval = false;
		goto _skip_init;
	}
	
	if(!global_app->init_timers())
	{
		retval = false;
		goto _skip_init;
	}

	clog << "Initialization completed." << endl;
	clog << "*** Now running ***" << endl << endl;

_skip_init:
	if(retval)
	{
		atexit(application::cleanup);
		return global_app;
	} else {
		delete global_app;
		return 0;
	}
}

void application::cleanup()
{
	clog << "Cleaning up..." << endl;

	if(global_app != 0)
		delete global_app;
}

// This function parses the command line arguments:
bool application::init_cmd_args(int argc, char * argv[])
{
	int option;

	while((option = getopt_long(argc, argv, opt_string, cmd_options, 0)) != -1)
	{
		switch(option)
		{
			case 'b':
				config_db::get().set_value("StartingPopulation", atoi(optarg));
				break;
			case 'c':
				config_filename = string(optarg);
				break;
			case 'f':
				config_db::get().set_value("StartingFood", atoi(optarg));
				break;
			case 'i':
				config_db::get().set_value("LoggerUpdateInterval", atoi(optarg));
				break;
			case 'h':
				display_help();
				return false;
			case 'v':
				display_version();
				return false;
		}
	}

	return true;
}

// This function reads the configuration file:
bool application::init_config()
{
	config_parser * config_file = 0;

	// If the config filename is not empty, parse the config file.
	if(!config_filename.empty())
	{
		clog << "Using configuration file " << config_filename << "... ";
		config_file = new config_parser(config_filename);
		if(!config_file->parse())
		{
			clog << "failed!" << endl;
			return false;
		} else
			clog << "ok" << endl;
	}

	if(config_file != 0)
		delete config_file;

	return true;
}

// This function sets up data logging:
bool application::init_logging()
{
	clog << "Initializing statistics... ";
	stats = new statistics(config_db::get().get_int_value("StartingPopulation"),
		config_db::get().get_int_value("StartingFood"));
	clog << "ok" << endl;

	clog << "Creating data logger...";
	data_logger = new logger(*stats, config_db::get().get_string_value("DatalogFilename"),
		config_db::get().get_int_value("LoggerUpdateInterval"));
	clog << "ok" << endl;

	return true;
}

// This function loads image files:
bool application::init_graphics()
{
	clog << "Loading graphics... ";
	try {
		bacteria_image = new image(BACTERIA_FILENAME, BACTERIA_ALPHA);
		food_image = new image(FOOD_FILENAME, FOOD_ALPHA);

		red_bar_segment = new image(RED_BAR_SEGMENT);
		yellow_bar_segment = new image(YELLOW_BAR_SEGMENT);
		green_bar_segment = new image(GREEN_BAR_SEGMENT);
	} catch(const exception & error)
	{
		clog << "failed!" << endl;
		cerr << "Error: " << error.what() << endl;
		return false;
	}
	clog << "ok" << endl;

	return true;
}

// This function sets up the initial populations of food and bacteria:
bool application::init_populations()
{
	// Create bacteria:
	clog << "Creating initial bacteria population..." << endl;
	for(int c = 0; c < config_db::get().get_int_value("StartingPopulation"); c++)
	{
		bacteria bact;
		bact.set_ancestor(c + 1);
		bacteria_list.push_back(bact);
	}

	ancestor_counter = config_db::get().get_int_value("StartingPopulation") + 1;

	// Create food:
	clog << "Creating initial food nuggets..." << endl;
	for(int c = 0; c < config_db::get().get_int_value("StartingFood"); c++)
	{
		food_list.push_back(food(rand() % (config_db::get().get_int_value("ScreenWidth") - food_image->get_width()),
			rand() % (config_db::get().get_int_value("ScreenHeight") - food_image->get_height())));
	}

	return true;
}

// This function starts the timers for screen updating and data logging:
bool application::init_timers()
{
	clog << "Starting timers..." << endl;
	refresh_timer = SDL_AddTimer(1000 / config_db::get().get_int_value("FramesPerSecond"), timer_callback, 0);
	logger_timer = SDL_AddTimer(config_db::get().get_int_value("LoggerUpdateInterval"),
		logger_timer_cb, (void *) data_logger);
	
	return true;
}

// This function runs the application:
int application::run()
{
	SDL_Event event_queue;

	// Parse events:
	while(SDL_WaitEvent(&event_queue) && running)
	{
		switch(event_queue.type)
		{
			case SDL_USEREVENT: // SDL_USEREVENT = Update timer has fired
				handle_update();
				break;
			case SDL_KEYDOWN:
				handle_key(event_queue.key.keysym.sym);
				break;
			case SDL_QUIT:
				running = false;
			default:
				break;
		}
	}

	return 0;
}

// Find a file in the application's data directory:
const char * application::find_file(const char * filename)
{
	for(int c = 0; image_search_path[c] != 0; c++)
	{
		string temp = image_search_path[c];
		temp += filename;
		ifstream test_stream(temp.c_str());

		if(test_stream.good())
		{
			test_stream.close();
			return temp.c_str();
		} else
			test_stream.close();
	}

	cerr << "ERROR: File not found: " << filename << endl;
	return 0;
}

// Handles an update event:
void application::handle_update()
{
	static int counter = 0;
	std::list<bacteria> spawn_list;
	
	counter++;

	// Clear the screen:
	main_window->clear();

	// Check if it's time for a new food nugget to spawn:
	if(counter >= config_db::get().get_int_value("FoodSpawningRate") && !stats->get_game_over())
	{
		counter = 0;
		food_list.push_back(food(rand() % (config_db::get().get_int_value("ScreenWidth") - food_image->get_width()),
			rand() % (config_db::get().get_int_value("ScreenHeight") - food_image->get_height())));
		stats->add_food();
	}

	// Draw food:
	if(!food_list.empty())
	{
		for(food_iterator = food_list.begin(); food_iterator != food_list.end();)
		{
			food & temp = *food_iterator;
			if(!bacteria_list.empty())
			{
				if(!temp.update())
				{
					temp.release_bacteria();
					food_iterator = food_list.erase(food_iterator);
					stats->remove_food();
					continue;
				}
			}

			// Check for attached bacteria and let them feed:
			temp.check_for_bacteria(bacteria_list);

			temp.draw();
			food_iterator++;
		}
	}

	// Draw bacteria:
	if(!bacteria_list.empty())
	{
		for(bacteria_iterator = bacteria_list.begin(); bacteria_iterator != bacteria_list.end();)
		{
			bacteria & temp = *bacteria_iterator;

			// Reproduce if possible:
			if(temp.can_reproduce())
			{
				temp.reproduce();
				spawn_list.push_back(bacteria(temp.get_vector().get_angle() + M_PI,
					temp.get_vector().get_magnitude(), temp.get_vector().get_x(),
					temp.get_vector().get_y(), config_db::get().get_int_value("ReproductionEnergy") / 2,
					temp.get_generation() + 1, temp.get_ancestor()));
				stats->add_bacteria(spawn_list.back().get_generation());
			}

			// Update the position of the bacteria:
			temp.update();

			// Remove dead bacteria:
			if(!temp.is_alive())
			{
				stats->remove_bacteria();
				bacteria_iterator = bacteria_list.erase(bacteria_iterator);
				continue;
			}

			// Draw bacteria:
			temp.draw();
			// Draw an info field for the bacteria:
			info_field(temp).draw();

			bacteria_iterator++;
		}
	} else // if the bacteria list is empty, the simulation ends:
		stats->set_game_over();

	// Insert new bacteria to the main bacteria list:
	bacteria_list.insert(bacteria_list.end(), spawn_list.begin(), spawn_list.end());
	spawn_list.clear();

	// Update and draw statistics:
	stats->update();
	if(display_stats)
		stats->draw();

	main_window->flip_buffers();
}

// Handles a keyboard press:
void application::handle_key(SDLKey key)
{
	bacteria new_bacteria;

	switch(key)
	{
		case SDLK_a: // A - Shows a bacteria's ancestor:
			if(info_mode != info_field::ANCESTOR)
				info_mode = info_field::ANCESTOR;
			else
				info_mode = info_field::NONE;
			break;
		case SDLK_b: // B - Add new bacteria
			new_bacteria.set_ancestor(++ancestor_counter);
			bacteria_list.push_back(new_bacteria);
			stats->add_bacteria();
			break;
		case SDLK_c: // C - Toggle display of coordinates of bacteria
			if(info_mode != info_field::POSITION)
				info_mode = info_field::POSITION;
			else
				info_mode = info_field::NONE;
			break;
		case SDLK_e: // E - Toggle energy bar for bacteria
			if(info_mode != info_field::ENERGY_BAR)
				info_mode = info_field::ENERGY_BAR;
			else
				info_mode = info_field::NONE;
			break;
		case SDLK_f: // F - Add food nugget
			food_list.push_back(food(rand() % (config_db::get().get_int_value("ScreenWidth") - food_image->get_width()),
				rand() % (config_db::get().get_int_value("ScreenHeight") - food_image->get_height())));
			stats->add_food();
			break;
		case SDLK_g: // G - Toggle generation display
			if(info_mode != info_field::GENERATION)
				info_mode = info_field::GENERATION;
			else
				info_mode = info_field::NONE;
			break;
		case SDLK_s: // S - Toggle statistics
			if(display_stats)
				display_stats = false;
			else
				display_stats = true;
			break;
		case SDLK_ESCAPE: // ESCAPE, Q - Exit application
		case SDLK_q:
			running = false;
		default:
			break;
	}
}

// Display the command line usage information for the application:
void application::display_help()
{
	clog << "Bacteria command line options:" << endl;
	clog << "\t--bacteria\t-b\tSpecify starting population" << endl;
	clog << "\t--config\t-c\tSpecify which configuration file to use" << endl;
	clog << "\t--food\t-f\tSpecify starting food amount" << endl;
	clog << "\t--help\t-h\tDisplay this message" << endl;
	clog << "\t--interval\t-i\tSpecify data logging interval (in milliseconds)" << endl;
	clog << "\t--version\t-v\tDisplays a version statement" << endl;
}

// Display application version information:
void application::display_version()
{
	clog << "Bacteria Simulator " << VERSION_MAJOR << '.' << VERSION_MINOR << endl;
	clog << "(c) Kristian Klomsten Skordal 2009 - 2012 <kristian.skordal@gmail.com>" << endl;
	clog << "Report bugs on <http://github.com/skordal/bacteria>" << endl;
}

// Clean up memory for the application:
application::~application()
{
	// Remove timers:
	SDL_RemoveTimer(refresh_timer);
	SDL_RemoveTimer(logger_timer);

	// Remove bacteria:
	if(!bacteria_list.empty())
		bacteria_list.clear();

	// Remove food nuggets:
	if(!food_list.empty())
		food_list.clear();

	// Delete all the images:
	delete bacteria_image;
	delete food_image;
	delete red_bar_segment;
	delete yellow_bar_segment;
	delete green_bar_segment;

	// Delete the statistic classes:
	delete data_logger;
	delete stats;
}

// Callback for the screen refresh timer (post an SDL_USEREVENT):
Uint32 timer_callback(Uint32 interval, void * unused __attribute((unused)))
{
	SDL_Event update_event;
	SDL_UserEvent update_struct = UPDATE_EVENT;

	update_event.type = SDL_USEREVENT;
	update_event.user = update_struct;

	SDL_PushEvent(&update_event);

	return interval;
}

// Callback for the data logger timer:
Uint32 logger_timer_cb(Uint32 interval, void * logger_object)
{
	logger * data_logger = (logger *) logger_object;
	data_logger->update();

	return interval;
}

