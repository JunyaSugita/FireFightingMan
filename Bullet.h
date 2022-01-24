#pragma once
#include "Struct.h"
#include "Map.h"

class Bullet {
public:
	Bullet();
	~Bullet();
	
public:
	void BulletShot(Transform transform, int x, int y);
	void BulletMove(const int G,int x,int y);
	void GetBullet(int BLOCK_SIZE);
	void BlockCollision(int map[][50]);
	void DeleteBullet();

	void DrawBullet(int scroll);
public:
	static const int BULLET_CONST = 5000;

	BULLET bullet[BULLET_CONST];

	//水の左右への広がり
	int randNum[BULLET_CONST];


	//左上の座標
	int leftTopX[ BULLET_CONST];
	int leftTopY[BULLET_CONST];
	//左下の座標
	int leftBottomX[BULLET_CONST];
	int	leftBottomY[BULLET_CONST];
	//右下の座標
	int rightTopX[BULLET_CONST];
	int rightTopY[BULLET_CONST];
	//右下の座標
	int rightBottomX[BULLET_CONST];
	int rightBottomY[BULLET_CONST];

	//水透明度
	int alpha[BULLET_CONST];
	int alphaTime[BULLET_CONST];

	//マップ
	Map* map;
};