#ifndef _SEARCH_LOAD
#define _SEARCH_LOAD

#include "Globals.h"
#include "VisionUtils.h"

bool findBottle()
{
	moveToZone zone = determineZone(scanField(globals.globalOrderParams.orderNumber));
	if (zone.xZone != 4)
	{
		log("Zone rejected", 5);
		return false;
	}

	log("Zone accepted", 5);
	return true;
}

bool searchFridge()
{
	sensorReadings readings = pullSensorData();

	log("Moving out of swing zone", 5);
	while (readings.frontLeftIR || readings.frontRightIR)
	{
		mav(0, globals.globalMotionParams.moveSpeed);
		mav(3, globals.globalMotionParams.moveSpeed);
		sleep(0.10);
		ao();
		readings = pullSensorData();
	}

	log("Moving to scan zone", 5);
	while (!readings.frontRightIR)
	{
		mav(0, globals.globalMotionParams.moveSpeed);
		mav(3, globals.globalMotionParams.moveSpeed);
		sleep(0.10);
		ao();
		readings = pullSensorData();
	}

	log("Scanning for beer", 5);
	bool stop = false;
	mav(0, -globals.globalMotionParams.turnSpeed);
	mav(3, globals.globalMotionParams.moveSpeed);
	while (!stop)
	{
		if (readings.frontLeftIR)
		{
			beepCode(4, 0.5);
			sleep(1);
			beepCode(1, 0.5);
			log("Could not find ordered beer", 1);
			exit(1);
		}

		if (findBottle())
		{
			stop = true;
		}

		sleep(0.25);
		readings = pullSensorData();
	}
	ao();
}

bool loadBeer()
{
	sensorReadings readings = pullSensorData();
	log("Approaching beer", 5);
	bool stop = false;
	mav(0, globals.globalMotionParams.turnSpeed);
	mav(3, globals.globalMotionParams.turnSpeed);
	while (!stop)
	{
		if (globals.globalSensorParams.clawBumperPort == 1)
		{
			stop = true;
		}
		readings = pullSensorData();
	}

	log("Grabbing beer", 5);
	clear_motor_position_counter(1);
	mtp(1, 250, 250);
	sleep(2);
	ao();

	return stop;
}

bool getBeer()
{
	sensorReadings readings = pullSensorData();

	log("Entering search and load state", 3);
	log("Entering search phase", 4);

	searchFridge();

	log("Exiting search phase", 3);
	log("Entering load state", 3);

	loadBeer();

	log("Exiting load state", 3);
	log("Exiting search and load state", 3);

	return true;
}

#endif
