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
	Unit* player1 = gpGame->getUnitManager()->getPlayerUnit();
	Unit* player2 = gpGame->getUnitManager()->getPlayer2Unit();

	if (player1 != nullptr && player2 != nullptr)
	{
		StateMachine* player1StateMachine = player1->getStateMachine();
		StateMachine* player2StateMachine = player2->getStateMachine();

		switch (mPlayerToSwap)
		{
		case P1:
			std::cout << "Player 1 swaped controll" << std::endl;
			player1StateMachine->handleSwapInput();
			break;
		case P2:
			std::cout << "Player 2 swapped controll" << std::endl;
			player2StateMachine->handleSwapInput();
			break;
		default:
			std::cout << "ERROR: No player set to swap" << std::endl;
			break;
		}
	}


}
