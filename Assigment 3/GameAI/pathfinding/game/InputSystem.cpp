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
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		//*****************************Press down systems********************************
		if (event.type == SDL_KEYDOWN)
		{
			int keyCode = event.key.keysym.sym;

			if (keyCode == SDLK_ESCAPE)
			{
				//End game
				std::cout << "End game" << std::endl;
				GameMessage * pMessage = new EndGameMessage();
				mpMessageManager->addMessage(pMessage, 0);
			}
			else if (keyCode == SDLK_q)
			{
				//P1 Fire
				GameMessage * pMessage = new PlayerShootMessage(Player::P1);
				mpMessageManager->addMessage(pMessage, 0);
			}
			else if (keyCode == SDLK_e)
			{
				//P1 swap controll
				GameMessage * pMessage = new PlayerSwapControll(Player::P1);
				mpMessageManager->addMessage(pMessage, 0);
			}
			else if (keyCode == SDLK_KP_7)
			{
				//P2 fire
				GameMessage * pMessage = new PlayerShootMessage(Player::P2);
				mpMessageManager->addMessage(pMessage, 0);
			}
			else if (keyCode == SDLK_KP_9)
			{
				//P2 swaped controll
				GameMessage * pMessage = new PlayerSwapControll(Player::P2);
				mpMessageManager->addMessage(pMessage, 0);
			}

		}


	}
	//*****************************Press held systems********************************
	SDL_PumpEvents();
	{
		//get keyboard state
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		//****************************************Misc controll systems***************************************************


		//****************************************P1 controll systems***************************************************
		if (state[SDL_SCANCODE_W])
		{
			//moveP1 forward
			GameMessage* pMessage = new PlayerMoveMessage(Player::P1, Accleration::ACCELERATING);
			mpMessageManager->addMessage(pMessage, 0);
		}
		else
		{
			//Stop P1 movement
			GameMessage* pMessage = new PlayerMoveMessage(Player::P1, Accleration::NONE);
			mpMessageManager->addMessage(pMessage, 0);
		}
		
		if (state[SDL_SCANCODE_A])
		{
			//Rotate P1 left
			GameMessage* pMessage = new PlayerRotateMessage(Player::P1, Direction::Left);
			mpMessageManager->addMessage(pMessage, 0);
		}
		else if (state[SDL_SCANCODE_D])
		{
			//Rotate P1 Right
			GameMessage* pMessage = new PlayerRotateMessage(Player::P1, Direction::Right);
			mpMessageManager->addMessage(pMessage, 0);
		}
		else
		{
			//Stop Rotate P1
			GameMessage* pMessage = new PlayerRotateMessage(Player::P1, Direction::Stop);
			mpMessageManager->addMessage(pMessage, 0);
		}


		//****************************************P2 controll systems***************************************************

		if (state[SDL_SCANCODE_KP_8])
		{
			//P2 move forward
			GameMessage* pMessage = new PlayerMoveMessage(Player::P2, Accleration::ACCELERATING);
			mpMessageManager->addMessage(pMessage, 0);
		}
		else
		{
			//Stop P2 movement
			GameMessage* pMessage = new PlayerMoveMessage(Player::P2, Accleration::NONE);
			mpMessageManager->addMessage(pMessage, 0);
		}

		if (state[SDL_SCANCODE_KP_4])
		{
			//P2 rotate Left
			GameMessage* pMessage = new PlayerRotateMessage(Player::P2, Direction::Left);
			mpMessageManager->addMessage(pMessage, 0);
		}
		else if (state[SDL_SCANCODE_KP_6])
		{
			//P2 rotate right
			GameMessage* pMessage = new PlayerRotateMessage(Player::P2, Direction::Right);
			mpMessageManager->addMessage(pMessage, 0);
		}
		else
		{
			//Stop Rotate P2
			GameMessage* pMessage = new PlayerRotateMessage(Player::P2, Direction::Stop);
			mpMessageManager->addMessage(pMessage, 0);
		}



	}

	mpMessageManager->processMessagesForThisframe();
}
