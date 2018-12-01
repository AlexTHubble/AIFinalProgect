#include <Trackable.h>
#include "Steering.h"

class ArriveAndFace : public Steering
{
public:
	ArriveAndFace(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

	//friend FaceSteering;
protected:
	virtual Steering* getSteering();
};