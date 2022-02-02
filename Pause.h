#pragma once
#include "Struct.h"
#include "StageSelect.h"

class Pause{
public:
	Pause();
	~Pause();

public:
	int select;
	int isPush;
	int x;
	int y;
	int xr;
	int yr;
	int isReset;
	int isPause;
	int pauseSE;
	int botan;
	int py;

public:
	void ChangePause(int pad, int& scene);
	void ChangeScene(int pad, int& scene);
	void Move();
	void Draw();
};

