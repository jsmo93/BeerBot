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

	//State 1 - Order
	//State 2 - Retrieve
	//State 3 - Open Fridge
	//State 4 - Search and Load
	//State 5 - Deliver
	while (1)
	{
		getOrder();

		if (!moveRetrieval())
		{
			log("Error, could not move to fridge", 1);
			beepCode(2, 1);
			beepCode(1, 0);
			return 1;
		}

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
		}
	}

	return 0;
}
