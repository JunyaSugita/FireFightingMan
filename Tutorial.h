#pragma once
#include "Struct.h"

class Tutorial{
public:
	Tutorial();
	~Tutorial();

public:
	void CountTimer();
	void StepUpdate(int select, int pad, int isRescued, double& playerX, int isFire, int isFire2, int isFire3);
	void NextStep();
	void Step0(int pad, double& playerX);
	void Step1(int pad, double& playerX);
	void Step2(double playerX);
	void Step3(double& playerX, int isFire, int isFire2, int isFire3);
	void Step4(int isRescued);

	void DrawTutorial(int select, int scrollint,int isRescued);

public:
	int timer;
	int step;
	static const int STEP_TIME = 50;
	int stepTimer;
	int isNext;

	int tutorial1[4];
	int tutorial2[4];
	int tutorial3[4];
	int tutorial4[4];
	int tutorial5;
	int tutorial6;
	int tutorial7;
	int help[2];
	int textSE;
	int isEx;
};

