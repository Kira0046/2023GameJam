#include "block.h"

void Block::Initialize(int windowWidth, int windowHeight) {
	//�摜�ǂݍ���
	fieldHandle = LoadGraph("Resource/field/field_kari.png");
	//�摜�T�C�Y�擾
	GetGraphSize(fieldHandle,&fieldSizeX,&fieldSizeY);
	//�t�B�[���h���W����
	fieldPosX[0] = windowWidth / 2 - fieldSizeX / 2;
	fieldPosY[0] = windowHeight / 2 - fieldSizeY / 2;
}

void Block::Draw() {
	DrawGraph(fieldPosX[0], fieldPosY[0], fieldHandle, true);
}