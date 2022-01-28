#pragma once
#include"Global.h"

class Smoke {
public:
	static const int SMOKE_FLAME_MAX = 4;
	int smokeGraph[SMOKE_FLAME_MAX];
	int flameCount;
	int animFlame;
	int smokeDensity;
	float currentFlameRatio;
	
public:
	Smoke();
	~Smoke();
	void Move();
	void Draw();
};