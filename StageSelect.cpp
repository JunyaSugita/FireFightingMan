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

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(0, 0, WIN_WIDTH, WIN_HEIGHT / 2, GetColor(96, 172, 255), true);
	DrawBox(0, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, GetColor(128, 96, 96), true);
	DrawBox(0, WIN_HEIGHT / 2, WIN_WIDTH, 510, GetColor(36, 128, 36), true);
	DrawBox(0, 640, WIN_WIDTH, WIN_HEIGHT, GetColor(64, 48, 48), true);

	DrawBox(x - width, y - height, x + width, y + height, GetColor(255, 32, 32), true);
	DrawBox(x - 190, y - 80, x + 150, y +30, GetColor(230, 230, 232), true);
	DrawBox(x + 190, y - height - 36, x + width - 20, y - height, GetColor(255, 0, 0), true);
	DrawBox(x + 190, y - height - 10, x + width - 20, y - height, GetColor(64, 64, 64), true);
	for (int i = 0; i < 10; i++) {
		DrawBox(x - width+(i*1), y - height - 80 + (i * 1), x + 120 + (i * 1), y - height - 9 + (i * 1), GetColor(128, 128, 128), false);
	}
	for (int i = 0; i < 7; i++) {
		DrawLine(x - 200 + (i * 50), y - height - 80, x - 200 + (i * 50), y - height - 9, GetColor(128, 128, 128), 8);
	}
	DrawLine(x - 220, y - height - 80, x - 150, y - height - 80, GetColor(255, 255, 64), 4);
	DrawBox(x + 200, y - 80, x + width, y + 10, GetColor(64, 192, 192), true);
	DrawLine(x - 220, y - 20, x - 230, y + 80, GetColor(144, 144, 144), 16);
	DrawLine(x + 160, y + 20, x + 190, y + 20, GetColor(128, 128, 128), 16);
	DrawLine(x - width, y + height, x + 120, y + height, GetColor(200, 200, 200), 16);
	DrawCircle(x - 150, y + height, 40, GetColor(32, 32, 32), true);
	DrawCircle(x - 150, y + height, 30, GetColor(128, 128, 128), true);
	DrawCircle(x + 150, y + height, 40, GetColor(32, 32, 32), true);
	DrawCircle(x + 150, y + height, 30, GetColor(128, 128, 128), true);
	DrawFormatString(x - 64, 430, GetColor(0, 0, 0), "チュートリアル");
	DrawFormatString(x - 64, 450, GetColor(0, 0, 0), "ステージ1");
	DrawFormatString(x - 64, 470, GetColor(0, 0, 0), "ステージ2");
	DrawFormatString(x - 64, 490, GetColor(0, 0, 0), "ステージ3");
	DrawFormatString((x - 40) - 64, 430 + (select * 20), GetColor(0, 0, 0), "-->");

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < 5; i++) {
		DrawCircle(1000, 0, 300 - (i * 60), GetColor(24, 24, 24), true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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