#pragma once
#include "struct.h"
#include "Fire.h"
#include "Player.h"

class Particle {
public:
	static const int PARTICLE_CONST = 10000; 
	EMIT particle[PARTICLE_CONST];
	Fire* fire;
	Player* player;
	int centerX;
	int centerY;

public:
	Particle();
	~Particle();
	void Move();
	void Emit(int x, int y, int fireR, int isFire);
	void DeleteParticle();

	void Draw(int scroll);
};