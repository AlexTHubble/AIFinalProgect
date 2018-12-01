#include "Node.h"

Node::Node()
:mId(BAD_NODE_ID)
{
	mCost = 0;
}

Node::Node( const NODE_ID& id )
:mId(id)
{
	mCost = 0;
}

Node::~Node()
{
	//Empty out found paths
	for (std::map<NODE_ID, Path*>::iterator nodeForDeletion = foundPaths.begin(); nodeForDeletion != foundPaths.end(); ++nodeForDeletion)
	{
		delete nodeForDeletion->second;
		nodeForDeletion->second = nullptr;
	}
	foundPaths.clear();
}

Path* Node::addFoundPath(NODE_ID toNode, Path * path)
{

	Path * newPath = new Path;

	//Copyies the pointer contents over to the new path
	
	for(int i = 0; i < path->getNumNodes(); i++)
	{
		Node* tempNode = path->peekNode(i);
		newPath->addNode(tempNode);
	}

	foundPaths.insert(pair<NODE_ID, Path*>(toNode, newPath));

	return newPath;


}

Path * Node::getPreviousPath(NODE_ID toNode)
{

	if (foundPaths.find(toNode) != foundPaths.end())
	{
		if (foundPaths.find(toNode)->second->getNumNodes() > 0)
		{
			Path* returnPath = foundPaths.find(toNode)->second;
			return returnPath;
		}
		else
		{
			return nullptr;
		}

	}
	else
	{
		return nullptr;
	}

	
 }
