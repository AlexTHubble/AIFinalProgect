#pragma once

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <limits>
#include <Vector2D.h>

#include "Component.h"
#include "PositionComponent.h"
#include "Sprite.h"
#include "Steering.h"

//#include "CircularQueue.h"
//#include "Transaction.h"
//#include "TransactionProcessor.h"

class PhysicsComponent;
class SteeringComponent;
class Sprite;
class UnitManager;
class Path;

const Uint32 DEFAULT_QUEUE_CAPACITY = 8;


//class Unit : public TransactionProcessor
class Unit : public Trackable
{
public:
	virtual ~Unit();

	void draw() const;
	float getFacing() const;
	void update(float elapsedTime){};


	PositionComponent* getPositionComponent() const;
	PhysicsComponent* getPhysicsComponent() const;
	SteeringComponent* getSteeringComponent() const;
	float getMaxAcc() const { return mMaxAcc; };
	float getMaxSpeed() const { return mMaxSpeed; };
	float getMaxRotAcc() const { return mMaxRotAcc; };
	float getMaxRotVel() const { return mMaxRotVel; };
	void setShowTarget(bool val) { mShowTarget = val; };
	void setPath(Path* path);
	void setToUpdateTarget(bool update) { ShouldUpdateTarget = update; };
	void resetPath();
	UnitID getID() { return mID; };

	void setSteering(Steering::SteeringType type, Vector2D targetLoc, UnitID targetUnitID);
	void updateTarget();

private:
	UnitID mID;
	ComponentID mPhysicsComponentID;
	ComponentID mPositionComponentID;
	ComponentID mSteeringComponentID;
	PositionComponent* mpPositionComponent = NULL;
	Sprite mSprite;
	float mMaxAcc;
	float mMaxSpeed;
	float mMaxRotAcc;
	float mMaxRotVel;
	bool mShowTarget;

	Path* mPath;
	bool ShouldUpdateTarget;
	int mCurrentNode;

	Unit(const Sprite& sprite);


	Unit(Unit&);//invalidate copy constructor
	void operator=(Unit&);//invalidate assignment operator

	friend class UnitManager;
};
