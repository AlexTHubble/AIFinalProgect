#include <assert.h>
#include "StateMachine.h"

StateMachineState::~StateMachineState()
{
}

void StateMachineState::addTransition( StateTransition* pTransition )
{
	mTransitions[ pTransition->getTransitionType()] = pTransition;
}

void StateMachineState::handleMovmentInput(bool accelerating, bool decelerating)
{
}

void StateMachineState::handleSwapInput()
{
}

void StateMachineState::handleFireInput()
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
		std::cout << "------------------------------ " << pTransition->getTargetStateID() << std::endl;
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
