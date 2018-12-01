#include <cassert>

//#include "Steering.h"
#include "Arrive.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

//Dynamic steering type
Arrive::Arrive(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::SEEK;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* Arrive::getSteering()
{

	float targetSpeed = 0;
	float temp = 0;
	Vector2D targetVelocity;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	float maxSpeed = pOwner->getMaxSpeed();
	//float maxAcceleation = pOwner->getMaxAcc();
	

	//are we seeking a location or a unit?
	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
		
	}
	Vector2D direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	float distance = direction.getLength();

	testForArrival(distance);

	switch (mType)
	{
	case Steering::INVALID_TYPE:
		break;
	case Steering::SEEK: //Seek algorithm
		targetVelocity = direction;
		targetSpeed = maxSpeed;

		break;
	case Steering::FLEE: //Flee algorithim
		targetVelocity = direction * -1;
		targetSpeed = maxSpeed;
		break;
	case Steering::ARRIVE: //Arrive algorithim
		targetVelocity = direction;
		targetSpeed = maxSpeed * distance / mSlowRadius;
		break;
	case Steering::STOP:
		targetSpeed = 0;
		
		break;
	default:
		return this;
		break;
	}

	targetVelocity.normalize();
	targetVelocity *= targetSpeed;

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	Vector2D currentVelocity = data.vel;

	data.acc = targetVelocity - currentVelocity;
	//float timeToTarget = distance / targetSpeed;
	data.acc /= 0.1;

	if (data.acc.getLength() > data.maxAccMagnitude)
	{
		data.acc.normalize();
		data.acc *= data.maxAccMagnitude;
	}

	this->mData = data;
	return this;
}

//This function will test to see if the unit should slow down or stop depending on how close it is to it's destination
void Arrive::testForArrival(float distance)
{

	if (distance < mStopSteeringRadius) //Arrived
	{
		mType = Steering::STOP;
		return;
	}	
	if (distance > mSlowRadius) //Outside radius
	{
		mType = Steering::SEEK;
	}
	else //Within radius 
	{
		mType = Steering::ARRIVE;
	}

}

