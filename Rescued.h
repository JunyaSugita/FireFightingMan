#pragma once
#include "struct.h"
#include "Player.h"
#include "map.h"

class Rescued {
	//
public:
	Transform transform;
	int r;
	int isRescued;
	int rescueGraph[5];
	int rescueAniTime;
	Player* player;
	int cx;
	int cy[2];
	int cr;
	int time;
	int alpha;
	int catchGraph;
	Map* map;
	int rescueSE;

	//
public:
	Rescued();
	~Rescued();

	void Spawn(int mapChip[][50]);
	void RescuedCollision(Player* player, int& hp, int scene);
	void Move(Player* player);
	void Draw(int scroll);
	void Reset();
	void CatchRescued();
};