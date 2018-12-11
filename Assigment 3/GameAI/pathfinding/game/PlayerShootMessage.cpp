#include "PlayerShootMessage.h"
#include "Game.h"

PlayerShootMessage::PlayerShootMessage(Player playerShooting)
	:GameMessage(PLAYER_FIRE_MESSAGE)
{
	mPlayerShooting = playerShooting;
}

PlayerShootMessage::~PlayerShootMessage()
{
}

void PlayerShootMessage::process()
{
	Unit* player1 = gpGame->getUnitManager()->getPlayerUnit();
	Unit* player2 = gpGame->getUnitManager()->getPlayer2Unit();

	StateMachine* player1StateMachine = player1->getStateMachine();
	StateMachine* player2StateMachine = player2->getStateMachine();
	switch (mPlayerShooting)
	{

	case P1:
		player1StateMachine->handleFireInput();
		break;
	case P2:
		player2StateMachine->handleFireInput();
		break;
	default:
		std::cout << "ERROR: No player set to shooting" << std::endl;
		break;
	}
}
