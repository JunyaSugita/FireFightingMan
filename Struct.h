#pragma once
#include "Global.h"

typedef struct {
	double x;
	double y;
} Transform;

//プレイヤーの定義
typedef struct {
	Transform transform;
	int r;
	int isJump;
	int jumpPow;
} PLAYER;

//前フレームのプレイヤーの定義
typedef struct {
	int x;
	int y;
}OldPlayer;

//水の定義
typedef struct {
	Transform transform;
	int r;
	float speedX;
	float speedY;
	int isBullet;
}BULLET;

//火の定義
typedef struct {
	Transform transform;
	int Xr;
	int Yr;
	int isFire;
}FIRE;

//敵の定義
typedef struct {
	Transform transform;
	int r;
	double Xs;
	double Ys;
	int isAlive;
	int hp;
	int time;
	int coolTime;
	int way;
}ENEMY;

//パーティクル
typedef struct {
	Transform transform;
	int r;
	float speedX;
	float speedY;
	int isEmit;
	int timer;
	int alpha;
}EMIT;