#include "City.h"



City::City()
{
	cityName = "";
}

City::City(string cityName)
{
	this->cityName = cityName;
}

City::City(string cityName, Player * player)
{
	this->cityName=cityName,
	this->owner = player;
}


City::~City()
{
	delete owner;
	delete &adjacentCities;
}

void City::setCityName(const string cityName)
{
	this->cityName = cityName;
}

string City::getCityName() const
{

	return this->cityName;
}

void City::addAdjacentCity(City* city)
{
	adjacentCities.push_back(city);
}

vector<City*> City::getAdjacentCities() const
{
	return this->adjacentCities;
}

void City::removeAdjacentCity(City * city)
{
	for (unsigned int i = 0; i < adjacentCities.size(); i++) {
		if (adjacentCities.at(i) == city)
		{
			adjacentCities.erase(adjacentCities.begin() + i);
		}
	}

}

void City::setOwner(Player* player)
{
	this->owner = player;
}

Player * City::getOwner() const
{
	return this->owner;
}
