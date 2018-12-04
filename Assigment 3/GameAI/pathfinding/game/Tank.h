#ifndef TANK_H
#define TANK_H

#include "Unit.h"

class Sprite;
class TankMovement;

class Tank : public Unit
{
public:
	//Constructor
	Tank(const Sprite& sprite, float maxMoveSpeed, float maxRotationSpeed);
	//Destructor
	~Tank();
	//Update
	virtual void update(int elapsedTime);
	//Accessors
	void SetMaxMoveSpeed(float maxSpeed) { SetMaxSpeed(maxSpeed); };
	void SetMaxRotateSpeed(float maxSpeed) { SetMaxRotateSpeed(maxSpeed); };
	virtual TankMovement* Movement() { return mpTankMovement; };
private:
	//Class Instances
	TankMovement* mpTankMovement;
};

#endif // !TANK_H

