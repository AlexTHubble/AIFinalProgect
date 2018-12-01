#include <Trackable.h>
#include "Steering.h"
//#include "FaceSteering.h"

class WanderAndChase : public Steering
{
public:
	WanderAndChase(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	//friend FaceSteering;
	//friend Steering;

protected:
	virtual Steering* getSteering();
	//Vector2D getWanderTarget();

	float mDetectionRadius = 100;
};