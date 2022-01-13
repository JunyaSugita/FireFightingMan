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
	void RescuedCollision(Player* player);
	void Move(Transform transform);
	void Draw(int scroll);
};