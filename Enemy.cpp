#include "Enemy.h"
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"



Enemy::Enemy() {
	for (int i = 0; i < ENEMY_CONST; i++) {
		enemy[i].isAlive = 0;
		enemy[i].transform.x = 0;
		enemy[i].transform.y = 0;
		enemy[i].r = 32;
		enemy[i].time = 0;
		enemy[i].coolTime = 0;
		enemy[i].hp = 80;
		enemy[i].way = 0;
		enemy[i].Xs = 1;
		enemy[i].Ys = 0;
	}

	map = new Map;
}
Enemy::~Enemy() {
	delete map;
}

void Enemy::Make(int mapChip[][50]) {
	for (int y = 0; y < map->mapCountY; y++) {
		for (int x = 0; x < map->mapCountX; x++) {
			if (mapChip[y][x] == FLAMEENEMY) {
				for (int i = 0; i < ENEMY_CONST; i++)
				{
					if (enemy[i].isAlive == 0 && enemy[i].coolTime <= 0) {
						enemy[i].transform.x = x * map->BLOCK_SIZE + (map->BLOCK_SIZE / 2);
						enemy[i].transform.y = (y + 1) * map->BLOCK_SIZE;

						enemy[i].time = GetRand(49);
						enemy[i].isAlive = 1;
						break;
					}
				}
			}
		}
	}

}

void Enemy::Update(BULLET bullet[], Map* map) {
	for (int i = 0; i < ENEMY_CONST; i++)
	{
		if (map == nullptr) {
			return;
		}
		BulletColision(bullet);
		Move();
		Make(map->map);

	}

}
void Enemy::BulletColision(BULLET bullet[]) {
	for (int i = 0; i < ENEMY_CONST; i++) {
		for (int j = 0; j < 500; j++) {
			if (enemy[i].isAlive == 1 && bullet[j].isBullet == 1) {
				if ((enemy[i].r + bullet[j].r) * (enemy[i].r + bullet[j].r) >=
					(bullet[j].transform.x - enemy[i].transform.x) * (bullet[j].transform.x - enemy[i].transform.x) +
					(bullet[j].transform.y - enemy[i].transform.y) * (bullet[j].transform.y - enemy[i].transform.y)) {

					bullet[j].isBullet = 0;
					enemy[i].isAlive = 0;
					enemy[i].coolTime = 3000;
				}
			}
		}
	}
}

void Enemy::Move() {
	for (int i = 0; i < ENEMY_CONST; i++) {
		enemy[i].coolTime--;
		if (enemy[i].coolTime <= 0) {
			enemy[i].coolTime = 0;
		}
		if (enemy[i].isAlive == 1) {


			enemy[i].time++;

			if (enemy[i].way == 0) {
				if (0 < enemy[i].time && enemy[i].time < 50) {
					//taiki
					enemy[i].transform.x += 0;
				}
				if (50 < enemy[i].time && enemy[i].time < 200) {
					enemy[i].transform.x += enemy[i].Xs;
				}
				if (200 < enemy[i].time) {
					enemy[i].time = GetRand(49);
					enemy[i].way = 1;
					enemy[i].coolTime = (GetRand(40) + 100);
				}
			}

			if (enemy[i].way == 1) {
				if (0 < enemy[i].time && enemy[i].time < 50) {
					//taiki
					enemy[i].transform.x += 0;
				}
				if (50 < enemy[i].time && enemy[i].time < 200) {
					enemy[i].transform.x -= enemy[i].Xs;
				}
				if (200 < enemy[i].time) {
					enemy[i].time = GetRand(49);
					enemy[i].way = 0;
					enemy[i].coolTime = (GetRand(40) + 100);
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