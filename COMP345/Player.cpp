#include"GameBoard.h"
#include<string>


Player::Player()
{
	name = "";
	elektro = 0;
	coal = 0;
	garbage = 0;
	oil = 0;
	uranium = 0;

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
	maxPlants = 0;
	largestPlant = 0;
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
	this->maxPlants = maxPlants;
	largestPlant = 0;
}

string Player::getHouseColor() {
	return this->color;
}

Player::~Player()
{
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
	std::cout << "Player Name: " << name << "\nColor: " << color << "\nTotal Houses on Board: " << totalHouses << "\nElektro: " << elektro << "\nCoal: " << coal << "\nGarbage: " << garbage << "\nOil: " << oil << "\nUranium: " << uranium << std::endl;
}

void Player::assignOil(int num) {
	this->oil = oil + num;
	GameBoard::availableOil = GameBoard::availableOil - num;
}

void Player::assignGarbage(int num) {
	this->garbage = garbage + num;
	GameBoard::availableGarbage = GameBoard::availableGarbage - num;
}

void Player::assignCoal(int num) {
	this->coal = coal + num;
	GameBoard::availableCoal = GameBoard::availableCoal - num;
}

void Player::assignUranium(int num) {
	this->uranium = uranium + num;
	GameBoard::availableUranium = GameBoard::availableUranium - num;
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

