#ifndef COLLISION_H
#define COLLISION_H

#include "Trackable.h"

class Unit;

class Collision : public Trackable
{
public:
	//Constructor
	Collision();
	//Deconstructor
	~Collision();
	//Update
	bool CheckForCollisions(Unit* unit);

private:
	//Variables

	//Accessors

	//Functions
	bool InsideGridBlock(int index, Unit* unit);
};

#endif // !COLLISION_H

