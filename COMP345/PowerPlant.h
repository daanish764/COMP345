#pragma once
#include <iostream>

class PowerPlant
{
private:

public:
	int plantNumber;
	int powersCities;
	int coalRequired;
	int oilRequired;
	int garbageRequired;
	int uraniumRequired;
	int hybridRequired;

	PowerPlant();
	PowerPlant(int plantNumber);
	PowerPlant(int plantNumber, int powersCities, int coalRequired, int oilRequired, int garbageRequired, int uraniumRequired, int hybridRequired);
	~PowerPlant();

	int getPlantNumber() const;
};