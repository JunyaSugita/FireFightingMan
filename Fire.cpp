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
	
	fireSE = LoadSoundMem("sound/fire.mp3");
	hitSE = LoadSoundMem("sound/hit.wav");

	ChangeVolumeSoundMem(130, fireSE);
	ChangeVolumeSoundMem(180, hitSE);
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

void Fire::FireFighting(BULLET bullet[],Smoke* smoke,int map[][50]) {
	for (int i = 0; i < FIRE_CONST; i++) {
		for (int j = 0; j < this->bullet->BULLET_CONST; j++) {
			if (fire[i].isFire == true && bullet[j].isShot == true) {
				if (fire[i].transform.x + fire[i].Xr > bullet[j].transform.x - this->bullet->bullet[j].r &&
					fire[i].transform.x - fire[i].Xr < bullet[j].transform.x + this->bullet->bullet[j].r &&
					fire[i].transform.y + fire[i].Yr > bullet[j].transform.y - this->bullet->bullet[j].r &&
					fire[i].transform.y - fire[i].Yr < bullet[j].transform.y + this->bullet->bullet[j].r) {

					fire[i].Xr -= 1;
					fire[i].Yr -= 2;
					bullet[j].isShot = false;
					
					if (fire[i].Xr <= 5 || fire[i].Yr <= 10) {
						charcoal->SetChar(fire[i].transform.x, fire[i].transform.y,map);
						fire[i].isFire = false;
						fire[i].Xr = 0;
						fire[i].Yr = 0;
						if (smoke->smokeDensity > -2) {
							smoke->smokeDensity-= 2;
						}
						PlaySoundMem(hitSE, DX_PLAYTYPE_BACK, true);
					}
				}
			}
		}
	}

	for (int i = 0; i < FIRE_CONST; i++) {
		if (fire[i].isFire == true) {
			if (CheckSoundMem(fireSE) == false) {
				PlaySoundMem(fireSE, DX_PLAYTYPE_BACK, true);
			}
		}
	}
}

void Fire::DeleteFire() {
	for (int i = 0; i < FIRE_CONST; i++) {
		fire[i].isFire = false;
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