#pragma once
#include"Player.h"

class DamParticle {
public:
	const int TRI_CONST = 40;
	int triX[40];
	int triY[40];
	int triR;
	int cirR[2];
	int speedX[40];
	int speedY[40];
	int isDam;
	int alpha;
	int damTime;
	int triAlpha;
	int isShow;

public:
	DamParticle();
	~DamParticle();
	void Reset();
	void Draw(int x,int y,int scroll);
};