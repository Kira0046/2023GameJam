#include "RedBlock.h"
#include <ctime>

RedBlock::RedBlock(int x, int y, int pattern) {
	this->x = x;
	this->y = y;
	this->pattern = pattern;
}

void RedBlock::Initialize() {


}

void RedBlock::Update() {
}

void RedBlock::Draw() {

	if (isdelete == false) {
		if (pattern == 1) {
			DrawBox(x - size, y - size, x + size, y + size, GetColor(255, 0, 0), true);
		}
		if (pattern == 2) {
			DrawBox(x - size, y - size, x + size, y + size, GetColor(255, 0, 0), true);
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

void RedBlock::MoveY() {
	//srand((unsigned)time(NULL));
	fall = false;
	y += 40;
}
