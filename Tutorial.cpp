#include "Tutorial.h"

Tutorial::Tutorial() {
	timer = 0;
	step = 0;
	stepTimer = STEP_TIME;

	LoadDivGraph("resource/tutorial1.png", 4, 4, 1, 149, 149, tutorial1);
	LoadDivGraph("resource/tutorial2.png", 4, 4, 1, 149, 149, tutorial2);
	LoadDivGraph("resource/tutorial3.png", 4, 4, 1, 149, 149, tutorial3);
	LoadDivGraph("resource/tutorial4.png", 4, 4, 1, 149, 149, tutorial4);
	LoadDivGraph("resource/help.png", 2, 2, 1, 128, 64, help);
	tutorial5 = LoadGraph("resource/tutorial5.png");
	tutorial6 = LoadGraph("resource/tutorial6.png");
	tutorial7 = LoadGraph("resource/tutorial7.png");
}

Tutorial::~Tutorial() {}

void Tutorial::CountTimer() {
	timer++;
	if (timer == 150) {
		timer = 0;
	}
}

void Tutorial::StepUpdate(int select, int pad, int isRescued) {
	if (select == 0) {
		switch (step) {
			case 0:
				Step0(pad);
				break;
			case 1:
				Step1(pad);
				break;
			case 2:
				Step2();
				break;
			case 3:
				Step3(isRescued);
				break;
		}
		NextStep();
	}
}

void Tutorial::NextStep() {
	if (isNext == 1) {
		stepTimer--;
		if (stepTimer <= 0) {
			step++;
			isNext = 0;
		}
	}
}

void Tutorial::Step0(int pad) {
	if (pad & PAD_INPUT_1 || pad & PAD_INPUT_2 || pad & PAD_INPUT_3 || pad & PAD_INPUT_4) {
		isNext = 1;
	}
}

void Tutorial::Step1(int pad) {

}

void Tutorial::Step2() {

}

void Tutorial::Step3(int isRescued) {

}

void Tutorial::DrawTutorial(int serect, int scroll, int isRescued) {
	if (serect == 0) {
		/*DrawGraph(100 - scroll, 450, tutorial1[timer / 50], true);
		DrawGraph(500 - scroll, 450, tutorial2[timer / 50], true);
		DrawGraph(1280 - scroll, 800, tutorial3[timer / 50], true);
		DrawGraph(2150 - scroll, 500, tutorial4[timer / 50], true);
		DrawGraph(800 - scroll, 450, tutorial5, true);
		DrawGraph(1950 - scroll, 500, tutorial6, true);
		DrawRotaGraph2(-100 - scroll, -110,0,0,2.5,0, tutorial7, true);*/
		DrawRotaGraph2(2100 - scroll, 120, 0, 0, 1.8, 0, help[isRescued], true);
	}
}