#ifndef SHOOT_PROJECTILE_H
#define SHOOT_PROJECTILE_H

#include "Trackable.h"

class Unit;

class ShootProjectile : public Trackable
{
public:
	//Constructor
	ShootProjectile();
	//Destructor
	~ShootProjectile();
	//Update

	//Functions
	void Shoot(Unit* unit);
	//Accessors
	void SetProjectileVelocity(float vel) { mProjecctileVel = vel; };

private:
	//Variables
	float mProjecctileVel;
	//Accessors
	float GetProjectileVelocity() { return mProjecctileVel; };
};

#endif // !SHOOT_PROJECTILE_H

