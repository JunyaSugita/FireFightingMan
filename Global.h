#pragma once
#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "救済！ヒケシーマン";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 960;

//マップ
enum MapInfo {
	NONE,	//0
	BLOCK,	//1
	FLAME,	//2
	FLAMEENEMY,	//3
};