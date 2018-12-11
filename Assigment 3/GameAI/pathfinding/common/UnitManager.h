#pragma once

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <MemoryPool.h>
#include <map>
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "Unit.h"

class Unit;
class Sprite;
struct PositionData;
struct PhysicsData;

const UnitID PLAYER_UNIT_ID = 0;
const UnitID PLAYER2_UNIT_ID = 1;


class UnitManager : public Trackable
{
public:
	UnitManager(Uint32 maxSize);
	~UnitManager() {};

	void cleanup();

	Unit* createUnit(const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);
	Unit* createBullet(const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);
	Unit* createPowerUp(const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);
	Unit* createPlayerUnit(const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA);
	Unit* createPlayer2Unit(const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA);
	Unit* createRandomUnit(const Sprite& sprite);

	Unit* getUnit(const UnitID& id) const;
	void deleteUnit(const UnitID& id);
	void deleteRandomUnit();

	void drawAll() const;
	void updateAll(float elapsedTime);

	Unit* getPlayerUnit() const { return getUnit(PLAYER_UNIT_ID); };
	Unit* getPlayer2Unit() const { return getUnit(PLAYER2_UNIT_ID); };

	std::map<UnitID, Unit*> getUnitMap() { return mUnitMap; };
	std::map<UnitID, Unit*> getBulletMap() { return mBulletMap; };
	std::map<UnitID, Unit*> getPowerUpMap() { return mPowerUpMap; };

private:
	static UnitID msNextUnitID;
	MemoryPool mPool;
	std::map<UnitID, Unit*> mUnitMap;
	std::map<UnitID, Unit*> mBulletMap;
	std::map<UnitID, Unit*> mPowerUpMap;
};

