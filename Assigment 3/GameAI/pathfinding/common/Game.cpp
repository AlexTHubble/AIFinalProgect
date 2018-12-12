
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

	mpFileSystem = new FileSystem(gFileFolder, gFileName);
	mpFileSystem->loadFiles();
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
	mpGraphicsBufferManager->loadBuffer(mP1IconBufferID, "arrow.png");
	mpGraphicsBufferManager->loadBuffer(mP2IconBufferID, "enemy-arrow.png");
	mpGraphicsBufferManager->loadBuffer(mBulletIconBufferID, "target.png");
	mpGraphicsBufferManager->loadBuffer(mSpeedIconBufferID, "speed.png");

	//load Font
	mpFont = new Font("cour.ttf", 24);

	//Setup sprite
	GraphicsBuffer* pP1Buffer = mpGraphicsBufferManager->getBuffer(mP1IconBufferID);
	Sprite* pP1Tank = NULL;
	if (pP1Buffer != NULL)
	{
		pP1Tank = mpSpriteManager->createAndManageSprite(P1_ICON_ID, pP1Buffer, 0, 0, (float)pP1Buffer->getWidth(), (float)pP1Buffer->getHeight());
	}
	//Setup sprite
	GraphicsBuffer* pP2Buffer = mpGraphicsBufferManager->getBuffer(mP2IconBufferID);
	Sprite* pP2Tank = NULL;
	if (pP2Buffer != NULL)
	{
		pP2Tank = mpSpriteManager->createAndManageSprite(P2_ICON_ID, pP2Buffer, 0, 0, (float)pP2Buffer->getWidth(), (float)pP2Buffer->getHeight());
	}
	//Setup sprite
	GraphicsBuffer* pBulletBuffer = mpGraphicsBufferManager->getBuffer(mBulletIconBufferID);
	Sprite* pBullet = NULL;
	if (pBulletBuffer != NULL)
	{
		pBullet = mpSpriteManager->createAndManageSprite(BULLET_ICON_ID, pBulletBuffer, 0, 0, (float)pBulletBuffer->getWidth(), (float)pBulletBuffer->getHeight());
	}
	//Setup sprite
	GraphicsBuffer* pSpeedBuffer = mpGraphicsBufferManager->getBuffer(mSpeedIconBufferID);
	Sprite* pSpeed = NULL;
	if (pSpeedBuffer != NULL)
	{
		pSpeed = mpSpriteManager->createAndManageSprite(SPEED_ICON_ID, pSpeedBuffer, 0, 0, (float)pSpeedBuffer->getWidth(), (float)pSpeedBuffer->getHeight());
	}

	//Create p1
	Unit* pPlayer1 = mpUnitManager->createPlayerUnit(*pP1Tank);
	pPlayer1->getPositionComponent()->setPosition(Vector2D(mpFileSystem->getP1StartX(), mpFileSystem->getP1StartY()));
	pPlayer1->setTag("Player1");

	//Create p2
	Unit* pPlayer2 = mpUnitManager->createPlayer2Unit(*pP2Tank);
	pPlayer2->getPositionComponent()->setPosition(Vector2D(mpFileSystem->getP2StartX(), mpFileSystem->getP2StartY()));
	pPlayer2->setTag("Player2");

	//Create Buff
	Unit* pBuff = mpUnitManager->createPowerUp(*pSpeed);

	mpUnitManager->setBulletSprite(pBullet);

	return true;
}

void Game::cleanup()
{

	delete mpFileSystem;
	mpFileSystem = NULL;

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
