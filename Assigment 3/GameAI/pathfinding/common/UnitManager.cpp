#include <map>

#include "UnitManager.h"
#include "Unit.h"
#include "..\game\GameApp.h"
#include "ComponentManager.h"
#include "GraphicsSystem.h"
#include "..\game\Graph.h"
#include "Grid.h"
#include "..\game\GridGraph.h"
#include "..\game\StateMachine.h"


UnitID UnitManager::msNextUnitID = PLAYER2_UNIT_ID + 1;

using namespace std;

UnitManager::UnitManager(Uint32 maxSize)
	:mPool(maxSize, sizeof(Unit))
{
}

void UnitManager::cleanup()
{

 	for (std::map<UnitID, Unit*>::iterator unit = mUnitMap.begin(); unit != mUnitMap.end(); ++unit)
	{
		deleteUnit(unit->second->getID());
	}

}

Unit* UnitManager::createUnit(const Sprite& sprite, bool shouldWrap, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/, const UnitID& id)
{
	Unit* pUnit = NULL;

	Byte* ptr = mPool.allocateObject();
	if (ptr != NULL)
	{


		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//create unit
		pUnit = new (ptr)Unit(sprite, theID, PLAYER_CONTROLLED_STATE);//placement new

		//place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some components
		ComponentManager* pComponentManager = gpGame->getComponentManager();
		ComponentID id = pComponentManager->allocatePositionComponent(posData,shouldWrap);
		pUnit->mPositionComponentID = id;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(id);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;

	}

	return pUnit;
}

Unit * UnitManager::createBullet(bool shouldWrap, const PositionData & posData, const PhysicsData & physicsData, const UnitID & id)
{
	Unit* pUnit = NULL;

	Byte* ptr = mPool.allocateObject();
	if (ptr != NULL)
	{


		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//create unit
		pUnit = new (ptr)Unit(*mpBulletSprite, theID, BULLET_STATE);//placement new

											 //place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some components
		ComponentManager* pComponentManager = gpGame->getComponentManager();
		ComponentID id = pComponentManager->allocatePositionComponent(posData, shouldWrap);
		pUnit->mPositionComponentID = id;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(id);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;

		pUnit->setTag("Bullet");

	}

	return pUnit;
}

Unit * UnitManager::createPowerUp(const Sprite & sprite, bool shouldWrap, const PositionData & posData, const PhysicsData & physicsData, const UnitID & id)
{
	Unit* pUnit = NULL;

	Byte* ptr = mPool.allocateObject();
	if (ptr != NULL)
	{


		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//create unit
		pUnit = new (ptr)Unit(sprite, theID, POWERUP_STATE);//placement new

											 //place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some components
		ComponentManager* pComponentManager = gpGame->getComponentManager();
		ComponentID id = pComponentManager->allocatePositionComponent(posData, shouldWrap);
		pUnit->mPositionComponentID = id;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(id);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;

		pUnit->setTag("PowerUP");

	}

	return pUnit;
}


Unit* UnitManager::createPlayerUnit(const Sprite& sprite, bool shouldWrap /*= true*/, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/)
{
	return createUnit(sprite, shouldWrap, posData, physicsData, PLAYER_UNIT_ID);
}

Unit * UnitManager::createPlayer2Unit(const Sprite & sprite, bool shouldWrap /*= true*/, const PositionData & posData /*= ZERO_POSITION_DATA*/, const PhysicsData & physicsData /*= ZERO_PHYSICS_DATA*/)
{
	return createUnit(sprite, shouldWrap, posData, physicsData, PLAYER2_UNIT_ID);
}


Unit* UnitManager::createRandomUnit(const Sprite& sprite)
{
	Grid* grid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	GridGraph* gridGraph = dynamic_cast<GameApp*>(gpGame)->getGridGraph();
	Vector2D randomNodeLocation = grid->getULCornerOfSquare(gridGraph->getRandomNonWallNode()->getId());


	Unit* pUnit = createUnit(sprite, true, PositionData(randomNodeLocation, 0));
	if (pUnit != NULL)
	{
		UnitID playerId = PLAYER_UNIT_ID;
		pUnit->setShowTarget(false);
		pUnit->setSteering(Steering::PATHSEEK, NULL, playerId);
	
	}
	return pUnit;
}

Unit* UnitManager::getUnit(const UnitID& id) const
{
	auto it = mUnitMap.find(id);
	if (it != mUnitMap.end())//found?
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

void UnitManager::setToDeleteUnit(UnitID id)
{
	getUnit(id)->setToBeDeleted();
}

void UnitManager::deleteUnit(const UnitID& id)
{
	auto it = mUnitMap.find(id);
	if (it != mUnitMap.end())//found?
	{
		Unit* pUnit = it->second;//hold for later

		//remove from map
		mUnitMap.erase(it);

		//remove components
		ComponentManager* pComponentManager = gpGame->getComponentManager();
		pComponentManager->deallocatePhysicsComponent(pUnit->mPhysicsComponentID);
		pComponentManager->deallocatePositionComponent(pUnit->mPositionComponentID);
		pComponentManager->deallocateSteeringComponent(pUnit->mSteeringComponentID);

		//call destructor
		pUnit->~Unit();

		//free the object in the pool
		mPool.freeObject((Byte*)pUnit);
	}
}

void UnitManager::deleteRandomUnit()
{
	if (mUnitMap.size() >= 1)
	{
		Uint32 target = rand() % mUnitMap.size();
		if (target == 0)//don't allow the 0th element to be deleted as it is the player unit
		{
			target = 1;
		}
		Uint32 cnt = 0;
		for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it, cnt++)
		{
			if (cnt == target)
			{
				deleteUnit(it->first);
				break;
			}
		}
	}
}

void UnitManager::drawAll() const
{
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		it->second->draw();
	}
}

void UnitManager::updateAll(float elapsedTime)
{
	CheckGameEnd();
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		it->second->update(elapsedTime);
		it->second->updateTarget();
	}
	deleteUnitsFromDeletionVector();
}

void UnitManager::deleteUnitsFromDeletionVector()
{
	std::map<UnitID, Unit*> mUnitMapClone = getUnitMap();

	for (std::map<UnitID, Unit*>::iterator unit = mUnitMapClone.begin(); unit != mUnitMapClone.end(); ++unit)
	{
		if (unit->second->getToBeDeleted())
		{
			unit->second->getStateMachine()->cleanupStates();
			gpGame->getUnitManager()->deleteUnit(unit->second->getID());
		}

	}
}

void UnitManager::CheckGameEnd()
{
	if (!mGameOver1 && !mGameOver2)
	{
		if (getPlayerUnit()->getPlayerHealth() == 0)
		{
			mGameOver1 = true;
		}
		if (getPlayer2Unit()->getPlayerHealth() == 0)
		{
			mGameOver2 = true;
		}
	}
	else
	{
		string toDisplay;
		string toDisplay2;

		if (mGameOver1)
		{
			toDisplay = "Game Over: Player 2 Wins";
			toDisplay2 = "Press ESC to exit";
		}
		else if (mGameOver2)
		{
			toDisplay = "Game Over: Player 1 Wins";
			toDisplay2 = "Press ESC to exit";
		}
		gpGame->getGraphicsSystem()->writeText(*gpGame->getGraphicsSystem()->getBackBuffer(), *(gpGame->getFont()), 350, 180, toDisplay, BLACK_COLOR);
		gpGame->getGraphicsSystem()->writeText(*gpGame->getGraphicsSystem()->getBackBuffer(), *(gpGame->getFont()), 350, 250, toDisplay2, BLACK_COLOR);
	}
}
