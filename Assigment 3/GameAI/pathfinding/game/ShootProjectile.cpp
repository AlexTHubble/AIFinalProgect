#include "ShootProjectile.h"
#include "Unit.h"

ShootProjectile::ShootProjectile()
{

}

ShootProjectile::~ShootProjectile()
{

}

void ShootProjectile::Shoot(Unit * unit)
{
	//Send bullet straight
	PhysicsData phyData = unit->getPhysicsComponent()->getData();
	phyData.vel = GetProjectileVelocity();
}
