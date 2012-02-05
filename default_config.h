/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/*************************************************/

#ifdef DEFAULT_CONFIG_H
#	error "default_config.h should only be included once by config_db.h!"
#else
#	define DEFAULT_CONFIG_H
#endif

#include "config_db.h"
#include "macros.h"

typedef struct {
	const char * name;
	config_type_t type;
	struct {
		int int_val;
		bool bool_val;
		float float_val;
		char * string_val;
	};
} default_config_value_t;

static default_config_value_t default_config[] =  {
	CFG_INT("StartingPopulation", STARTING_POP),
	CFG_INT("StartingFood", STARTING_FOOD),
	CFG_INT("FramesPerSecond", DEFAULT_FPS),
	CFG_INT("GrowthRateSamplingInterval", AVG_GROWTH_RATE_INT),
	CFG_INT("BacteriaStartingEnergy", 0),
	CFG_FLOAT("FoodSmellingDistance", FOOD_SMELLING_DISTANCE),
	CFG_INT("FoodEnergy", FOOD_ENERGY),
	CFG_INT("ReproductionEnergy", REPRODUCTION_ENERGY),
	CFG_INT("FeedingEnergy", FEEDING_ENERGY),
	CFG_INT("FoodSpawningRate", SPAWNING_RATE),
	CFG_STRING("DatalogFilename", DATALOG_FILENAME),
	CFG_INT("LoggerUpdateInterval", LOGGER_UPDATE_INTERVAL),
	CFG_INT("ScreenWidth", SCREEN_WIDTH),
	CFG_INT("ScreenHeight", SCREEN_HEIGHT),
	CFG_BOOL("Fullscreen", false),
	CFG_NULL
};

