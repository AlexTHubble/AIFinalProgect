#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

#include <Trackable.h>

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PATH_TO_MESSAGE = 0,
	END_GAME_MESSAGE = 1,
	PLAYER_ROTATE_MESSAGE = 2,
	PLAYER_ACCLERATE_MESSAGE = 3,
	PLAYER_FIRE_MESSAGE = 4,
	PLAYER_SWAP_CONTROLL = 5
};

enum Player
{
	P1 = 0,
	P2 = 1
};

enum Direction
{
	Left = 0,
	Right = 1,
	Stop = 2
};

enum Accleration
{
	ACCELERATING = 0,
	DECCELERATING = 1,
	NONE = 2
};

class GameMessage : public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage(MessageType type);
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0;
};

#endif // !GAME_MESSAGE_H



