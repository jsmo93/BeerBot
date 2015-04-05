#ifndef _BEEP_CODE
#define _BEEP_CODE

#include "Globals.h"

beepCode(unsigned beepCount, float delay)
{
	unsigned i = 0;
	for (i = 0; i < beepCount; i++)
	{
		beep();
		sleep(delay);
	}
}

#endif
