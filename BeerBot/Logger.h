#ifndef _LOGGER
#define _LOGGER

#include "Globals.h"

void log(char* msg, unsigned level)
{
	if (globals.globalLogParams.logLevel == 0)
	{
		return;
	}

	if (level <= globals.globalLogParams.logLevel)
	{
		if (level == 1)
		{
			printf("\nERROR - ");
			printf(msg);
		}

		if (level == 2)
		{
			printf("\nWARN - ");
			printf(msg);
		}

		if (level == 3)
		{
			printf("\nV1 - ");
			printf(msg);
		}

		if (level == 4)
		{
			printf("\nV2 - ");
			printf(msg);
		}

		if (level == 5)
		{
			printf("\nV3 - ");
			printf(msg);
		}
	}
}

#endif
