#ifndef _ORDER
#define _ORDER

#include "Globals.h"

bool getOrder()
{
	unsigned orderRead = 0;
	while (orderRead == 0)
	{
		orderRead = analog10(globals.globalSensorParams.arduinoPort);
	}

	if (orderRead > 0 && orderRead <= 256)
	{
		globals.globalOrderParams.orderNumber = 0;
	}
	if (orderRead > 256 && orderRead <= 512)
	{
		globals.globalOrderParams.orderNumber = 1;
	}
	if (orderRead > 512 && orderRead <= 768)
	{
		globals.globalOrderParams.orderNumber = 2;
	}
	if (orderRead > 768 && orderRead <= 1023)
	{
		globals.globalOrderParams.orderNumber = 3;
	}

	return true;
}

#endif
