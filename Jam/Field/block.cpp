#include "block.h"

void Block::Initialize() {
	//�摜�ǂݍ���
	fieldHandle = LoadGraph("field/field_kari.png");
}

void Block::Draw() {
	DrawGraph(0, 0, fieldHandle, true);
}