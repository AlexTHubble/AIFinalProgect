#pragma once
#ifndef POWER_UP_STATE_H
#define POWER_UP_STATE_H

#include "StateMachine.h"
#include "Defines.h"
#include "Node.h"
#include "SmoothPathFinding.h"

class PowerUpState : public StateMachineState
{
public:
	PowerUpState(const SM_idType& id, UnitID unitId) :StateMachineState(id) {
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

#endif //!POWER_UP_STATE_H