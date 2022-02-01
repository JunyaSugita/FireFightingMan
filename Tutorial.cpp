#include "Tutorial.h"

Tutorial::Tutorial() {
	timer = 0;
	step = 0;
	stepTimer = STEP_TIME;
	isEx = 0;

	LoadDivGraph("resource/tutorial1.png", 4, 4, 1, 149, 149, tutorial1);
	LoadDivGraph("resource/tutorial2.png", 4, 4, 1, 149, 149, tutorial2);
	LoadDivGraph("resource/tutorial3.png", 4, 4, 1, 149, 149, tutorial3);
	LoadDivGraph("resource/tutorial4.png", 4, 4, 1, 149, 149, tutorial4);
	LoadDivGraph("resource/help.png", 2, 2, 1, 128, 64, help);
	tutorial5 = LoadGraph("resource/tutorial5.png");
	tutorial6 = LoadGraph("resource/tutorial6.png");
	tutorial7 = LoadGraph("resource/tutorial7.png");
	blackGraph = LoadGraph("resource/black.png");

	textSE = LoadSoundMem("sound/text.mp3");

	ChangeVolumeSoundMem(140, textSE);
}

Tutorial::~Tutorial() {}

void Tutorial::CountTimer() {
	timer++;
	if (timer == 150) {
		timer = 0;
	}
}

void Tutorial::StepUpdate(int select, int pad, int isRescued, double& playerX, int isFire, int isFire2, int isFire3) {
	if (select == 0) {
		switch (step) {
			case 0:
				Step0(pad, playerX);
				break;
			case 1:
				Step1(pad, playerX);
				break;
			case 2:
				Step2(playerX);
				break;
			case 3:
				Step3(playerX, isFire, isFire2, isFire3);
				break;
			case 4:
				Step4(isRescued);
		}
		NextStep();
		if (isEx == 0) {
			if (CheckSoundMem(textSE) == false) {
				PlaySoundMem(textSE, DX_PLAYTYPE_BACK, true);
			}
			isEx = 1;
		}
	}
}

void Tutorial::NextStep() {
	if (isNext == 1) {
		stepTimer--;
		if (stepTimer <= 0) {
			step++;
			stepTimer = STEP_TIME;
			isNext = 0;
			isEx = 0;
		}
	}
}

void Tutorial::Step0(int pad, double& playerX) {
	if (pad & PAD_INPUT_1 || pad & PAD_INPUT_2 || pad & PAD_INPUT_3 || pad & PAD_INPUT_4) {
		isNext = 1;
	}
	if (432 <= playerX + 20) {
		playerX = 412;
	}
}

void Tutorial::Step1(int pad, double& playerX) {
	if (pad & PAD_INPUT_5) {
		isNext = 1;
	}
	if (672 <= playerX + 20) {
		playerX = 652;
	}
}

void Tutorial::Step2(double playerX) {
	if (playerX >= 700) {
		isNext = 1;
	}
}

void Tutorial::Step3(double& playerX, int isFire, int isFire2, int isFire3) {
	if (isFire == 0 && isFire2 == 0 && isFire3 == 0) {
		isNext = 1;
	}

	if (1440 <= playerX + 20) {
		playerX = 1420;
	}
}

void Tutorial::Step4(int isRescued) {
	if (isRescued == 1) {
		isNext = 1;
	}
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
		/*DrawGraph(0, 0, blackGraph, true);*/
		DrawRotaGraph2(2100 - scroll, 120, 0, 0, 1.8, 0, help[isRescued], true);
		switch (step) {
			case 0:
				DrawLine(432 - scroll, 0, 432 - scroll, 960, GetColor(200, 0, 0), true);
				DrawFormatString(200, 400, GetColor(200, 0, 0), "B + Rスティックでダッシュしよう");
				break;
			case 1:
				DrawLine(672 - scroll, 0, 672 - scroll, 960, GetColor(200, 0, 0), true);
				DrawFormatString(200, 400, GetColor(200, 0, 0), "Lでジャンプしよう");
				break;
			case 2:
				DrawFormatString(200, 400, GetColor(200, 0, 0), "Rスティックで水を出そう");
				break;
			case 3:
				DrawLine(1440 - scroll, 0, 1440 - scroll, 960, GetColor(200, 0, 0), true);
				DrawFormatString(200, 400, GetColor(200, 0, 0), "火を3つ消そう");
				break;
			case 4:
				DrawFormatString(200, 400, GetColor(200, 0, 0), "女を助けよう");
				break;
			case 5:
				DrawFormatString(200, 400, GetColor(200, 0, 0), "女をお持ち帰りしよう！");
				break;
		}
	}
}