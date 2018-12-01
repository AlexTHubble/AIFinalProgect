#include <Trackable.h>
#include "Steering.h"
#include "UnitManager.h"
#include "AllignSteering.h"
#include "Seperation.h"
#include "Cohesion.h"
#include "WanderSteering.h"
//#include "InputSystem.h"

class Flock : public Steering
{
public:
	Flock(const UnitID& ownerID, const Vector2D& targetLoc,const UnitID& targetID = INVALID_UNIT_ID);
	~Flock();
	//void setUnitManager(UnitManager *unitManager) { mUnitManager = unitManager; };

	//Setters for weight
	void setAllignWeight(float theWeight) { mAllignWeight = theWeight; };
	void setSeperationWeight(float theWeight) { mSeperationWeight = theWeight; };
	void setCohesionWeight(float theWeight) { mCohesionWeigth = theWeight; };
	void setWanderWeight(float theWeight) { mWanderWeight = theWeight; };

	//Setters for wander variables
	void setWanderOffSet(float theWanderOffset) { mWanderOffSet = theWanderOffset; };
	void setWanderRadius(float theWanderRadius) { mWanderRadius = theWanderRadius; };
	void setWanderRate(float theWanderRate) { mWanderRate = theWanderRate; };

	//Getters for weights
	float getAllignWeight() { return mAllignWeight; };
	float getSeperationWeight() { return mSeperationWeight; };
	float getCohesionWeight() { return mCohesionWeigth; };
	float getWanderWeight() { return mWanderWeight; };

	//Getters for wander variables
	float getWanderOffSet() { return mWanderOffSet; };
	float getWanderRadius() { return mWanderRadius; };
	float getWanderRate() { return mWanderRate; };

	//Getters for radius
	int getAllignmentRadius() { return mAllignSteering->getRadius(); };
	int getSeperationRadius() { return mSeperationSteering->getRadius(); };
	int getCohesionRadius() { return mCohesionSteering->getRadius(); };

	//Setters for radius
	void setAllignmentRadius(int theRadius) { mAllignSteering->setRadius(theRadius); };
	void setSeperationRadius(int theRadius) { mSeperationSteering->setRadius(theRadius); };
	void setCohesionRadius(int theRadius) { mCohesionSteering->setRadius(theRadius); };

	//Flock* getFlockSteering() { return this; }; //A getter for returning the class

protected:
	virtual Steering* getSteering();

	Allign *mAllignSteering;
	Seperation *mSeperationSteering;
	Cohesion *mCohesionSteering;
	WanderSteering *mWanderSteering;

	float mAllignWeight = 0.4;
	float mSeperationWeight = 1.0;
	float mCohesionWeigth = 0.6;
	float mWanderWeight = 0.3;

	float mWanderOffSet = 100.0f;
	float mWanderRadius = 50.0f;
	float mWanderRate = 0.8f;
	float mWanderOrientation = 0;
	float mTargetOrientation = 0;
	Vector2D mTarget;

	Steering* mpFaceSteering;

};