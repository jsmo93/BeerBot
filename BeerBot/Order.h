#ifndef _ORDER
#define _ORDER

#include "Globals.h"

bool getOrder()
{
	log("Entering order state", 3);
	unsigned orderRead = 0;
	while (orderRead == 0)
	{
		log("Entering recieve order phase", 4);
		orderRead = digital(globals.globalSensorParams.arduinoPort);
	}
	sleep(1);
	orderRead = digital(globals.globalSensorParams.arduinoPort);

	log("Exiting receive order phase", 4);
	log("Entering determine order phase", 4);
	if (orderRead == 0)
	{
		log("Received order 0", 5);
		globals.globalOrderParams.orderNumber = 0;
	}
	else
	{
		log("Received order 1", 5);
		globals.globalOrderParams.orderNumber = 1;
	}

	log("Exiting determine phase", 4);
	log("Exiting order state", 3);
	return true;
}

#endif
