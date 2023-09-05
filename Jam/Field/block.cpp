#include "block.h"

void Block::Initialize() {
	//‰æ‘œ“Ç‚İ‚İ
	fieldHandle = LoadGraph("field/field_kari.png");
}

void Block::Draw() {
	DrawGraph(0, 0, fieldHandle, true);
}