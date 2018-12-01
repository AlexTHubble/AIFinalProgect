#include "SpawnRandomEnemyMessage.h"
#include "Unit.h"
#include "UnitManager.h"
#include "SpriteManager.h"

SpawnRandomEnemyMessage::SpawnRandomEnemyMessage( UnitManager* unitManager, SpriteManager* spriteManager, IDType spriteId, int numberToSpawn)
	:GameMessage(SPAWN_RANDOM_ENEMEY)
{
	mpUnitManager = unitManager;
	mpSpriteManager = spriteManager;
	mAiSpriteId = spriteId;
	mNumberToSpawn = numberToSpawn;
}

SpawnRandomEnemyMessage::~SpawnRandomEnemyMessage()
{
}

void SpawnRandomEnemyMessage::process()
{
	std::map<UnitID, Unit*> mUnitMap = mpUnitManager->getUnitMap();

	for (std::map<UnitID, Unit*>::iterator unit = mUnitMap.begin(); unit != mUnitMap.end(); ++unit)
	{
		mpUnitManager->deleteUnit(unit->second->getID());
	}


	for(int i = 0; i < mNumberToSpawn; i++)
		Unit* pUnit = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(mAiSpriteId));
}
