#include "OverviewCard.h"
#include "Player.h"
#include <iostream>
using namespace std;


OverviewCard::OverviewCard()
{

}

OverviewCard::OverviewCard(int num)
{
	this->overviewCardNumber = num;
}


void OverviewCard::setOwner(Player* name) {
	this->owner = name;
}

const Player* OverviewCard::getOwner() const {
	return this->owner;
}

void OverviewCard::printDescription() const
{
	cout << "OverViewCard: " << this->getOwner()->getName() << "\n" << this->description << endl;
}