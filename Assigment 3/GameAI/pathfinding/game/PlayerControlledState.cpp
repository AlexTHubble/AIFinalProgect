#include "PlayerControlledState.h"
#include "PositionComponent.h"
#include "UnitManager.h"
#include "Game.h"
#include "Unit.h"
#include "Collision.h"
#include <iostream>

using namespace std;

void PlayerControlledState::onEntrance()
{
	mTransferToAIControll = false;
	gpGame->getUnitManager()->getUnit(mUnitId)->setToUpdateTarget(false);
 	gpGame->getUnitManager()->getUnit(mUnitId)->setSteering(Steering::NONE, NULL, mUnitId);
}

void PlayerControlledState::onExit()
{
}

StateTransition * PlayerControlledState::update(int elapsedTime)
{

	if (mTransferToAIControll) //If the state has been marked to transition into the new state...
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(TO_AI_CONTROLLED_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	//Gets data
	PhysicsData data = gpGame->getUnitManager()->getUnit(mUnitId)->getPhysicsComponent()->getData();
	//Movement update
	mpTankMovment->UpdateMovement(elapsedTime);
	//Set rotation
	data.rotVel = mpTankMovment->GetRotateSpeed();
	//Set movement
	float temp = gpGame->getUnitManager()->getUnit(mUnitId)->getFacing() - (PI / 2);
	Vector2D currentDirection = Vector2D(cos(temp), sin(temp));

	data.vel = currentDirection * mpTankMovment->GetMovementSpeed();

	gpGame->getUnitManager()->getUnit(mUnitId)->getPhysicsComponent()->setData(data);

	//Check collision
	Collision* collision = new Collision();
	collision->CheckForCollisions(gpGame->getUnitManager()->getUnit(mUnitId));

	delete collision;
	return NULL;//no transition
}

void PlayerControlledState::handleMovmentInput(bool accelerating, bool decelerating)
{
	if (accelerating)
	{
		//acclerating
		mpTankMovment->MoveForward();
	}
	else if (decelerating)
	{
		//Declerating
		mpTankMovment->MoveBackwards();
	}
	else
	{
		//zeroOutMovment
		mpTankMovment->ZeroOutMovement();
	}
}

void PlayerControlledState::handleRotateInput(bool left, bool right)
{
	if (left)
	{
		mpTankMovment->RotateCounterClockwise();
	}
	else if (right)
	{
		mpTankMovment->RotateClockwise();
	}
	else
	{
		mpTankMovment->ZeroOutRotate();
	}
}

void PlayerControlledState::handleSwapInput()
{
	mTransferToAIControll = true;
}

void PlayerControlledState::handleFireInput()
{
	gpGame->getUnitManager()->getUnit(mUnitId)->shootBullet();
}

void PlayerControlledState::cleanupTransitions()
{
	for (std::map<TransitionType, StateTransition*>::iterator transition = mTransitions.begin(); transition != mTransitions.end(); ++transition)
	{
		if (transition->second != nullptr)
		{
			delete transition->second;
		}
	}
}

