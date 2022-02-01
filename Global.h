#pragma once
#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "救済！ヒケシーマン";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 960;

const float PI = 3.141592f;

//マップ
enum MapInfo {
	NONE,			//0
	BLOCK,			//1
	FLAME,			//2
	FLAMEENEMY,		//3
	PLAYER_SPAWN,	//4
	WOMAN_SPAWN		//5
};

enum SceneInfo {
	MAIN_TITLE,			//0
	MAIN_GAME,			//1
	STAGE_SELECT,		//2
	GAMEOVER,			//3
	CLEAR,				//4
	PAUSE,				//5
	TEXT				//6
};

enum SelectInfo {
	TUTORIAL,	//0
	STAGE1,		//1
	STAGE2,     //2
	STAGE3		//3
};