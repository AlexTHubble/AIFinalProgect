#include "PlayerMoveMessage.h"
#include "TankMovement.h"
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
	TankMovement * tankMovment = gpGame->getUnitManager()->getPlayerUnit()->Movement();

	switch (mPlayerMoving) //This handles bolth players rotation and direction based on input
	{

	case P1: //If player 1
	
		switch (mPlayerAccerlation) //Handles the direction
		{
		case ACCELERATING: //If accelerating
			std::cout << "Player 1 accelerating" << std::endl;
			tankMovment->MoveForward();
			break;
		case DECCELERATING: //If decelerating
			std::cout << "Player 1 decelerating" << std::endl;
			tankMovment->MoveBackwards();
			break;
		case NONE: //If no input
			std::cout << "Player 1 No Movement" << std::endl;
			tankMovment->ZeroOutMovement();
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
			std::cout << "Player 2 accerlating" << std::endl;
			break;
		case DECCELERATING: //If decelerating
			std::cout << "Player 2 declerating" << std::endl;
			break;
		case NONE: //If no input
			std::cout << "Player 2 No Movement" << std::endl;
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
