#ifndef NODE_H
#define NODE_H

#include <map>
#include <Trackable.h>
#include "Connection.h"
#include "Path.h"

const int BAD_NODE_ID = -1;
#define NODE_ID int

using namespace std;

class Node :public Trackable
{
public:
	Node(const NODE_ID& id);
	Node();
	virtual ~Node();


	int getCost() { return mCost; };
	void setCost(int newCost) { mCost = newCost; };
	//void setConnection(Connection* newConnection) { mConnection = newConnection; };
	//Connection* getConnection() { return mConnection; };
	void setPreviousNode(Node* newNode) { mPreviousNode = newNode; };
	Node* getPreviousNode() { return mPreviousNode; };
	Path* addFoundPath(NODE_ID toNode, Path* path);
	Path* getPreviousPath(NODE_ID toNode);

	const NODE_ID& getId() const { return mId; };

private:
	const NODE_ID mId;
	int mCost = 1;
	Node *mPreviousNode;

	//map<int, Path*> foundPaths;
	map<NODE_ID, Path*> foundPaths;
};


#endif // !NODE_H