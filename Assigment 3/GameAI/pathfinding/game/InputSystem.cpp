#include "InputSystem.h"
#include "GameApp.h"
#include "Unit.h"
#include "UnitManager.h"

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

		if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			static Vector2D lastPos(0.0f, 0.0f);
			Vector2D pos(x, y);
			if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
			{
				
				GameMessage* pMessage = new PathToMessage(lastPos, pos);
				mpMessageManager->addMessage(pMessage, 0);
				lastPos = pos;
			}
		}


		if (state[SDL_SCANCODE_F])
		{
			dynamic_cast<GameApp*>(gpGame)->setPathDepthFirst();
		}

		if (state[SDL_SCANCODE_D])
		{
			dynamic_cast<GameApp*>(gpGame)->setPathDijsktra();
		}

		if (state[SDL_SCANCODE_A])
		{
			dynamic_cast<GameApp*>(gpGame)->setPathAstar();
		}

		if (state[SDL_SCANCODE_S])
		{
			GameMessage* pMessage = new SpawnRandomEnemyMessage(mpUnitManager, mpSpriteManager, mAiSpriteID, 10);
			mpMessageManager->addMessage(pMessage, 0);
		}

		//if escape key was down then exit the loop
		if (state[SDL_SCANCODE_ESCAPE])
		{
			GameMessage* pMessage = new EndGameMessage();
			mpMessageManager->addMessage(pMessage, 0);
		}
	}

	mpMessageManager->processMessagesForThisframe();
}
