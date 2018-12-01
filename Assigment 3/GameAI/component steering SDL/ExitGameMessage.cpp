#include "ExitGameMessage.h"

ExitGameMessage::ExitGameMessage()
	:GameMessage(END_GAME)
{
}

ExitGameMessage::~ExitGameMessage()
{
}

void ExitGameMessage::process()
{
	gpGame->endGame();
}
