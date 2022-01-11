#pragma once
#include"Bullet.h"
#include"Fire.h"
#include"Map.h"
#include"Player.h"
#include"Rescued.h"
#include "Goal.h"
#include "Enemy.h"


class Scene {
public:
	Player* player;
	Bullet* bullet;
	Rescued* rescued;
	Map* map;
	Fire* fire;
	Goal* goal;
	DINPUT_JOYSTATE padInput;
	Enemy* ene;
	int pad;

public:
	Scene();
	~Scene();
	void Update(char* keys, char* oldkeys);
	void Draw();
};