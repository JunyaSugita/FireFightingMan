#pragma once
#include "Struct.h"

class Map {
public:
	static const int Map_MAX_X = 50;

	int map[20][Map_MAX_X];
	int mapCountX;
	int mapCountY;
	int mapGraph[4];
	static const int BLOCK_SIZE = 48;

public:
	Map();
	~Map();
	
public:
	int Map1(int y, int x);
	int Map2(int y, int x);

	void MapSelect(int select);

	void DrawMap(int map[][Map_MAX_X], int scroll);

};