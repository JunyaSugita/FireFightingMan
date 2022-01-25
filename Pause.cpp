#include "Pause.h"

Pause::Pause() {
	select = 0;
}

Pause::~Pause(){}

void Pause::ChangePause(int pad, int& scene) {
	if (pad & PAD_INPUT_8) {
		scene = PAUSE;
	}
}