#include "block.h"

void Block::Initialize() {
	//画像読み込み
	fieldHandle = LoadGraph("field/field_kari.png");
}

void Block::Draw() {
	DrawGraph(0, 0, fieldHandle, true);
}