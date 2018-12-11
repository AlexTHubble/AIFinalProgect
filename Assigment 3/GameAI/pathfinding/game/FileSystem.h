#pragma once
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <iostream>

using namespace std;

class FileSystem : public Trackable
{
public:
	FileSystem(string fileLocation, string fileName);
	~FileSystem();

	void loadFiles();

	//-------------------Getters for variables----------------------

private:
	/*
	--!Variables needed!--
	Player health
	Bullet Damage
	Player speed
	Ai see player radius
	AI disengage player radius
	PowerUp Speed increase
	Shoot Speed
	*/
	//-------------------Variables from file----------------------
	int mPlayerHealth;
	int mBulletDamage;
	float mPlayerSpeed;
	float mAiSeePlayerRadius;
	float mAiDisengagePlayerRadius;
	float mPowerUpSpeedIncrease;
	float mShootSpeed;

	//-------------------Variables for file location----------------------
	string mFileLocation;
	string mFileName;
};



#endif//!FILE_SYSTEM_H
