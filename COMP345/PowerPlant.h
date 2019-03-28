/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

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

	bool power(int coal, int oil, int garbage, int uranium);

};