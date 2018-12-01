#ifndef DIJSKTRA_PATHFINDER_H
#define DIJSKTRA_PATHFINDER_H

#include "GridPathfinder.h"
#include <vector>

using namespace std;
class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

class Dijsktra :public GridPathfinder
{
public:
	Dijsktra(Graph* pGraph, bool Astar);
	virtual ~Dijsktra();

	Path* findPath(Node* pFrom, Node* pTo);

private:
	bool mApplyAStar = true;

};

#endif // !DIJSKTRA_PATHFINDER_H

