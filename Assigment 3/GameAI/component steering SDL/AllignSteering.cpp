#include "AllignSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

Allign::Allign(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Vector2D Allign::getAlligment()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	std::map<UnitID, Unit*> mUnitMap = gpGame->getUnitManager()->getUnitMap(); //Gets the unit map from mUnitManager, this will act as our neigberhood
	float temp;

	Vector2D resultVector = Vector2D(0,0);
	int neighborCount = 0;

	for (std::map<UnitID, Unit*>::iterator unit = mUnitMap.begin(); unit != mUnitMap.end(); unit++)
	{
		if (unit->second != pOwner)
		{
			Vector2D direction = unit->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
			float distance = direction.getLength();

			if (distance < mNeighborRadius)
			{
				//temp = resultVector.getX() + unit->second->getPhysicsComponent()->getVelocity().getX();
				//resultVector.setX(temp);

				//temp = resultVector.getY() + unit->second->getPhysicsComponent()->getVelocity().getY();
				//resultVector.setY(temp);

 				resultVector += unit->second->getPhysicsComponent()->getData().vel;

				neighborCount++;
			}
		}
	}

	if (neighborCount == 0)
	{
		return resultVector;
	}

	//temp = resultVector.getX() / neighborCount;
	//resultVector.setX(temp);

	//temp = resultVector.getY() / neighborCount;
	//resultVector.setY(temp);

	resultVector /= neighborCount;

	//resultVector.normalize();

	return resultVector;
}
