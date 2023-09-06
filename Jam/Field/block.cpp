#include "block.h"

void Block::Initialize(int windowWidth, int windowHeight) {
	//�t�B�[���h
	//�摜�ǂݍ���
	fieldHandle = LoadGraph("Resource/field/field_kari.png");
	//�摜�T�C�Y�擾
	GetGraphSize(fieldHandle, &fieldSizeX, &fieldSizeY);
	//�t�B�[���h���W����
	fieldPosX[0] = windowWidth / 2 - fieldSizeX / 2;
	fieldPosY[0] = windowHeight / 2 - fieldSizeY / 2;

	//�u���b�N
	//�摜�ǂݍ���
	LoadDivGraph("Resource/field/color_block_800.png", 6, 6, 1, blockSizeX, blockSizeY, blockHandle);
	LoadDivGraph("Resource/field/color_block_connect.png", 6, 6, 1, blockSizeX, blockSizeY, connectHandle);
	//�u���b�N������
	for (int i = 0; i < blockNum; i++) {
		block[i].posX = 0.0f;
		block[i].posY = 0.0f;
		block[i].colorPattern = 0;
		block[i].isFall = false;
		block[i].isControl = false;
		block[i].appearingNow = false;
		block[i].isDelete = false;
		for (int j = 0; j < connectNum; j++) {
			block[i].connectionStatus[j] = false;
		}
	}

	//�e�X�g�ݒu
	int numX = 0;
	int numY = 1;
	for (int i = 0; i < 81; i++) {
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

void Block::Update() {
	CheckConnect();
	//IsConnect(0);
}

void Block::Draw() {
	//�t�B�[���h�`��
	DrawGraph(fieldPosX[0], fieldPosY[0], fieldHandle, true);
	//�u���b�N�`��
	for (int i = 0; i < blockNum; i++) {
		if (block[i].appearingNow) {
			if (block[i].isDelete) {
				DrawGraph(block[i].posX, block[i].posY, connectHandle[block[i].colorPattern], true);
			}
			else {
				DrawGraph(block[i].posX, block[i].posY, blockHandle[block[i].colorPattern], true);
			}
		}
	}
}

//�ڑ��`�F�b�N
void Block::CheckConnect() {
	//�S�u���b�N�ɂ���
	for (int i = 0; i < blockNum; i++) {
		//�t�B�[���h�ɂ��邩�`�F�b�N
		if (block[i].appearingNow) {
			//������Ԃł͂Ȃ����Ƃ̃`�F�b�N
			if (!block[i].isFall) {
				//�ڑ��m�F
				IsConnect(i);
			}
		}

	}
}

void Block::IsConnect(int num) {
	//�u���b�N�̒������W�擾
	//float centerPosX = block[num].posX + blockSizeX / 2;
	//float centerPosY = block[num].posY + blockSizeY / 2;
	//�אڂ����u���b�N�̍��W�擾
	float connectPos[8];
	//��
	connectPos[0] = block[num].posX;
	connectPos[1] = block[num].posY - blockSizeY;
	//��
	connectPos[2] = block[num].posX;
	connectPos[3] = block[num].posY + blockSizeY;
	//��
	connectPos[4] = block[num].posX - blockSizeX;
	connectPos[5] = block[num].posY;
	//�E
	connectPos[6] = block[num].posX + blockSizeX;
	connectPos[7] = block[num].posY;
	//��v�����ꍇ�̂݃J�E���g�A2�ȏ�ŏ�����
	int matchCount[2][2] = { { 0,0 },{0,0} };	//�F��v��,����v��
	//��v�����u���b�N�̔ԍ�
	int upNum = 0;
	int downNum = 0;
	int leftNum = 0;
	int rightNum = 0;

	//���W�ƈ�v���Ă�u���b�N�����邩����
	for (int i = 0; i < 180; i++) {
		for (int j = 0; j < 8; j) {
			//�㉺���E�̏��Őڑ��`�F�b�N
			if (connectPos[j] == block[i].posX && connectPos[j + 1] == block[i].posY) {
				
				//�F��v�m�F
				if (block[i].colorPattern / 2 == block[num].colorPattern / 2) {
					block[num].connectionStatus[j] = true;	//�F��v
					//�㉺��v�̏ꍇ
					if (j < 4) {
						matchCount[0][0]++;
						if (j < 2) {
							upNum = i;
						}
						else {
							downNum = i;
						}
					}
					//���E��v�̏ꍇ
					else if (j > 3) {
						matchCount[0][1]++;
						if (j > 5) {
							rightNum = i;
						}
						else {
							leftNum = i;
						}
					}

				}
				//����v�m�F
				if (block[i].colorPattern % 2 == block[num].colorPattern % 2) {
					block[num].connectionStatus[j + 1] = true;	//����v
					//�㉺��v�̏ꍇ
					if (j < 4) {
						matchCount[1][0]++;
						if (j < 2) {
							upNum = i;
						}
						else {
							downNum = i;
						}
					}
					//���E��v�̏ꍇ
					else if (j > 3) {
						matchCount[1][1]++;
						if (j > 5) {
							rightNum = i;
						}
						else {
							leftNum = i;
						}
					}
				}
			}
			j += 2;
		}
	}
	//�J�E���g���������ꍇ����
	for (int i = 0; i < 2; i++) {
		if (matchCount[i][0] > 1) {
			block[num].isDelete = true;
			block[upNum].isDelete = true;
			block[downNum].isDelete = true;
		}
		if (matchCount[i][1] > 1) {
			block[num].isDelete = true;
			block[leftNum].isDelete = true;
			block[rightNum].isDelete = true;
		}
	}
}