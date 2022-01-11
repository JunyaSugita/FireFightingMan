#include "Enemy.h"
#include "DxLib.h"
#include "Struct.h"



Enemy::Enemy() {
	for (int i = 0; i < ENEMY_CONST; i++) {
		enemy[i].isAlive = 0;
		enemy[i].transform.x = 0;
		enemy[i].transform.y = 0;
		enemy[i].r = 32;
		enemy[i].time = 0;
		enemy[i].hp = 800;
	}
}
Enemy::~Enemy() {

}

void Enemy::Make() {
	for (int i = 0, z = 0; i < ENEMY_CONST; i++)
	{
		if (enemy[i].isAlive == 0) {
			enemy[i].transform.x = 300 + z;
			enemy[i].transform.y = 300 + z;

			z += 30;
			enemy[i].isAlive = 1;
		}


	}

}
void Enemy::Update(BULLET bullet[]) {
	for (int i = 0; i < ENEMY_CONST; i++)
	{
		BulletColision(bullet);
		Move();
		Make();


	}

}
void Enemy::BulletColision(BULLET bullet[]) {
	for (int i = 0; i < ENEMY_CONST; i++) {
		for (int j = 0; j < 500; j++) {
			if (enemy[i].isAlive == 1 && bullet[j].isBullet) {
				if ((enemy[i].r + bullet[j].r) * (enemy[i].r + bullet[j].r) >=
					(bullet[j].transform.x - enemy[i].transform.x) * (bullet[j].transform.x - enemy[i].transform.x) +
					(bullet[j].transform.y - enemy[i].transform.y) * (bullet[j].transform.y - enemy[i].transform.y)) {

					bullet[j].isBullet = 0;
					enemy[i].isAlive = 0;
				}
			}
		}
	}
}

void Enemy::Move() {
	for (int i = 0; i < ENEMY_CONST; i++) {
		if (enemy[i].isAlive == 1) {

			enemy[i].time++;
			if (enemy[i].way == 0) {
				if (0 < enemy[i].time && enemy[i].time < 50) {
					//taiki
					enemy[i].transform.x += 0;
				}
				if (50 < enemy[i].time && enemy[i].time < 200) {
					enemy[i].transform.x -= enemy[i].Xr;
				}
				if (200 < enemy[i].time) {
					enemy[i].time = 0;
					enemy[i].way = 1;
				}
			}

			if (enemy[i].way == 1) {
				if (0 < enemy[i].time && enemy[i].time < 50) {
					//taiki
					enemy[i].transform.x += 0;
				}
				if (50 < enemy[i].time && enemy[i].time < 200) {
					enemy[i].transform.x -= enemy[i].Xr;
				}
				if (200 < enemy[i].time) {
					enemy[i].time = 0;
					enemy[i].way = 1;
				}
			}

		}
	}
}

void Enemy::Draw(int scll) {
	for (int i = 0; i < ENEMY_CONST; i++) {
		if (enemy[i].isAlive == 1) {
			DrawCircle(enemy[i].transform.x - scll, enemy[i].transform.y, enemy[i].r, GetColor(255, 123, 0), true);
		}
	}
}