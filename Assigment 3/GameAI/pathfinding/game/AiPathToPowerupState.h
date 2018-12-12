#pragma once
#ifndef AI_PATH_TO_POWERUP_STATE_H
#define AI_PATH_TO_POWERUP_STATE_H

#include "StateMachine.h"
#include "TankMovement.h"
#include "Defines.h"
#include "Node.h"
#include "SmoothPathFinding.h"


class AiPathToPowerUpState : public StateMachineState
{
public:
	AiPathToPowerUpState(const SM_idType& id, TankMovement* tankMovment, UnitID unitId) :StateMachineState(id) { mpTankMovment = tankMovment; mUnitId = unitId; };

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
	Vector2D mPowerUpLocation;
	Path* mUnitPath;
	//SmoothPathFinding* mSmoothPathfinding;

	bool testForPowerUpSeen();
	bool pathToPowerUp();
	void findAndApplyNewPath();
	bool RaycastToTarget(float xPos, float yPos, float xTarget, float yTarget);

};

#endif //!AI_PATH_TO_POWERUP_STATE_H