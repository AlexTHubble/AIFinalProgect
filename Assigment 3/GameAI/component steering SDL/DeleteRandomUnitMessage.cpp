#include "DeleteRandomUnitMessage.h"
#include "Unit.h"
#include "UnitManager.h"
#include "SpriteManager.h"

DeleteRandomUnitMessage::DeleteRandomUnitMessage(UnitManager * unitManager)
	:GameMessage(DELETE_RANDOM_ENEMY)
{
	mpUnitManager = unitManager;
}

DeleteRandomUnitMessage::~DeleteRandomUnitMessage()
{
}

void DeleteRandomUnitMessage::process()
{
	mpUnitManager->deleteRandomUnit();
}
