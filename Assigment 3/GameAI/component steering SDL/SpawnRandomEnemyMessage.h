#pragma once

#include "GameMessage.h"
//#include "Vector2D.h"
#include "Game.h"

class SpawnRandomEnemyMessage :public GameMessage
{
public:
	SpawnRandomEnemyMessage(UnitManager* unitManager, SpriteManager* spriteManager, IDType spriteId, int numberToSpawn);
	~SpawnRandomEnemyMessage();

	void process();

private:
	//Vector2D mPos;
	UnitManager* mpUnitManager;
	SpriteManager* mpSpriteManager;
	IDType mAiSpriteId;
	int mNumberToSpawn = 1;
};