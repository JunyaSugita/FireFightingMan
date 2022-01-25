#pragma once
#include "Bullet.h"
#include "Fire.h"
#include "Map.h"
#include "Player.h"
#include "Rescued.h"
#include "Goal.h"
#include "Enemy.h"
#include "Particle.h"
#include "StageSelect.h"
#include "Gameover.h"
#include "Tutorial.h"
#include "Damparticle.h"
#include "Pause.h"

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
	Gameover* gameover;
	Tutorial* tutorial;
	DamParticle* damParticle;
	Pause* pause;

	int pad;
	int x;
	int y;
	int isPush;
	int time;
	int isChange;

public:
	Scene();
	~Scene();
	void Update(char* keys, char* oldkeys);
	void Draw();
	void reset();
	void restart();
};