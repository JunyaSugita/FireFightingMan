#pragma once
#include"Bullet.h"
#include"Fire.h"
#include"Map.h"
#include"Player.h"
#include"Rescued.h"
#include "Goal.h"
#include "Enemy.h"
#include "Particle.h"
#include "StageSelect.h"


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
	Particle* particle;
	StageSelect* stageSelect;
	int pad;
	int x[10];
	int y[10];
	int isPush;

public:
	Scene();
	~Scene();
	void Update(char* keys, char* oldkeys);
	void Draw();
};