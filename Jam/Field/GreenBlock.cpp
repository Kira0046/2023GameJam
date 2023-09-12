#include "GreenBlock.h"

GreenBlock::GreenBlock(int x, int y, int pattern) {
	this->x = x;
	this->y = y;
	this->pattern = pattern;
	LoadDivGraph("Resource/field/color_block_800.png", 6, 6, 1, blockSizeX, blockSizeY, blockHandle);
}

void GreenBlock::Initialize() {
	

}


void GreenBlock::Update() {
}

void GreenBlock::Draw() {
	
	if (pattern == 1) {
		DrawGraph(x - size, y - size, blockHandle[4], true);
		//DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 255, 0), true);
	}
	if (pattern == 2) {
		//DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 255, 0), true);
		DrawGraph(x - size, y - size, blockHandle[5], true);
	}
	
}
