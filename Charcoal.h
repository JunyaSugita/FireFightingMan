#pragma once
#include "Struct.h"

class Charcoal{
public:
	Charcoal();
	~Charcoal();

public:
	void SetChar(int fireX,int fireY,int map[][50]);

public:
	int brockenChar[20][50];
	int isBrocken[20][50];
	bool isChar[20][50];
};

