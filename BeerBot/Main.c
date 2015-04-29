#include <stdio.h>
#include <stdlib.h>
#include "Globals.h"
#include "Logger.h"
#include "BeepCode.h"
#include "Retrieve.h"
#include "Open-Fridge.h"
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
		if (globals.globalDebugParams.enableDebug == false || globals.globalDebugParams.startInState == 1)
		{
			getOrder();
			moveRetrieve();
			moveOpenFridge();
			getBeer();
			//close
			moveDeliver();
		}
		else if (globals.globalDebugParams.enableDebug == true && globals.globalDebugParams.startInState == 2)
		{
			globals.globalOrderParams.orderNumber = 0;
			moveRetrieve();
			moveOpenFridge();
			getBeer();
			//close
			moveDeliver();
		}
		else if (globals.globalDebugParams.enableDebug == true && globals.globalDebugParams.startInState == 3)
		{
			globals.globalOrderParams.orderNumber = 0;
			moveOpenFridge();
			getBeer();
			//close
			moveDeliver();
		}
		else if (globals.globalDebugParams.enableDebug == true && globals.globalDebugParams.startInState == 4)
		{
			globals.globalOrderParams.orderNumber = 0;
			getBeer();
			//close
			moveDeliver();
		}
		else if (globals.globalDebugParams.enableDebug == true && globals.globalDebugParams.startInState == 5)
		{
			//close
			moveDeliver();
		}
		else if (globals.globalDebugParams.enableDebug == true && globals.globalDebugParams.startInState == 6)
		{
			moveDeliver();
		}
		else
		{
			log("Could not determine start state", 1);
			log("Check debug settings for mismatches", 1);
			beepCode(1, 1);
		}
	}

	return 0;
}