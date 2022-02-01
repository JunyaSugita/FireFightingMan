#pragma once
#include "Struct.h"

class Charcoal{
public:
	Charcoal();
	~Charcoal();

public:
	void SetChar(int fireX,int fireY,int map[][50]);

public:
	static const int CHAR_CONST = 50;
	int x[CHAR_CONST];
	int y[CHAR_CONST];
	int isChar[CHAR_CONST];
};

