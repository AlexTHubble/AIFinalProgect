#pragma once
#ifndef AI_CONTROLLED_STATE_H
#define AI_CONTROLLED_STATE_H

#include "StateMachine.h"
#include "TankMovement.h"
#include "Defines.h"
#include "Node.h"
#include "SmoothPathFinding.h"

class AIControlledState : public StateMachineState
{
public:
	AIControlledState(const SM_idType& id, TankMovement* tankMovment, UnitID unitId) :StateMachineState(id) {
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
	float mDistanceToTargetForStop = 30;
	float mDistanceForPlayerSeen = 999;
	Node* mPlayerNode;
	Path* mUnitPath;
	SmoothPathFinding* mSmoothPathfinding;

	bool testForPlayerSeen();
	bool testForPowerUpSeen();
	void pathfindToPlayer();
	void findAndApplyNewPath();
	bool RaycastToTarget(float xPos, float yPos, float xTarget, float yTarget);
};

#endif //!AI_CONTROLLED_STATE_H