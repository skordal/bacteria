/*************************************************/
/* Bacteria - The interesting bacteria simulator */
/*      (c) Kristian K. Skordal 2009 - 2012      */
/*************************************************/

#include "application.h"

int main(int argc, char * argv[])
{
	application * app = application::init(argc, argv);

	if(app == 0)
		return 1;
	else
		return app->run();
}

