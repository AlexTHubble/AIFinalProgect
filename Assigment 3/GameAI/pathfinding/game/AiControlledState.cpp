#include "AiControlledState.h"
#include "UnitManager.h"
#include "Game.h"
#include "Unit.h"
#include "GameApp.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Path.h"

using namespace std;

void AIControlledState::onEntrance()
{
	//This will kickstart the pathfinding prossess
	mTransferToPlayerControll = false;

	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);


	mUnitPath = NULL;

	findAndApplyNewPath();

}

void AIControlledState::onExit()
{
	gpGame->getUnitManager()->getUnit(mUnitId)->setToUpdateTarget(false);
	//delete mUnitPath;
	//delete mSmoothPathfinding;
}

StateTransition * AIControlledState::update(int elapsedTime)
{

	if (mTransferToPlayerControll) //If the state has been marked to transition into the new state...
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
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(TO_AI_SHOOTING_AT_PLAYER_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	if (testForPowerUpSeen())//Run test to see if the unit is within range of a powerup, if so transition to the appopriate state
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(TO_AI_PATHING_TO_POWERUP_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	pathfindToPlayer();

	return nullptr;
}

void AIControlledState::handleMovmentInput(bool accelerating, bool decelerating)
{
}

void AIControlledState::handleRotateInput(bool left, bool right)
{
}

void AIControlledState::handleSwapInput()
{
	mTransferToPlayerControll = true;
}

void AIControlledState::handleFireInput()
{
}

void AIControlledState::cleanupTransitions()
{
	for (std::map<TransitionType, StateTransition*>::iterator transition = mTransitions.begin(); transition != mTransitions.end(); ++transition)
	{
		if (transition->second != nullptr)
		{
			delete transition->second;
		}
	}
}

bool AIControlledState::testForPlayerSeen()
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


	//Gets the distance between the unit and it's target
	Vector2D direction = mEnemyPlayerLoc - gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition();
	float distance = direction.getLength();
	//Current x and y position
	float xPos = gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition().getX();
	float yPos = gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition().getY();

	if (!RaycastToTarget(xPos, yPos, mEnemyPlayerLoc.getX(), mEnemyPlayerLoc.getY()))
	{
		return true;
	}

	return false;
}

bool AIControlledState::testForPowerUpSeen()
{
	return false;
}

void AIControlledState::pathfindToPlayer()
{
	//Gets the distance between the unit and it's target
	Vector2D direction = mEnemyPlayerLoc - gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition();
	float distance = direction.getLength(); 

	if (distance < mDistanceToTargetForStop) //If the unit is within the desired distance, find a new path
	{
		findAndApplyNewPath();
	}

	gpGame->getUnitManager()->getUnit(mUnitId)->updateTarget();

}

void AIControlledState::findAndApplyNewPath()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	GridGraph* pGridGraph = pGame->getGridGraph();
	mSmoothPathfinding = new SmoothPathFinding(pGridGraph);
	//mSmoothPathfinding = new SmoothPathFinding(pGridGraph);

	//Gets the enemy player's location
	if (mUnitId == 0) //If the player is p1
	{
		mEnemyPlayerLoc = gpGame->getUnitManager()->getPlayer2Unit()->getPositionComponent()->getPosition();
	}
	else if (mUnitId == 1)//If the player is p2
	{
		mEnemyPlayerLoc = gpGame->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
	}

	Node* from = pGridGraph->getNodeClosestToLocation(gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition());
	Node* to = pGridGraph->getNodeClosestToLocation(mEnemyPlayerLoc);

	
	mUnitPath = mSmoothPathfinding->findPath(from, to);

	gpGame->getUnitManager()->getUnit(mUnitId)->setPath(mUnitPath);
	gpGame->getUnitManager()->getUnit(mUnitId)->setToUpdateTarget(true);

	delete mUnitPath;
	//delete mSmoothPathfinding;
	
}

bool AIControlledState::RaycastToTarget(float xPos, float yPos, float xTarget, float yTarget)
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
