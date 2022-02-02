#include "Charcoal.h"

Charcoal::Charcoal() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 50; j++) {
			brockenTimer[i][j] = 60;
			isBrocken[i][j] = false;
		}
	}

	brockenSE = LoadSoundMem("sound/brocken.mp3");

	ChangeVolumeSoundMem(150, brockenSE);
}

Charcoal::~Charcoal(){}

void Charcoal::SetChar(int fireX, int fireY, int map[][50]) {
	map[(fireY / 48) - 1][fireX / 48] = CHARCOAL;
}

void Charcoal::BrockenChar(int map[][50]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 50; j++) {
			if (isBrocken[i][j] == true && map[i][j] == CHARCOAL) {
				brockenTimer[i][j]--;
				if (brockenTimer[i][j] <= 0) {
					map[i][j] = BROCKEN;
						PlaySoundMem(brockenSE, DX_PLAYTYPE_BACK, true);
				}
			}
		}
	}
}