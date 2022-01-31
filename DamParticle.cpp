#include"DamParticle.h"
#include"stdlib.h"
#include"time.h"

DamParticle::DamParticle() {
	for (int i = 0; i < TRI_CONST; i++) {
		triX[i] = 0;
		triY[i] = 0;
		speedX[i] = 0;
		speedY[i] = 0;
	}
	for (int i = 0; i < 2; i++) {
		cirR[i] = 0;
	}
	srand(time(NULL));
	triR = 8;
	isDam = 0;
	alpha = 255;
	damTime = 0;
	triAlpha = 255;
	isShow = 1;
}

DamParticle::~DamParticle() {

}


void DamParticle::Reset() {
	isDam = 0;
	for (int i = 0; i < TRI_CONST; i++) {
		triX[i] = 0;
		triY[i] = 0;
		speedX[i] = 0;
		speedY[i] = 0;
	}
	damTime = 0;
}


void DamParticle::Draw(int x,int y,int scroll) {
	if (isDam == 0) {
		for (int i = 0; i < TRI_CONST; i++) {
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
		damTime = 0;
		triAlpha = 255;
		isShow = 1;
	}
	else {
		damTime++;
		for (int i = 0; i < TRI_CONST; i++) {
			if (damTime > 30) {
				speedY[i] = 4;
			}
			triX[i] += speedX[i];
			triY[i] += speedY[i];
		}

		if (damTime > 10) {
			cirR[0] += 6;
			cirR[1] += 4;
		}
		else {
			cirR[0] += 2;
			cirR[1] += 1;
		}

		if (damTime < 30) {
			if (damTime % 5 == 0) {
				if (isShow == 0) {
					isShow = 1;
				}
				else {
					isShow = 0;
				}
			}
		}
		else {
			triAlpha -= 24;
		}
		alpha -= 5;
	}

	SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		for (int i = 0; i < 10; i++) {
			DrawCircle(x - scroll, y, cirR[0] - (1 * i), GetColor(200, 144, 64), false);
		}
		for (int i = 0; i < 10; i++) {
			DrawCircle(x - scroll, y, cirR[1] - (1 * i), GetColor(200, 144, 64), false);
		}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	if (damTime < 30) {
		if (isShow == 1) {
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < TRI_CONST; i++) {
					SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
					DrawTriangle(triX[i] - scroll + triR - (j * 1), triY[i] + triR - (j * 1), triX[i] - scroll - triR - 4 + (j * 1), triY[i] + triR + 4 - (j * 1), triX[i] - scroll - triR + (j * 1), triY[i] - triR + (j * 1), GetColor(200, 144, 64), false);
					DrawTriangle(triX[i] - scroll - triR - 8 + (j * 1), triY[i] - triR + 8 + (j * 1), triX[i] - scroll + triR - 2 - (j * 1), triY[i] - triR + 2 + (j * 1), triX[i] - scroll + triR - 8 - (j * 1), triY[i] + triR + 8 - (j * 1), GetColor(200, 144, 64), false);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
			}
		}
	}
	else {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < TRI_CONST; i++) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, triAlpha);
				DrawTriangle(triX[i] - scroll + triR - (j * 1), triY[i] + triR - (j * 1), triX[i] - scroll - triR - 4 + (j * 1), triY[i] + triR + 4 - (j * 1), triX[i] - scroll - triR + (j * 1), triY[i] - triR + (j * 1), GetColor(128, 72, 32), false);
				DrawTriangle(triX[i] - scroll - triR - 8 + (j * 1), triY[i] - triR + 8 + (j * 1), triX[i] - scroll + triR - 2 - (j * 1), triY[i] - triR + 2 + (j * 1), triX[i] - scroll + triR - 8 - (j * 1), triY[i] + triR + 8 - (j * 1), GetColor(128, 72, 32), false);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}