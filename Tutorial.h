#pragma once
#include "Struct.h"

class Tutorial{
public:
	Tutorial();
	~Tutorial();

public:

	void DrawTutorial(int select, int scrollint,int isRescued,int isShow);

public:
	int timer;
	int step;
	static const int STEP_TIME = 50;
	int isPush;
	int isCom[6];
	int textNum;
	int lostNum;

	int exNum[4];
	int help[2];
	int textSE;
	int isEx;
};

