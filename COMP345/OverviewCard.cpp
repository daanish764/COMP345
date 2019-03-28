/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#include "OverviewCard.h"
#include "Player.h"
#include <iostream>
using namespace std;


OverviewCard::OverviewCard()
{

}

OverviewCard::~OverviewCard()
{
	delete owner;
	owner = NULL;
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