#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering
{
	/*friend WanderSteering;*/
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLocation, const UnitID& targetID = INVALID_UNIT_ID);
	virtual Steering* getSteering();
protected:

	float mTargetRotationRadius = 0.1f;
	float mSlowRadius = 0.5f;
	//float mMaxRotation = 10;
};