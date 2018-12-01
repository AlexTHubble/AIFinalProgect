#include <Trackable.h>
#include "Steering.h"
#include "Path.h"

//This is a modifyed seek algorithm that will be used with the pathfinding algorithms
class SeekPathfinder : public Steering
{
public:
	SeekPathfinder(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	virtual Steering* getSteering();
	bool getArrived() { return mArrived; };
	void setNewTarget(const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

protected:
	
	float mArriveRadius = 0.5f;
	bool mArrived = false;
};