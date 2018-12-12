#pragma once

/* Game - base class for actual application class

	Dean Lawson
	Champlain College
	2011
*/
#include <Trackable.h>
#include <Timer.h>
#include "Defines.h"
#include "../game/FileSystem.h"

class MemoryTracker;
class PerformanceTracker;
class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class Game;
class Font;
class ComponentManager;
class UnitManager;

extern PerformanceTracker* gpPerformanceTracker;
extern Game* gpGame;

const std::string gFileName = "Variables.txt";
const std::string gFileFolder = "Files/";
const IDType BACKGROUND_SPRITE_ID = 0;
const IDType TARGET_SPRITE_ID = 3;
const IDType AI_ICON_SPRITE_ID = 2;
const IDType BULLET_ICON_ID = 5;
const IDType SPEED_ICON_ID = 6;
const IDType P1_ICON_ID = 7;
const IDType P2_ICON_ID = 8;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game:public Trackable
{
public:
	Game();
	virtual ~Game();

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline Font* getFont() const { return mpFont; };
	inline void markForExit() { mShouldExit = true; };
	inline ComponentManager* getComponentManager() { return mpComponentManager; };
	inline UnitManager* getUnitManager() { return mpUnitManager; };
	inline FileSystem* getFileSystem() { return mpFileSystem; };

protected:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	ComponentManager* mpComponentManager;
	UnitManager* mpUnitManager;
	FileSystem* mpFileSystem;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	float mLoopTargetTime;
	bool mShouldExit;

	

	//should be somewhere else
	Font* mpFont;

	GraphicsBufferID mBackgroundBufferID = "background";
	GraphicsBufferID mP1IconBufferID = "player1";
	GraphicsBufferID mP2IconBufferID = "player2";
	GraphicsBufferID mBulletIconBufferID = "bullet";
	GraphicsBufferID mSpeedIconBufferID = "speed";

};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge
float mapRotationToRange( float rotation, float low, float high );

const double PI = std::atan(1.0)*4;//could proved useful!
