#include "ShootProjectile.h"
#include "Unit.h"
#include "GameApp.h"

ShootProjectile::ShootProjectile()
{
	SetProjectileVelocity(gpGame->getFileSystem()->getBulletSpeed());
}

ShootProjectile::~ShootProjectile()
{

}

void ShootProjectile::Shoot(Unit * unit)
{
	//Send bullet straight
	PositionData posData = unit->getPositionComponent()->getData();
	PhysicsData phyData = unit->getPhysicsComponent()->getData();
	//Get current direction to move in
	float temp = posData.facing - (PI / 2);
	Vector2D currentDirection = Vector2D(cos(temp), sin(temp));
	//Set velcity in facing direction
	phyData.vel = currentDirection * GetProjectileVelocity();
	//Set data
	unit->getPhysicsComponent()->setData(phyData);
}
