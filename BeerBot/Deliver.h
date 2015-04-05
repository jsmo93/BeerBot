#ifndef _DELIVER
#define _DELIVER

#include "Globals.h"
#include "MoveUtils.h"

void moveStraightDeliver()
{
	mav(0, -globals.globalMotionParams.moveSpeed);
	mav(3, -globals.globalMotionParams.moveSpeed);
	sleep(globals.globalMotionParams.moveInterval);
	ao();
}

void turnLeftDeliver()
{
	mav(0, -globals.globalMotionParams.moveSpeed);
	mav(3, -globals.globalMotionParams.turnSpeed);
	sleep(globals.globalMotionParams.turnInterval);
	ao();
}

void turnRightDeliver()
{
	mav(0, -globals.globalMotionParams.turnSpeed);
	mav(3, -globals.globalMotionParams.moveSpeed);
	sleep(globals.globalMotionParams.turnInterval);
	ao();
}

void approachDeliveryPad()
{
	mav(0, -globals.globalMotionParams.turnSpeed);
	mav(3, -globals.globalMotionParams.turnSpeed);
	sleep(globals.globalMotionParams.turnInterval);
	ao();
}

bool moveDeliver()
{
	IRReadings = pullSensorData();

	if (IRReadings.rearRightIR && !IRReadings.rearLeftIR)
	{
		turnLeftDeliver();
	}
	else if (!IRReadings.rearRightIR && IRReadings.rearLeftIR)
	{
		turnRightDeliver();
	}
	else if (IRReadings.rearRightIR && IRReadings.rearLeftIR && !IRReadings.frontLeftIR && !IRReadings.frontRightIR)
	{
		approachDeliveryPad();
	}
	else if (IRReadings.rearRightIR && IRReadings.rearLeftIR && IRReadings.frontLeftIR && IRReadings.frontRightIR)
	{
		return true;
	}
	else
	{
		moveStraightDeliver();
	}

	return false;
}

#endif