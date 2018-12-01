#pragma once
#include <sstream>
#include <SDL.h>


#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "GraphicsBufferManager.h"
#include "GraphicsSystem.h"
#include "GameMessageManager.h"
#include "Game.h"
#include "SpawnRandomEnemyMessage.h"
#include "DeleteRandomUnitMessage.h"
#include "HandleValues.h"
//#include "SaveValues.h"
#include "ExitGameMessage.h"
//#include "FlockSteering.h"

//#include "SpriteManager.h"
//#include "UnitManager.h"


class InputSystem : public Trackable
{
public:
	InputSystem(SpriteManager* spriteManager, UnitManager* unitManager, IDType aiSpriteID);
	~InputSystem();

	void init();
	void cleanup();
	void update();

	//void setFlockSteering(Flock *theSteering) { mpFlockSteering = theSteering; };
	void addFlockSteering(Flock *theSteering, UnitID theID) { mFlockMap.insert(std::pair<UnitID,Flock*>(theID, theSteering)); }

private:
	GameMessageManager * mpMessageManager;
	UnitManager * mpUnitManager;
	SpriteManager * mpSpriteManager;
	IDType mAiSpriteID;
	//Flock *mpFlockSteering;

	std::map<UnitID, Flock*> mFlockMap;
};