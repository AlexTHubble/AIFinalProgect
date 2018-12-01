#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

#include <Trackable.h>

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	PATH_TO_MESSAGE = 1,
	SPAWN_RANDOM_ENEMEY = 2,
	END_GAME_MESSAGE = 3
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



