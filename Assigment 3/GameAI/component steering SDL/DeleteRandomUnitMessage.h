#pragma once

#include "GameMessage.h"
//#include "Vector2D.h"
#include "Game.h"

class DeleteRandomUnitMessage :public GameMessage
{
public:
	DeleteRandomUnitMessage(UnitManager* unitManager);
	~DeleteRandomUnitMessage();

	void process();
private:
	UnitManager * mpUnitManager;

};
