#pragma once
#include"Player.h"

class DamParticle {
public:
	const int TRI_CONST = 30;
	int triX[30];
	int triY[30];
	int triR;
	int cirR[2];
	int speedX[30];
	int speedY[30];
	int isDam;
	int alpha;
	int damTime;

public:
	DamParticle();
	~DamParticle();
	void Reset();
	void Draw(int x,int y,int scroll);
};