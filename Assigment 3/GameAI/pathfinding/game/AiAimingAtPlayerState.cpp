#include "AiAimingAtPlayerState.h"
#include "UnitManager.h"
#include "Game.h"
#include "Unit.h"
#include "GameApp.h"
#include "GridGraph.h"
#include "../common/Steering.h"

void AIAimAtPlayerState::onEntrance()
{



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

	if (testForPlayerSeen()) //Run test to see if the unit is within range of the opposing player, if so transition to the appopriate state
	{
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(AI_CONTROLLED_STATE);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	aimAtPlayer();

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

	if (distance > mDistanceForPlayerSeen)
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
