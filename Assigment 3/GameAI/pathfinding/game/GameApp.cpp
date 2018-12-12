#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include <Vector2D.h>
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"
#include "DepthFirstPathfinder.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"
#include "DijsktraPathfinder.h"
#include "InputSystem.h"
#include <iostream>


#include <SDL.h>
#include <fstream>
#include <vector>

const int GRID_SQUARE_SIZE = 32;
const std::string gMapFileName = "MapList.txt";
const std::string gMapFolder = "Maps/";

GameApp::GameApp()
:mpMessageManager(NULL)
,mpGrid(NULL)
,mpGridGraph(NULL)
,mpPathfinder(NULL)
,mpDebugDisplay(NULL)
{
}

GameApp::~GameApp()
{
	cleanup();
}

bool GameApp::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	mpMessageManager = new GameMessageManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpGridVisualizer = new GridVisualizer( mpGrid );
	
	loadMapList();

	loadMap(0);

	//load buffers
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent( mpPathfinder );
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );

	mpInputSystem = new InputSystem(mpSpriteManager, mpUnitManager, P1_ICON_ID);
	mpInputSystem->init();

	mpMasterTimer->start();

	return true;
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	delete mpGrid;
	mpGrid = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	delete mpInputSystem;
	mpInputSystem = NULL;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpInputSystem->update();

	mpGridVisualizer->draw( *pBackBuffer );
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
#endif

	mpDebugDisplay->draw( pBackBuffer );

	mpMessageManager->processMessagesForThisframe();

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}

void GameApp::setPathAstar()
{
	cout << "Setting to A*" << endl;

	//Deletes old pathfinder
	delete mpPathfinder;
	mpPathfinder = NULL;
	
	//Creates new pathfinder
	mpPathfinder = new Dijsktra(mpGridGraph, true);

	//Deletes old debug display
	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	//Sets up debug
	PathfindingDebugContent* pContent = new PathfindingDebugContent(mpPathfinder);
	mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);
}

void GameApp::setPathDijsktra()
{
	cout << "Setting to Dijsktra" << endl;

	//Deletes old pahtfinder
	delete mpPathfinder;
	mpPathfinder = NULL;

	//Sets up new pathfinder
	mpPathfinder = new Dijsktra(mpGridGraph, false);

	//Deletes old debug display
	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	//Sets up debug
	PathfindingDebugContent* pContent = new PathfindingDebugContent(mpPathfinder);
	mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);
}

void GameApp::setPathDepthFirst()
{
	cout << "Setting to DepthFirstSearch" << endl;

	//Deletes old pathfinder
	delete mpPathfinder;
	mpPathfinder = NULL;

	//sets up new pathfinder
	mpPathfinder = new DepthFirstPathfinder(mpGridGraph);

	//Deletes old debug display
	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	//sets up debug
	PathfindingDebugContent* pContent = new PathfindingDebugContent(mpPathfinder);
	mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);
}

//Loads all the maps into the file
void GameApp::loadMapList() 
{
	bool endOfFile = false;
	std::string data;
	ifstream file(gMapFolder + gMapFileName);

	if (file.is_open())
	{
		while (!file.eof() && !endOfFile)
		{
			getline(file, data, ';');
			if (data == "EOF")
			{
				endOfFile = true;
			}
			else
			{
				mMapList.push_back(gMapFolder + data);
			}
		}
		file.close();
	}
}

void GameApp::loadMap(int mapIndex)
{
	std::ifstream theStream(mMapList[mapIndex]);
	mpGrid->load(theStream);

	if(mpGridGraph != NULL)
		delete mpGridGraph;

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();

	if (mpPathfinder != NULL)
		delete mpPathfinder;

	mpPathfinder = new Dijsktra(mpGridGraph, true);
}
