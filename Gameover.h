#pragma once
#include "Struct.h"
#include "Rescued.h"
#include "Player.h"
#include "Fire.h"
#include "Goal.h"
#include "Particle.h"
#include "Bullet.h"

class Gameover {
public:
	Gameover();
	~Gameover();

public:
	void GotoGameover(int& scene, int& hp);
	void GotoTitle(int pad, Rescued* rescued, Player* player, Fire* fire, Goal* goal, Particle* particle, Bullet* bullet);

	void DrawGameover();
};

