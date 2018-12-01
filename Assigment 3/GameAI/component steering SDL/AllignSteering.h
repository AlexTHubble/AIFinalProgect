#include <Trackable.h>
#include "Steering.h"



class Allign : public Steering
{
public:
	Allign(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	Vector2D getAlligment();
	int getRadius() { return mNeighborRadius; };
	void setRadius(int radius) { mNeighborRadius = radius; };
protected:

	int mNeighborRadius = 300;
};