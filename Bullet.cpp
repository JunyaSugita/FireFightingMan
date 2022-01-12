#include "Bullet.h"
#include "time.h"

Bullet::Bullet() {
	for (int i = 0; i < BULLET_CONST; i++) {
		bullet[i] = {
			{
				0,
				0
			},
			8,
			0,
			0,
			false
		};
		//左上の座標
		leftTopX[i] = 0;
		leftTopY[i] = 0;
		//左下の座標
		leftBottomX[i] = 0;
		leftBottomY[i] = 0;
		//右下の座標
		rightTopX[i] = 0;
		rightTopY[i] = 0;
		//右下の座標
		rightBottomX[i] = 0;
		rightBottomY[i] = 0;
	}

	map = new Map;

	srand(time(NULL));
}

Bullet::~Bullet() {
	delete map;
}

void Bullet::BulletShot(Transform transform, int x, int y) {
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < BULLET_CONST; i++) {
			if (bullet[i].isBullet == false) {
				bullet[i].isBullet = true;
				bullet[i].transform.x = transform.x;
				bullet[i].transform.y = transform.y - 10;
				bullet[i].speedX = x / 50 + rand() % 3 - 1;
				bullet[i].speedY = y / 50 + rand() % 3 - 1;
				break;
			}
		}
	}
}

void Bullet::BulletMove(const int G) {
	for (int i = 0; i < BULLET_CONST; i++) {
		if (bullet[i].isBullet == true) {
			bullet[i].transform.x += bullet[i].speedX;
			bullet[i].transform.y += bullet[i].speedY;
			bullet[i].speedY++;
		}
	}
}

void Bullet::GetBullet(int BLOCK_SIZE) {
	for (int i = 0; i < BULLET_CONST; i++) {
		//左上の座標の取得
		leftTopX[i] = (bullet[i].transform.x - bullet[i].r) / BLOCK_SIZE;
		leftTopY[i] = (bullet[i].transform.y - bullet[i].r) / BLOCK_SIZE;
		//右上の座標の取得
		rightTopX[i] = (bullet[i].transform.x + bullet[i].r - 1) / BLOCK_SIZE;
		rightTopY[i] = (bullet[i].transform.y - bullet[i].r) / BLOCK_SIZE;
		//左下の座標の取得
		leftBottomX[i] = (bullet[i].transform.x - bullet[i].r) / BLOCK_SIZE;
		leftBottomY[i] = (bullet[i].transform.y + bullet[i].r - 1) / BLOCK_SIZE;
		//右下の座標の取得
		rightBottomX[i] = (bullet[i].transform.x + bullet[i].r - 1) / BLOCK_SIZE;
		rightBottomY[i] = (bullet[i].transform.y + bullet[i].r - 1) / BLOCK_SIZE;
	}
}

void Bullet::BlockCollision(int map[][50]) {
	for (int i = 0; i < 500; i++) {
		if (bullet[i].isBullet == true) {
			if (map[leftTopY[i]][leftTopX[i]] == BLOCK) {
				bullet[i].isBullet = false;
			}
			if (map[leftBottomY[i]][leftBottomX[i]] == BLOCK) {
				bullet[i].isBullet = false;
			}
			if (map[rightTopY[i]][rightTopX[i]] == BLOCK) {
				bullet[i].isBullet = false;
			}
			if (map[rightBottomY[i]][rightBottomX[i]] == BLOCK) {
				bullet[i].isBullet = false;
			}
		}
	}
}


void Bullet::DrawBullet(int scroll) {
	for (int i = 0; i < BULLET_CONST; i++) {
		if (bullet[i].isBullet == true) {
			DrawCircle(bullet[i].transform.x - scroll, bullet[i].transform.y, bullet[i].r, GetColor(150, 200, 255), true);
		}
	}
}