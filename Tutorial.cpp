#include "Tutorial.h"

Tutorial::Tutorial() {
	timer = 0;

	LoadDivGraph("resource/tutorial1.png", 4, 4, 1, 149, 149, tutorial1);
	LoadDivGraph("resource/tutorial2.png", 4, 4, 1, 149, 149, tutorial2);
	LoadDivGraph("resource/tutorial3.png", 4, 4, 1, 149, 149, tutorial3);
	LoadDivGraph("resource/tutorial4.png", 4, 4, 1, 149, 149, tutorial4);
	tutorial5 = LoadGraph("resource/tutorial5.png");
	tutorial6 = LoadGraph("resource/tutorial6.png");
}

Tutorial::~Tutorial() {}

void Tutorial::CountTimer() {
	timer++;
	if (timer == 200) {
		timer = 0;
	}
}

void Tutorial::DrawTutorial(int serect, int scroll) {
	if (serect == 0) {
		DrawGraph(100 - scroll, 500, tutorial1[timer / 50], true);
		DrawGraph(500 - scroll, 500, tutorial2[timer / 50], true);
		DrawGraph(1280 - scroll, 800, tutorial3[timer / 50], true);
		DrawGraph(2150 - scroll, 400, tutorial4[timer / 50], true);
		DrawGraph(800 - scroll, 500, tutorial5, true);
		DrawGraph(1950 - scroll, 500, tutorial6, true);
	}
}