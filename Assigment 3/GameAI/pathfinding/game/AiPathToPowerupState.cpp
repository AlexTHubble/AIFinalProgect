#include "AiPathToPowerupState.h"
#include "UnitManager.h"
#include "Game.h"
#include "Unit.h"
#include "GameApp.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Path.h"
#include "Collision.h"
#include "GameApp.h"


void AiPathToPowerUpState::onEntrance()
{
	mUnitPath = NULL;
	Unit* powerUp = gpGame->getUnitManager()->getUnit(mUnitId)->getClosestPowerUpLocation();
	if (powerUp != NULL)
	{
		mPowerUpLocation = powerUp->getPositionComponent()->getPosition();
		findAndApplyNewPath();
	}

}

void AiPathToPowerUpState::onExit()
{
	gpGame->getUnitManager()->getUnit(mUnitId)->setToUpdateTarget(false);
}

StateTransition * AiPathToPowerUpState::update(int elapsedTime)
{
	if (mTransferToPlayerControll)
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(TO_PLAYER_CONTROLLED_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	if (testForPowerUpSeen())
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(TO_AI_CONTROLLED_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	Collision* collision = new Collision();
	collision->CheckForCollisions(gpGame->getUnitManager()->getUnit(mUnitId));



	if (pathToPowerUp())
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(TO_AI_CONTROLLED_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	delete collision;
	return nullptr;
}

void AiPathToPowerUpState::handleMovmentInput(bool accelerating, bool decelerating)
{
}

void AiPathToPowerUpState::handleRotateInput(bool left, bool right)
{
}

void AiPathToPowerUpState::handleSwapInput()
{
	mTransferToPlayerControll = true;
}

void AiPathToPowerUpState::handleFireInput()
{
}

void AiPathToPowerUpState::cleanupTransitions()
{
}

bool AiPathToPowerUpState::testForPowerUpSeen()
{
	Unit* powerUp = gpGame->getUnitManager()->getUnit(mUnitId)->getClosestPowerUpLocation();
	if (mpTankMovment->IsMovementBuffed())
	{
		return true;
	}
	else if (mUnitId == PLAYER_UNIT_ID && gpGame->getUnitManager()->getUnit(PLAYER2_UNIT_ID)->Movement()->IsMovementBuffed()) //Player 1
	{
		return true;
	}
	else if (mUnitId == PLAYER2_UNIT_ID && gpGame->getUnitManager()->getUnit(PLAYER_UNIT_ID)->Movement()->IsMovementBuffed()) //Player 2
	{
		return true;
	}
	else
	{
		mPowerUpLocation = powerUp->getPositionComponent()->getPosition();
	}


	//Gets the distance between the unit and it's target
	Vector2D direction = mPowerUpLocation - gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition();
	float distance = direction.getLength();
	//Current x and y position
	float xPos = gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition().getX();
	float yPos = gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition().getY();

	if (RaycastToTarget(xPos, yPos, mPowerUpLocation.getX(), mPowerUpLocation.getY()))
	{
		return true;
	}

	return false;
}

bool AiPathToPowerUpState::pathToPowerUp()
{
	////Gets the distance between the unit and it's target
	//Vector2D direction = mPowerUpLocation - gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition();
	//float distance = direction.getLength();

	gpGame->getUnitManager()->getUnit(mUnitId)->updateTarget();
	return false;
}

void AiPathToPowerUpState::findAndApplyNewPath()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	GridGraph* pGridGraph = pGame->getGridGraph();
	//mSmoothPathfinding = new SmoothPathFinding();
	//mSmoothPathfinding = new SmoothPathFinding(pGridGraph);
	Pathfinder* pathFinder = dynamic_cast<GameApp*>(gpGame)->getPathfinder();


	Node* from = pGridGraph->getNodeClosestToLocation(gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition());
	Node* to = pGridGraph->getNodeClosestToLocation(mPowerUpLocation);


	mUnitPath = pathFinder->findPath(from, to);

	gpGame->getUnitManager()->getUnit(mUnitId)->setPath(mUnitPath);
	gpGame->getUnitManager()->getUnit(mUnitId)->setToUpdateTarget(true);
}

bool AiPathToPowerUpState::RaycastToTarget(float xPos, float yPos, float xTarget, float yTarget)
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

