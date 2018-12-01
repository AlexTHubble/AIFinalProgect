#ifndef GRID_PATHFINDER_H
#define GRID_PATHFINDER_H

#include "Pathfinder.h"
class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;

class GridPathfinder :public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder(GridGraph* pGraph);
	virtual ~GridPathfinder();

	virtual Path* findPath(Node* pFrom, Node* pTo) = 0;

#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void drawVisualization(Grid* pGrid, GraphicsBuffer* pDest);
protected:
	std::vector<Node*> mVisitedNodes;
	Path* mpPath;
	GridVisualizer* mpVisualizer;
#endif

	double mTimeElapsed;
};

#endif // !GRID_PATHFINDER_H
