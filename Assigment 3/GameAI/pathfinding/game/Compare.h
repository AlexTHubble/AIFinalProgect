#ifndef COMPARE_H
#define COMPARE_H

#include "Node.h"

class Compare
{
public:
	bool operator() (Node* left, Node* right)
	{
		return left->getCost() > right->getCost();
	}
};

#endif // !COMPARE_H