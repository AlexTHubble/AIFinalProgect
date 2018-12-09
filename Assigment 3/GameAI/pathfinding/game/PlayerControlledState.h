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
	virtual void handleRotateInput(bool left, bool right);
	virtual void handleSwapInput();
	virtual void handleFireInput();
	virtual void cleanupTransitions();
private:
	TankMovement * mpTankMovment;
	UnitID mUnitId;
	bool mTransferToAIControll = false;


};

#endif //!PLAYER_CONTROLLED_STATE_H