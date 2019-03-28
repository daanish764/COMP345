/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#include "City.h"
#include "GameBoard.h"
#include<iostream>
#include<string>
using namespace std;


City::City()
{
	cityName = "";
}

City::City(string cityName)
{
	this->cityName = cityName;
}


City::~City()
{
	// the vector class will handle deleting of pointers in adjacentCities
}

void City::setCityName(const string cityName)
{
	this->cityName = cityName;
}

string City::getCityName() const
{

	return this->cityName;
}

void City::addAdjacentCity(City* city, int cost)
{
	adjacentCities.push_back(city);
	this->cost.push_back(cost);
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
			cost.erase(cost.begin() + i);
		}
	}

}

void City::printAllAdjacentCities()
{
	for (unsigned int i = 0; i < adjacentCities.size(); i++)
	{
		cout << adjacentCities.at(i)->getCityName()<< " at a cost " << cost.at(i) << std::endl;
	}
}

string City::getCityStatus() {
	return ("\n" + cityName + " | Red House: " + std::to_string(redHouse) + " | Green House: " + std::to_string(greenHouse) + " | Blue House: " + std::to_string(blueHouse)
		+ " | Purple House: " + std::to_string(purpleHouse) + " | Orange House: " + std::to_string(orangeHouse) + " | Yellow House: " + std::to_string(yellowHouse));
}

void City::placeRedHouse() {
	redHouse = 1;
	GameBoard::availableRedHouses -= 1;
}

void City::placeGreenHouse() {
	greenHouse = 1;
	GameBoard::availableGreenHouses -= 1;
}

void City::placeBlueHouse() {
	blueHouse = 1;
	GameBoard::availableBlueHouses -= 1;
}

void City::placePurpleHouse() {
	purpleHouse = 1;
	GameBoard::availablePurpleHouses -= 1;
}

void City::placeOrangeHouse() {
	orangeHouse = 1;
	GameBoard::availableOrangeHouses -= 1;
}

void City::placeYellowHouse() {
	yellowHouse = 1;
	GameBoard::availableYellowHouses -= 1;
}

int City::getNumberOfHouses(string color)
{
	if (color == "red")
		return redHouse;
	else if (color == "green")
		return greenHouse;
	else if (color == "blue")
		return blueHouse;
	else if (color == "purple")
		return purpleHouse;
	else if (color == "orange")
		return orangeHouse;
	else if (color == "yellow")
		return yellowHouse;
	else
		return 0;
}

int City::getNumberOfHouses()
{
	return redHouse + greenHouse + blueHouse + purpleHouse + orangeHouse + yellowHouse;
}

void City::placeHouse(string color)
{
	if (color == "red")
		placeRedHouse();
	else if (color == "green")
		placeGreenHouse();
	else if (color == "blue")
		placeBlueHouse();
	else if (color == "purple")
		placePurpleHouse();
	else if (color == "orange")
		placeOrangeHouse();
	else if (color == "yellow")
		placeYellowHouse();
}