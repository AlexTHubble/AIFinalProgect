#include "Collision.h"
#include "GameApp.h"
#include "Grid.h"
#include "GridGraph.h"
#include "Unit.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::CheckForCollisions(Unit* unit)
{
	//Get Grid
	Grid* grid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	//Get grid size
	int gridSize = grid->getGridWidth() * grid->getGridHeight();
	//Search through grid for collision with any walls
	for (int i= 0; i < gridSize; i++)
	{
		if (grid->getValueAtIndex(i))
		{
			if (InsideGridBlock(i, unit))
			{
				return true;
			}
		}
	}
	return false;
}

bool Collision::InsideGridBlock(int index, Unit* unit)
{
	//Get Grid
	Grid* grid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	//Grid block UL X and Y
	float gridBlockULX = grid->getULCornerOfSquare(index).getX();
	float gridBlockULY = grid->getULCornerOfSquare(index).getY();
	float gridBlockOffset = grid->getSquareSize();
	//Get Unit Center + radius spacing
	float unitX = unit->getPositionComponent()->getPosition().getX();
	float unitY = unit->getPositionComponent()->getPosition().getY();
	float unitXOffset = 0;
	float unitYOffset = 0;

	//Check if inside blocks x position
	if (gridBlockULX < unitX && (gridBlockULX + gridBlockOffset) > unitX)
	{
		//Check if inside blocks y position
		if (gridBlockULY < unitY && (gridBlockULY + gridBlockOffset) > unitY)
		{
			//Inside grid block
			return true;
		}
	}
	//Outside grid block
	return false;
}
