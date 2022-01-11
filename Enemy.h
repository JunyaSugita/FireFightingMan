#pragma once
#include "Struct.h"
#include "Bullet.h"
#include "bullet.h"

class Enemy {
public:
	const int ENEMY_CONST = 10;
	ENEMY enemy[10];

public:
	Enemy();
	~Enemy();

	void Make();
	void Update(BULLET bullet[]);
	void BulletColision(BULLET bullet[]);

	void Move();
	void Draw(int scll);

};