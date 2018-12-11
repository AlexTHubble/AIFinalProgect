#pragma once
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <map>
#include <Trackable.h>
#include "Path.h"
#include "Steering.h"

/*Collection of base classes to implement a StateMachine.  Heavily borrowed from
	Millington text.

	Dean lawson
	Champlain College 
	2011
*/

class StateTransition;

enum TransitionType
{
	INVALID_TRANSITION_TYPE = -1,
	TO_PLAYER_CONTROLLED_STATE = 0,
	TO_AI_CONTROLLED_STATE = 1,
	TO_AI_SHOOTING_AT_PLAYER_STATE = 2,
	TO_AI_PATHING_TO_POWERUP_STATE = 3
};

enum StateType
{
	INVALID_STATE_TYPE = -1,
	PLAYER_CONTROLLED_STATE = 0,
	AI_CONTROLLED_STATE = 1,
	AI_SHOOTING_AT_PLAYER_STATE = 2,
	AI_PATHING_TO_POWERUP_STATE = 3,
	BULLET_STATE = 4,
	POWERUP_STATE = 5
};

typedef int SM_idType;

class StateMachineState:public Trackable
{
public:
	StateMachineState( const SM_idType& id ):mID(id){};
	~StateMachineState();

	void addTransition( StateTransition* pTransition );
	inline const SM_idType& getID() const { return mID; };

	virtual void cleanupTransitions();

	virtual void onEntrance()=0;//code to run when the state is entered
	virtual void onExit()=0;//code to run when the state is exitted
	virtual StateTransition* update(int elapsedTime)=0;//code to run each frame - returning NULL means no transition
	virtual void handleMovmentInput(bool accelerating, bool decelerating);
	virtual void handleRotateInput(bool left, bool right);
	virtual void handleSwapInput();
	virtual void handleFireInput();

protected:
	SM_idType mID;
	UnitID mOwnerUnitId;
	std::map<TransitionType, StateTransition*> mTransitions;
};

class StateTransition:public Trackable
{
public:
	StateTransition( TransitionType type, const SM_idType& targetID ):mType(type),mpTargetStateID(targetID){};
	~StateTransition(){};

	int getTargetStateID() const { return mpTargetStateID; };
	TransitionType getTransitionType() const { return mType; };

protected:
	SM_idType mpTargetStateID;//id of the state to transition to if this transition is taken
	TransitionType mType;
};

class StateMachine:public Trackable
{
public:
	StateMachine():mpCurrentState(NULL),mInitialStateID(-1){};
	~StateMachine();

	void addState( StateMachineState* pState );
	void setInitialStateID( const SM_idType& id ){ mInitialStateID = id; };

	void update(int elapsedTime);//give the current state a chance to run
	void start();//go to the initial state

	void handleMovmentInput(bool accelerating, bool decelerating);
	void handleRotateInput(bool left, bool right);
	void handleSwapInput();
	void handleFireInput();

	void cleanupStates();

protected:
	void transitionToState( const SM_idType& targetID );//call onExit for old state and onEntrance for the new state

	std::map<SM_idType, StateMachineState*> mStates;//all states indexed by stateID
	StateMachineState* mpCurrentState;//the current state that is running
	SM_idType mInitialStateID;//the id of the state which should run first
};

#endif //!STATE_MACHINE_H