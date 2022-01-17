#pragma once
#include "struct.h"
#include "Fire.h"
#include "Player.h"

class Particle {
public:
	const int PARTICLE_CONST = 30000;
	EMIT particle[30000];
	Fire* fire;
	Player* player;
	int centerX;
	int centerY;

public:
	Particle();
	~Particle();
	void Move();
	void Emit(int x, int y, int fireR);
	void DeleteParticle();

	void Draw(int scroll);
};