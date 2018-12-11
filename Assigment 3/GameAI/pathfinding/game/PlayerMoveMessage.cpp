#include "PlayerMoveMessage.h"
#include "Unit.h"

PlayerMoveMessage::PlayerMoveMessage(Player playerMoving, Accleration acceleration)
	:GameMessage(PLAYER_ACCLERATE_MESSAGE)
{
	mPlayerMoving = playerMoving;
	mPlayerAccerlation = acceleration;
}

PlayerMoveMessage::~PlayerMoveMessage()
{
}

void PlayerMoveMessage::process()
{
	Unit* player1 = gpGame->getUnitManager()->getPlayerUnit();
	Unit* player2 = gpGame->getUnitManager()->getPlayer2Unit();

	if (player1 != nullptr && player2 != nullptr)
	{
		StateMachine* player1StateMachine = player1->getStateMachine();
		StateMachine* player2StateMachine = player2->getStateMachine();
		switch (mPlayerMoving) //This handles bolth players rotation and direction based on input
		{

		case P1: //If player 1

			switch (mPlayerAccerlation) //Handles the direction
			{
			case ACCELERATING: //If accelerating
				player1StateMachine->handleMovmentInput(true, false);
				break;
			case NONE: //If no input
				player1StateMachine->handleMovmentInput(false, false);
				break;
			default: //ERROR
				std::cout << "ERROR: player 1 has no accleration" << std::endl;
				break;
			}
			break;
		case P2: //If player 2
			switch (mPlayerAccerlation) //Handles direction
			{
			case ACCELERATING: //If accerlating
				player2StateMachine->handleMovmentInput(true, false);
				break;
			case NONE: //If no input
				player2StateMachine->handleMovmentInput(false, false);
				break;
			default: //ERROR
				std::cout << "ERROR: Player 2 has no accleration assigned" << std::endl;
				break;
			}
			break;
		default: //ERROR
			std::cout << "ERROR: No player set to rotate" << std::endl;
			break;
		}
	}
}
