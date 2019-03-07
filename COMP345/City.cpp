#include "City.h"
#include "Map.h"
#include <string>

City::City()
{
	cityName = "";
}

City::City(string cityName)
{
	this->cityName = cityName;
	redHouse = 0;
	greenHouse = 0;
	blueHouse = 0;
	purpleHouse = 0;
	orangeHouse = 0;
	yellowHouse = 0;
}

City::City(string cityName, Player * player)
{
	this->cityName=cityName,
	this->owner = player;
}


City::~City()
{
	
}

void City::setCityName(const string cityName)
{
	this->cityName = cityName;
}

string City::getCityName() const
{

	return this->cityName;
}

string City::getCityStatus() {
	return ("\n" + cityName + " | Red House: " + std::to_string(redHouse) + " | Green House: " + std::to_string(greenHouse) + " | Blue House: " + std::to_string(blueHouse)
		+ " | Purple House: " + std::to_string(purpleHouse) + " | Orange House: " + std::to_string(orangeHouse) + " | Yellow House: " + std::to_string(yellowHouse));
}

void City::placeRedHouse() {
	redHouse = 1;
	Map::availableRedHouses -=1;
}

void City::placeGreenHouse() {
	greenHouse = 1;
	Map::availableGreenHouses -= 1;
}

void City::placeBlueHouse() {
	blueHouse = 1;
	Map::availableBlueHouses -= 1;
}

void City::placePurpleHouse() {
	purpleHouse = 1;
	Map::availablePurpleHouses -= 1;
}

void City::placeOrangeHouse() {
	orangeHouse = 1;
	Map::availableOrangeHouses -= 1;
}

void City::placeYellowHouse() {
	yellowHouse = 1;
	Map::availableYellowHouses -= 1;
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
