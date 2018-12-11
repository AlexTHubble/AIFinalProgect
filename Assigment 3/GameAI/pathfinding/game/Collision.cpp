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

void Collision::CheckForCollisions(Unit* unit)
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
			InsideGridBlock(i, unit);
		}
	}
	//Search through Unitmanager for bullets
	for (int j = 0; j < gpGame->getUnitManager()->getUnitMap().size(); j++)
	{
		if (gpGame->getUnitManager()->getUnitMap()[j]->getTag() == "Bullet")
		{
			if (HitByBullet(unit, gpGame->getUnitManager()->getUnitMap()[j]))
			{
				//Hit by bullet
				std::cout << "Hit by Bullet" << std::endl;
			}
		}
	}
}

void Collision::InsideGridBlock(int index, Unit* unit)
{
	//References
	//https://stackoverflow.com/questions/31022269/collision-detection-between-two-rectangles-in-java
	//https://silentmatt.com/rectangle-intersection/

	//Get Grid
	Grid* grid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	//Unit Center and radius spacing
	float unitXOffset = (unit->getSprite()->getWidth());
	float unitYOffset = (unit->getSprite()->getHeight());
	float unitX = unit->getPositionComponent()->getPosition().getX();
	float unitY = unit->getPositionComponent()->getPosition().getY();
	//-------------------------------------------------------------------//
	//Unit UL and BR corners
	float unitULX = (unitX);
	float unitULY = (unitY);
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
		TankWallCollision(unit);
	}
}

bool Collision::HitByBullet(Unit * player, Unit * bullet)
{
	//Unit Center and radius spacing
	float unitX = player->getPositionComponent()->getPosition().getX();
	float unitY = player->getPositionComponent()->getPosition().getY();
	//-------------------------------------------------------------------//
	//Bullet center and radius
	float bulletRadius = (bullet->getSprite()->getWidth());
	float bulletX = bullet->getPositionComponent()->getPosition().getX();
	float bulletY = bullet->getPositionComponent()->getPosition().getY();
	
	//Check to see if player is within radius of bullet
	float yDiff = unitY - bulletY;
	float xDiff = unitX - bulletX;
	//Get distance between points
	float distance = std::sqrtf((xDiff * xDiff) + (yDiff * yDiff));
	//If within radius of bullet
	if (distance <= bulletRadius)
	{
		return true;
	}
	//If outside radius of bullet
	else
	{
		return false;
	}
}

void Collision::TankWallCollision(Unit* unit)
{
	PhysicsData phyData = unit->getPhysicsComponent()->getData();
	PositionData posData = unit->getPositionComponent()->getData();
	//Get current direction
	float temp = gpGame->getUnitManager()->getUnit(unit->getID())->getFacing() - (PI / 2);
	Vector2D currentDirection = Vector2D(cos(temp), sin(temp));
	//If looking down
	if (currentDirection.getY() > 0.0f)
	{
		//If Y movement greater than X
		if (phyData.vel.getY() > phyData.vel.getX())
		{
			posData.pos.setY(posData.pos.getY() - 1.0f);
		}
		//Adjust X
		if (currentDirection.getX() > 0.0f)
		{
			posData.pos.setX(posData.pos.getX() - 1.0f);
		}
		else
		{
			posData.pos.setX(posData.pos.getX() + 1.0f);
		}
	}
	//If looking up
	else 
	{
		//If Y movement greater than X
		if (phyData.vel.getY() > phyData.vel.getX())
		{
			posData.pos.setY(posData.pos.getY() + 1.0f);
		}
		//Adjust X
		if (currentDirection.getX() > 0.0f)
		{
			posData.pos.setX(posData.pos.getX() - 1.0f);
		}
		else
		{
			posData.pos.setX(posData.pos.getX() + 1.0f);
		}
	}
	//Stop velocity for collision
	//phyData.vel = 0.0f;
	//Set data
	unit->getPhysicsComponent()->setData(phyData);
	unit->getPositionComponent()->setData(posData);
}
