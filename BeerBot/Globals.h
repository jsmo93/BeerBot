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
	unsigned scanSpeed;
	unsigned ramSpeed;
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
	unsigned clawBumperPort;
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

	globals.globalMotionParams.moveSpeed = 300;
	globals.globalMotionParams.turnSpeed = 200;
	globals.globalMotionParams.scanSpeed = 50;
	globals.globalMotionParams.ramSpeed = 800;
	globals.globalMotionParams.moveInterval = 0.5;
	globals.globalMotionParams.turnInterval = 0.25;

	globals.globalDebugParams.enableBreakpoints = false;
	globals.globalDebugParams.enableDebug = true;
	globals.globalDebugParams.startInState = 3;

	globals.globalSensorParams.clawBumperPort = 15;
	globals.globalSensorParams.frontLeftIRPort = 3;
	globals.globalSensorParams.frontRightIRPort = 2;
	globals.globalSensorParams.rearLeftIRPort = 1;
	globals.globalSensorParams.rearRightIRPort = 0;
	globals.globalSensorParams.remoteControlPort = 6;
	globals.globalSensorParams.arduinoPort = 8;
	globals.globalSensorParams.IRThreshold = 750;

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
