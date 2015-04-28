#ifndef _ORDER
#define _ORDER

#include "Globals.h"

bool getOrder()
{
	unsigned orderRead = 0;
	while (orderRead == 0)
	{
		orderRead = digital(globals.globalSensorParams.arduinoPort);
	}
	sleep(1);
	orderRead = digital(globals.globalSensorParams.arduinoPort);

	if (orderRead == 0)
	{
		globals.globalOrderParams.orderNumber = 0;
	}
	else
	{
		globals.globalOrderParams.orderNumber = 1;
	}

	return true;
}

#endif
