#pragma once
#include "struct.h"
#include "Fire.h"
#include "Player.h"

class Particle {
public:
	const int PARTICLE_CONST = 2000;
	EMIT particle[2000];
	Fire* fire;
	Player* player;
	int centerX;
	int centerY;

public:
	Particle();
	~Particle();
	void Move(int x,int y,int scroll, int fireR);
	void Draw(int scroll);
};