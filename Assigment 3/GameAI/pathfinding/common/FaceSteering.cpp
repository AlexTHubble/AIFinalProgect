#include "FaceSteering.h"
//#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include <math.h>


//const float PI = 3.1456;
const float RADIAN_TO_DEGREE = 180 / PI; //Formula for converting a radian to a degree
const float DEGREE_TO_RADIAN = PI / 180; //Fomula for converting a degree to a radian 


FaceSteering::FaceSteering(const UnitID & ownerID, const Vector2D & targetLocation, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLocation);
}

Steering * FaceSteering::getSteering()
{

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	Vector2D direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	//float rotationToTarget = atan2(direction.getY(), direction.getX()) + .5f * PI;
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	//Vector2D rotation = mTargetFacing - pOwner->getFacing();

	//Converts to a 2Pi interval
	float currentRotation = fmod(pOwner->getFacing(), 2.0 * PI);
	float rotationSize; // = rotationToTarget - currentRotation;
	float rotationSpeed = 0;
	float rotationTarget = 0;

	float angle = (atan2(direction.getY(), direction.getX()) + (PI / 2)) - pOwner->getFacing();
	
	float convertion = fmod((angle), 2.0 * PI);
	if (convertion > PI)
	{
		convertion - PI;
		convertion *= -1.0;
	}
	else if (convertion < -PI)
	{
		convertion + PI;
		convertion *= -1.0;
	}

	angle = convertion;

	rotationSize = abs(angle);

	//std::cout << currentRotation * RADIAN_TO_DEGREE << "\t" << rotationToTarget*RADIAN_TO_DEGREE << std::endl;

	if (rotationSize < mTargetRotationRadius) //If facing target, stop rotation
	{
		data.rotAcc = 0;
		data.rotVel = 0;
		this->mData = data;
		return this;
	}

	if (rotationSize > mSlowRadius)
	{
		rotationTarget = data.maxRotAcc;
	}
	else
	{
		rotationTarget = data.maxRotAcc * rotationSize / mSlowRadius;
	}

	rotationTarget *= angle / rotationSize;

	data.rotAcc = rotationTarget - data.rotVel;
	data.rotAcc /= 0.1;

	float anglularAccleration = abs(data.rotAcc);

	if (anglularAccleration > data.maxRotAcc)
	{
		data.rotAcc /= anglularAccleration;
		data.rotAcc *= data.maxRotAcc;
	}

	data.acc = 0;
	data.vel = 0;

	this->mData = data;
	return this;
}
