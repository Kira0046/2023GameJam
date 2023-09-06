#include "RedBlock.h"

void RedBlock::Initialize(int x, int y, int pattern) {
	this->x = x;
	this->y = y;
	this->pattern = pattern;

}

void RedBlock::Update() {
}

void RedBlock::Draw() {
	DrawBox(x - size, y - size, x + size, y + size, GetColor(255, 0, 0), true);
}
