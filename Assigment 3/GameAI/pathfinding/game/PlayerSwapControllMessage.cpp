#include "PlayerSwapControllMessage.h"

PlayerSwapControll::PlayerSwapControll(Player playerToSwap)
	:GameMessage(PLAYER_SWAP_CONTROLL)
{
	mPlayerToSwap = playerToSwap;
}

PlayerSwapControll::~PlayerSwapControll()
{
}

void PlayerSwapControll::process()
{
	switch (mPlayerToSwap)
	{
	case P1:
		std::cout << "Player 1 swaped controll" << std::endl;
		break;
	case P2:
		std::cout << "Player 2 swapped controll" << std::endl;
		break;
	default:
		std::cout << "ERROR: No player set to swap" << std::endl;
		break;
	}
}
