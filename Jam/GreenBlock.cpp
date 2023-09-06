#include "GreenBlock.h"

void GreenBlock::Initialize(int x, int y, int pattern) {
	this->x = x;
	this->y = y;
	this->pattern = pattern;

}

void GreenBlock::Update() {
}

void GreenBlock::Draw() {
	DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 255, 0), true);
}
