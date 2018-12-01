#include "Cohesion.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

Cohesion::Cohesion(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Vector2D Cohesion::getCohesion()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	std::map<UnitID, Unit*> mUnitMap = gpGame->getUnitManager()->getUnitMap(); //Gets the unit map from mUnitManager, this will act as our neigberhood
	float temp;
	int neighborCount = 0;
	Vector2D resultVector;

	for (std::map<UnitID, Unit*>::iterator unit = mUnitMap.begin(); unit != mUnitMap.end(); unit++)
	{
		if (unit->second != pOwner)
		{
			Vector2D direction = unit->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
			float distance = direction.getLength();

			if (distance < mNeighborRadius)
			{
				temp = resultVector.getX() + unit->second->getPositionComponent()->getPosition().getX();
				resultVector.setX(temp);

				temp = resultVector.getY() + unit->second->getPositionComponent()->getPosition().getY();
				resultVector.setY(temp);

				neighborCount++;
			}
		}
	}

	if (neighborCount == 0)
	{
		return resultVector;
	}

	temp = resultVector.getX() / neighborCount;
	resultVector.setX(temp);

	temp = resultVector.getY() / neighborCount;
	resultVector.setY(temp);

	resultVector = Vector2D(resultVector.getX() - pOwner->getPositionComponent()->getPosition().getX(), 
		resultVector.getY() - pOwner->getPositionComponent()->getPosition().getY());

	//resultVector.normalize();

	return resultVector;
}
