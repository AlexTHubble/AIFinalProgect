#pragma once
#ifndef BULLET_STATE_H
#define BULLET_STATE_H

#include "StateMachine.h"
#include "Defines.h"
#include "Node.h"
#include "SmoothPathFinding.h"

class BulletState : public StateMachineState
{
public:
	BulletState(const SM_idType& id, UnitID unitId) :StateMachineState(id) {
		mUnitId = unitId;
	};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update(int elapsedTime);
	virtual void handleMovmentInput(bool accelerating, bool decelerating);
	virtual void handleRotateInput(bool left, bool right);
	virtual void handleSwapInput();
	virtual void handleFireInput();
	virtual void cleanupTransitions();
private:
	UnitID mUnitId;

};

#endif //!BULLET_STATE_H