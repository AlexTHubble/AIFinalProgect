#ifndef PLAYER_SHOOT_MESSAGE_H
#define PLAYER_SHOOT_MESSAGE_H

#include "GameMessage.h"
#include "UnitManager.h"

class PlayerShootMessage : public GameMessage
{
public:
	PlayerShootMessage(Player playerShooting);
	~PlayerShootMessage();


	void process();

private:
	Player mPlayerShooting;
};

#endif // !PLAYER_SHOOT_MESSAGE_H
