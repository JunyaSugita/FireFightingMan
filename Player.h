#pragma once
#include "Struct.h"
#include "Bullet.h"
#include "Map.h"

class Player {
public:
	Player();
	~Player();
public:
	PLAYER player;
	OldPlayer oldPlayer;

	//体力
	int hp;
	int isDamage;
	int isDamageTimer;

	//水タンク
	static const int WATER_CONST = 350;
	int water;

	//プレイヤーのスピード管理
	float speed;

	//プレイヤーの上下移動慣性
	int inertia, inertiaSpeed;

	//ボタンの長押し対策
	int isButton;

	//左上の座標
	int leftTopX, leftTopY;
	//左下の座標
	int leftBottomX, leftBottomY;
	//右下の座標
	int rightTopX, rightTopY;
	//右下の座標
	int rightBottomX, rightBottomY;
	//1フレーム前の左上の座標
	int oldLeftTopX, oldLeftTopY;
	//1フレーム前の右上の座標
	int oldRightTopX, oldRightTopY;
	//1フレーム前の左下の座標
	int oldLeftBottomX, oldLeftBottomY;
	//1フレーム前の右下の座標
	int oldRightBottomX, oldRightBottomY;

	//ジャンプ管理用の座標
	int jumpLeftBottomX, jumpLeftBottomY;
	int jumpRightBottomX, jumpRightBottomY;

	//重力
	const int G = 10;

	//スクロール
	int scroll;

	//シーン管理
	int scene;

	//グラフ
	int graph_h;
	int graph_h2;
	int waterTank;

	//チュートリアル用
	int isShow;

	//弾
	Bullet* bullet;
	//マップ
	Map* map;

	//SE
	int damageSE;
	int waterSE;
	int walkSE;
	int startSE;
	int jumpSE;
	int dashSE;

public:
	void Spawn(int mapChip[][50]);

	void SaveOldPlayer();
	void GetPlayerBottom(int BLOCK_SIZE);

	void Dash(int pad, int isRescued, int inputX, int inputY);
	void PlayerMove(int LInputX, int RInputX, int RInputY, int isRescued);
	void PlayerJump(int pad, int isRescued, int map[][50]);
	void PlayerShot(int InputX, int InputY, int isRescued);
	void PlayerDamage(int fireX, int fireY, int fireR, int isFire, int isRescued, int select);
	void DamageCount();
	void GetPlayer(int BLOCK_SIZE);
	void GetOldPlayer(int BLOCK_SIZE);
	void GetScroll();
	void BlockCollision(int map[][50]);
	void DownPlayer(int map[][50], int BLOCK_SIZE);
	void CheckStick(int InputY, int isRescued);

	void DrawPlayer(int isRescued);
	void DrawHp();
	void DrawWater();
};