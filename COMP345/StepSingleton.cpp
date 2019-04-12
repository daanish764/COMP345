/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/


#include "StepSingleton.h"

#include<iostream>
using std::cout;
using std::endl;

StepSingleton::StepSingleton()
{
	// step 1 and lazy loading 
	// only when step incease to 2 an object was created
	step = 1;
	instance = nullptr;
}


StepSingleton::~StepSingleton()
{
	delete instance;
	instance = nullptr;
}

int StepSingleton::getStep() const
{
	return step;
}

void StepSingleton::setStep(int stepNumber)
{
	// only increment the step up to 3
	if (stepNumber >= 1 && step <= 3)
		step = stepNumber;
}


StepSingleton * StepSingleton::getInstance()
{
	// if the instance is not already created make one and then if it doesn't exist return the current instance
	// it'll guarentee only 1 intance of the singleton
	if (instance == nullptr)
		instance = new StepSingleton();
	return instance;
}

StepSingleton* StepSingleton::instance = 0;
