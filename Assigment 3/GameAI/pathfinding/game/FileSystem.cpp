#include "FileSystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

FileSystem::FileSystem(string fileLocation, string fileName)
{
	mFileLocation = fileLocation;
	mFileName = fileName;
}

FileSystem::~FileSystem()
{
}

void FileSystem::loadFiles()
{
	string data;
	string variableName;
	bool endOfFile = false;
	ifstream file(mFileLocation + mFileName);
	
	ifstream fileStream(mFileLocation + mFileName);
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, variableName, '=');
			if (variableName == "\nPLAYER_HEALTH")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mPlayerHealth;
			}
			else if (variableName == "\nBULLET_DAMAGE")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mBulletDamage;
			}
			else if (variableName == "\nPLAYER_SPEED")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mPlayerSpeed;
			}
			else if (variableName == "\nPLAYER_ROTATE_SPEED")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mPlayerRotateSpeed;
			}
			else if (variableName == "\nSHOOT_DELAY")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mShootDelay;
			}
			else if (variableName == "\nBULLET_SPEED")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mBulletSpeed;
			}
			else if (variableName == "\nBUFF_SPEED")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mPowerUpSpeedIncrease;
			}
			else if (variableName == "\nBUFF_TIMER")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mBuffDuration;
			}
			else if (variableName == "\nP1_START_X")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mP1StartX;
			}
			else if (variableName == "\nP1_START_Y")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mP1StartY;
			}
			else if (variableName == "\nP2_START_X")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mP2StartX;
			}
			else if (variableName == "\nP2_START_Y")
			{
				getline(file, data, ';');
				stringstream ss;
				ss << data;
				ss >> mP2StartY;
			}
			else
			{
				getline(file, data, ';');
			}
		}
		file.close();

	}
}
