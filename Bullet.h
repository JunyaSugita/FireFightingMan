#pragma once
#include "Struct.h"
#include "Map.h"

class Bullet {
public:
	Bullet();
	~Bullet();

public:
	void BulletShot(Transform transform, int x, int y);
	void BulletMove(const int G);
	void GetBullet(int BLOCK_SIZE);
	void BlockCollision(int map[][50]);

	void DrawBullet(int scroll);
public:
	const int BULLET_CONST = 500;
	BULLET bullet[500];

	//左上の座標
	int leftTopX[500];
	int leftTopY[500];
	//左下の座標
	int leftBottomX[500];
	int	leftBottomY[500];
	//右下の座標
	int rightTopX[500];
	int rightTopY[500];
	//右下の座標
	int rightBottomX[500];
	int rightBottomY[500];

	//マップ
	Map* map;
};