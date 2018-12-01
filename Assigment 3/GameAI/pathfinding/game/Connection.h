#ifndef CONNECTION_H
#define CONNECTION_H

#include <Trackable.h>
class Node;

class Connection :public Trackable
{
public:
	Connection(Node* pFrom, Node* pTo, float cost);
	~Connection();

	inline Node* getFromNode() const { return mpFrom; };
	inline Node* getToNode() const { return mpTo; };
	inline float getCost() const { return mCost; };

	void setToNode(Node* node) { mpTo = node; };
	void setFromNode(Node* node) { mpFrom = node; };

private:
	Node* mpFrom;
	Node* mpTo;
	float mCost;
};

#endif // !CONNECTION_H
