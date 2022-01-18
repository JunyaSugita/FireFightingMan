#pragma once
#include "struct.h"
#include "Player.h"

class Rescued {
	//
public:
	Transform transform;
	int r;
	int isRescued;
	Player* player;

	//
public:
	Rescued();
	~Rescued();
	void RescuedCollision(Player* player, int& hp, int scene);
	void Move(Player* player);
	void Draw(int scroll);
	void Reset();
};