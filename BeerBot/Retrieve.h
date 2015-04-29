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
	mav(0, -globals.globalMotionParams.turnSpeed);
	mav(3, globals.globalMotionParams.moveSpeed);
	sleep(globals.globalMotionParams.turnInterval);
	ao();
}

void turnRightRetrieve()
{
	mav(0, globals.globalMotionParams.moveSpeed);
	mav(3, -globals.globalMotionParams.turnSpeed);
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
		log("Correct left", 5);
		turnLeftRetrieve();
	}
	else if (!IRReadings.frontLeftIR && IRReadings.frontRightIR)
	{
		log("Correct right", 5);
		turnRightRetrieve();
	}
	else if (IRReadings.frontLeftIR && IRReadings.frontRightIR && !IRReadings.rearRightIR && !IRReadings.rearLeftIR)
	{
		log("Nearing fridge pad", 5);
		approachFridge();
	}
	else if (IRReadings.frontLeftIR && IRReadings.frontRightIR && IRReadings.rearRightIR && IRReadings.rearLeftIR)
	{
		log("On fridge pad", 5);
		return true;
	}
	else
	{
		log("Moving straight", 5);
		moveStraightRetrieve();
	}

	return false;
}

bool launchRetrieval()
{
	IRReadings = pullSensorData();

	if (!IRReadings.frontLeftIR && !IRReadings.frontRightIR && !IRReadings.rearRightIR && !IRReadings.rearLeftIR)
	{
		log("Off order pad", 5);
		return true;
	}
	else
	{
		log("Moving off order pad", 5);
		moveStraightRetrieve();
	}

	return false;
}

bool moveRetrieve()
{
	bool atLocation = false;

	log("Entering retrieval state", 3);
	log("Entering retrieval launch phase", 4);
	while (!atLocation)
	{
		atLocation = launchRetrieval();
	}
	log("Exiting retrieval launch phase", 4);
	atLocation = false;


	while (!atLocation)
	{
		atLocation = moveRetrieval();
	}
	log("Exiting retrieval state", 3);

	return atLocation;
}

#endif