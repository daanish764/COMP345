#pragma once
#include <iostream>
using namespace std;

#include "PowerPlant.h"

//Different players require different strategies. ALL OF THE FUNCTIONS BELOW take in the initial decision player made, assess the player type
//and weather he/she should have made a different decision. if yes, it makes that decision for the player. Else, returns the original call the player made.
class Strategy {
public:
	virtual int auctionAction(int numberOfPlantsOwned, int currentElektro, int plantPosition, int highestBid, int playerBid, bool environmental) {
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
	
	//AFFECTS PHASE 2 DURING AUCTIONING(NOT PLANT PICKING)
	//This player accounts for the number of plants he owns, the elektro he has on hand and if the plant is one of the most expensive ones in the available market to
	//aggressively keep bidding on it until a certain threshold.
	int auctionAction(int numberOfPlantsOwned, int currentElektro, int plantPosition, int highestBid, int playerBid, bool environmental) {
		
		//this algorithm basically uses an arbitrary algorithm. The float needs to round up to 1 to greenlight the player to keep bidding aggressively. Float calculation
		//takes in to account the number of plants the player already owns(more aggressive if owns less) and the plant position in the market(more aggressive if at higher spot in actual market)
		float action = (4 - numberOfPlantsOwned) * plantPosition;
		action = action / 16;
		action = round(action);

		if (playerBid <= highestBid && action>0 && (currentElektro/4)>highestBid) {
			cout << "Player is aggressive, owns " << numberOfPlantsOwned << " plants, has more than enough Elektros and this plant is one of the higher rated ones in the market! \nWe chose to up the bid for you!" << endl;
			return highestBid + 1;
		}
		return playerBid;
	}

	//AFFECTS PHASE 3
	//Basically makes the player fill up his resources to the max capacity as long as there's some elektro in the bank. 24 was chosen arbitrarily.
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
	//AFFECTS PHASE 2(PLANT PICKING, NOT AUCTION)
	//If the moderate player has not chosen the most efficient plant, it chooses it for him
	int pickingAction(int numberOfPlantsOwned, int currentElektro, vector<PowerPlant*> plants, int initialAction) {
		int mostEfficientPlant = -1;
		int highestEfficiency = -100;
		
		for (int i = 0; i < 4; i++) {
			int plantEfficiency = plants[i]->powersCities - plants[i]->coalRequired - plants[i]->oilRequired - plants[i]->garbageRequired - plants[i]->uraniumRequired - plants[i]->hybridRequired;
				if (plantEfficiency > highestEfficiency) {
					highestEfficiency = plantEfficiency;
					mostEfficientPlant = plants[i]->getPlantNumber();
				}
		}
		if (initialAction != mostEfficientPlant) {
			cout << "Moderate player ideally should go for the most efficient plant!\nWe chose the plant for you!";
			return mostEfficientPlant;
		}
		return initialAction;
	}

	//AFFECTS PHASE 4
	//Moderate player's target is to avoid triggering step 2(if it's already not triggered). So this function checks if the building decision will 
	//lead to step 2 and if step 2 has not already been activated. If that's not true, it avoids building, else goes with the original decision.
	int buildingAction(int numberOfCitiesOwned, int step, int step2trigger, int initialAction) {
		if (step2trigger - numberOfCitiesOwned < 2 && step<2 && initialAction!=-1) {
			cout << "Player is moderate and looking to avoid step 2! We chose not to build for now for you!";
			return -1;
		}
		return initialAction;
	}
};

class Environmentalist : public Strategy {
public:

	//AFFECTS PHASE 2 AUCTIONING(NOT PLANT PICKING)
	//If the plant being auctioned is a windmill one, the environmentalist will keep bidding higher up until a point(see if loop for details)
	int auctionAction(int numberOfPlantsOwned, int currentElektro, int plantPosition, int highestBid, int playerBid, bool environmental) {
		if (environmental == true && (currentElektro / 4) > highestBid) {
			cout << "It's a wind plant and the player is a tree hugger!\nWe chose to up the bid for you!" << endl;
			return highestBid + 1;
		}
		return playerBid;
	}
	//AFFECTS PHASE 2 PLANT PICKING(NOT AUCTIONING)
	//If the current market has a windmill plant, the environmentalist will always choose that to pick for auctioning. The for loop scans the actual market for any 
	//environmental plants, else returns the initial call the player made
	int pickingAction(int numberOfPlantsOwned, int currentElektro, vector<PowerPlant*> plants, int initialAction) {
		for (int i = 0; i < 4; i++) {
			if (plants[i]->environmentalPlant==true && (currentElektro) > 24 && numberOfPlantsOwned<4) {
					cout << "Environmentalist must always go for a wind plant if it's available\nChoosing the plant for you!" << endl;
					return plants[i]->getPlantNumber();
				}
		}
		return initialAction;
	}
};