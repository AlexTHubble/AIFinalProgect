#pragma once

#include "GameMessage.h"
#include "Game.h"

class ExitGameMessage :public GameMessage
{
public:
	ExitGameMessage();
	~ExitGameMessage();

	void process();
private:
	UnitManager * mpUnitManager;

};
