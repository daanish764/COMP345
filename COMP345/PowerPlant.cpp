#include "PowerPlant.h"
#include "Player.h"
#include <iostream>


PowerPlant::PowerPlant()
{
	plantNumber = 0;
	powersCities = 0;
	coalRequired = 0;
	oilRequired = 0;
	garbageRequired = 0;
	uraniumRequired = 0;
	hybridRequired = 0;
}

PowerPlant::PowerPlant(int plantNumber)
{
	this->plantNumber = plantNumber;
}

PowerPlant::PowerPlant(int plantNumber, int powersCities, int coalRequired, int oilRequired, int garbageRequired, int uraniumRequired, int hybridRequired)
{
	this->plantNumber = plantNumber;
	this->powersCities = powersCities;
	this->coalRequired = coalRequired;
	this->oilRequired = oilRequired;
	this->garbageRequired = garbageRequired;
	this->uraniumRequired = uraniumRequired;
	this->hybridRequired = hybridRequired;
}

PowerPlant::~PowerPlant()
{
}

int PowerPlant::getPlantNumber() const
{
	return plantNumber;
}

void PowerPlant::setOwner(Player* name, int cost) {
	this->owner = name;
	name->subtractElektro(cost);
	if (plantNumber > name->largestPlant) {
		name->largestPlant = plantNumber;
	}
}

Player* PowerPlant::getOwner() {
	return this->owner;
}
