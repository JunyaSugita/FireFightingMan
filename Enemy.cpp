#include "Enemy.h"
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"

Enemy::Enemy() {
	for (int i = 0; i < ENEMY_CONST; i++) {
		enemy[i].hp = 0;
		enemy[i].transform.x = 0;
		enemy[i].transform.y = 0;
		enemy[i].arrow = 0;
		enemyLX[i] = 0;
		enemyRX[i] = 0;
		enemyX[i] = 0;
		enemyDY[i] = 0;
		enemyY[i] = 0;
	}
	map = new Map;
	fire = new Fire;

	hitSE = LoadSoundMem("sound/hit.wav");

	ChangeVolumeSoundMem(180, hitSE);
}
Enemy::~Enemy() {
	delete map;
	delete fire;
}

void Enemy::Make(int mapChip[][50]) {
	for (int y = 0; y < map->mapCountY; y++) {
		for (int x = 0; x < map->mapCountX; x++) {
			if (mapChip[y][x] == FLAMEENEMY) {
				for (int i = 0; i < ENEMY_CONST; i++) {
					if (enemy[i].hp == 0) {
						enemy[i].transform.x = x * map->BLOCK_SIZE + (map->BLOCK_SIZE / 2);
						enemy[i].transform.y = y * map->BLOCK_SIZE + (map->BLOCK_SIZE / 2);
						enemy[i].hp = 64;
						break;
					}
				}
			}
		}
	}

}

void Enemy::Update(BULLET bullet[], int mapChip[][50]) {
	BulletColision(bullet);
	Move(mapChip);
}
void Enemy::FireColision(double fireX, double fireY, int fireXr, int fireYr, int isFire) {
	for (int i = 0; i < ENEMY_CONST; i++) {
		if (enemy[i].hp > 0 && isFire == true) {
			if (fireX - fireXr < enemy[i].transform.x + (enemy[i].hp / 4) &&
				enemy[i].transform.x - (enemy[i].hp / 4) < fireX + fireXr &&
				fireY - fireYr < enemy[i].transform.y + (enemy[i].hp / 4) &&
				enemy[i].transform.y - (enemy[i].hp / 4) < fireY + fireYr) {
				if (enemy[i].arrow == 0) {
					enemy[i].arrow = 1;
				}
				else if (enemy[i].arrow == 1) {
					enemy[i].arrow = 0;
				}
			}
		}
	}
}

void Enemy::BulletColision(BULLET bullet[]) {
	for (int i = 0; i < ENEMY_CONST; i++) {
		for (int j = 0; j < 5000; j++) {
			if (enemy[i].hp > 0 && bullet[j].isShot == 1) {
				if (((enemy[i].hp / 4) + bullet[j].r) * ((enemy[i].hp / 4) + bullet[j].r) >=
					(bullet[j].transform.x - enemy[i].transform.x) * (bullet[j].transform.x - enemy[i].transform.x) +
					(bullet[j].transform.y - enemy[i].transform.y) * (bullet[j].transform.y - enemy[i].transform.y)) {

					bullet[j].isShot = 0;
					enemy[i].hp--;
					if (enemy[i].hp == 5) {
						PlaySoundMem(hitSE, DX_PLAYTYPE_BACK, true);
					}
				}
			}
		}
	}
}

void Enemy::Move(int map[][50]) {
	for (int i = 0; i < ENEMY_CONST; i++) {
		enemyRX[i] = (enemy[i].transform.x + enemy[i].hp - 1) / this->map->BLOCK_SIZE;
		enemyLX[i] = (enemy[i].transform.x - enemy[i].hp) / this->map->BLOCK_SIZE;

		enemyX[i] = enemy[i].transform.x / this->map->BLOCK_SIZE;
		enemyDY[i] = (enemy[i].transform.y + (enemy[i].hp / 4) - 1) / this->map->BLOCK_SIZE;
		enemyY[i] = enemy[i].transform.y / this->map->BLOCK_SIZE;
		for (int j = 0; j < ENEMY_CONST; j++) {


			//xŽ²ˆÚ“®
			if (enemy[i].arrow == 0) {
				if (enemy[i].hp > 0 && enemy[j].hp > 0) {
					enemy[i].transform.x--;
					if (map[enemyY[i]][enemyLX[i] + 1] == BLOCK || map[enemyY[i]][enemyLX[i] + 1] == CHARCOAL) {
						enemy[i].arrow = 1;
					}
					else if (map[enemyDY[i]][enemyLX[i] + 1] != BLOCK && map[enemyDY[i]][enemyLX[i] + 1] != CHARCOAL) {
						enemy[i].transform.x += 2;
						enemy[i].arrow = 1;
					}

					if (i == j) {
						break;
					}
					else if (enemy[j].transform.x - (enemy[j].hp / 4) < enemy[i].transform.x + (enemy[i].hp / 4) &&
						enemy[i].transform.x - (enemy[i].hp / 4) < enemy[j].transform.x + (enemy[j].hp / 4) &&
						enemy[j].transform.y - (enemy[j].hp / 4) < enemy[i].transform.y + (enemy[i].hp / 4) &&
						enemy[i].transform.y - (enemy[i].hp / 4) < enemy[j].transform.y + (enemy[j].hp / 4)) {

						enemy[i].arrow = 1;
						enemy[j].arrow = 0;
					}
				}
			}
			else if (enemy[i].arrow == 1) {
				if (enemy[i].hp > 0 && enemy[j].hp > 0) {
					enemy[i].transform.x++;
					if (map[enemyY[i]][enemyRX[i] - 1] == BLOCK || map[enemyY[i]][enemyRX[i] - 1] == CHARCOAL) {
						enemy[i].arrow = 0;
					}
					else if (map[enemyDY[i]][enemyRX[i] - 1] != BLOCK && map[enemyDY[i]][enemyRX[i] - 1] != CHARCOAL) {
						enemy[i].transform.x -= 2;
						enemy[i].arrow = 0;
					}

					if (i == j) {
						break;
					}
					else if (enemy[j].transform.x - (enemy[j].hp / 4) < enemy[i].transform.x + (enemy[i].hp / 4) &&
						enemy[i].transform.x - (enemy[i].hp / 4) < enemy[j].transform.x + (enemy[j].hp / 4) &&
						enemy[j].transform.y - (enemy[j].hp / 4) < enemy[i].transform.y + (enemy[i].hp / 4) &&
						enemy[i].transform.y - (enemy[i].hp / 4) < enemy[j].transform.y + (enemy[j].hp / 4)) {

						enemy[i].arrow = 0;
						enemy[j].arrow = 1;
					}
				}
			}
		}
		//yŽ²ˆÚ“®
		enemy[i].transform.y += 1;
		if (map[enemyDY[i]][enemyX[i]] == BLOCK) {
			enemy[i].transform.y--;
		}
		else if (map[enemyDY[i]][enemyX[i]] == CHARCOAL) {
			enemy[i].transform.y--;
		}

		if (enemy[i].hp <= 16) {
			enemy[i].hp = 0;
		}
	}
}

void Enemy::Debug(Fire* fire, int scroll) {
	for (int i = 0; i < ENEMY_CONST; i++) {
		DrawBox(enemy[i].transform.x - (enemy[i].hp / 4) - scroll, enemy[i].transform.y - (enemy[i].hp / 4), enemy[i].transform.x + (enemy[i].hp / 4) - scroll, enemy[i].transform.y + (enemy[i].hp / 4), GetColor(255, 255, 255), true);
		DrawBox(fire->fire[i].transform.x - fire->fire[i].Xr - scroll, fire->fire[i].transform.y - fire->fire[i].Yr, fire->fire[i].transform.x + fire->fire[i].Xr - scroll, fire->fire[i].transform.y + fire->fire[i].Yr, GetColor(255, 255, 255), true);
	}
}