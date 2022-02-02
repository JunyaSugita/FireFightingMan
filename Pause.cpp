#include "Pause.h"

Pause::Pause() {
	select = 0;
	isPush = 0;
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2;
	xr = 0;
	yr = 0;
	py = -50;
	isReset = true;
	isPause = false;
	botan = LoadGraph("resource/botan.png");

	pauseSE = LoadSoundMem("sound/pause.ogg");

	ChangeVolumeSoundMem(130, pauseSE);
}

Pause::~Pause(){}

void Pause::ChangePause(int pad, int& scene) {
	if (py < 0) {
		py += 4;
	}
	
		if (pad & PAD_INPUT_8) {
			if (isPush == false) {
				scene = PAUSE;
				isPush = true;
				isPause = true;
				PlaySoundMem(pauseSE, DX_PLAYTYPE_BACK, true);
			}
		}
		else {
			isPush = false;
		}
}

void Pause::ChangeScene(int pad, int& scene) {
	if (pad & PAD_INPUT_8) {
		if (isPush == false) {
			scene = MAIN_GAME;
			isPush = true;
			isPause = false;
			PlaySoundMem(pauseSE, DX_PLAYTYPE_BACK, true);
		}
	}
	else {
		isPush = false;
	}
}

void Pause::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, py - 50, 150, py + 50, GetColor(0, 0, 12), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	for (int i = 0; i < 2; i++) {
		DrawBox(0 - (i + 1), py - 50 - (i + 1), 150 + (i + 1), py + 50 + (i + 1), GetColor(255,255,255), false);
	}
	DrawGraph(10, py + 8, botan,true);
	DrawFormatString(50, py + 16, GetColor(255, 255, 255), ": ポーズ");
	if (xr > 0 && yr > 0) {
		for (int i = 0; i < 5; i++) {
			DrawBox(x - xr - (1 * i), y - yr - (1 * i), x + xr + (1 * i), y + yr + (1 * i), GetColor(192, 192, 192), false);
		}
	}
	DrawBox(x - xr, y - yr, x + xr, y + yr, GetColor(48, 48, 96), true);
	SetFontSize(64);
	if (xr >= 500) {
		if (isReset == 1) {
			DrawBox(470, 340, 795, 440, GetColor(192, 192, 192 ),true);
			DrawBox(470, 500, 795, 600, GetColor(192, 192, 192), true);
			DrawFormatString(510, 360, GetColor(255, 255, 0), "リセット");
			DrawFormatString(510, 520, GetColor(255, 255, 255), "タイトル");
		}
		else {
			DrawBox(470, 340, 795, 440, GetColor(192, 192, 192), true);
			DrawBox(470, 500, 795, 600, GetColor(192, 192, 192), true);
			DrawFormatString(510, 360, GetColor(255, 255, 255), "リセット");
			DrawFormatString(510, 520, GetColor(255, 255, 0), "タイトル");
		}
	}
	SetFontSize(16);
}

void Pause::Move() {
	if (isPause == true) {
		if (xr < 512) {
			xr += 32;
		}
		if (yr < 256) {
			yr += 16;
		}
	}
	else {
		if (xr > 0) {
			xr -= 32;
		}
		if (yr > 0) {
			yr -= 32;
		}
	}
}