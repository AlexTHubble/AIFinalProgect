#include <cassert>

//#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "ArriveAndFace.h"
#include "FaceSteering.h"
#include "Arrive.h"

ArriveAndFace::ArriveAndFace(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering * ArriveAndFace::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	FaceSteering * faceSteering = new FaceSteering(mOwnerID, mTargetLoc, mTargetID);
	Arrive * arriveSteering = new Arrive(mOwnerID, mTargetLoc, mTargetID);

	Steering * faceSteeringData = faceSteering->getSteering();
	Steering * arriveSteeringData = arriveSteering->getSteering();

	PhysicsData facePhysicsData = faceSteeringData->getData();
	PhysicsData arrivePhysicsData = arriveSteeringData->getData();
	
	data.acc = arrivePhysicsData.acc; //Get acceleration from arrive
	data.rotAcc = facePhysicsData.rotAcc; //Get rotation acceleration from face
	data.rotVel = facePhysicsData.rotVel; //Get the rotational velocity from face

	delete faceSteering;
	delete arriveSteering;

	this->mData = data;
	return this;
}
