#include "BlueBlock.h"

BlueBlock::BlueBlock(int x, int y, int pattern) {
	this->x = x;
	this->y = y;
	this->pattern = pattern;
}

void BlueBlock::Initialize() {

}

void BlueBlock::Update() {
}

void BlueBlock::Draw() {

	if (isdelete == false) {
		if (pattern == 1) {
			DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 0, 255), true);
		}
		if (pattern == 2) {
			DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 0, 255), true);
		}
	}
	if (isdelete == true) {
		if (pattern == 1) {
			DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 0, 0), true);
		}
		if (pattern == 2) {
			DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 0, 0), true);
		}
	}
}

void BlueBlock::MoveY() {
	fall = false;
	y += 48;
}
