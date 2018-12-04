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
	TankMovement * tankMovment = gpGame->getUnitManager()->getPlayerUnit()->Movement();

	switch (mPlayerToRotate) //This handles bolth players rotation and direction based on input
	{
	case P1: //If player 1
		switch (mDirection) //Handles the direction
		{
		case Left: //If left
			std::cout << "Player 1 rotating left" << std::endl;
			tankMovment->RotateCounterClockwise();
			break;
		case Right: //If right
			std::cout << "Player 1 rotating right" << std::endl;
			tankMovment->RotateClockwise();
			break;
		case Stop: //If no rotation input
			std::cout << "Player 1 No Rotate" << std::endl;
			tankMovment->ZeroOutRotate();
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
			break;
		case Right: //If right
			std::cout << "Player 2 rotating right" << std::endl;
			break;
		case Stop: //If no rotation input
			std::cout << "Player 2 No Rotate" << std::endl;
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
