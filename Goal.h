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
	int isShow;
	int efectX[10];
	int isMove[10];
	int randNum[10];
	int time;
	int goalSE;
	int goalGraph[2];

public:
	Goal();
	~Goal();
	void GetGoal(Player* player, Rescued* rescued, int& hp, Fire* fire);
	void Draw(Rescued* rescued, int scroll);
	void Reset(Rescued* rescued, int& hp);
	void Efect();
};