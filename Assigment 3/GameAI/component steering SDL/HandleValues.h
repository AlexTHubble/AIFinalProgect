#pragma once

#include "GameMessage.h"
#include "Game.h"
#include "FlockSteering.h"

class HandleValue :public GameMessage
{
public:
	HandleValue(Flock* steeringToLoadTo, bool isSaving);
	~HandleValue();

	void process();
private:
	void loadValues();
	void saveValues();

	Flock * mpFlockSteering;
	string mFileName = "FlockValues.txt";
	bool mIsSaving;


};