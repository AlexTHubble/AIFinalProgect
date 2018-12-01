#include <Trackable.h>
#include "Steering.h"



class Arrive : public Steering
{
public:
	Arrive(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	virtual Steering* getSteering();

protected:

	void testForArrival(float distance);
	float mSlowRadius = 300.0;
	float mStopSteeringRadius = 10.0;
};