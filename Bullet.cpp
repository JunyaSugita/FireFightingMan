#include "Bullet.h"
#include "time.h"

Bullet::Bullet() {
	for (int i = 0; i < BULLET_CONST; i++) {
		bullet[i] = {
			{
				0,
				0
			},
			10,
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
	for (int j = 0; j <15; j++) {
		for (int i = 0; i < BULLET_CONST; i++) {
			if (bullet[i].isShot == false) {
				bullet[i].isShot = true;
				bullet[i].transform.x = transform.x;
				bullet[i].transform.y = transform.y - 10;
				bullet[i].speedX = x / 50 + rand() % 3 - 1;
				bullet[i].speedY = y / 80 + rand() % 3 - 1;
				break;
			}
		}
	}
}

void Bullet::BulletMove(const int G,int x, int y) {
	for (int i = 0; i < BULLET_CONST; i++) {
		if (bullet[i].isShot == true) {
			bullet[i].speedX = rand() % 5 - 2;
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
	for (int i = 0; i < BULLET_CONST; i++) {
		if (bullet[i].isShot == true) {
			if (map[leftTopY[i]][leftTopX[i]] == BLOCK) {
				bullet[i].isShot = false;
			}
			if (map[leftBottomY[i]][leftBottomX[i]] == BLOCK) {
				bullet[i].isShot = false;
			}
			if (map[rightTopY[i]][rightTopX[i]] == BLOCK) {
				bullet[i].isShot = false;
			}
			if (map[rightBottomY[i]][rightBottomX[i]] == BLOCK) {
				bullet[i].isShot = false;
			}
		}
	}
}

void Bullet::DeleteBullet() {
	for (int i = 0; i < BULLET_CONST; i++) {
		bullet[i].isShot = false;
	}
}

void Bullet::DrawBullet(int scroll) {
	SetDrawBlendMode(DX_BLENDMODE_ADD, 72);
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < BULLET_CONST; i++) {
			if (bullet[i].isShot == true) {
				DrawCircle(bullet[i].transform.x - scroll, bullet[i].transform.y, bullet[i].r, GetColor(12, 16, 16), true);
				DrawCircle(bullet[i].transform.x - scroll, bullet[i].transform.y, bullet[i].r - 8, GetColor(1, 3, 4), true);
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}