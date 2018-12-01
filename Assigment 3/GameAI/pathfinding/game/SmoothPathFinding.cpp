#include "SmoothPathFinding.h"
#include "DijsktraPathfinder.h"
#include "PathSmoothing.h"
#include "GridGraph.h"

SmoothPathFinding::SmoothPathFinding(Graph * pGraph)
	:Dijsktra(dynamic_cast<GridGraph*>(pGraph), true)
{
}

SmoothPathFinding::~SmoothPathFinding()
{
}

Path * SmoothPathFinding::FindPath(Node * pFrom, Node * pTo)
{
	//Path
	Path* pPath;
	//PathSmoothing
	PathSmoothing* pathSmoothing = new PathSmoothing();
	//A* Pathfinding
	pPath = findPath(pFrom, pTo);
	//Smooth path
	pPath = pathSmoothing->SmoothPath(mpGraph, pPath);
	//Return Smooth Path

	delete pathSmoothing;
	return pPath;
}
