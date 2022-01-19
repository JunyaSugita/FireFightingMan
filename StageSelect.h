#pragma once
#include "Struct.h"

class StageSelect{
public:
	StageSelect();
	~StageSelect();

public:
	void Select(int LInputY);
	void DrawStageSelect();
	void Reset();
	void Move();
	float EaseInQuint(float speed);

public:
	int select;
	int isSelect;
	float x;
	float y;
	float height;
	float width;
	float time;
	float maxTime;
	float speed;
	int isStop;
};

