#pragma once
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <Trackable.h>
#include <DeanLibDefines.h>



class FileSystem : public Trackable
{
public:
	FileSystem(std::string fileLocation, std::string fileName);
	~FileSystem();

	void loadFiles();

	//-------------------Getters for variables----------------------
	int getPlayerHealth() { return mPlayerHealth; };
	int getBulletDamage() { return mBulletDamage; };
	float getPlayerSpeed() { return mPlayerSpeed; };
	float getPlayerRotateSpeed() { return mPlayerRotateSpeed; };
	float getPowerUpSpeedIncrease() { return mPowerUpSpeedIncrease; };
	float getShotSpeed() { return mShootSpeed; };
	float getShootDelay() { return mShootDelay; };
	float getBulletSpeed() { return mBulletSpeed; };
	float getBufDuration() { return mBuffDuration; };
	int getP1StartX() { return mP1StartX; };
	int getP1StartY() { return mP1StartY; };
	int getP2StartX() { return mP2StartX; };
	int getP2StartY() { return mP2StartY; };

private:

	//-------------------Variables from file----------------------
	int mPlayerHealth;
	int mBulletDamage;
	float mPlayerSpeed;
	float mPowerUpSpeedIncrease;
	float mShootSpeed;
	float mPlayerRotateSpeed;
	float mShootDelay;
	float mBulletSpeed;
	float mBuffDuration;
	int mP1StartX;
	int mP1StartY;
	int mP2StartX;
	int mP2StartY;

	//-------------------Variables for file location----------------------
	std::string mFileLocation;
	std::string mFileName;
};



#endif//!FILE_SYSTEM_H
