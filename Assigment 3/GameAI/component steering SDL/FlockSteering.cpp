//#include "FlockSteering.h" //FLOCK STEERING IS INCLUDED IN INPUT SYSTEM
#include <map>
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include "FaceSteering.h"
#include "InputSystem.h"

const float PI = 3.1456;
const float RADIAN_TO_DEGREE = 180 / PI;
const float DEGREE_TO_RADIAN = PI / 180;

Flock::Flock(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	mWanderSteering = new WanderSteering(mOwnerID, mTargetID);

	//Declare allign, seperation, and cohesion
	mAllignSteering = new Allign(mOwnerID, mTargetLoc, mTargetID);
	mSeperationSteering = new Seperation(mOwnerID, mTargetLoc, mTargetID);
	mCohesionSteering = new Cohesion(mOwnerID, mTargetLoc, mTargetID);
	gpGame->getInputManager()->addFlockSteering(this , ownerID); //Adds the flock steering to the list of steering within the 

	
}

Flock::~Flock()
{
	delete mWanderSteering;
	delete mCohesionSteering;
	delete mSeperationSteering;
	delete mAllignSteering;

}

Steering * Flock::getSteering()
{
	//std::cout << "Flock weight: " << mAllignWeight << endl;

	//std::map<UnitID, Unit*> mUnitMap = gpGame->getUnitManager()->getUnitMap(); //Gets the unit map from mUnitManager, this will act as our neigberhood
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	//float tempX;
	//float tempY;

	//-------------BEGINING OF WANDER STEERING CODE---------------------\\
	data = pOwner->getPhysicsComponent()->getData();

	float randomBinomial = genRandomBinomial();
	mWanderOrientation += randomBinomial * mWanderRate; //Update wander orientation

	mTargetOrientation = mWanderOrientation + (pOwner->getFacing() - (PI / 2)); //Calculate combined orientation

	//Calculates direction
	float temp = pOwner->getFacing() - (PI / 2);
	Vector2D currentDirection = Vector2D(cos(temp), sin(temp));

	//Calculates the target location
	mTarget = Vector2D(cos(mTargetOrientation), sin(mTargetOrientation));
	mTargetLoc = currentDirection * mWanderOffSet;
	mTargetLoc += mTarget * mWanderRadius;

	//-------------END OF WANDER STEERING CODE---------------------\\
	
	//Get the vectors out of each algorithm and applies their weights
	Vector2D allignVector = mAllignSteering->getAlligment() * mAllignWeight;
	Vector2D seperationVector = mSeperationSteering->getSeperation() * mSeperationWeight;
	Vector2D cohesionVector = mCohesionSteering->getCohesion() * mCohesionWeigth;
	Vector2D wanderVector = mTargetLoc * mWanderWeight;

	//Blends wander with the three vectors
	Vector2D newAcceleration = wanderVector + allignVector + seperationVector + cohesionVector; 
	newAcceleration.normalize();

	//Sets the acceleration to it's new value
	newAcceleration *= pOwner->getMaxAcc();
	data.acc = newAcceleration;

	//-------BEGINGING OF FACE STEERING CODE -------\\

	//Get steering data from face steering
	mpFaceSteering = new FaceSteering(mOwnerID, newAcceleration + pOwner->getPositionComponent()->getPosition(), mTargetID);
	Steering * newSteering = mpFaceSteering->getSteering(); //NOTE: Figure out how to get working wihtout making getSteering public
	PhysicsData steeringPhysics = newSteering->getData();

	data.rotAcc = steeringPhysics.rotAcc;
	data.rotVel = steeringPhysics.rotVel;

	delete mpFaceSteering;
	//-------END OF FACE STEERING CODE -------\\
	

	this->mData = data;
	return this;
}
