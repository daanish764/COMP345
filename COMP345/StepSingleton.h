/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/


#pragma once


class StepSingleton
{
private:
	StepSingleton();
	~StepSingleton();
	int step;
	static StepSingleton* instance;
public:
	int getStep() const;
	void setStep(int stepNumber);
	static StepSingleton* getInstance();
};