#ifndef PATH_H
#define PATH_H

#include <vector>
#include <Trackable.h>

class Node;
using namespace std;

class Path :public Trackable
{
public:
	Path();
	~Path();

	Node* peekNode(int index) const;
	Node* peekNextNode() const;
	Node* getAndRemoveNextNode();
	bool containsNode(Node* pNode);
	int getNumNodes() const { return mNodes.size(); };

	void addNode(Node* pNode);
	void outputMapToConsole();

private:
	std::vector<Node*> mNodes;

};


#endif // !PATH_H