#include "AiControlledState.h"
#include "UnitManager.h"
#include "Game.h"
#include "Unit.h"
#include "GameApp.h"
#include "SmoothPathFinding.h"
#include "GridGraph.h"

using namespace std;

void AIControlledState::onEntrance()
{
	//This will kickstart the pathfinding prossess
	mTransferToPlayerControll = false;
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	GridGraph* pGridGraph = pGame->getGridGraph();

	Node* from = pGridGraph->getNodeClosestToLocation(gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition());

	SmoothPathFinding* smoothPathfinding = new SmoothPathFinding(pGridGraph);

	//Gets the enemy player's location
	if (mUnitId == 0) //If the player is p1
	{
		mEnemyPlayerLoc = gpGame->getUnitManager()->getPlayer2Unit()->getPositionComponent()->getPosition();
	}
	else if(mUnitId == 1)//If the player is p2
	{
		mEnemyPlayerLoc = gpGame->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
	}

	Node* to = pGridGraph->getNodeClosestToLocation(mEnemyPlayerLoc);

	gpGame->getUnitManager()->getUnit(mUnitId)->setPath(smoothPathfinding->findPath(from, to));

	delete smoothPathfinding;
}

void AIControlledState::onExit()
{
}

StateTransition * AIControlledState::update(int elapsedTime)
{
	std::cout << "Updating from AI state!" << std::endl;

	if (mTransferToPlayerControll) //If the state has been marked to transition into the new state...
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(PLAYER_CONTROLLED_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	if (testForPlayerSeen()) //Run test to see if the unit is within range of the opposing player, if so transition to the appopriate state
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(AI_SHOOTING_AT_PLAYER_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	if (testForPowerUpSeen())//Run test to see if the unit is within range of a powerup, if so transition to the appopriate state
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(AI_PATHING_TO_POWERUP_STATE);
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
		mTransferToPlayerControll = false;
		GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
		GridGraph* pGridGraph = pGame->getGridGraph();

		Node* from = pGridGraph->getNodeClosestToLocation(gpGame->getUnitManager()->getUnit(mUnitId)->getPositionComponent()->getPosition());

		SmoothPathFinding* smoothPathfinding = new SmoothPathFinding(pGridGraph);

		//Gets the enemy player's location
		if (mUnitId == 0) //If the player is p1
		{
			mEnemyPlayerLoc = gpGame->getUnitManager()->getPlayer2Unit()->getPositionComponent()->getPosition();
		}
		else if (mUnitId == 1)//If the player is p2
		{
			mEnemyPlayerLoc = gpGame->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
		}

		Node* to = pGridGraph->getNodeClosestToLocation(mEnemyPlayerLoc);

		gpGame->getUnitManager()->getUnit(mUnitId)->setPath(smoothPathfinding->findPath(from, to));

		delete smoothPathfinding;
	}
	gpGame->getUnitManager()->getUnit(mUnitId)->updateTarget();
	gpGame->getUnitManager()->getUnit(mUnitId)->setToUpdateTarget(true);

}
