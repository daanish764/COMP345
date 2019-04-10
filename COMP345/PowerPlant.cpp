/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#include "PowerPlant.h"
#include <iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

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
	powersCities = 0;
	coalRequired = 0;
	oilRequired = 0;
	garbageRequired = 0;
	uraniumRequired = 0;
	hybridRequired = 0;
	environmentalPlant == false;
}

PowerPlant::PowerPlant(int plantNumber, int powersCities, int coalRequired, int oilRequired, int garbageRequired, int uraniumRequired, int hybridRequired, bool environmentalPlant)
{
	this->plantNumber = plantNumber;
	this->powersCities = powersCities;
	this->coalRequired = coalRequired;
	this->oilRequired = oilRequired;
	this->garbageRequired = garbageRequired;
	this->uraniumRequired = uraniumRequired;
	this->hybridRequired = hybridRequired;
	this->environmentalPlant = environmentalPlant;
}

PowerPlant::~PowerPlant()
{
}

int PowerPlant::getPlantNumber() const
{
	return plantNumber;
}

void PowerPlant::printPlantInfo() const
{
	
	


	string zero = "";
	if (this->getPlantNumber() < 10) {
		zero = "0";
	}
	else {
		zero = "";
	}
	cout << "|   " << zero << this->getPlantNumber() << "   |   " << this->coalRequired << "   |  " << this->oilRequired << "   |     " << this->garbageRequired << "   |    " << this->uraniumRequired << "     |        " << this->hybridRequired << "         |       " << this->powersCities << "            |"; 

	

}

bool PowerPlant::power(int coal, int oil, int garbage, int uranium)
{

	if (garbageRequired != 0 && garbage <= garbageRequired)
		return false;
	if (uraniumRequired != 0 && uranium <= uraniumRequired)
		return false;
	int coalAndOil = coal + oil;

	if (hybridRequired != 0 && coalAndOil <= hybridRequired)
	{
		return false;
	}

	if (coalRequired != 0 && coal <= coalRequired)
		return false;

	if (oilRequired != 0 & oil <= oilRequired)
		return false;

	return true;
}
