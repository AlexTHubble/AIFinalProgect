#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <sstream>
#include <SDL.h>

#include "GameMessageManager.h"
#include "GraphicsBufferManager.h"
#include "GraphicsSystem.h"
#include "GameMessageManager.h"
#include "Game.h"
#include "EndGameMessage.h"
#include "PlayerMoveMessage.h"
#include "PlayerRotateMessage.h"
#include "PlayerShootMessage.h"
#include "PlayerSwapControllMessage.h"

class InputSystem : public Trackable
{
public:
	InputSystem(SpriteManager* spriteManager, UnitManager* unitManager, IDType aiSpriteID);
	~InputSystem();

	void init();
	void cleanup();
	void update();

	//void setFlockSteering(Flock *theSteering) { mpFlockSteering = theSteering; };


private:
	GameMessageManager * mpMessageManager;
	SpriteManager * mpSpriteManager;
	UnitManager * mpUnitManager;
	IDType mAiSpriteID;
};

#endif // !INPUT_SYSTEM_H