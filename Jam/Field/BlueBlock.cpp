#include "BlueBlock.h"

BlueBlock::BlueBlock(int x, int y, int pattern) {
	this->x = x;
	this->y = y;
	this->pattern = pattern;
	LoadDivGraph("Resource/field/color_block_800.png", 6, 6, 1, blockSizeX, blockSizeY, blockHandle);
}

void BlueBlock::Initialize() {

}

void BlueBlock::Update() {
}

void BlueBlock::Draw() {

	if (pattern == 1) {
		//DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 0, 255), true);
		DrawGraph(x - size, y - size, blockHandle[2], true);
	}
	if (pattern == 2) {
		//DrawBox(x - size, y - size, x + size, y + size, GetColor(0, 0, 255), true);
		DrawGraph(x - size, y - size, blockHandle[3], true);
	}

}
