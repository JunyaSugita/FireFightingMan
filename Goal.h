#pragma once
#include "player.h"
#include "Rescued.h"
#include "Fire.h"

class Goal {
public:
	Player* player;
	Rescued* rescued;
	Fire* fire;
	int isGoal;
	int x;

public:
	Goal();
	~Goal();
	void GetGoal(Player* player, Rescued* rescued, int& hp, Fire* fire);
	void Gameover(int& scene, Rescued* rescued, int& hp, Player* player, Fire* fire);
	void Draw(Rescued* rescued, int scroll);
	void Reset(Rescued* rescued, int& hp);
};