#pragma once
#include "Struct.h"

class Tutorial{
public:
	Tutorial();
	~Tutorial();

public:
	void CountTimer();

	void DrawTutorial(int select, int scrollint,int isRescued);

public:
	int timer;

	int tutorial1[4];
	int tutorial2[4];
	int tutorial3[4];
	int tutorial4[4];
	int tutorial5;
	int tutorial6;
	int tutorial7;
	int help[2];
};

