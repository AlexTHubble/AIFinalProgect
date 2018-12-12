#include "Unit.h"
#include <assert.h>

#include "Game.h"
#include "../game/GameApp.h"
#include "GraphicsSystem.h"
#include "Component.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "SteeringComponent.h"
#include "ComponentManager.h"
#include "SpriteManager.h"
#include "../game/Path.h"
#include "Steering.h"
#include "../game/Node.h"
#include "Grid.h"
#include "../game/TankMovement.h"
#include "../game/PlayerControlledState.h"
#include "../game/AiControlledState.h"
#include "../game/AiAimingAtPlayerState.h"
#include "../game/BulletState.h"
#include "../game/ShootProjectile.h"
#include "../game/PowerUpState.h"
#include "Timer.h"


void Unit::applyBuff()
{
	mpTankMovement->MovementBuff();
}

Unit::Unit(const Sprite& sprite, UnitID idToBeSet, StateType stateToStartIn)
	:mSprite(sprite)
	,mPositionComponentID(INVALID_COMPONENT_ID)
	,mPhysicsComponentID(INVALID_COMPONENT_ID)
	,mSteeringComponentID(INVALID_COMPONENT_ID)
	,mShowTarget(false)
{
	mCurrentHP = gpGame->getFileSystem()->getPlayerHealth();
	mShootDelay = gpGame->getFileSystem()->getShootDelay();

	mMaxSpeed = gpGame->getFileSystem()->getPlayerSpeed();
	//mMaxRotVel = gpGame->getFileSystem()->getPlayerRotateSpeed();
	mpTankMovement = new TankMovement(gpGame->getFileSystem()->getPlayerSpeed(), gpGame->getFileSystem()->getPlayerRotateSpeed()); // <--- Hard coded values for max speeds
	mCurrentNode = 0;
	ShouldUpdateTarget = false;
	mPath = nullptr;

	//Sets up the state machine for the new class
	mpUnitStateMachine = new StateMachine();
	PlayerControlledState* pPlayerControlledState = new PlayerControlledState(PLAYER_CONTROLLED_STATE, mpTankMovement, idToBeSet);
	AIControlledState* pAiControlledState = new AIControlledState(AI_CONTROLLED_STATE, mpTankMovement, idToBeSet);
	AIAimAtPlayerState* pAiAimAtPlayerState = new AIAimAtPlayerState(AI_SHOOTING_AT_PLAYER_STATE, mpTankMovement, idToBeSet);
	BulletState* pBulletState = new BulletState(BULLET_STATE, idToBeSet);
	PowerUpState* pPowerUpState = new PowerUpState(POWERUP_STATE, idToBeSet);

	//Sets up transitions
	StateTransition* pToAIControlledState = new StateTransition(TO_AI_CONTROLLED_STATE, AI_CONTROLLED_STATE);
	StateTransition* pToPlayerControlledState = new StateTransition(TO_PLAYER_CONTROLLED_STATE, PLAYER_CONTROLLED_STATE);
	StateTransition* pToAiAimAtPlayerState = new StateTransition(TO_AI_SHOOTING_AT_PLAYER_STATE, AI_SHOOTING_AT_PLAYER_STATE);

	//Add transtions to states
	pPlayerControlledState->addTransition(pToAIControlledState);
	pAiControlledState->addTransition(pToPlayerControlledState);
	pAiControlledState->addTransition(pToAiAimAtPlayerState);
	pAiAimAtPlayerState->addTransition(pToAIControlledState);
	pAiAimAtPlayerState->addTransition(pToPlayerControlledState);

	//Adds the states
	mpUnitStateMachine->addState(pPlayerControlledState);
	mpUnitStateMachine->addState(pAiControlledState);
	mpUnitStateMachine->addState(pAiAimAtPlayerState);
	mpUnitStateMachine->addState(pBulletState);
	mpUnitStateMachine->addState(pPowerUpState);

	//set the initial state
	mpUnitStateMachine->setInitialStateID(stateToStartIn);
}

Unit::~Unit()
{
	delete mPath;
	mPath = nullptr;
	delete mpTankMovement;
	delete mpUnitStateMachine;
}

void Unit::draw() const
{
	PositionComponent* pPosition = getPositionComponent();
	assert(pPosition != NULL);
	const Vector2D& pos = pPosition->getPosition();
	gpGame->getGraphicsSystem()->draw(mSprite, pos.getX(), pos.getY(), pPosition->getFacing());

	if (mShowTarget)
	{
		SteeringComponent* pSteering = getSteeringComponent();
		assert(pSteering != NULL);
		const Vector2D& targetLoc = pSteering->getTargetLoc();
		if (&targetLoc != &ZERO_VECTOR2D)
		{
			Sprite* pTargetSprite = gpGame->getSpriteManager()->getSprite(TARGET_SPRITE_ID);
			assert(pTargetSprite != NULL);
			gpGame->getGraphicsSystem()->draw(*pTargetSprite, targetLoc.getX(), targetLoc.getY());
		}
	}
}

float Unit::getFacing() const
{
	PositionComponent* pPosition = getPositionComponent();
	assert(pPosition != NULL);
	return pPosition->getFacing();
}

PositionComponent* Unit::getPositionComponent() const
{
	return mpPositionComponent;
}

PhysicsComponent* Unit::getPhysicsComponent() const
{
	PhysicsComponent* pComponent = gpGame->getComponentManager()->getPhysicsComponent(mPhysicsComponentID);
	return pComponent;
}

SteeringComponent* Unit::getSteeringComponent() const
{
	SteeringComponent* pComponent = gpGame->getComponentManager()->getSteeringComponent(mSteeringComponentID);
	return pComponent;
}

void Unit::setPath(Path * path)
{
	resetPath();
	mPath = new Path;

	for (int i = 0; i < path->getNumNodes(); i++)
	{
		Node* tempNode = path->peekNode(i);
		mPath->addNode(tempNode);
	}
	
}

void Unit::resetPath()
{
	mCurrentNode = 0;
	delete mPath;
	mPath = nullptr;
}

void Unit::setSteering(Steering::SteeringType type, Vector2D targetLoc, UnitID targetUnitID)
{
	SteeringComponent* pSteeringComponent = getSteeringComponent();
	if (pSteeringComponent != NULL)
	{
		pSteeringComponent->setData(SteeringData(type, targetLoc, mID, targetUnitID));
	}
}

void Unit::updateTarget()
{
	if (mPath != nullptr)
	{
		
		if (ShouldUpdateTarget)
		{
			if (mCurrentNode < mPath->getNumNodes())
			{
				//Set Steering
				GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
				setSteering(Steering::ARRIVEANDFACE, pGame->getGrid()->getULCornerOfSquare(mPath->peekNode(mPath->getNumNodes() - (mCurrentNode + 1))->getId()), INVALID_UNIT_ID);
				
			}
			ShouldUpdateTarget = false;
			mCurrentNode++;
		}
	}
}

StateMachine * Unit::getStateMachine()
{
	if (mpUnitStateMachine != nullptr)
		return mpUnitStateMachine;
	else
		return nullptr;
}

void Unit::reducePlayerHp(int hpToReduceBy)
{
	mCurrentHP -= hpToReduceBy;
}

void Unit::shootBullet()
{

	if (!mShootDelayInitiaed)
	{
		mShootDelayInitiaed = true;
		mTimeUntillNextShootDelay = 0;

		//ToDo
		Unit* bullet;
		bullet = gpGame->getUnitManager()->createBullet();

		bullet->getPositionComponent()->setPosition(getPositionComponent()->getPosition());
		bullet->getPositionComponent()->setFacing(getFacing());

		ShootProjectile shootProjectile;
		shootProjectile.Shoot(bullet);

		bullet->setOwnerID(mID);
	}


}

void Unit::setTag(string tag)
{
	mTag = tag;
}

void Unit::update(float elapsedTime)
{
	if (mShootDelayInitiaed)
	{
		mTimeUntillNextShootDelay += elapsedTime;
		if (mTimeUntillNextShootDelay > mShootDelay)
		{
			mShootDelayInitiaed = false;
		}
	}

	mpUnitStateMachine->update(elapsedTime);
}
