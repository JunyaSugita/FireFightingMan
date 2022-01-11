#pragma once
#include "Struct.h"
#include "map.h"
#include "bullet.h"

class Fire {
public:
	Fire();
	~Fire();

public:
	void SetFire(int map[][50]);
	void FireFighting(BULLET bullet[]);

	void DrawFire(int scroll);
public:
	const int FIRE_CONST = 50;
	FIRE fire[50];

	Map* map;
	Bullet* bullet;
};
