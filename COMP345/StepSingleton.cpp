#include "StepSingleton.h"

#include<iostream>
using std::cout;
using std::endl;

StepSingleton::StepSingleton()
{
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
	//cout << "-----------------------------------------------" << endl;
	cout << "Step was set to " << step << "." << endl;
	cout << "-----------------------------------------------" << endl;
}


StepSingleton * StepSingleton::getInstance()
{
	if (instance == nullptr)
		instance = new StepSingleton();
	return instance;
}

StepSingleton* StepSingleton::instance = 0;