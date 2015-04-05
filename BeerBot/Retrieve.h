#ifndef _RETRIEVAL
#define _RETRIEVAL

#include "Globals.h"
#include "MoveUtils.h"

void moveStraightRetrieve()
{
	mav(0, globals.globalMotionParams.moveSpeed);
	mav(3, globals.globalMotionParams.moveSpeed);
	sleep(globals.globalMotionParams.moveInterval);
	ao();
}

void turnLeftRetrieve()
{
	mav(0, globals.globalMotionParams.turnSpeed);
	mav(3, globals.globalMotionParams.moveSpeed);
	sleep(globals.globalMotionParams.turnInterval);
	ao();
}

void turnRightRetrieve()
{
	mav(0, globals.globalMotionParams.moveSpeed);
	mav(3, globals.globalMotionParams.turnSpeed);
	sleep(globals.globalMotionParams.turnInterval);
	ao();
}

void approachFridge()
{
	mav(0, globals.globalMotionParams.turnSpeed);
	mav(3, globals.globalMotionParams.turnSpeed);
	sleep(globals.globalMotionParams.turnInterval);
	ao();
}

bool moveRetrieval()
{
	IRReadings = pullSensorData();

	if (IRReadings.frontLeftIR && !IRReadings.frontRightIR)
	{
		turnLeftRetrieve();
	}
	else if (!IRReadings.frontLeftIR && IRReadings.frontRightIR)
	{
		turnRightRetrieve();
	}
	else if (IRReadings.frontLeftIR && IRReadings.frontRightIR && !IRReadings.rearRightIR && !IRReadings.rearLeftIR)
	{
		approachFridge();
	}
	else if (IRReadings.frontLeftIR && IRReadings.frontRightIR && IRReadings.rearRightIR && IRReadings.rearLeftIR)
	{
		return true;
	}
	else
	{
		moveStraightRetrieve();
	}

	return false;
}

#endif