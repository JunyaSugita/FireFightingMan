#pragma once
#include "Struct.h"

class StageSelect{
public:
	StageSelect();
	~StageSelect();

public:
	void Select(int LInputY);

	void DrawStageSelect();

public:
	int select;
	int isSelect;
};

