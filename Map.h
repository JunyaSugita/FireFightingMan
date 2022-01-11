#pragma once
#include "Struct.h"

class Map {
public:
	Map();
	~Map();

public:
	int Map1(int y, int x);

	void SelectMap1();

	void DrawMap(int map[][50], int scroll);
public:
	int map[20][50];
	int mapCountX;
	int mapCountY;

	const int BLOCK_SIZE = 48;
};