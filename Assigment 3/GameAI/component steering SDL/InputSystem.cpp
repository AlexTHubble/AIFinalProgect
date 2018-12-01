#include "InputSystem.h"

InputSystem::InputSystem(SpriteManager* spriteManager, UnitManager* unitManager, IDType aiSpriteID)
{
	mpSpriteManager = spriteManager;
	mpUnitManager = unitManager;
	mAiSpriteID = aiSpriteID;
}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::init()
{
	mpMessageManager = new GameMessageManager();
}

void InputSystem::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;
}

void InputSystem::update()
{
	SDL_PumpEvents();
	int x, y;
	SDL_GetMouseState(&x, &y);

	SDL_PumpEvents();

	{
		//get keyboard state
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_A])
		{
			GameMessage* pMessage = new SpawnRandomEnemyMessage(mpUnitManager,mpSpriteManager,mAiSpriteID, 10);
			mpMessageManager->addMessage(pMessage, 0);
		}

		if (state[SDL_SCANCODE_L])
		{
			for (std::map<UnitID, Flock*>::iterator unit = mFlockMap.begin(); unit != mFlockMap.end(); unit++)
			{
				GameMessage* pMessage = new HandleValue(unit->second, false);
				mpMessageManager->addMessage(pMessage, 0);
			}

		}

		if (state[SDL_SCANCODE_S])
		{
			for (std::map<UnitID, Flock*>::iterator unit = mFlockMap.begin(); unit != mFlockMap.end(); unit++)
			{
				GameMessage* pMessage = new HandleValue(unit->second, true);
				mpMessageManager->addMessage(pMessage, 0);
			}

		}

		if (state[SDL_SCANCODE_D])
		{
			GameMessage* pMessage = new DeleteRandomUnitMessage(mpUnitManager);
			mpMessageManager->addMessage(pMessage, 0);
		}

		//if escape key was down then exit the loop
		if (state[SDL_SCANCODE_ESCAPE])
		{

			GameMessage* pMessage = new ExitGameMessage();
			mpMessageManager->addMessage(pMessage, 0);
		}
	}

	mpMessageManager->processMessagesForThisframe();
}
