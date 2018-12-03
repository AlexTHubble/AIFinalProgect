#ifndef TANK_MOVEMENT_H
#define TANK_MOVEMENT_H

#include "Trackable.h"

class TankMovement : public Trackable
{
public:
	//Constructor
	TankMovement(float maxSpeed, float maxRotateSpeed, float movementMultiplier = 1.0f);
	//Destructor
	~TankMovement();
	//Update
	void UpdateMovement();
	//Movement
	void MoveForward();
	void MoveBackwards();
	void RotateClockwise();
	void RotateCounterClockwise();
	//Buff Function
	void MovementBuff(float movementMultiplier, float seconds);
	//Variable Accessors
	float GetMovementSpeed() { return mMoveSpeed; };
	float GetRotateSpeed() { return mRotateSpeed; };
	float GetCurrentAngleDegrees() { return mCurrentAngle; };
	float GetCurrentAngleRadians();
	float GetMaxMoveSpeed() { return mMaxMoveSpeed; };
	float GetMaxRotateSpeed() { return mMaxRotateSpeed; };
	bool IsMovementBuffed() { return mIsMovementBuffed; };
	bool IsMoving() { return mIsMoving; };
	bool IsRotating() { return mIsRotating; };
	

private:
	//Variable Accessors
	void SetMovementSpeed(float speed) { mMoveSpeed = speed; };
	void SetRotateSpeed(float speed) { mRotateSpeed = speed; };
	void SetCurrentAngle();
	void SetMaxMovementSpeed(float maxSpeed) { mMaxMoveSpeed = maxSpeed; };
	void SetMaxRotateSpeed(float maxSpeed) { mMaxRotateSpeed = maxSpeed; };
	void SetIsMovementBuffed(bool buffed) { mIsMovementBuffed = buffed; };
	void SetIsMoving(bool moving) { mIsMoving = moving; };
	void SetIsRotating(bool rotating) { mIsRotating = rotating; };
	void SetMovementMultiplier(float multiplier) { mMovementMultiplier = multiplier; };
	//Reset Functions
	void EndMovementBuff();
	//Movement Variables
	float mMoveSpeed;
	float mRotateSpeed;
	float mCurrentAngle;
	float mMaxMoveSpeed;
	float mMaxRotateSpeed;
	float mMovementBuffTimer;
	float mMovementMultiplier;
	//Bool Checks
	bool mIsMovementBuffed;
	bool mIsMoving;
	bool mIsRotating;
};


#endif // !TANK_MOVEMENT_H
