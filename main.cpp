/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2011      */
/*************************************************/

#include "application.h"

int main(int argc, char * argv[])
{
	int retval = EXIT_SUCCESS;
	application * app = new application();

	if(!app->init(argc, argv))
		return EXIT_FAILURE;
	retval = app->run();

	delete app;
	return retval;
}

