#include "PlayerRotateMessage.h"
#include "TankMovement.h"
#include "Unit.h"

PlayerRotateMessage::PlayerRotateMessage(Player playerToRotate, Direction direction)
	:GameMessage(PLAYER_ROTATE_MESSAGE)
{
	mPlayerToRotate = playerToRotate;
	mDirection = direction;
}

PlayerRotateMessage::~PlayerRotateMessage()
{
}

void PlayerRotateMessage::process()
{
	Unit* player1 = gpGame->getUnitManager()->getPlayerUnit();
	Unit* player2 = gpGame->getUnitManager()->getPlayer2Unit();

	if (player1 != nullptr && player2 != nullptr)
	{
		StateMachine* player1StateMachine = player1->getStateMachine();
		StateMachine* player2StateMachine = player2->getStateMachine();
		switch (mPlayerToRotate) //This handles bolth players rotation and direction based on input
		{
		case P1: //If player 1
			switch (mDirection) //Handles the direction
			{
			case Left: //If left
				std::cout << "Player 1 rotating left" << std::endl;
				player1StateMachine->handleRotateInput(true, false);
				break;
			case Right: //If right
				std::cout << "Player 1 rotating right" << std::endl;
				player1StateMachine->handleRotateInput(false, true);
				break;
			case Stop: //If no rotation input
				std::cout << "Player 1 No Rotate" << std::endl;
				player1StateMachine->handleRotateInput(false, false);
				break;
			default: //ERROR
				std::cout << "ERROR: player 1 has no rotate direction assigned" << std::endl;
				break;
			}
			break;
		case P2: //If player 2
			switch (mDirection) //Handles direction
			{
			case Left: //If left
				std::cout << "Player 2 rotating left" << std::endl;
				player2StateMachine->handleRotateInput(true, false);
				break;
			case Right: //If right
				std::cout << "Player 2 rotating right" << std::endl;
				player2StateMachine->handleRotateInput(false, true);
				break;
			case Stop: //If no rotation input
				std::cout << "Player 2 No Rotate" << std::endl;
				player2StateMachine->handleRotateInput(false, false);
				break;
			default: //ERROR
				std::cout << "ERROR: Player 2 has no rotation assigned" << std::endl;
				break;
			}
			break;
		default: //ERROR
			std::cout << "ERROR: No player set to rotate" << std::endl;
			break;
		}
	}

}
