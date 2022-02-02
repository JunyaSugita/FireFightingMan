#include "Clear.h"
#include "dxlib.h"

Clear::Clear(){
	isNext = 1;
	isPush = 0;
	backGraph = LoadGraph("resource/selectBack.png");
}

Clear::~Clear(){}

void Clear::Draw() {
	DrawGraph(0, 0, backGraph, true);

	SetFontSize(128);

	DrawFormatString(255, 250, GetColor(255, 255, 64), "STAGE  CLEAR");

	SetFontSize(64);

	if (isNext == 1) {
		DrawBox(320, 540, 945, 640, GetColor(192, 192, 192), true);
		DrawBox(320, 700, 945, 800, GetColor(192, 192, 192), true);
		DrawFormatString(400, 560, GetColor(255, 255, 0), "ステージ選択へ");
		DrawFormatString(490, 720, GetColor(255, 255, 255), "タイトルへ");
	}
	else {
		DrawBox(320, 540, 945, 640, GetColor(192, 192, 192), true);
		DrawBox(320, 700, 945, 800, GetColor(192, 192, 192), true);
		DrawFormatString(400, 560, GetColor(255, 255, 255), "ステージ選択へ");
		DrawFormatString(490, 720, GetColor(255, 255, 0), "タイトルへ");
	}
	SetFontSize(16);
}