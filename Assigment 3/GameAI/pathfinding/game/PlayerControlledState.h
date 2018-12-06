#pragma once
#ifndef PLAYER_CONTROLLED_STATE_H
#define PLAYER_CONTROLLED_STATE_H

#include "StateMachine.h"
#include "TankMovement.h"
#include "Defines.h"

class PlayerControlledState : public StateMachineState
{
public:
	PlayerControlledState(const SM_idType& id, TankMovement* tankMovment, UnitID unitId) :StateMachineState(id) { mpTankMovment = tankMovment; mUnitId = unitId; };

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update(int elapsedTime);
	virtual void handleMovmentInput(bool accelerating, bool decelerating);
	virtual void handleSwapInput();
	virtual void handleFireInput();
private:
	TankMovement * mpTankMovment;
	UnitID mUnitId;
};

#endif //!PLAYER_CONTROLLED_STATE_H