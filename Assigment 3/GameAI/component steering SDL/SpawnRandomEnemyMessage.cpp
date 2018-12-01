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

	for(int i = 0; i < mNumberToSpawn; i++)
		Unit* pUnit = mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(mAiSpriteId));
}
