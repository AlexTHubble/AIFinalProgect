#include "PowerUpState.h"

void PowerUpState::onEntrance()
{
}

void PowerUpState::onExit()
{
}

StateTransition * PowerUpState::update(int elapsedTime)
{
	return nullptr;
}

void PowerUpState::handleMovmentInput(bool accelerating, bool decelerating)
{
}

void PowerUpState::handleRotateInput(bool left, bool right)
{
}

void PowerUpState::handleSwapInput()
{
}

void PowerUpState::handleFireInput()
{
}

void PowerUpState::cleanupTransitions()
{
}
