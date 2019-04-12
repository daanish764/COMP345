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


Player::Player(string name, string color, int maxPlants, int playerType)
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
	//this->strategy = new Environmentalist();
	if(playerType == 1)this->strategy = new Aggressive();
	else if(playerType == 2)this->strategy = new Moderate();
	else if(playerType == 3)this->strategy = new Environmentalist();
	else {
		this->strategy = new Moderate();
		cout << "\nAssigned Moderate by default" << endl;
	}
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

void Player::printPhaseStatus(){
	Notify();
}

void Player::printGameStatus() {
	NotifyGameStatus();
}

void Player::getPlayerInfo()
{
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


void Player::setStrategy(int playerType)
{
	if (playerType == 1) { this->strategy = new Aggressive(); cout << "\nChanged to AGGRESSIVE!" << endl; ; }
	else if (playerType == 2) { this->strategy = new Moderate();  cout << "\nChanged to MODERATE!" << endl; ; }
	else if (playerType == 3) { this->strategy = new Environmentalist(); cout << "\nChanged to ENVIRONMENTALIST!" << endl; }
	else {
		//do nothing and assume they didn't want to change
		cout << "\nNo changes made!" << endl;
	}
}

int Player::strategicBid(int plantPosition, int highestBid, int playerBid, bool environmental)
{
	int numberOfPlantsOwned = ownedPlants.size();
	int currentElektro = this->getElektro();
	return this->strategy->auctionAction(numberOfPlantsOwned, currentElektro, plantPosition, highestBid, playerBid, environmental);
}

int Player::strategicResourceBuy(int capacity, int initialAction) {
	int currentElektro = this->getElektro();
	return this->strategy->resourceAction(currentElektro, capacity, initialAction);
}

int Player::strategicPlantPick(vector<PowerPlant*> plants, int initialAction) {
	int currentElektro = this->getElektro();
	int numberOfPlantsOwned = ownedPlants.size();
	return this->strategy->pickingAction(numberOfPlantsOwned, currentElektro, plants, initialAction);
}

int Player::strategicBuilding(int step2, int step2trigger, int initialAction) {
	int numberOfCitiesOwned = this->ownedCities.size();
	return this->strategy->buildingAction(numberOfCitiesOwned, step2, step2trigger, initialAction);
}

void Player::printPlayerNetwork(vector<City*> cityList) {
	cout << "\nPlayer " + name + " has in his network:";

	if (color == "red") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->redHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
	if (color == "blue") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->blueHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
	if (color == "green") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->greenHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
	if (color == "purple") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->purpleHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
	if (color == "orange") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->orangeHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
	if (color == "yellow") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->yellowHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
}

void Player::printPlayerGraph(vector<City*> cityList) {
	cout << "\n" << name + " : ";

	if (color == "red") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->redHouse == 1) {
				cout << " *";
			}
		}
	}
	if (color == "blue") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->blueHouse == 1) {
				cout << " *";
			}
		}
	}
	if (color == "green") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->greenHouse == 1) {
				cout << " *";
			}
		}
	}
	if (color == "purple") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->purpleHouse == 1) {
				cout << " *";
			}
		}
	}
	if (color == "orange") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->orangeHouse == 1) {
				cout << " *";
			}
		}
	}
	if (color == "yellow") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->yellowHouse == 1) {
				cout << " *";
			}
		}
	}
}