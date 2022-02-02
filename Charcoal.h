#pragma once
#include "Struct.h"

class Charcoal{
public:
	Charcoal();
	~Charcoal();

public:
	void SetChar(int fireX,int fireY,int map[][50]);
	void BrockenChar(int map[][50]);

public:
	int brockenTimer[20][50];
	int isBrocken[20][50];

	int brockenSE;
};

