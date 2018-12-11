
#include <sstream>
#include <ctime>
#include <cstdlib>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Font.h"
#include <Timer.h>
#include "Defines.h"
#include "UnitManager.h"
#include "ComponentManager.h"

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;
const Uint32 MAX_UNITS = 100;

Game::Game()
	:mpGraphicsSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mShouldExit(false)
	,mpFont(NULL)
	,mLoopTargetTime(0.0f)
	,mpUnitManager(NULL)
	,mpComponentManager(NULL)
{
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	srand((UINT)time(0));//seed random number generator

	mShouldExit = false;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;


	//create and init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();
	bool goodGraphics = mpGraphicsSystem->init(WIDTH, HEIGHT);
	if (!goodGraphics)
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager(mpGraphicsSystem);
	mpSpriteManager = new SpriteManager();

	mpComponentManager = new ComponentManager(MAX_UNITS);
	mpUnitManager = new UnitManager(MAX_UNITS);

	//load background & arrow 
	//mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID, "wallpaper.bmp");
	mpGraphicsBufferManager->loadBuffer(mEnemyIconBufferID, "enemy-arrow.png");

	//load Font
	mpFont = new Font("cour.ttf", 24);

	//Setup sprite
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer(mEnemyIconBufferID);
	Sprite* pEnemyArrow = NULL;
	if (pAIBuffer != NULL)
	{
		pEnemyArrow = mpSpriteManager->createAndManageSprite(AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, (float)pAIBuffer->getWidth(), (float)pAIBuffer->getHeight());
	}

	//Create p1
	Unit* pPlayer1 = mpUnitManager->createPlayerUnit(*pEnemyArrow);
	pPlayer1->getPositionComponent()->setPosition(Vector2D(300, 300));

	//Create p2
	Unit* pPlayer2 = mpUnitManager->createPlayer2Unit(*pEnemyArrow);
	pPlayer2->getPositionComponent()->setPosition(Vector2D(500, 300));

	Unit* pBulletTest = mpUnitManager->createBullet(*pEnemyArrow);
	pBulletTest->getPositionComponent()->setPosition(Vector2D(500, 100));

	return true;
}

void Game::cleanup()
{

	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	//cleanup font
	delete mpFont;
	mpFont = NULL;

	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;

	mpUnitManager->cleanup();
	delete mpUnitManager;
	mpUnitManager = NULL;
	delete mpComponentManager;
	mpComponentManager = NULL;
}

void Game::beginLoop()
{
	mpLoopTimer->start();

	//draw background
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite( BACKGROUND_SPRITE_ID );
	mpGraphicsSystem->draw(*pBackgroundSprite, 0.0f, 0.0f);
}

const float TARGET_ELAPSED_MS = LOOP_TARGET_TIME / 1000.0f;

void Game::processLoop()
{
	mpUnitManager->updateAll(TARGET_ELAPSED_MS);
	mpComponentManager->update(TARGET_ELAPSED_MS);

	//draw units
	mpUnitManager->drawAll();

	mpGraphicsSystem->swap();
}

bool Game::endLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed( mLoopTargetTime );
	return mShouldExit;
}


float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

float mapRotationToRange( float rotation, float low, float high )
{
	while( rotation < low )
	{
		rotation += ( 2.0f * (float)PI );
	}

	while( rotation > high )
	{
		rotation -= ( 2.0f * (float)PI );
	}
	return rotation;
}
