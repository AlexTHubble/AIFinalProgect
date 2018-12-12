#ifndef SMOOTH_PATHFINDING_H
#define SMOOTH_PATHFINDING_H

#include "DijsktraPathfinder.h"
#include "UnitManager.h"

class Grid;
class Graph;
class Path;
class PathSmoothing;

class SmoothPathFinding : public Dijsktra
{
public:
	SmoothPathFinding(Graph* pGraph);
	~SmoothPathFinding();
	//
	Path* FindPath(Node* pFrom, Node* pTo, UnitID id);
private:
};

#endif // !SMOOTH_PATHFINDING_H

