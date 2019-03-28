/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#include"GameBoard.h"
#include<string>
#include<algorithm>
using namespace std;

Player::Player()
{
	name = "";
	elektro = 0;
	coal = 0;
	garbage = 0;
	oil = 0;
	uranium = 0;
	poweredCities = 0;
	startCity = NULL;

}

Player::Player(string playerName)
{
	this->name = name;
	elektro = 50;
	coal = 0;
	garbage = 0;
	oil = 0;
	uranium = 0;
	totalHouses = 0;
	largestPlant = 0;
	poweredCities = 0;
	startCity = NULL;
}


Player::Player(string name, string color, int maxPlants)
{
	this->name = name;
	this->color = color;
	elektro = 50;
	coal = 0;
	garbage = 0;
	oil = 0;
	uranium = 0;
	totalHouses = 0;
	largestPlant = 0;
	poweredCities = 0;
	startCity = NULL;
}

string Player::getHouseColor() {
	return this->color;
}

City * Player::getStartCity()
{
	return this->startCity;
}

void Player::setStartCity(City * startCity)
{
	this->startCity = startCity;
}

Player::~Player()
{
	// ownedCities is deleted by vector class
	// ownedPlants is deleted by vector class
	delete startCity;
	startCity = NULL;
}

string Player::getName() const
{
	return name;
}

int Player::getElektro()
{
	return this->elektro;
}


int Player::getCoal()
{
	return this->coal;
}



int Player::getGarbage()
{
	return this->garbage;
}


int Player::getOil()
{
	return this->oil;
}



int Player::getUranium()
{
	return this->uranium;
}

string Player::getColor() const
{
	return this->color;
}

void Player::getPlayerInfo()
{
	std::cout << "*******";
	std::cout << "Player Name: " << name << "\nColor: " << color << "\nTotal Houses on Board: " << totalHouses << "\nElektro: " << elektro << "\nCoal: " << coal << "\nGarbage: " << garbage << "\nOil: " << oil << "\nUranium: " << uranium << std::endl;
	std::cout << "Owned power plants:";
	for (int i = 0; i < ownedPlants.size(); i++) {
		std::cout << " " << ownedPlants[i]->getPlantNumber();
	}
	std::cout << std::endl;
}

void Player::assignOil(int num, int cost) {
	this->oil = oil + num;
	GameBoard::availableOil = GameBoard::availableOil - num;
	elektro -= cost;
}

void Player::assignGarbage(int num, int cost) {
	this->garbage = garbage + num;
	GameBoard::availableGarbage = GameBoard::availableGarbage - num;
	elektro -= cost;
}

void Player::assignCoal(int num, int cost) {
	this->coal = coal + num;
	GameBoard::availableCoal = GameBoard::availableCoal - num;
	elektro -= cost;
}

void Player::assignUranium(int num, int cost) {
	this->uranium = uranium + num;
	GameBoard::availableUranium = GameBoard::availableUranium - num;
	elektro -= cost;
}

void Player::assignElektro(int num) {
	this->elektro = elektro + num;
}

void Player::subtractElektro(int num) {
	this->elektro = elektro - num;
}

void Player::placeHouse(City * city)
{
	totalHouses += 1;
	if (color == "red") {
		city->placeRedHouse();
	}
	if (color == "green") {
		city->placeGreenHouse();
	}
	if (color == "blue") {
		city->placeBlueHouse();
	}
	if (color == "purple") {
		city->placePurpleHouse();
	}
	if (color == "orange") {
		city->placeOrangeHouse();
	}
	if (color == "yellow") {
		city->placeYellowHouse();
	}
}

void Player::buyPlant(PowerPlant * plant, int cost, int maxPlants)
{
	if (ownedPlants.size() == maxPlants) { //If there's no more capacity, takes out the smallest plant by sorting first and removing first plant
		
		stable_sort(ownedPlants.begin(), ownedPlants.end(), [](const PowerPlant* lhs, const PowerPlant* rhs) { //CHANGE stable_sort TO sort IF YOU ENCOUNTER ANY ISSUES
			return lhs->getPlantNumber() < rhs->getPlantNumber();
		});
		ownedPlants.erase(ownedPlants.begin());
	}

	ownedPlants.push_back(plant);
	elektro -= cost;

	//setting the largest plant here
	if (largestPlant < plant->getPlantNumber()) {
		largestPlant = plant->getPlantNumber();
	}
}

bool Player::isConnectedToCity(City * city)
{
	for (int i = 0; i < ownedCities.size(); i++)
	{
		if (ownedCities.at(i) == city)
			return true;
	}
	return false;
}

void Player::connectToCity(City * city)
{
	ownedCities.push_back(city);
}

vector<City*> Player::getOwnedCities()
{
	return this->ownedCities;
}
