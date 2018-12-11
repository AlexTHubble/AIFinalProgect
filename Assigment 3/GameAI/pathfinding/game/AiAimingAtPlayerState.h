#pragma once
#ifndef AI_AIMING_AT_PLAYER_STATE_H
#define AI_AIMING_AT_PLAYER_STATE_H

#include "StateMachine.h"
#include "TankMovement.h"
#include "Defines.h"
#include "Node.h"
#include "SmoothPathFinding.h"

class AIAimAtPlayerState : public StateMachineState
{
public:
	AIAimAtPlayerState(const SM_idType& id, TankMovement* tankMovment, UnitID unitId) :StateMachineState(id) {
		mpTankMovment = tankMovment;
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
	TankMovement * mpTankMovment;
	UnitID mUnitId;
	bool mTransferToPlayerControll = false;
	Vector2D mEnemyPlayerLoc;
	float mDistanceForPlayerSeen = 300;
	Node* mPlayerNode;
	Path* mUnitPath;
	SmoothPathFinding* mSmoothPathfinding;

	bool testForPlayerSeen();
	void aimAtPlayer();
};

#endif //!AI_AIMING_AT_PLAYER_STATE_H