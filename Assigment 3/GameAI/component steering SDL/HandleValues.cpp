#include "HandleValues.h"
#include "UnitManager.h"
#include "SteeringComponent.h"
#include <fstream>
#include <string>

HandleValue::HandleValue(Flock * steeringToLoadTo, bool isSaving)
	:GameMessage(LOAD_DATA)
{
	mIsSaving = isSaving;
	mpFlockSteering = steeringToLoadTo;
}

HandleValue::~HandleValue()
{
	delete mpFlockSteering;
}

void HandleValue::process()
{
	if (mIsSaving)
	{
		saveValues();
	}
	else
	{
		loadValues();
	}

}

void HandleValue::loadValues()
{
	ifstream fout;

	//string line;
	string variableName;
	string data;

	fout.open(mFileName);


	if (fout.is_open())
	{
		while (!fout.eof())
		{
			getline(fout, variableName, '=');
			if (variableName == "\nAllignWeight")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setAllignWeight(output);
			}
			else if (variableName == "\nSeperationWeight")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setSeperationWeight(output);
			}
			else if (variableName == "\nCohesionWeigth")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setCohesionWeight(output);
			}
			else if (variableName == "\nWanderWeight")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setWanderWeight(output);
			}
			else if (variableName == "\nWanderOffSet")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setWanderOffSet(output);
			}
			else if (variableName == "\nWanderRadius")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setWanderRadius(output);
			}
			else if (variableName == "\nWanderRate")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setWanderRate(output);
			}
			else if (variableName == "\nAllignRadius")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setAllignmentRadius(output);
			}
			else if (variableName == "\nSeperationRadius")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setSeperationRadius(output);
			}
			else if (variableName == "\nCohesionRadius")
			{
				getline(fout, data, ';');
				float output = stof(data); //Converts data to float
				mpFlockSteering->setCohesionRadius(output);
			}
			else
			{
				getline(fout, data, ';');
			}
		}
	}
	fout.close();
}

void HandleValue::saveValues()
{
 	ofstream fout;

	//string line;
	string variableName;
	string data;

	fout.open(mFileName);


	if (fout.is_open())
	{
		fout << "VARIABLE_NAME=VALUE;\n";
		fout << "AllignWeight=" << mpFlockSteering->getAllignWeight() << ";\n";
		fout << "SeperationWeight=" << mpFlockSteering->getSeperationWeight() << ";\n";
		fout << "CohesionWeigth=" << mpFlockSteering->getCohesionWeight() << ";\n";
		fout << "WanderWeight=" << mpFlockSteering->getWanderRate() << ";\n";
		fout << "WanderOffSet=" << mpFlockSteering->getWanderOffSet() << ";\n";
		fout << "WanderRadius=" << mpFlockSteering->getWanderRadius() << ";\n";
		fout << "WanderRate=" << mpFlockSteering->getWanderRate() << ";\n";
		fout << "AllignRadius=" << mpFlockSteering->getAllignmentRadius() << ";\n";
		fout << "SeperationRadius=" << mpFlockSteering->getSeperationRadius() << ";\n";
		fout << "CohesionRadius=" << mpFlockSteering->getCohesionRadius() << ";\n";


	}

}
