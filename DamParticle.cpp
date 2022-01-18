#include"DamParticle.h"
#include"stdlib.h"
#include"time.h"

DamParticle::DamParticle() {
	for (int i = 0; i < TRI_CONST; i++) {
		triX[i] = 0;
		triY[i] = 0;
		triR[i] = 5;
		speedX[i] = 0;
		speedY[i] = 0;
	}
	for (int i = 0; i < 2; i++) {
		cirR[i] = 0;
	}
	srand(time(NULL));
	isDam = 0;
	alpha = 255;
}

DamParticle::~DamParticle() {

}


void DamParticle::Reset() {
	isDam = 0;
}


void DamParticle::Draw(int x,int y,int scroll) {
	if (isDam == 0) {
		for (int i = 0; i < 30; i++) {
			if (speedX[i] == 0) {
				speedX[i] = rand() % 11 - 5;
			}
			if (speedY[i] == 0) {
				speedY[i] = rand() % 11 - 5;
			}
			triX[i] = x;
			triY[i] = y;
		}
		for (int i = 0; i < 2; i++) {
			cirR[i] = 0;
		}
		alpha = 255;
		isDam = 1;
	}
	else {
		for (int i = 0; i < 30; i++) {
			triX[i] += speedX[i];
			triY[i] += speedY[i];
		}
		cirR[0] += 5;
		cirR[1] += 3;
		alpha -= 4;
	}

	SetDrawBlendMode(DX_BLENDMODE_ADD, 144);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 30; i++) {
			DrawCircle(x - scroll, y, cirR[0] - (1 * i), GetColor(32, 128, 255), false);
		}
		for (int i = 0; i < 30; i++) {
			DrawCircle(x - scroll, y, cirR[1] - (1 * i), GetColor(32, 128, 255), false);
		}
	}

	for (int i = 0; i < TRI_CONST; i++) {
		DrawTriangle(x + triR[i], y + triR[i], x + triR[i], y + triR[i], x - triR[i], y - triR[i], GetColor(0, 96, 255), true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}