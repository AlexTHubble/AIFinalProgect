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
	//References
	//https://stackoverflow.com/questions/31022269/collision-detection-between-two-rectangles-in-java
	//https://silentmatt.com/rectangle-intersection/

	//Get Grid
	Grid* grid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	//Unit Center and radius spacing
	float unitXOffset = (unit->getSprite()->getWidth() / 2.0f);
	float unitYOffset = (unit->getSprite()->getHeight() / 2.0f);
	float unitX = unit->getPositionComponent()->getPosition().getX();
	float unitY = unit->getPositionComponent()->getPosition().getY();
	//-------------------------------------------------------------------//
	//Unit UL and BR corners
	float unitULX = (unitX - unitXOffset);
	float unitULY = (unitY - unitYOffset);
	float unitBRX = (unitX + unitXOffset);
	float unitBRY = (unitY + unitYOffset);
	//Grid block UL and BR corners
	float gridBlockOffset = grid->getSquareSize();
	float gridBlockULX = grid->getULCornerOfSquare(index).getX();
	float gridBlockULY = grid->getULCornerOfSquare(index).getY();
	float gridBlockBRX = (gridBlockULX + gridBlockOffset);
	float gridBlockBRY = (gridBlockULY + gridBlockOffset);
	
	//Check to see if all opposite edges overlap
	if (unitULX < gridBlockBRX && unitBRX > gridBlockULX &&
		unitULY < gridBlockBRY && unitBRY > gridBlockULY)
	{
		return true;
	}
	//All opposite edges don't overlap
	return false;
}
