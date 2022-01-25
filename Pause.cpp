#include "Pause.h"

Pause::Pause() {
	select = 0;
	isPush = 0;
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2;
	xr = 0;
	yr = 0;
	isReset = true;
	isPause = false;
}

Pause::~Pause(){}

void Pause::ChangePause(int pad, int& scene) {
	
		if (pad & PAD_INPUT_8) {
			if (isPush == false) {
				scene = PAUSE;
				isPush = true;
				isPause = true;
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
		}
	}
	else {
		isPush = false;
	}
}

void Pause::Draw() {
	if (xr > 0 && yr > 0) {
		for (int i = 0; i < 5; i++) {
			DrawBox(x - xr - (1 * i), y - yr - (1 * i), x + xr + (1 * i), y + yr + (1 * i), GetColor(192, 192, 192), false);
		}
	}
	DrawBox(x - xr, y - yr, x + xr, y + yr, GetColor(48, 48, 96), true);
	if (xr >= 500) {
		if (isReset == 1) {
			DrawFormatString(640, 460, GetColor(255, 255, 0), "リセット");
			DrawFormatString(640, 520, GetColor(255, 255, 255), "タイトル");
		}
		else {
			DrawFormatString(640, 460, GetColor(255, 255, 255), "リセット");
			DrawFormatString(640, 520, GetColor(255, 255, 0), "タイトル");
		}
	}
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