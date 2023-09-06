#include "BlueBlock.h"

void BlueBlock::Initialize(int x, int y, int pattern) {
	this->x = x;
	this->y = y;
	this->pattern = pattern;
}

void BlueBlock::Update() {
}

void BlueBlock::Draw() {
	DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 0, 255), true);
}
