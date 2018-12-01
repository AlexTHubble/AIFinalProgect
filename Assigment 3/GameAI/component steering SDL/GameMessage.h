#pragma once

#include "Trackable.h"
#include <string>

using namespace std;

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	SPAWN_RANDOM_ENEMEY = 1,
	DELETE_RANDOM_ENEMY = 2,
	END_GAME = 3,
	LOAD_DATA = 4,
	SAVE_DATA = 5
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
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

