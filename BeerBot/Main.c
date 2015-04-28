#include <stdio.h>
#include <stdlib.h>
#include "Globals.h"
#include "Logger.h"
#include "BeepCode.h"
#include "Retrieve.h"
#include "Deliver.h"
#include "Order.h"
#include "Search-Load.h"

int main()
{
	setDefaults();
	bool atLocation = false;
	//State 1 - Order
	//State 2 - Retrieve
	//State 3 - Open Fridge
	//State 4 - Search and Load
	//State 5 - Close Fridge
	//State 6 - Deliver
	while (1)
	{
		getOrder();
		printf("\nOrder - Beer %d", globals.globalOrderParams.orderNumber);
		sleep(10);

		while (!atLocation)
		{
			atLocation = launchRetrieval();
		}
		atLocation = false;
		while (!atLocation)
		{
			atLocation = moveRetrieval();
		}
		atLocation = false;

		beep();

		//getOrder();
		while (!atLocation)
		{
			atLocation = launchDeliver();
		}
		atLocation = false;
		while (!atLocation)
		{
			atLocation = moveDeliver();
		}
		atLocation = false;
		/*
		if (!positionClaw())
		{
			log("Error, could locate or load beer", 1);
			beepCode(3, 1);
			beepCode(1, 0);
			return 1;
		}

		if (!moveDeliver())
		{
			log("Error, could deliver beer", 1);
			beepCode(5, 1);
			beepCode(1, 0);
			return 1;
		}*/
	}

	return 0;
}
