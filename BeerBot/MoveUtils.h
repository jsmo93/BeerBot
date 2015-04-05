#ifndef _MOVE_UTILS
#define _MOVE_UTILS

#include "Globals.h"

sensorReadings pullSensorData()
{
	unsigned frontRight = analog10(globals.globalSensorParams.frontRightIRPort);
	unsigned frontLeft = analog10(globals.globalSensorParams.frontLeftIRPort);
	unsigned rearRight = analog10(globals.globalSensorParams.rearRightIRPort);
	unsigned rearLeft = analog10(globals.globalSensorParams.rearLeftIRPort);
	sensorReadings readings;

	readings.frontLeftIR = false;
	readings.frontRightIR = false;
	readings.rearLeftIR = false;
	readings.rearRightIR = false;

	if (frontRight > globals.globalSensorParams.IRThreshold)
	{
		readings.frontRightIR = true;
	}

	if (frontLeft > globals.globalSensorParams.IRThreshold)
	{
		readings.frontLeftIR = true;
	}

	if (rearRight > globals.globalSensorParams.IRThreshold)
	{
		readings.rearRightIR = true;
	}

	if (rearLeft > globals.globalSensorParams.IRThreshold)
	{
		readings.rearLeftIR = true;
	}

	return readings;
}

#endif