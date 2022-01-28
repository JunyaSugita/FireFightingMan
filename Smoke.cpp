#include"Smoke.h"
#include "math.h"


Smoke::Smoke() {
	char fileName[] = "resource/smoke00.png";
	flameCount = 0;
	animFlame = 0;
	smokeDensity = 20;
	currentFlameRatio = 0.0f;

	for (int i = 0; i < SMOKE_FLAME_MAX; i++) {
		fileName[14] = i / 10 + 48;
		fileName[15] = (i % 10) + 48;

		smokeGraph[i] = LoadGraph(fileName);
	}
}

Smoke::~Smoke() {

}

void Smoke::Move() {
	flameCount++;

	if (flameCount == 50) {
		flameCount = 0;
	}

	if (flameCount % 12 == 0) {
		animFlame++;
	}
	if (animFlame == SMOKE_FLAME_MAX) {
		animFlame = 0;
	}
	currentFlameRatio = static_cast<float>(animFlame) / static_cast<float>(SMOKE_FLAME_MAX);
}

void Smoke::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ADD,
		smokeDensity * sin(PI * currentFlameRatio) + smokeDensity + 2
	);

	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, smokeGraph[animFlame], true);
}