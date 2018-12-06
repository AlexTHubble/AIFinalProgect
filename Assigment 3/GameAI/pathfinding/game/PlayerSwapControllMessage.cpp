#include "PlayerSwapControllMessage.h"
#include "Game.h"

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
	Unit* player = gpGame->getUnitManager()->getPlayerUnit();

	if (player != nullptr)
	{
		StateMachine* playerStateMachine = player->getStateMachine();
		switch (mPlayerToSwap)
		{
		case P1:
			std::cout << "Player 1 swaped controll" << std::endl;
			playerStateMachine->handleSwapInput();
			break;
		case P2:
			std::cout << "Player 2 swapped controll" << std::endl;
			break;
		default:
			std::cout << "ERROR: No player set to swap" << std::endl;
			break;
		}
	}


}
