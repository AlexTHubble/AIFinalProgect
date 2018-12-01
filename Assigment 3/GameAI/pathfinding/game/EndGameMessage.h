#ifndef END_GAME_MESSAGE_H
#define END_GAME_MESSAGE_H

#include "GameMessage.h"
#include "Game.h"

class EndGameMessage :public GameMessage
{
public:
	EndGameMessage();
	~EndGameMessage();

	void process();

private:

};

#endif // !END_GAME_MESSAGE_H