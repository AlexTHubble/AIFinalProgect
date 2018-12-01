#ifndef PATHFINDING_DEBUG_CONTENT_H
#define PATHFINDING_DEBUG_CONTENT_H

#include "DebugContent.h"

class GridPathfinder;

class PathfindingDebugContent :public DebugContent
{
public:
	PathfindingDebugContent(GridPathfinder* pPathfinder);
	~PathfindingDebugContent() {};

	std::string getDebugString();

private:
	GridPathfinder* mpPathfinder;
};

#endif // !PATHFINDING_DEBUG_CONTENT_H
