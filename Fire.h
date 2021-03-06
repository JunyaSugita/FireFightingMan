#pragma once
#include "Struct.h"
#include "map.h"
#include "bullet.h"
#include "Smoke.h"
#include "Charcoal.h"

class Fire {
public:
	Fire();
	~Fire();

public:
	void SetFire(int map[][50]);
	void FireFighting(BULLET bullet[], Smoke* smoke, int map[][50]);
	void DeleteFire();

	void DrawFire(int scroll);
public:
	static const int FIRE_CONST = 500;
	FIRE fire[FIRE_CONST];

	Map* map;
	Bullet* bullet;
	Smoke* smoke;
	Charcoal* charcoal;

	int fireSE;
	int hitSE;
};
