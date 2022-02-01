#pragma once
#include "Struct.h"

class Tutorial{
public:
	Tutorial();
	~Tutorial();

public:
	void StepUpdate(int select, int pad, int isRescued, double& playerX, int isFire, int isFire2, int isFire3, int scene);

	void DrawTutorial(int select, int scrollint,int isRescued,int isShow);

public:
	int timer;
	int step;
	static const int STEP_TIME = 50;
	int isNext;
	int isPush;
	int isCom[6];
	int textNum;


	int help[2];
	int textSE;
	int isEx;
};

