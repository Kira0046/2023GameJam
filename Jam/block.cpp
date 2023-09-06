#include "block.h"

void Block::Initialize(int windowWidth, int windowHeight) {
	//�摜�ǂݍ���
	fieldHandle = LoadGraph("Resource/field/field_kari.png");
	//�摜�T�C�Y�擾
	GetGraphSize(fieldHandle,&fieldSizeX,&fieldSizeY);
	//�t�B�[���h���W����
	fieldPosX[0] = windowWidth / 2 - fieldSizeX / 2;
	fieldPosY[0] = windowHeight / 2 - fieldSizeY / 2;

	//�u���b�N
	//�摜�ǂݍ���
	LoadDivGraph("Resource/field/color_block_800.png", 6, 6, 1, blockSizeX, blockSizeY, blockHandle);
	//�u���b�N������
	for (int i = 0; i < blockNum; i++) {
		block[i].posX = 0.0f;
		block[i].posY = 0.0f;
		block[i].colorPattern = 0;
		block[i].isFall = false;
		block[i].appearingNow = false;
		for (int j = 0; j < connectNum; j++) {
			block[i].connectionStatus[j] = false;
		}
	}

	//�e�X�g�ݒu
	int numX = 0;
	int numY = 1;
	for (int i = 0; i < 162; i++) {
		block[i].posX = float(fieldPosX[0]) + float(fieldFlameSizeX) + blockSizeX * numX;
		block[i].posY = float(fieldPosY[0]) + fieldSizeY - float(fieldFlameSizeX) - blockSizeY * numY;
		block[i].appearingNow = true;
		block[i].colorPattern = GetRand(5);
		numX++;
		if (numX > 8) {
			numX = 0;
			numY++;
		}
	}
}

void Block::Draw() {
	// �t�B�[���h�`��
	DrawGraph(fieldPosX[0], fieldPosY[0], fieldHandle, true);
	//�u���b�N�`��
	for (int i = 0; i < blockNum; i++) {
		if (block[i].appearingNow) {
			DrawGraph(block[i].posX, block[i].posY, blockHandle[block[i].colorPattern], true);
		}
	}
}