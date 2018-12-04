#ifndef PLAYER_MOVE_MESSAGE_H
#define PLAYER_MOVE_MESSAGE_H

#include "GameMessage.h"
#include "UnitManager.h"
#include "Game.h"

class PlayerMoveMessage : public GameMessage
{
public:

	PlayerMoveMessage(Player playerMoving, Accleration acceleration);
	~PlayerMoveMessage();

	void process();

private:
	Player mPlayerMoving;
	Accleration mPlayerAccerlation;
};

#endif // !PLAYER_MOVE_MESSAGE_H
