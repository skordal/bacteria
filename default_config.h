/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#ifndef CONFIG_DB_CPP
#	error "default_config.h should only be included in config_db.cpp!"
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
	CFG_STRING("DatalogFilename", "graph_data.dat"),
	CFG_INT("FeedingEnergy", 6),
	CFG_INT("FramesPerSecond", 25),
	CFG_INT("FoodEnergy", 800),
	CFG_FLOAT("FoodSmellingDistance", 50.0f),
	CFG_INT("FoodSpawningRate", 50),
	CFG_BOOL("Fullscreen", false),
	CFG_INT("GrowthRateSamplingInterval", 1),
	CFG_INT("LoggerUpdateInterval", 100),
	CFG_INT("ReproductionEnergy", 500),
	CFG_INT("ScreenWidth", 800),
	CFG_INT("ScreenHeight", 600),
	CFG_INT("StartingPopulation", 10),
	CFG_INT("StartingFood", 10),
	CFG_NULL
};

