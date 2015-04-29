#ifndef _CLOSE_FRIDGE
#define _CLOSE_FRIDGE

#include "Globals.h"

bool moveCloseFridge()
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

bool positionForSwing()
{
	sensorReadings readings;
	bool stop = false;

	while (!stop)
	{

	}
	//Launch off the pad
	log("Launching off retrieval pad", 5);
	mav(0, globals.globalMotionParams.ramSpeed);
	mav(3, globals.globalMotionParams.ramSpeed);
	sleep(1);

	//Go until you hit the line
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
	mav(0, globals.globalMotionParams.moveSpeed);
	mav(3, -globals.globalMotionParams.turnSpeed);
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

	log("Moving to front of swing zone", 5);
	while (readings.frontLeftIR || readings.frontRightIR)
	{
		mav(0, globals.globalMotionParams.moveSpeed);
		mav(3, globals.globalMotionParams.moveSpeed);
		sleep(0.10);
		ao();
		readings = pullSensorData();
	}

	log("Moving back inside swing zone", 5);
	mav(0, -globals.globalMotionParams.moveSpeed);
	mav(3, -globals.globalMotionParams.moveSpeed);
	sleep(0.25);

	log("Swinging to the right", 5);
	while (readings.frontRightIR)
	{
		mav(0, globals.globalMotionParams.moveSpeed);
		mav(3, -globals.globalMotionParams.turnSpeed);
		sleep(0.10);
		ao();
		readings = pullSensorData();
	}

	log("Swinging to the left", 5);
	bool stop = false;
	mav(0, -globals.globalMotionParams.turnSpeed);
	mav(3, globals.globalMotionParams.moveSpeed);
	while (!stop)
	{
		if (!readings.frontLeftIR)
		{
			stop = true;
		}
		readings = pullSensorData();
	}
	ao();

	log("Swinging back to the right", 5);
	while (readings.frontRightIR)
	{
		mav(0, globals.globalMotionParams.moveSpeed);
		mav(3, -globals.globalMotionParams.turnSpeed);
		sleep(0.10);
		ao();
		readings = pullSensorData();
	}

	return stop;
}

#endif
