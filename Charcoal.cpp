#include "Charcoal.h"

Charcoal::Charcoal() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 50; j++) {
			brockenChar[i][j] = 100;
			isBrocken[i][j] = false;
			isChar[i][j] = false;
		}
	}
}

Charcoal::~Charcoal(){}

void Charcoal::SetChar(int fireX, int fireY, int map[][50]) {
	map[(fireY / 48) - 1][fireX / 48] = CHARCOAL;
	isChar[(fireY / 48) - 1][fireX / 48] = true;
}