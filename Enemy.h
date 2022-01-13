#pragma once
#include "Struct.h"
#include "Bullet.h"
#include "bullet.h"
#include "Map.h"

class Enemy {
public:
	const int ENEMY_CONST = 10;
	ENEMY enemy[10];

	Map* map;

public:
	Enemy();
	~Enemy();

	void Make(int mapChip[][50]);
	void Update(BULLET bullet[], Map* map);
	void BulletColision(BULLET bullet[]);

	void Move();
	void Draw(int scll);

};