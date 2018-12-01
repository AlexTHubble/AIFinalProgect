#include "Game.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "UnitManager.h"

PlayerMoveToMessage::PlayerMoveToMessage( const Vector2D& pos )
:GameMessage(PLAYER_MOVETO_MESSAGE)
,mPos(pos)
{
	std::cout << "Player Move To message called for position: " << pos.getX() << " , " << pos.getY() << std::endl;
}

PlayerMoveToMessage::~PlayerMoveToMessage()
{
}

void PlayerMoveToMessage::process()
{
	Unit* pPlayer = gpGame->getUnitManager()->getPlayerUnit();
	pPlayer->setSteering(Steering::ARRIVE_AND_FACE, mPos, INVALID_UNIT_ID);
	pPlayer->setShowTarget(true);
}

