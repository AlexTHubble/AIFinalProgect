#include "Tank.h"
#include "TankMovement.h"

Tank::Tank(const Sprite& sprite, float maxMoveSpeed, float maxRotationSpeed)
	:Unit(sprite)
{
	mpTankMovement = new TankMovement(maxMoveSpeed, maxRotationSpeed);
}

Tank::~Tank()
{
	delete mpTankMovement;
}

void Tank::update(int elapsedTime)
{
	mpTankMovement->UpdateMovement(elapsedTime);
	SetMaxMoveSpeed(mpTankMovement->GetMovementSpeed());
	SetMaxRotateSpeed(mpTankMovement->GetRotateSpeed());
}


