#ifndef PLAYER_SWAP_CONTROLL_MESSAGE_H
#define PLAYER_SWAP_CONTROLL_MESSAGE_H

#include "GameMessage.h"
#include "UnitManager.h"

class PlayerSwapControll : public GameMessage
{
public:
	PlayerSwapControll(Player playerToSwap);
	~PlayerSwapControll();


	void process();

private:
	Player mPlayerToSwap;
};

#endif // !PLAYER_SWAP_CONTROLL_MESSAGE_H
