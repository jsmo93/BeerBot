#ifndef _GLOBALS
#define _GLOBALS

#include <stdbool.h>

typedef struct
{
	unsigned logLevel;
	bool logToScreen; //Display log messages on LCD
} logParams; //Collection of log parameters

typedef struct
{
	unsigned moveSpeed; //General move speed
	unsigned turnSpeed;
} motionParams; //Collection of motion parameters

typedef struct
{
	bool enableDebug;
	bool enableBreakpoints;
	unsigned startInState; //Set to begin the sequence in a specific state (1-6)
} debugParams; //Collection of debug parameters

typedef struct
{
	unsigned frontBumperPort;
	unsigned rearBumperPort;
	unsigned frontLeftIRPort;
	unsigned frontRightIRPort;
	unsigned rearLeftIRPort;
	unsigned rearRightIRPort;
	unsigned visionPort;
	unsigned remoteControlPort;
} sensorParams; //Collection of sensor parameters

typedef struct
{
	logParams globalLogParams;
	motionParams globalMotionParams;
	debugParams globalDebugParams;
	sensorParams globalSensorParams;
} globalParams;

globalParams setDefaults();

#endif
