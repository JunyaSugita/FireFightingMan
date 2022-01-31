#include "StageSelect.h"

StageSelect::StageSelect() {
	select = 0;
	isSelect = 0;
	x = -500;
	y = WIN_HEIGHT / 2;
	width = 250.0f;
	height = 100.0f;
	time = 0.0f;
	maxTime = 60.0f;
	speed = 122;
	isStop = 0;
	isPush = 0;

	selectSE = LoadSoundMem("sound/select.mp3");

	ChangeVolumeSoundMem(120, selectSE);

	carGraph = LoadGraph("resource/fireTruck.png");
	backGraph = LoadGraph("resource/selectBack.png");
}

StageSelect::~StageSelect(){}

void StageSelect::Select(int LInputY,int pad) {

	Move();

	if (LInputY < 0 && isSelect == 0 || pad & PAD_INPUT_UP) {
		if (isPush == 0) {
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
			select--;
			isSelect = 1;
			isPush = 1;
		}
	}
	else if (LInputY > 0 && isSelect == 0 || pad & PAD_INPUT_DOWN) {
		if (isPush == 0) {
			PlaySoundMem(selectSE, DX_PLAYTYPE_BACK, true);
			select++;
			isSelect = 1;
			isPush = 1;
		}
	}
	else if (LInputY == 0) {
		isSelect = 0;
		isPush = 0;
	}

	if (select < 0) {
		select = 0;
	}
	else if (select > 3) {
		select = 3;
	}
}

void StageSelect::DrawStageSelect() {

	DrawGraph(0, 0, backGraph, true);

	DrawRotaGraph2(x - 400, y - (height*2) - 50,0,0,1.5,0, carGraph, true);
	DrawBox(x - 210, y - 110, x + 130, y, GetColor(230, 230, 232), true);
	for (int i = 0; i < 3; i++) {
		DrawBox(x - 210 -(1+i), y - 110 - (1 + i), x + 130 + (1 + i), y  + (1 + i), GetColor(0, 0, 0), false);
	}
	DrawFormatString(x - 84, 380, GetColor(0, 0, 0), "チュートリアル");
	DrawFormatString(x - 84, 400, GetColor(0, 0, 0), "ステージ1");
	DrawFormatString(x - 84, 420, GetColor(0, 0, 0), "ステージ2");
	DrawFormatString(x - 84, 440, GetColor(0, 0, 0), "ステージ3");
	DrawFormatString((x - 40) - 84, 380 + (select * 20), GetColor(0, 0, 0), "-->");
}


float StageSelect::EaseInQuint(float speed) {
	speed = time / maxTime;

	return speed * speed * speed * speed * speed;
}

void StageSelect::Move() {
	time++;
	if (time < maxTime) {
		x += speed * EaseInQuint(speed);
	}
	else {
		isStop = 1;
	}
}

void StageSelect::Reset() {
	time = 0;
	x = -500;
}