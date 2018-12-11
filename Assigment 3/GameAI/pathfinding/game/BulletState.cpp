#include "BulletState.h"
#include "Collision.h"
#include "Game.h"
#include "UnitManager.h"

void BulletState::onEntrance()
{
}

void BulletState::onExit()
{
}

StateTransition * BulletState::update(int elapsedTime)
{
	Collision* collision = new Collision;
	collision->CheckForCollisions(gpGame->getUnitManager()->getUnit(mUnitId));

	delete collision;
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
