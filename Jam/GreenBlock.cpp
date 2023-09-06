#include "GreenBlock.h"

	GreenBlock::GreenBlock(int x, int y, int pattern) {
		this->x = x;
		this->y = y;
		this->pattern = pattern;
	}

	void GreenBlock::Initialize() {


	}


	void GreenBlock::Update() {
	}

	void GreenBlock::Draw() {
		if (pattern == 1) {
			DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 255, 0), true);
		}
		if (pattern == 2) {
			DrawBox(x - size, y - size, x + size, y + size, GetColor(255, 0, 0), true);
		}
	}