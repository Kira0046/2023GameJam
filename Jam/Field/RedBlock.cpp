#include "RedBlock.h"

RedBlock::RedBlock(int x, int y, int pattern) {
	this->x = x;
	this->y = y;
	this->pattern = pattern;
	LoadDivGraph("Resource/field/color_block_800.png", 6, 6, 1, blockSizeX, blockSizeY, blockHandle);
}

void RedBlock::Initialize() {


}

void RedBlock::Update() {
}

void RedBlock::Draw() {

	
	if (pattern == 1) {
		//DrawBox(x - size, y - size, x + size, y + size, GetColor(255, 0, 0), true);
		DrawGraph(x - size, y - size, blockHandle[0], true);
	}
	if (pattern == 2) {
		//DrawBox(x - size, y - size, x + size, y + size, GetColor(255, 0, 0), true);
		DrawGraph(x - size, y - size, blockHandle[1], true);
	}
	
}
