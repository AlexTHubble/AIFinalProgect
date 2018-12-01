#include "PathSmoothing.h"
#include "GameApp.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Path.h"
#include <math.h>

PathSmoothing::PathSmoothing()
{
}

PathSmoothing::~PathSmoothing()
{
}


Path* PathSmoothing::SmoothPath(Graph * pGraph, Path * pPath)
{
	//If the path is two nodes long, then smoothing is not needed
	//So return the path
	if (pPath->getNumNodes() == 2)
	{
		return pPath;
	}
	//Create output path
	Path* smoothPath = new Path();
	//We start at 3rd nos in cause we assum first two nodes are adjacent
	//and will pass the Raycast
	int pathIndex = 2;
	//Add first node to path
	smoothPath->addNode(pPath->peekNode(0));

	//Loop until we find the last item in the smoothPath
	while (pathIndex < pPath->getNumNodes() - 1)
	{
		//Do Raycast
		//If it doesn't pass
		if (RaycastToTarget(smoothPath->peekNode(smoothPath->getNumNodes() - 1), pPath->peekNode(pathIndex)))
		{
			//If Raycast does not clear, add the last node that
			//passed to the output list
			smoothPath->addNode(pPath->peekNode(pathIndex - 1));
		}
		//Increment to next node
		pathIndex++;
	}	
	//We've reached the end of the path list, ass the
	//end node to the output and return it
	smoothPath->addNode(pPath->peekNode(pPath->getNumNodes() - 1));
	return smoothPath;
}

bool PathSmoothing::RaycastToTarget(Node * current, Node * target)
{
	//Get Grid
	Grid* grid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	//Get point variables
	float x0 = grid->getULCornerOfSquare(current->getId()).getX();
	float y0 = grid->getULCornerOfSquare(current->getId()).getY();
	float x1 = grid->getULCornerOfSquare(target->getId()).getX();
	float y1 = grid->getULCornerOfSquare(target->getId()).getY();
	
	//
	float dx = abs(x1 - x0);
	float dy = abs(y1 - y0);
	float x = x0;
	float y = y0;
	float n = 1 + dx + dy;
	float x_inc = (x1 > x0) ? 1 : -1;
	float y_inc = (y1 > y0) ? 1 : -1;
	float error = dx - dy;
	dx *= 2;
	dy *= 2;
	

	for (; n > 0; --n)
	{
		//If any walls intersect with Raycast between points, return Raycast hit as true
		if (grid->getValueAtPixelXY(x, y))
		{
			//Raycast hit a wall block
			return true;
		}
		
		if (error > 0)
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}

	return false;
}




