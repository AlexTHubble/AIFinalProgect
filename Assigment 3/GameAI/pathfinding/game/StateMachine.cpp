#include <assert.h>
#include "StateMachine.h"

StateMachineState::~StateMachineState()
{

}

void StateMachineState::addTransition( StateTransition* pTransition )
{
	mTransitions[ pTransition->getTransitionType()] = pTransition;
}

void StateMachineState::cleanupTransitions()
{
	for (std::map<TransitionType, StateTransition*>::iterator transition = mTransitions.begin(); transition != mTransitions.end(); ++transition)
	{
		if (transition->second != nullptr)
		{
			delete transition->second;
		}
	}
}

void StateMachineState::handleMovmentInput(bool accelerating, bool decelerating)
{
}

void StateMachineState::handleRotateInput(bool left, bool right)
{
}

void StateMachineState::handleSwapInput()
{
}

void StateMachineState::handleFireInput()
{
}


StateMachine::~StateMachine()
{
}

void StateMachine::addState( StateMachineState* pState )
{
	mStates[ pState->getID() ] = pState;
}

void StateMachine::start()
{
	if( mInitialStateID != -1 )
	{
		transitionToState( mInitialStateID );
	}
}

void StateMachine::handleMovmentInput(bool accelerating, bool decelerating)
{
	if(mpCurrentState != nullptr)
		mpCurrentState->handleMovmentInput(accelerating, decelerating);
}

void StateMachine::handleRotateInput(bool left, bool right)
{
	if (mpCurrentState != nullptr)
		mpCurrentState->handleRotateInput(left, right);
}

void StateMachine::handleSwapInput()
{
	if (mpCurrentState != nullptr)
		mpCurrentState->handleSwapInput();
}

void StateMachine::handleFireInput()
{
	if (mpCurrentState != nullptr)
		mpCurrentState->handleFireInput();
}

void StateMachine::cleanupStates()
{
	for (std::map<SM_idType, StateMachineState*>::iterator state = mStates.begin(); state != mStates.end(); ++state)
	{
		if (state->second != nullptr)
		{
			state->second->cleanupTransitions();
			delete state->second;
		}
	}
}

void StateMachine::update(int elapsedTime)
{
	if( mpCurrentState == NULL )
	{
		start();
		assert( mpCurrentState != NULL );
	}

	StateTransition* pTransition = mpCurrentState->update(elapsedTime);
	if( pTransition != NULL )
	{
		transitionToState( pTransition->getTargetStateID() );
	}
}

void StateMachine::transitionToState( const SM_idType& targetID )
{
	if( mpCurrentState != NULL )
	{
		mpCurrentState->onExit();
	}

	mpCurrentState = mStates[targetID];
	if( mpCurrentState != NULL )
	{
		mpCurrentState->onEntrance();
	}
}
