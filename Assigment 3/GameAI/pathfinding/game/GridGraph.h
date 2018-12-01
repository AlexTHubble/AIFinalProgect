#ifndef GRID_GRAPH_H
#define GRID_GRAPH_H

#include "Graph.h"

class Grid;

class GridGraph :public Graph
{
public:
	GridGraph(Grid* pGrid);
	virtual ~GridGraph();

	void setGrid(Grid* pGrid) { mpGrid = pGrid; };
	void init();

	Node* getRandomNonWallNode();

private:
	Grid* mpGrid;
};

#endif // !GRID_GRAPH_H
