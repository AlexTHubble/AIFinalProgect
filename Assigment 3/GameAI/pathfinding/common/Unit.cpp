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


Unit::Unit(const Sprite& sprite) 
	:mSprite(sprite)
	,mPositionComponentID(INVALID_COMPONENT_ID)
	,mPhysicsComponentID(INVALID_COMPONENT_ID)
	,mSteeringComponentID(INVALID_COMPONENT_ID)
	,mShowTarget(false)
{
	mpTankMovement = new TankMovement(2.0f, 1.0f); // <--- Hard coded values for max speeds
	mCurrentNode = 0;
	ShouldUpdateTarget = false;
	mPath = nullptr;
}

Unit::~Unit()
{
	delete mPath;
	mPath = nullptr;
	delete mpTankMovement;
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

void Unit::update(int elapsedTime)
{
	std::cout << "here" << std::endl;
	//Update movement in tank movement script
	mpTankMovement->UpdateMovement(elapsedTime);
	//Set facing
	getPositionComponent()->setFacing(mpTankMovement->GetCurrentAngleRadians());
	//Set movement
	getPositionComponent()->setPosition(getPositionComponent()->getPosition() *  mpTankMovement->GetCurrentAngleRadians());
}
