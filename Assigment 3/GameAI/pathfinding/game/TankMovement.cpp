#include "TankMovement.h"
#include "Game.h"
#include <math.h>

//const double BETTERPI = std::atan(1.0) * 4;
const float DEGREE_TO_RADIAN = PI / 180;

TankMovement::TankMovement(float maxSpeed, float maxRotateSpeed, float movementMultiplier)
{
	//Init movement variables
	SetMaxMovementSpeed(maxSpeed);
	SetMaxRotateSpeed(maxRotateSpeed);
	SetMovementMultiplier(movementMultiplier);
	//Init bool
	SetIsMoving(false);
	SetIsRotating(false);
	SetIsMovementBuffed(false);
	//Init buff timer
	mMovementBuffTimer = 0;
}

TankMovement::~TankMovement()
{

}

void TankMovement::UpdateMovement(int elapsedTime)
{

	//Adjust movement buffed timer
	if (mIsMovementBuffed)
	{
		//Decrement timer
		mMovementBuffTimer -= elapsedTime;
		//If buff time is over
		if (mMovementBuffTimer < 0)
		{
			//End buff and reset movement
			EndMovementBuff();
		}
	}
}

void TankMovement::MoveForward()
{
	SetMovementSpeed(mMaxMoveSpeed * mMovementMultiplier);
}

void TankMovement::MoveBackwards()
{
	SetMovementSpeed(-mMaxMoveSpeed * mMovementMultiplier);
}

void TankMovement::RotateClockwise()
{
	SetRotateSpeed(mMaxRotateSpeed * mMovementMultiplier);
	SetCurrentAngle();
}

void TankMovement::RotateCounterClockwise()
{
	SetRotateSpeed(-mMaxRotateSpeed * mMovementMultiplier);
	SetCurrentAngle();
}

void TankMovement::ZeroOutMovement()
{
	SetMovementSpeed(0);
}

void TankMovement::ZeroOutRotate()
{
	SetRotateSpeed(0);
}

void TankMovement::MovementBuff()
{
	if (mIsMovementBuffed)
	{
		//Increase timer and change multiplier
		mMovementBuffTimer += gpGame->getFileSystem()->getBufDuration();
		SetMovementMultiplier(gpGame->getFileSystem()->getPowerUpSpeedIncrease());
	}
	else
	{
		//Set buffed to true
		SetIsMovementBuffed(true);
		//Set timer and multiplier
		mMovementBuffTimer = gpGame->getFileSystem()->getBufDuration();
		SetMovementMultiplier(gpGame->getFileSystem()->getPowerUpSpeedIncrease());
	}
}

float TankMovement::GetCurrentAngleRadians()
{
	return (GetCurrentAngleDegrees() * DEGREE_TO_RADIAN);
}

void TankMovement::SetCurrentAngle()
{
	float tempAngle = mCurrentAngle + mRotateSpeed;

	//If angle is negative
	if (tempAngle < 0)
	{
		//subtract remaining from 360 to get degrees
		mCurrentAngle = (360 - abs(tempAngle));
	}
	//If angle is above 360
	else if (tempAngle > 360)
	{
		//subtract from 360 to get remaining degrees
		mCurrentAngle = (tempAngle - 360);
	}
	//If between 0-360
	else
	{
		//Set current angle
		mCurrentAngle = tempAngle;
	}
}

void TankMovement::EndMovementBuff()
{
	//End of movement buff
	SetMovementMultiplier(1.0f);
	SetIsMovementBuffed(false);
	mMovementBuffTimer = 0.0f;
}
