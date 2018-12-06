#pragma once

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <limits>
#include <Vector2D.h>

#include "Component.h"
#include "PositionComponent.h"
#include "Sprite.h"
#include "Steering.h"
#include "../game/StateMachine.h"

//#include "CircularQueue.h"
//#include "Transaction.h"
//#include "TransactionProcessor.h"

class PhysicsComponent;
class SteeringComponent;
class Sprite;
class UnitManager;
class Path;
class TankMovement;

const Uint32 DEFAULT_QUEUE_CAPACITY = 8;


//class Unit : public TransactionProcessor
class Unit : public Trackable
{
public:
	virtual ~Unit();

	void draw() const;
	float getFacing() const;
	void update(int elapsedTime);

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
	//Tank Functions
	TankMovement* Movement() { return mpTankMovement; };
	void SetMaxMoveSpeed(float maxSpeed) { SetMaxSpeed(maxSpeed); };
	void SetMaxRotateSpeed(float maxSpeed) { SetMaxRotateSpeed(maxSpeed); };

	void setSteering(Steering::SteeringType type, Vector2D targetLoc, UnitID targetUnitID);
	void updateTarget();
	StateMachine* getStateMachine();

protected:
	Unit(const Sprite& sprite, UnitID idToBeSet);
	void SetMaxSpeed(float maxSpeed) { mMaxSpeed = maxSpeed; };
	void SetMaxRotVel(float maxVel) { mMaxRotVel = maxVel; };

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

	//Class Instances
	TankMovement* mpTankMovement;

	Unit(Unit&);//invalidate copy constructor
	void operator=(Unit&);//invalidate assignment operator

	StateMachine* mpUnitStateMachine;

	friend class UnitManager;
};
