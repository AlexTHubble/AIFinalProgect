#include "Seperation.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


Seperation::Seperation(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Vector2D Seperation::getSeperation()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	std::map<UnitID, Unit*> mUnitMap = gpGame->getUnitManager()->getUnitMap(); //Gets the unit map from mUnitManager, this will act as our neigberhood
	float temp;
	int neighborCount = 0;
	Vector2D resultVector;

	//Cycles through the map to test each unit
	for (std::map<UnitID, Unit*>::iterator unit = mUnitMap.begin(); unit != mUnitMap.end(); unit++)
	{
		//If it is not the owner...
		if (unit->second != pOwner)
		{
			Vector2D direction = unit->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
			float distance = direction.getLength();
			
			//If it is within the desired distance
			if (distance < mNeighborRadius)
			{
				temp = resultVector.getX() + (unit->second->getPositionComponent()->getPosition().getX() - pOwner->getPositionComponent()->getPosition().getX());
				resultVector.setX(temp);

				temp = resultVector.getY() + (unit->second->getPositionComponent()->getPosition().getY() - pOwner->getPositionComponent()->getPosition().getY());
				resultVector.setY(temp);

				neighborCount++;
			}
		}
	}

	if (neighborCount == 0)
	{
		return resultVector;
	}

	temp = (resultVector.getX() / neighborCount);
	temp *= -1;
	resultVector.setX(temp);

	temp = (resultVector.getY() / neighborCount);
	temp *= -1;
	resultVector.setY(temp);

	//resultVector.normalize();

	return resultVector;
}
