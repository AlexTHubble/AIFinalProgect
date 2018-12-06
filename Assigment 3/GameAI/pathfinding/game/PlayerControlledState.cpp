#include "PlayerControlledState.h"
#include "PositionComponent.h"
#include "UnitManager.h"
#include "Game.h"
#include "Unit.h"
#include <iostream>

using namespace std;

void PlayerControlledState::onEntrance()
{
	mTransferToAIControll = false;
}

void PlayerControlledState::onExit()
{
}

StateTransition * PlayerControlledState::update(int elapsedTime)
{
	std::cout << "Update from player controlled statemachine!" << std::endl;

	if (mTransferToAIControll) //If the state has been marked to transition into the new state...
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(AI_CONTROLLED_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	//Gets data
	PhysicsData data = gpGame->getUnitManager()->getUnit(mUnitId)->getPhysicsComponent()->getData();

	mpTankMovment->UpdateMovement(elapsedTime);
	//Set rotation
	data.rotVel = mpTankMovment->GetRotateSpeed();
	//Set movement
	float temp = gpGame->getUnitManager()->getUnit(mUnitId)->getFacing() - (PI / 2);
	Vector2D currentDirection = Vector2D(cos(temp), sin(temp));

	data.vel = currentDirection * mpTankMovment->GetMovementSpeed();

	gpGame->getUnitManager()->getUnit(mUnitId)->getPhysicsComponent()->setData(data);



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

void PlayerControlledState::handleSwapInput()
{
	mTransferToAIControll = true;
}

void PlayerControlledState::handleFireInput()
{
}
