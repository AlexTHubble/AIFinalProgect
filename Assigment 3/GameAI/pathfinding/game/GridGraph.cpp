#include "GridGraph.h"
#include "Connection.h"
#include "Node.h"
#include "Grid.h"
#include "Game.h"
#include "Vector2D.h"
#include <vector>

GridGraph::GridGraph( Grid* pGrid )
:Graph()
,mpGrid(pGrid)
{
}

GridGraph::~GridGraph()
{
}

void GridGraph::init()
{
	if( mpGrid != NULL )
	{
		int numGridIndices = mpGrid->getGridWidth() * mpGrid->getGridHeight();

		//size the node vector
		mNodes.resize( numGridIndices, NULL );
		
		//go through all elements of the grid and make Nodes for them - also add them to Node vector
		for( int i=0; i<numGridIndices; i++ )
		{
			//create a Node for this location
			Node* pNode = new Node( i );
			//add to NodeVector
			mNodes[i] = pNode;
		}

		//go through all elements of the grid - get adjacencies and create connections for each
		for( int i=0; i<numGridIndices; i++ )
		{
			//get the Node for this location
			Node* pFromNode = mNodes[i];

			//get all the adjacencies
			std::vector<int> adjacencies = mpGrid->getAdjacentIndices( i );

			//create a vector of Connections
			std::vector<Connection*> connections;

			//go through all adjacent indices, get the nodes for them, create connections, and add to connections map
			for( unsigned int adjIndex = 0; adjIndex < adjacencies.size(); adjIndex++ )
			{
				//check for blocking terrain
				if( mpGrid->getValueAtIndex(adjacencies[adjIndex]) != BLOCKING_VALUE )
				{
					Connection* pConnection;
					Node* pToNode = mNodes[ adjacencies[adjIndex] ];//find to node

					//Get corner pos of from node and to node
					Vector2D fromNodePosition = mpGrid->getULCornerOfSquare(pFromNode->getId());
					Vector2D toNodePosition = mpGrid->getULCornerOfSquare(pToNode->getId());
					//Check if adjacent to pToNode by seeing if they line up in either the x or y position
					if (fromNodePosition.getX() == toNodePosition.getX() || fromNodePosition.getY() == toNodePosition.getY())
					{
						//If they do then they are not adjacent
						//Set connection cost to 1
						pConnection = new Connection(pFromNode, pToNode, 1.0f); //create a connection
					}
					else
					{
						//If they don't then they must be adjacent
						//Set connection cost to sqrt 2
						pConnection = new Connection(pFromNode, pToNode, sqrtf(2.0f)); //create a connection
					}

					//add connection to connection vectors
					mConnections.push_back( pConnection );
					connections.push_back( pConnection );
				}
			}

			//put temp connection vector into map
			mConnectionMap[i] = connections;
		}
	}
}

Node * GridGraph::getRandomNonWallNode()
{
	int randIndex = rand() % mNodes.size(); //Gets a random index within the node list

	if (mpGrid->getValueAtIndex(randIndex) != BLOCKING_VALUE)
	{
		return getNode(randIndex);
	}
	else
	{
		return getNode(0);
	}

	
}
