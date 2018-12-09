#include "Graph.h"
#include "Connection.h"
#include "Grid.h"
#include "GameApp.h"

Graph::Graph()
{
}

Graph::~Graph()
{
	for( unsigned int i=0; i<mNodes.size(); i++ )
	{
		delete mNodes[i];
	}

	for( unsigned int i=0; i<mConnections.size(); i++ )
	{
		delete mConnections[i];
	}
}

void Graph::init()
{
}

std::vector<Connection*> Graph::getConnections( const Node& from )
{
	return getConnections( from.getId() );
}

std::vector<Connection*> Graph::getConnections( const NODE_ID& fromId )
{
	static std::vector<Connection*> sEmpty;
	
	std::map< NODE_ID, std::vector<Connection*> >::iterator iter = mConnectionMap.find( fromId );
	if( iter == mConnectionMap.end() )
	{
		return sEmpty;
	}
	else
	{
		return iter->second;
	}
}

Node* Graph::getNode( int index )
{
	if( index < (int)mNodes.size() )
	{
		return mNodes[index];
	}
	else
	{
		return NULL;
	}
}

Node * Graph::getNodeClosestToLocation(Vector2D targetLocation)
{
	Node* closestNode = mNodes[0];
	float closestDistance = 99999; //Set to something arbitraily large to represent infinity
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	Grid* pGrid = pGame->getGrid();

	for (int i = 0; i < mNodes.size(); i++)
	{
		Vector2D nodeLocation = pGrid->getULCornerOfSquare(mNodes[i]->getId());
		Vector2D direction = targetLocation - nodeLocation;
		float distance = direction.getLength();


		if (distance < closestDistance)
		{
			closestNode = mNodes[i];
			closestDistance = distance;
		}
	}

	return closestNode;
}

