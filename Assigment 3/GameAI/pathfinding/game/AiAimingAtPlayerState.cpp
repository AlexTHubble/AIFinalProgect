#include "AiAimingAtPlayerState.h"

void AIAimAtPlayerState::onEntrance()
{
}

void AIAimAtPlayerState::onExit()
{
}

StateTransition * AIAimAtPlayerState::update(int elapsedTime)
{
	std::cout << "update in AI" << std::endl;

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
	return false;
}
