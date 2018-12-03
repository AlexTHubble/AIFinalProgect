#ifndef PLAYER_ROTATE_MESSAGE_H
#define PLAYER_ROTATE_MESSAGE_H

#include "GameMessage.h"
#include "UnitManager.h"

class PlayerRotateMessage : public GameMessage
{
public:
	PlayerRotateMessage(Player playerToRotate, Direction direction);
	~PlayerRotateMessage();


	void process();

private:
	Player mPlayerToRotate;
	Direction mDirection;
};

#endif // !PLAYER_ROTATE_MESSAGE_H
