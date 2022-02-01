#include "Charcoal.h"

Charcoal::Charcoal() {}

Charcoal::~Charcoal(){}

void Charcoal::SetChar(int fireX, int fireY, int map[][50]) {
	map[(fireY / 48) - 1][fireX / 48] = CHARCOAL;
}