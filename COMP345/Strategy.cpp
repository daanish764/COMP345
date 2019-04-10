#pragma once
#include <iostream>
using namespace std;

#include "PowerPlant.h"

class Strategy {
public:
	virtual int auctionAction(int numberOfPlantsOwned, int currentElektro, int plantPosition, int highestBid, int playerBid, bool environmental) { //plant position in the current market (0 to 3 where 3 is the most expensive)
		return playerBid;
	}
	virtual int resourceAction(int currentElektro, int capacity, int initialAction) {
		return initialAction;
	}
	virtual int pickingAction(int numberOfPlantsOwned, int currentElektro, vector<PowerPlant*> plants, int initialAction) {
		return initialAction;
	}
	virtual int buildingAction(int numberOfCitiesOwned, int step2 , int step2trigger, int initialAction) {
		return initialAction;
	}
};

class Aggressive : public Strategy {
public:
	
	int auctionAction(int numberOfPlantsOwned, int currentElektro, int plantPosition, int highestBid, int playerBid, bool environmental) {
		
		//this algorithm basically uses an arbitrary algorithm that checks 
		float action = (4 - numberOfPlantsOwned) * plantPosition;
		action = action / 16;
		action = round(action);

		if (playerBid <= highestBid && action>0 && (currentElektro/4)>highestBid) {
			cout << "Player is aggressive, owns " << numberOfPlantsOwned << " plants, has more than enough Elektros and this plant is one of the higher rated ones in the market! \nWe chose to up the bid for you!" << endl;
			return highestBid + 1;
		}
		return playerBid;
	}

	int resourceAction(int currentElektro, int capacity, int initialAction) {
		if (initialAction<capacity && currentElektro > 24) {
			cout << "Player is aggressive, has more than enough Elektro and has capacity to store more! \nWe chose to buy upto capacity for you!";
				return capacity;
		}

		return initialAction;
	}
};

//This player has least restrictions on him
class Moderate : public Strategy {
public:

	int pickingAction(int numberOfPlantsOwned, int currentElektro, vector<PowerPlant*> plants, int initialAction) {
		
		int mostEfficientPlant = initialAction;
		for (int i = 0; i < 4; i++) {
			int plantEfficiency = plants[i]->powersCities - plants[i]->coalRequired - plants[i]->oilRequired - plants[i]->garbageRequired - plants[i]->uraniumRequired;
				if (plantEfficiency > mostEfficientPlant) {
					mostEfficientPlant = plants[i]->getPlantNumber();
				}
		}
		if (initialAction != mostEfficientPlant) {
			cout << "Moderate player ideally should go for the most efficient plant!\n We chose the plant for you!";
		}
		return initialAction;
	}

	int buildingAction(int numberOfCitiesOwned, int step2, int step2trigger, int initialAction) {
		if (step2trigger - numberOfCitiesOwned < 2 && step2==0 && initialAction!=-1) {
			cout << "Player is moderate and looking to avoid step 2! We chose not to build for now for you!";
		}
		return initialAction;
	}
};

class Environmentalist : public Strategy {
public:

	int auctionAction(int numberOfPlantsOwned, int currentElektro, int plantPosition, int highestBid, int playerBid, bool environmental) {
		if (environmental == true && (currentElektro / 4) > highestBid) {
			cout << "It's a wind plant and the player is a tree hugger!\nWe chose to up the bid for you!" << endl;
			return highestBid + 1;
		}
		return playerBid;
	}

	int pickingAction(int numberOfPlantsOwned, int currentElektro, vector<PowerPlant*> plants, int initialAction) {
		for (int i = 0; i < 4; i++) {
			if (plants[i]->hybridRequired>0 && (currentElektro) > 24 && numberOfPlantsOwned<4) {
					cout << "Environmentalist must always go for a wind plant if it's available\nChoosing the plant for you!" << endl;
					return plants[i]->getPlantNumber();
				}
		}
		return initialAction;
	}
};