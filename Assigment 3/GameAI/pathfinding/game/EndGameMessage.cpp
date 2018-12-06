#include "EndGameMessage.h"
#include "Unit.h"
#include "UnitManager.h"

EndGameMessage::EndGameMessage()
	:GameMessage(END_GAME_MESSAGE)
{
}

EndGameMessage::~EndGameMessage()
{
}

void EndGameMessage::process()
{
	std::map<UnitID, Unit*> mUnitMap = gpGame->getUnitManager()->getUnitMap();

	for (std::map<UnitID, Unit*>::iterator unit = mUnitMap.begin(); unit != mUnitMap.end(); ++unit)
	{
		unit->second->getStateMachine()->cleanupStates();
		gpGame->getUnitManager()->deleteUnit(unit->second->getID());
	}

	gpGame->markForExit();
}
