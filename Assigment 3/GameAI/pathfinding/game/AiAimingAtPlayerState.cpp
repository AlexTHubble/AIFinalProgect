#include "AiAimingAtPlayerState.h"
#include "UnitManager.h"
#include "Game.h"
#include "Unit.h"
#include "GameApp.h"
#include "GridGraph.h"
#include "Grid.h"
#include "../common/Steering.h"
#include "Collision.h"

void AIAimAtPlayerState::onEntrance()
{
	mTransferToPlayerControll = false;
	gpGame->getUnitManager()->getUnit(mUnitId)->setToUpdateTarget(false);
}

void AIAimAtPlayerState::onExit()
{
}

StateTransition * AIAimAtPlayerState::update(int elapsedTime)
{
	//Gets the enemy player's location
	if (mUnitId == 0) //If the player is p1
	{
		mEnemyPlayerLoc = gpGame->getUnitManager()->getPlayer2Unit()->getPositionComponent()->getPosition();
	}
	else if (mUnitId == 1)//If the player is p2
	{
		mEnemyPlayerLoc = gpGame->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
	}

	if (mTransferToPlayerControll)
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(TO_PLAYER_CONTROLLED_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	if (testForPlayerSeen()) //Run test to see if the unit is within range of the opposing player, if so transition to the appopriate state
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(TO_AI_CONTROLLED_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	gpGame->getUnitManager()->getUnit(mUnitId)->shootBullet();
	aimAtPlayer();

	//Check collision
	Collision* collision = new Collision();
	collision->CheckForCollisions(gpGame->getUnitManager()->getUnit(mUnitId));

	delete collision;

	return nullptr;
}

void AIAimAtPlayerState::handleMovmentInput(bool accelerating, bool decelerating)
{
}

void AIAimAtPlayerState::handleRotateInput(bool left, bool right)
{
}

void AIAimAtPlayerState::handleSwapInput()
{
	mTransferToPlayerControll = true;
}

void AIAimAtPlayerState::handleFireInput()
{
}

void AIAimAtPlayerState::cleanupTransitions()
{
}

bool AIAimAtPlayerState::testForPlayerSeen()
{
	//Gets the distance between the unit and it's target
	Vector2D direction = mEnemyPlayerLoc - gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition();
	float distance = direction.getLength();

	//Current x and y position
	float xPos = gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition().getX();
	float yPos = gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition().getY();

	if (RaycastToTarget(xPos, yPos, mEnemyPlayerLoc.getX(), mEnemyPlayerLoc.getY()))
	{
		return true;
	}

	return false;
}

void AIAimAtPlayerState::aimAtPlayer()
{


	if (mUnitId == PLAYER_UNIT_ID) //Is player 1
	{
		gpGame->getUnitManager()->getUnit(mUnitId)->setSteering(Steering::FACE, mEnemyPlayerLoc, PLAYER2_UNIT_ID);
	}
	else if (mUnitId == PLAYER2_UNIT_ID) //Is player 2
	{
		gpGame->getUnitManager()->getUnit(mUnitId)->setSteering(Steering::FACE, mEnemyPlayerLoc, PLAYER_UNIT_ID);
	}
}

bool AIAimAtPlayerState::RaycastToTarget(float xPos, float yPos, float xTarget, float yTarget)
{
	//Get Grid
	Grid* grid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	//Get point variables
	float x0 = xPos;
	float y0 = yPos;
	float x1 = xTarget;
	float y1 = yTarget;

	//
	float dx = abs(x1 - x0);
	float dy = abs(y1 - y0);
	float x = x0;
	float y = y0;
	float n = 1 + dx + dy;
	float x_inc = (x1 > x0) ? 1 : -1;
	float y_inc = (y1 > y0) ? 1 : -1;
	float error = dx - dy;
	dx *= 2;
	dy *= 2;


	for (; n > 0; --n)
	{
		//If any walls intersect with Raycast between points, return Raycast hit as true
		if (grid->getValueAtPixelXY(x, y))
		{
			//Raycast hit a wall block
			return true;
		}

		if (error > 0)
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}

	return false;
}
