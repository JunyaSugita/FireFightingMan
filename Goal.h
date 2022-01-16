#pragma once
#include "player.h"
#include "Rescued.h"

class Goal {
public:
	Player* player;
	Rescued* rescued;
	int isGoal;
	int x;

public:
	Goal();
	~Goal();
	void GetGoal(Player* player, Rescued* rescued, int& hp);
	void Gameover(int& scene, Rescued* rescued, int hp);
	void Draw(Rescued* rescued, int scroll);
	void Reset(Rescued* rescued, int& hp);
};