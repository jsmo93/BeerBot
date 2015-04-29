#ifndef _VISION_UTILS
#define _VISION_UTILS

#include "Globals.h"

typedef struct
{
	bool found;
	unsigned x;
	unsigned y;
} blobCoords; //Represents if a blob was found and where
typedef struct
{
	unsigned xZone;
	unsigned yZone;
} moveToZone; //Represents which area the robot should move toward

//Scan for matching color bottle
blobCoords scanField(unsigned color)
{
	blobCoords firstBottle;
	//Take a new reading
	track_update();
	if (track_count(color) > 0)
	{
		if (track_size(color, 0) > 20)
		{
			firstBottle.x = track_x(color, 0);
			firstBottle.y = track_y(color, 0);
			firstBottle.found = true;
			return firstBottle;
		}
	}

	firstBottle.found = false;
	return firstBottle;
}

//Convert the image coordinates into a move-to zone
/*
(0, 0)
############################################
## 1,6 ## 2,6 ## 3,6 ## 4,6 ## 5,6 ## 6,6 ##
############################################
## 1,5 ## 2,5 ## 3,5 ## 4,5 ## 5,5 ## 6,5 ##
############################################
## 1,4 ## 2,4 ## 3,4 ## 4,4 ## 5,4 ## 6,4 ##
############################################
## 1,3 ## 2,3 ## 3,3 ## 4,3 ## 5,3 ## 6,3 ##
############################################
## 1,2 ## 2,2 ## 3,2 ## 4,2 ## 5,2 ## 6,2 ##
############################################
## 1,1 ## 2,1 ## 3,1 ## 4,1 ## 5,1 ## 6,1 ##
############################################ (159, 119)
*/
moveToZone determineZone(blobCoords thisBlob)
{
	//This function is just converting the screen coordinates
	//into Cartesian coordinates with values from 1-3
	moveToZone move_to;

	if (thisBlob.y >= 0 && thisBlob.y < 20)
	{
		move_to.yZone = 6;
	}
	else if (thisBlob.y >= 20 && thisBlob.y < 40)
	{
		move_to.yZone = 5;
	}
	else if (thisBlob.y >= 40 && thisBlob.y < 60)
	{
		move_to.yZone = 4;
	}
	else if (thisBlob.y >= 60 && thisBlob.y < 80)
	{
		move_to.yZone = 3;
	}
	else if (thisBlob.y >= 80 && thisBlob.y < 100)
	{
		move_to.yZone = 2;
	}
	else
	{
		move_to.yZone = 1;
	}

	if (thisBlob.x >= 0 && thisBlob.x < 26)
	{
		move_to.xZone = 1;
	}
	else if (thisBlob.x >= 26 && thisBlob.x < 52)
	{
		move_to.xZone = 2;
	}
	else if (thisBlob.x >= 52 && thisBlob.x < 78)
	{
		move_to.xZone = 3;
	}
	else if (thisBlob.x >= 78 && thisBlob.x < 104)
	{
		move_to.xZone = 4;
	}
	else if (thisBlob.x >= 104 && thisBlob.x < 130)
	{
		move_to.xZone = 5;
	}
	else
	{
		move_to.xZone = 6;
	}

	return move_to;
}

#endif
