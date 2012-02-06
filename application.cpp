/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/*************************************************/

#include "application.h"

using std::list;

// Global screen:
SDL_Surface * screen;

#ifndef DISABLE_SDLTTF
// Global font:
TTF_Font * font;
#endif

// Global image variables:
image * bacteria_image, * food_image;
image * red_bar_segment, * yellow_bar_segment, * green_bar_segment;
config_db * config;

// Lists of organisms:
list<bacteria> bacteria_list;
list<food> food_list;

// Search path for finding image files:
const char * image_search_path[] = {
	"/usr/share/bacteria/",
	"/usr/local/share/bacteria/",
	"/opt/local/share/bacteria/",
	"./",
	NULL
};

const char * opt_string = "b:c:f:i:x:y:hv";
static struct option cmd_options[] = {
{"bacteria", required_argument, NULL, 'b'},
{"config", required_argument, NULL, 'c'},
{"food", required_argument, NULL, 'f'},
{"interval", required_argument, NULL, 'i'},
{"help", no_argument, NULL, 'h'},
{"version", no_argument, NULL, 'v'},
{0, 0, 0, 0}
};

application::application()
{
	config_filename = NULL;
	window_icon = NULL;
	printf("Bacteria %d.%d - (c) Kristian K. Skordal 2009\n\n", VERSION_MAJOR, VERSION_MINOR);

	display_coords = false;
	display_energy = false;
	display_stats = true;
	graphical_energy_bar = true;
	
	starting_pop = STARTING_POP;
	starting_food = STARTING_FOOD;
	logging_interval = LOGGER_UPDATE_INTERVAL;
	screen_x = SCREEN_WIDTH;
	screen_y = SCREEN_HEIGHT;
}

// This function initializes the application by running
// all the other initialization functions:
bool application::init(int argc, char * argv[])
{
	config_parser * config_file = NULL;

	if(!init_cmd_args(argc, argv))
		return false;

	if(!init_config())
		return false;

	if(!init_random())
		return false;

	if(!init_sdl())
		return false;
	
	if(!init_graphics())
		return false;
	
	if(!init_logging())
		return false;

	if(!init_populations())
		return false;
	
	if(!init_timers())
		return false;

	printf("Initialization completed.\n");
	printf("\n*** Now running ***\n\n");

	return true;
}

// This function parses the command line arguments:
bool application::init_cmd_args(int argc, char * argv[])
{
	printf("Parsing command line arguments...\n");

	while((option = getopt_long(argc, argv, opt_string, cmd_options, NULL)) != -1)
	{
		switch(option)
		{
			case 'b':
				starting_pop = atoi(optarg);
				break;
			case 'c':
				config_filename = new char[strlen(optarg) + 1];
				strcpy(const_cast<char *>(config_filename), optarg);
				break;
			case 'f':
				starting_food = atoi(optarg);
				break;
			case 'i':
				logging_interval = atoi(optarg);
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
	config_parser * config_file = NULL;

	printf("Reading configuration...\n");
	config = new config_db();

	// Check if command line arguments override the default settings.
	if(starting_pop != config->get_int_value("StartingPopulation"))
		config->set_value("StartingPopulation", starting_pop);
	
	if(starting_food != config->get_int_value("StartingFood"))
		config->set_value("StartingFood", starting_food);
	
	if(logging_interval != config->get_int_value("LoggerUpdateInterval"))
		config->set_value("LoggerUpdateInterval", logging_interval);

	if(config_filename != NULL)
	{
		if(config_parser::config_file_exists(config_filename))
		{
			printf("Using configuration file %s...\n", config_filename);
			config_file = new config_parser(config, config_filename);
			if(!config_file->parse())
			{	
				printf("Error while reading configuration file!\n");
				delete[] config_filename;
				return false;
			}
		 } else
			printf("Cannot access \"%s\", continuing without...\n", config_filename);
		delete[] config_filename;
	}
	if(config_file != NULL)
		delete config_file;

	return true;
}

// This function initializes the random number generator:
bool application::init_random()
{
	printf("Initializing random number generator...\n");
	srandom(time(NULL));

	return true;
}

// This function initializes SDL:
bool application::init_sdl()
{
	printf("Initializing SDL...\n");
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) == -1)
		return false;

#ifndef DISABLE_SDLTTF
	printf("Initializing SDL_ttf...\n");
	if(TTF_Init() == -1)
		return false;

	font = TTF_OpenFont(STATUS_FONT, STATUS_FONT_SIZE);
	if(font == NULL)
	{
		printf("ERROR: Could not load font \"%s\"\n", STATUS_FONT);
		return false;
	}
#endif

	printf("Creating main window (%d x %d)...\n", config->get_int_value("ScreenWidth"), config->get_int_value("ScreenHeight"));
	screen = SDL_SetVideoMode(config->get_int_value("ScreenWidth"), config->get_int_value("ScreenHeight"), 0, config->get_bool_value("Fullscreen") ? SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN : SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(screen == NULL)
	{
		printf("Could not create main window!\n");
		return false;
	}

	printf("Setting up window decorations...\n");
	SDL_WM_SetCaption("Bacteria Simulator", "Bacteria");

	window_icon = SDL_LoadBMP(ICON_FILENAME);
	if(window_icon != NULL)
	{
		SDL_SetColorKey(window_icon, SDL_SRCCOLORKEY, SDL_MapRGB(window_icon->format, 255, 0, 255));
		SDL_WM_SetIcon(window_icon, NULL);
	} else
		printf("WARNING: Could not load icon file: \"%s\"\n", ICON_FILENAME);
	
	return true;
}

// This function sets up data logging:
bool application::init_logging()
{
	printf("Creating status text object...\n");
	stats = new statistics(config->get_int_value("StartingPopulation"), config->get_int_value("StartingFood"));

	printf("Creating data logger object...\n");
	data_logger = new logger(stats, config->get_string_value("DatalogFilename"), config->get_int_value("LoggerUpdateInterval"));

	return true;
}

// This function loads image files:
bool application::init_graphics()
{
	printf("Loading graphics...\n");
	try {
		bacteria_image = new image(BACTERIA_FILENAME, BACTERIA_ALPHA);
		food_image = new image(FOOD_FILENAME, FOOD_ALPHA);

		red_bar_segment = new image(RED_BAR_SEGMENT);
		yellow_bar_segment = new image(YELLOW_BAR_SEGMENT);
		green_bar_segment = new image(GREEN_BAR_SEGMENT);
	} catch(...)
	{
		return false;
	}

	return true;
}

// This function sets up the initial populations of food and bacteria:
bool application::init_populations()
{
	// Create bacteria:
	printf("Creating initial population...\n");
	for(int c = 0; c < config->get_int_value("StartingPopulation"); c++)
	{
		bacteria_list.push_back(bacteria());
	}

	// Create food:
	printf("Creating initial food nugget amount...\n");
	for(int c = 0; c < config->get_int_value("StartingFood"); c++)
	{
		food_list.push_back(food(random() % (config->get_int_value("ScreenWidth") - FOOD_WIDTH), random() % (config->get_int_value("ScreenHeight") - FOOD_HEIGHT)));
	}

	return true;
}

// This function starts the timers for screen updating and data logging:
bool application::init_timers()
{
	printf("Starting timers...\n");
	refresh_timer = SDL_AddTimer(1000 / config->get_int_value("FramesPerSecond"), timer_callback, NULL);
	logger_timer = SDL_AddTimer(config->get_int_value("LoggerUpdateInterval"), logger_timer_cb, (void *) data_logger);
	
	return true;
}

// This function runs the application:
int application::run()
{
	SDL_Event event_queue;
	bool running = true;

	// Parse events:
	while(SDL_WaitEvent(&event_queue) && running)
	{
		switch(event_queue.type)
		{
			case SDL_USEREVENT: // SDL_USEREVENT = Update timer has fired
				counter++;

				// Clear the screen:
				SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B));

				// Check if it's time for a new food nugget to spawn:
				if(counter >= config->get_int_value("FoodSpawningRate") && !stats->get_game_over())
				{
					counter = 0;
					food_list.push_back(food(random() % (config->get_int_value("ScreenWidth") - FOOD_WIDTH), random() % (config->get_int_value("ScreenHeight") - FOOD_HEIGHT)));
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

						if(temp.can_reproduce()) // Reproduce if possible:
						{
							temp.reproduce();
							spawn_list.push_back(bacteria(temp.get_vector().get_angle() + M_PI,
								temp.get_vector().get_magnitude(), temp.get_vector().get_x(),
								temp.get_vector().get_y(), REPRODUCTION_ENERGY / 2,
								temp.get_generation() + 1));
							stats->add_bacteria(spawn_list.back().get_generation());
						}

						// Remove dead bacteria:
						if(!temp.update())
						{
							stats->remove_bacteria();
							bacteria_iterator = bacteria_list.erase(bacteria_iterator);
							continue;
						}

						// Draw bacteria and any annotations attached to it:
						temp.draw();
						if(display_coords)
							temp.draw_coords();
						if(display_energy)
							temp.draw_energy(graphical_energy_bar);
						bacteria_iterator++;
					}
				} else
					stats->set_game_over();

				// Insert new bacteria to the main bacteria list:
				bacteria_list.insert(bacteria_list.end(), spawn_list.begin(), spawn_list.end());
				spawn_list.clear();

				// Update and draw statistics:
				stats->update();
				if(display_stats)
					stats->draw();

				SDL_Flip(screen);
				break;
			case SDL_KEYDOWN:
				switch(event_queue.key.keysym.sym)
				{
					case SDLK_b: // B - Add new bacteria
						bacteria_list.push_back(bacteria());
						stats->add_bacteria();
						break;
					case SDLK_f: // F - Add food nugget
						food_list.push_back(food(random() % (config->get_int_value("ScreenWidth") - FOOD_WIDTH), random() % (config->get_int_value("ScreenHeight") - FOOD_HEIGHT)));
						stats->add_food();
						break;
					case SDLK_e: // E - Toggle energy bar for bacteria
						if(display_energy)
							display_energy = false;
						else
							display_energy = true;
						break;
#ifndef DISABLE_TTF
					case SDLK_c: // C - Toggle display of coordinates of bacteria
						if(display_coords)
							display_coords = false;
						else
							display_coords = true;
						break;
					case SDLK_s: // S - Toggle statistics
						if(display_stats)
							display_stats = false;
						else
							display_stats = true;
						break;
					case SDLK_t: // T - Toggle graphical or text energy display
						if(graphical_energy_bar)
							graphical_energy_bar = false;
						else
							graphical_energy_bar = true;
						break;
#endif
					case SDLK_ESCAPE: // ESCAPE, Q - Exit application
					case SDLK_q:
						running = false;
					default:
						break;
				}
				break;
			case SDL_QUIT:
				running = false;
			default:
				break;
		}
	}

	return EXIT_SUCCESS;
}

// Find a file in the application's data directory:
char * application::find_file(const char * filename)
{
	char * current_search_path;
	for(int c = 0; image_search_path[c] != NULL; c++)
	{
		char * temp = new char[MAX_PATHLEN];
		current_search_path = const_cast<char *>(image_search_path[c]);
		strncpy(temp, image_search_path[c], MAX_PATHLEN);
		strncat(temp, filename, MAX_PATHLEN - (strlen(temp) + 1));
		if(access(temp, F_OK) == 0)
		{
			return temp;
		} else
			delete[] temp;
	}

	printf("File not found: %s\n", filename);
	return NULL;
}

// Display the command line usage information for the application:
void application::display_help()
{
	printf("Bacteria command line options:\n");
	printf("\t--bacteria\t-b\tSpecify starting population\n");
	printf("\t--config\t-c\tSpecify which configuration file to use\n");
	printf("\t--food\t-f\tSpecify starting food amount\n");
	printf("\t--interval\t-i\tSpecify datalogger interval (in milliseconds)\n");
	printf("\t--help\t-h\tDisplay this message\n");
	printf("\t--version\t-v\tDisplay a version statement\n");
}

// Display application version information:
void application::display_version()
{
	printf("Bacteria Simulator, version %d.%d\n", VERSION_MAJOR, VERSION_MINOR);
	printf("(c) Kristian K. Skordal 2009 - 2011\n");
}

// Clean up memory for the application:
application::~application()
{
	printf("Cleaning up memory mess...\n");

	// Remove timers:
	SDL_RemoveTimer(refresh_timer);
	SDL_RemoveTimer(logger_timer);

	// Remove bacteria:
	if(!bacteria_list.empty())
			bacteria_list.clear();

	// Remove food nuggets:
	if(!food_list.empty())
		food_list.clear();

	delete bacteria_image;
	delete food_image;

	delete red_bar_segment;
	delete yellow_bar_segment;
	delete green_bar_segment;

	delete data_logger;
	delete stats;

#ifndef DISABLE_SDLTTF
	TTF_CloseFont(font);
	TTF_Quit();
#endif

	SDL_Quit();
}

// Callback for the screen refresh timer (post an SDL_USEREVENT):
Uint32 timer_callback(Uint32 interval, void * unused)
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
