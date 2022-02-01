#pragma once
#include "Struct.h"
#include "Bullet.h"
#include "bullet.h"
#include "Map.h"
#include "fire.h"

class Enemy {
public:
	static const int ENEMY_CONST = 10;
	ENEMY enemy[ENEMY_CONST];
	int enemyLX[ENEMY_CONST];
	int enemyRX[ENEMY_CONST];
	int enemyX[ENEMY_CONST];
	int enemyDY[ENEMY_CONST];
	int enemyY[ENEMY_CONST];

	Map* map;
	Fire* fire;

	int hitSE;

public:
	Enemy();
	~Enemy();

	void Make(int mapChip[][50]);
	void Update(BULLET bullet[], int mapChip[][50], Fire* fire);
	void BulletColision(BULLET bullet[]);

	void Move(int mapChip[][50], Fire* fire);
};