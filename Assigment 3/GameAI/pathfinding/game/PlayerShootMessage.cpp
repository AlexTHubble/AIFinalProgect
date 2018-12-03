#include "PlayerShootMessage.h"

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
	switch (mPlayerShooting)
	{
	case P1:
		std::cout << "Player 1 shooting" << std::endl;
		break;
	case P2:
		std::cout << "Player 2 shooting" << std::endl;
		break;
	default:
		std::cout << "ERROR: No player set to shooting" << std::endl;
		break;
	}
}
