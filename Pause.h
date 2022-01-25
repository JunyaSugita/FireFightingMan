#pragma once
#include "Struct.h"

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

public:
	void ChangePause(int pad, int& scene);
	void ChangeScene(int pad, int& scene);
	void Move();
	void Draw();
};

