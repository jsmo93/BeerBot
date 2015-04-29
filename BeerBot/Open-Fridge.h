#ifndef _OPEN_FRIDGE
#define _OPEN_FRIDGE

#include "Globals.h"
#include "Deliver.h"

bool punchIt()
{
	sensorReadings readings;
	
	//Launch off the pad
	log("Launching off retrieval pad", 5);
	mav(0, globals.globalMotionParams.ramSpeed);
	mav(3, globals.globalMotionParams.ramSpeed);
	sleep(1);

	//Go until you hit the line
	bool stop = false;
	while (!stop)
	{
		readings = pullSensorData();
		if (readings.frontLeftIR && readings.frontRightIR)
		{
			log("Found end ram line", 5);
			stop = true;
		}
		else if (readings.frontLeftIR && !readings.frontRightIR)
		{
			log("Correct left", 5);
			mav(0, -globals.globalMotionParams.moveSpeed);
			mav(3, globals.globalMotionParams.ramSpeed);
			sleep(0.10);
			mav(0, globals.globalMotionParams.ramSpeed);
			mav(3, globals.globalMotionParams.ramSpeed);
		}
		else if (!readings.frontLeftIR && readings.frontRightIR)
		{
			log("Correct right", 5);
			mav(0, globals.globalMotionParams.ramSpeed);
			mav(3, -globals.globalMotionParams.moveSpeed);
			sleep(0.10);
			mav(0, globals.globalMotionParams.ramSpeed);
			mav(3, globals.globalMotionParams.ramSpeed);
		}
	}
	
	ao();
	return true;
}

bool returnFromPunch()
{
	sensorReadings readings;
	bool stop = false;

	log("Moving back to retrieval pad", 5);
	while (!stop)
	{
		stop = moveDeliver();
	}

	ao();
	return stop;
}

bool moveToDoor()
{
	sensorReadings IRReadings;
	bool stop = false;

	log("Adjusting direction to fridge", 5);
	mav(0, -globals.globalMotionParams.turnSpeed);
	mav(3, globals.globalMotionParams.moveSpeed);
	sleep(2);
	ao();

	log("Launching from fridge pad", 5);
	mav(0, globals.globalMotionParams.moveSpeed);
	mav(3, globals.globalMotionParams.moveSpeed);
	sleep(2);
	ao();

	log("Approaching fridge door", 5);
	mav(0, globals.globalMotionParams.moveSpeed);
	mav(3, globals.globalMotionParams.moveSpeed);
	while (!stop)
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
		else if (IRReadings.frontLeftIR && IRReadings.frontRightIR)
		{
			log("At fridge door location", 5);
			stop = true;
		}
		else
		{
			log("Moving straight", 5);
			moveStraightRetrieve();
		}
	}

	ao();
	return stop;
}

bool swingIt()
{
	sensorReadings readings = pullSensorData();

	log("Swinging to the right", 5);
	mav(0, globals.globalMotionParams.moveSpeed);
	mav(3, -globals.globalMotionParams.turnSpeed);
	sleep(3);
	ao();

	log("Swinging to the left", 5);
	mav(0, -globals.globalMotionParams.moveSpeed);
	mav(3, globals.globalMotionParams.ramSpeed);
	sleep(8);
	ao();

	log("Swinging back to the right", 5);

	mav(0, globals.globalMotionParams.moveSpeed);
	mav(3, -globals.globalMotionParams.turnSpeed);
	sleep(5);
	ao();

	return true;
}

bool moveOpenFridge()
{
	log("Entering open fridge state", 3);
	log("Entering punch it phase", 4);
	punchIt();
	log("Exiting punch it phase", 4);
	log("Entering punch it return phase", 4);
	returnFromPunch();
	log("Exiting punch it phase", 4);
	log("Entering move to door phase", 4);
	moveToDoor();
	log("Exiting move to door phase", 4);
	log("Entering swing it phase", 4);
	swingIt();
	log("Entering punch it phase", 4);

	return true;
}

#endif
