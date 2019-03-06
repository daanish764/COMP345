#include "Player.h"
#include<string>


Player::Player()
{
	name = "";
	electro = 0;
	coal = 0;
	garbage = 0;
	oil = 0;
	uranium = 0;

}

Player::Player(string playerName)
{
	
	name = playerName;
	electro = 0;
	coal = 0;
	garbage = 0;
	oil = 0;
	uranium = 0;
}

Player::~Player()
{
}

string Player::getName() const
{
	return name;
}

int Player::getElectro()
{
	return this->electro;
}

void Player::setElectro(int electro)
{
	this->electro = electro;
}



int Player::getCoal()
{
	return this->coal;
}

void Player::setCoal(int coal)
{
	this->coal = coal;
}

int Player::getGarbage()
{
	return this->garbage;
}

void Player::setGarbage(int garbage)
{
	this->garbage = garbage;
}

int Player::getOil()
{
	return this->oil;
}

void Player::setOil(int oil)
{
	this->oil = oil;
}

int Player::getUranium()
{
	return this->uranium;
}

void Player::setUranium(int uranium)
{
	this->uranium = uranium;
}

void Player::getPlayerInfo()
{
	std::cout << "Player Name: " << name << "\Color: " << color << "\nElectro: " << electro << "\nCoal: " << coal << "\nGarbage: " << garbage << "\nOil: " << oil << "\nUranium: " << uranium << std::endl;
}
