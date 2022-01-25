#pragma once
#include "Struct.h"

class Pause{
public:
	Pause();
	~Pause();

public:
	int select;

public:
	void ChangePause(int pad, int& scene);
};

