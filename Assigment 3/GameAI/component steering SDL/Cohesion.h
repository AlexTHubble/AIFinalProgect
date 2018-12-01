#include <Trackable.h>
#include "Steering.h"
#include <map>
#include "Unit.h"


class Cohesion : public Steering
{
public:
	Cohesion(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	Vector2D getCohesion();
	int getRadius() { return mNeighborRadius; };
	void setRadius(int radius) { mNeighborRadius = radius; };
protected:

	float mNeighborRadius = 200;
};