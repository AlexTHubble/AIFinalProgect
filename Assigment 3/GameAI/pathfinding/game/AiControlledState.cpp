#include "AiControlledState.h"

using namespace std;

void AIControlledState::onEntrance()
{
	mTransferToPlayerControll = false;
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

	return nullptr;
}

void AIControlledState::handleMovmentInput(bool accelerating, bool decelerating)
{
}

void AIControlledState::handleSwapInput()
{
	mTransferToPlayerControll = true;
}

void AIControlledState::handleFireInput()
{
}
