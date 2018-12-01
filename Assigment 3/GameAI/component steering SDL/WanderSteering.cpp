#include "WanderSteering.h"
#include "Steering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


const float PI = 3.1456;
const float RADIAN_TO_DEGREE = 180 / PI;
const float DEGREE_TO_RADIAN = PI / 180;


WanderSteering::WanderSteering(const UnitID & ownerID, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
}

Steering * WanderSteering::getSteering()
{

	//setTargetLoc(getWanderTarget());
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();


	float randomBinomial = genRandomBinomial();


	mWanderOrientation += randomBinomial * mWanderRate; //Update wander orientation

	mTargetOrientation = mWanderOrientation + (pOwner->getFacing() - (PI / 2)); //Calculate combined orientation

	float temp = pOwner->getFacing() - (PI / 2);
	Vector2D currentDirection = Vector2D(cos(temp), sin(temp));

	mTarget = Vector2D(cos(mTargetOrientation), sin(mTargetOrientation));

	mTargetLoc = pOwner->getPositionComponent()->getPosition() + currentDirection * mWanderOffSet;
	mTargetLoc += mTarget * mWanderRadius;

	//Get steering data from face steering
	mpFaceSteering = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);
	Steering * newSteering = mpFaceSteering->getSteering(); //NOTE: Figure out how to get working wihtout making getSteering public
	PhysicsData steeringPhysics = newSteering->getData();

	data.rotAcc = steeringPhysics.rotAcc;
	data.rotVel = steeringPhysics.rotVel;


	data.acc = currentDirection * data.maxSpeed;

	this->mData = data;
	delete newSteering;
	return this;
}

Vector2D WanderSteering::getWanderTarget()
{
	return Vector2D();
}
