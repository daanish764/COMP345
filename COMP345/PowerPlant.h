#pragma once
#include <iostream>
#include<string>

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

	void printPlantInfo() const;

};