#ifndef _GLOBALS
#define _GLOBALS

#include <stdbool.h>

typedef struct
{
	//Level 0 - No Output
	//Level 1 - Error
	//Level 2 - Level 1 + Warning
	//Level 3 - Level 2 + Verbose 1
	//Level 4 - Level 3 + Verbose 2
	//Level 5 - Level 4 + Verbose 3
	unsigned logLevel;
} logParams; //Collection of log parameters

typedef struct
{
	unsigned moveSpeed; //General move speed
	unsigned turnSpeed;
	float moveInterval;
	float turnInterval;
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
	unsigned arduinoPort;
	unsigned remoteControlPort;
	unsigned IRThreshold;
} sensorParams; //Collection of sensor parameters

typedef struct
{
	bool enableBeeps;
} errorParams; //Collection of log parameters

typedef struct
{
	unsigned orderNumber; //Also equals color track
} orderParams;

typedef struct
{
	logParams globalLogParams;
	motionParams globalMotionParams;
	debugParams globalDebugParams;
	sensorParams globalSensorParams;
	errorParams globalErrorParams;
	orderParams globalOrderParams;
} globalParams;

globalParams globals;
void setDefaults()
{
	globals.globalLogParams.logLevel = 5;

	globals.globalMotionParams.moveSpeed = 500;
	globals.globalMotionParams.turnSpeed = 200;
	globals.globalMotionParams.moveInterval = 0.5;
	globals.globalMotionParams.turnInterval = 0.25;

	globals.globalDebugParams.enableBreakpoints = false;
	globals.globalDebugParams.enableDebug = false;
	globals.globalDebugParams.startInState = 0;

	globals.globalSensorParams.frontBumperPort = 0;
	globals.globalSensorParams.frontLeftIRPort = 1;
	globals.globalSensorParams.frontRightIRPort = 2;
	globals.globalSensorParams.rearBumperPort = 3;
	globals.globalSensorParams.rearLeftIRPort = 4;
	globals.globalSensorParams.rearRightIRPort = 5;
	globals.globalSensorParams.remoteControlPort = 6;
	globals.globalSensorParams.arduinoPort = 7;
	globals.globalSensorParams.IRThreshold = 300;

	globals.globalErrorParams.enableBeeps = true;

	globals.globalOrderParams.orderNumber = 5;
}

typedef struct
{
	bool frontLeftIR;
	bool frontRightIR;
	bool rearLeftIR;
	bool rearRightIR;
} sensorReadings;

sensorReadings IRReadings;

#endif
