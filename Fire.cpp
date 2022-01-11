#include "Fire.h"

Fire::Fire() {
	for (int i = 0; i < FIRE_CONST; i++) {
		fire[i] = {
			{
				0,
				0
			},
			0,
			0,
			0
		};
	}

	map = new Map;
	bullet = new Bullet;
}

Fire::~Fire() {
	delete map;
	delete bullet;
}

void Fire::SetFire(int mapChip[][50]) {
	for (int y = 0; y < map->mapCountY; y++) {
		for (int x = 0; x < map->mapCountX; x++) {
			if (mapChip[y][x] == FLAME) {
				for (int i = 0; i < FIRE_CONST; i++) {
					if (fire[i].isFire == false) {
						fire[i].transform.x = x * map->BLOCK_SIZE + (map->BLOCK_SIZE / 2);
						fire[i].transform.y = (y + 1) * map->BLOCK_SIZE;
						fire[i].Xr = map->BLOCK_SIZE / 2;
						fire[i].Yr = map->BLOCK_SIZE;
						fire[i].isFire = true;
						break;
					}
				}
			}
		}
	}
}

void Fire::FireFighting(BULLET bullet[]) {
	for (int i = 0; i < FIRE_CONST; i++) {
		for (int j = 0; j < this->bullet->BULLET_CONST; j++) {
			if (fire[i].isFire == true && bullet[j].isBullet == true) {
				if (fire[i].transform.x + fire[i].Xr > bullet[j].transform.x - this->bullet->bullet[j].r &&
					fire[i].transform.x - fire[i].Xr < bullet[j].transform.x + this->bullet->bullet[j].r &&
					fire[i].transform.y + fire[i].Yr > bullet[j].transform.y - this->bullet->bullet[j].r &&
					fire[i].transform.y - fire[i].Yr < bullet[j].transform.y + this->bullet->bullet[j].r) {

					fire[i].Xr -= 2;
					fire[i].Yr -= 4;
					bullet[j].isBullet = false;

					if (fire[i].Xr <= 0 || fire[i].Yr <= 0) {
						fire[i].isFire = false;
					}
				}
			}
		}
	}
}

void Fire::DrawFire(int scroll) {
	for (int i = 0; i < FIRE_CONST; i++) {
		if (fire[i].isFire == 1) {
			DrawBox(fire[i].transform.x - fire[i].Xr - scroll, fire[i].transform.y - fire[i].Yr,
				fire[i].transform.x + fire[i].Xr - scroll, fire[i].transform.y + fire[i].Yr,
				GetColor(255, 0, 0), true);
		}
	}
}