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