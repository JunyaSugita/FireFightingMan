#include "StageSelect.h"

StageSelect::StageSelect() {
	select = 0;
	isSelect = 0;
}

StageSelect::~StageSelect(){}

void StageSelect::Select(int LInputY) {
	if (LInputY < 0 && isSelect == 0) {
		select--;
		isSelect = 1;
	}
	else if (LInputY > 0 && isSelect == 0) {
		select++;
		isSelect = 1;
	}
	else if (LInputY == 0) {
		isSelect = 0;
	}

	if (select < 0) {
		select = 0;
	}
	else if (select > 1) {
		select = 1;
	}
}

void StageSelect::DrawStageSelect() {
	DrawFormatString(640, 450, GetColor(255, 255, 255), "‚¿‚ã[‚Æ‚è‚ ‚é");
	DrawFormatString(640, 470, GetColor(255, 255, 255), "‚·‚Ä[‚¶‚¢‚¿");
	DrawFormatString(600, 450 + (select * 20), GetColor(255, 255, 255), "-->");
}