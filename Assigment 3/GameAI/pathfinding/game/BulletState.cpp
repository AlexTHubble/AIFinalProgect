#include "BulletState.h"

void BulletState::onEntrance()
{
}

void BulletState::onExit()
{
}

StateTransition * BulletState::update(int elapsedTime)
{
	return nullptr;
}

void BulletState::handleMovmentInput(bool accelerating, bool decelerating)
{
}

void BulletState::handleRotateInput(bool left, bool right)
{
}

void BulletState::handleSwapInput()
{
}

void BulletState::handleFireInput()
{
}

void BulletState::cleanupTransitions()
{
}
