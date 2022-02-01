#include "Tutorial.h"

Tutorial::Tutorial() {
	timer = 0;
	step = 0;
	isEx = 0;
	isPush = 0;
	for (int i = 0; i < 6; i++) {
		isCom[i] = 0;
	}
	textNum = 0;

	//LoadDivGraph("resource/tutorial1.png", 4, 4, 1, 149, 149, tutorial1);
	//LoadDivGraph("resource/tutorial2.png", 4, 4, 1, 149, 149, tutorial2);
	//LoadDivGraph("resource/tutorial3.png", 4, 4, 1, 149, 149, tutorial3);
	//LoadDivGraph("resource/tutorial4.png", 4, 4, 1, 149, 149, tutorial4);
	//LoadDivGraph("resource/help.png", 2, 2, 1, 128, 64, help);
	//tutorial5 = LoadGraph("resource/tutorial5.png");
	//tutorial6 = LoadGraph("resource/tutorial6.png");
	//tutorial7 = LoadGraph("resource/tutorial7.png");

	textSE = LoadSoundMem("sound/text.mp3");

	ChangeVolumeSoundMem(140, textSE);
}

Tutorial::~Tutorial() {}

void Tutorial::StepUpdate(int select, int pad, int isRescued, double& playerX, int isFire, int isFire2, int isFire3, int scene) {
	if (select == 0) {
		
		if (isEx == 0) {
			if (CheckSoundMem(textSE) == false) {
				PlaySoundMem(textSE, DX_PLAYTYPE_BACK, true);
			}
			isEx = 1;
		}
	}
}



void Tutorial::DrawTutorial(int serect, int scroll, int isRescued,int isShow) {
	if (serect == 0) {
		/*DrawGraph(100 - scroll, 450, tutorial1[timer / 50], true);
		DrawGraph(500 - scroll, 450, tutorial2[timer / 50], true);
		DrawGraph(1280 - scroll, 800, tutorial3[timer / 50], true);
		DrawGraph(2150 - scroll, 500, tutorial4[timer / 50], true);
		DrawGraph(800 - scroll, 450, tutorial5, true);
		DrawGraph(1950 - scroll, 500, tutorial6, true);
		DrawRotaGraph2(-100 - scroll, -110,0,0,2.5,0, tutorial7, true);*/
		DrawRotaGraph2(2100 - scroll, 120, 0, 0, 1.8, 0, help[isRescued], true);
		SetFontSize(32);
		if(player)
		switch (textNum) {
			case 1:
				DrawLine(432 - scroll, 0, 432 - scroll, 960, GetColor(200, 0, 0), true);
				DrawBox(130, 375, 470, 480, GetColor(192, 192, 192), true);
				DrawFormatString(150, 400, GetColor(200, 0, 0), "B + Rスティックで\nダッシュしよう");
				break;
			case 2:
				DrawBox(130, 375, 470, 480, GetColor(192, 192, 192), true);
				DrawFormatString(150, 400, GetColor(200, 0, 0), "Lでジャンプしよう");
				break;
			case 3:
				DrawBox(130, 375, 470, 480, GetColor(192, 192, 192), true);
				DrawFormatString(150, 400, GetColor(200, 0, 0), "Rスティックで\n水を出そう");
				break;
			case 4:
				DrawBox(130, 375, 470, 480, GetColor(192, 192, 192), true);
				DrawFormatString(150, 400, GetColor(200, 0, 0), "火を3つ消そう");
				break;
			case 5:
				DrawBox(130, 375, 470, 480, GetColor(192, 192, 192), true);
				DrawFormatString(150, 400, GetColor(200, 0, 0), "女を助けよう");
				break;
			case 6:
				DrawBox(130, 375, 470, 480, GetColor(192, 192, 192), true);
				DrawFormatString(150, 400, GetColor(200, 0, 0), "女をお持ち帰りしよう！");
				break;
		}
		SetFontSize(16);
	}
}