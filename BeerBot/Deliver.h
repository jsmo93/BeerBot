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
	mav(3, globals.globalMotionParams.turnSpeed);
	sleep(globals.globalMotionParams.turnInterval);
	ao();
}

void turnRightDeliver()
{
	mav(0, globals.globalMotionParams.turnSpeed);
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

bool moveDelivery()
{
	IRReadings = pullSensorData();

	if (IRReadings.rearRightIR && !IRReadings.rearLeftIR)
	{
		log("Correct left", 5);
		turnLeftDeliver();
	}
	else if (!IRReadings.rearRightIR && IRReadings.rearLeftIR)
	{
		log("Correct right", 5);
		turnRightDeliver();
	}
	else if (IRReadings.rearRightIR && IRReadings.rearLeftIR && !IRReadings.frontLeftIR && !IRReadings.frontRightIR)
	{
		log("Nearing delivery pad", 5);
		approachDeliveryPad();
	}
	else if (IRReadings.rearRightIR && IRReadings.rearLeftIR && IRReadings.frontLeftIR && IRReadings.frontRightIR)
	{
		log("On delivery pad", 5);
		return true;
	}
	else
	{
		log("Moving straight", 5);
		moveStraightDeliver();
	}

	return false;
}

bool launchDelivery()
{
	IRReadings = pullSensorData();

	if (!IRReadings.rearRightIR && !IRReadings.rearLeftIR && !IRReadings.frontLeftIR && !IRReadings.frontRightIR)
	{
		return true;
	}
	else
	{
		moveStraightDeliver();
	}

	return false;
}

bool moveDeliver()
{
	bool atLocation = false;

	log("Entering delivery state", 3);
	log("Entering delivery launch phase", 4);
	while (!atLocation)
	{
		atLocation = launchDelivery();
	}
	log("Exiting delivery launch phase", 4);
	atLocation = false;

	while (!atLocation)
	{
		atLocation = moveDelivery();
	}
	log("Exiting delivery state", 3);

	return atLocation;
}

#endif