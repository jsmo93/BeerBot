#ifndef _LOGGER
#define _LOGGER

#include "Globals.h"

class Logger
{
private:
	int logLevel = 0;
public:
	Logger(int level);
	int getLevel();
	void log(char msg); // TODO update this to char[]
};

#endif