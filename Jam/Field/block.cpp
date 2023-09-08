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
	LoadDivGraph("Resource/field/color_block_double.png", 6, 6, 1, blockSizeX, blockSizeY, doubleHandle);
	LoadDivGraph("Resource/field/color_block_Involvement.png", 6, 6, 1, blockSizeX, blockSizeY, involvementHnadle);
	//�u���b�N������
	for (int i = 0; i < blockNum; i++) {
		block[i].posX = 0.0f;
		block[i].posY = 0.0f;
		block[i].colorPattern = 0;
		block[i].isFall = false;
		block[i].isControl = false;
		block[i].appearingNow = false;
		block[i].isDelete = false;
		block[i].doubleMutch = false;
		block[i].involvement = false;
		for (int j = 0; j < connectNum; j++) {
			block[i].connectionStatus[j] = false;
		}
	}

	//�^�C�}�[������
	deleteTimer = maxTimer;
	countStart = false;

	//�X�R�A������
	hiScore = 0;
	score = 0;
	chain = 0;
	canChain = false;
	deleteBlockNum = 0;
	involvementBlockNum = 0;

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

void Block::Update() {
	//�ڑ��m�F
	CheckConnect();

	//�u���b�N����
	DeleteBlock();

	//�X�R�A���Z
	AddScore();
}

void Block::Draw() {
	//�t�B�[���h�`��
	DrawGraph(fieldPosX[0], fieldPosY[0], fieldHandle, true);
	//�u���b�N�`��
	for (int i = 0; i < blockNum; i++) {
		if (block[i].appearingNow) {
			if (block[i].isDelete && !block[i].doubleMutch && !block[i].involvement) {
				DrawGraph(block[i].posX, block[i].posY, connectHandle[block[i].colorPattern], true);
			}
			else if (block[i].isDelete && block[i].doubleMutch && !block[i].involvement) {
				DrawGraph(block[i].posX, block[i].posY, doubleHandle[block[i].colorPattern], true);
			}
			else if (block[i].involvement) {
				DrawGraph(block[i].posX, block[i].posY, involvementHnadle[block[i].colorPattern], true);
			}
			else {
				DrawGraph(block[i].posX, block[i].posY, blockHandle[block[i].colorPattern], true);
			}
		}
	}

	//�f�o�b�O�e�L�X�g
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Score : %d", score);
	DrawFormatString(10, 25, GetColor(255, 255, 255), "HIScore : %d", hiScore);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "DeleteTimer : %d", deleteTimer);
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
				if (block[i].isDelete) {
					countStart = true;
				}
			}
		}
	}
	for (int i = 0; i < blockNum; i++) {
		//�������݊m�F
		CheckInvolvement(i);
	}
}

void Block::IsConnect(int num) {
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
	int matchCount[2][2] = { { 0,0 },{0,0} };	//{{�c�F,���F},{�c��,����}}
	//��v�����u���b�N�̔ԍ�
	int upNum = 0;
	int downNum = 0;
	int leftNum = 0;
	int rightNum = 0;

	//���W�ƈ�v���Ă�u���b�N�����邩����
	for (int i = 0; i < blockNum; i++) {
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
	//����v�`�F�b�N
	//�㉺
	if (matchCount[0][0] > 1 && matchCount[1][0] > 1) {
		block[num].doubleMutch = true;
		block[upNum].doubleMutch = true;
		block[downNum].doubleMutch = true;
	}
	//���E
	if (matchCount[0][1] > 1 && matchCount[1][1] > 1) {
		block[num].doubleMutch = true;
		block[leftNum].doubleMutch = true;
		block[rightNum].doubleMutch = true;
	}
}

void Block::CheckInvolvement(int num) {
	//������ނ̃u���b�N�Ɋ������ݕt�^
	if (block[num].doubleMutch) {
		for (int i = 0; i < blockNum; i++) {
			if (block[i].colorPattern == block[num].colorPattern) {
				if (!block[i].isDelete) {
					block[i].involvement = true;
				}
			}
		}
	}
}

void Block::DeleteBlock() {
	//�J�E���g�X�^�[�g�t���O���I����������^�C�}�[�𓮂����Ĉ�莞�Ԍ�ɏ���
	if (countStart == true) {
		deleteTimer--;
		if (deleteTimer < 0) {
			countStart = false;
			deleteTimer = maxTimer;
			for (int i = 0; i < blockNum; i++) {
				//�ʏ�Ɗ������݂ŉ��Z����
				if (block[i].isDelete) {
					deleteBlockNum++;
				}
				else if (block[i].involvement) {
					involvementBlockNum++;
				}
				if (block[i].isDelete || block[i].involvement) {
					block[i].appearingNow = false;
					block[i].posX = 0.0f;
					block[i].posY = 0.0f;
					block[i].doubleMutch = false;
					block[i].isDelete = false;
					block[i].involvement = false;
				}
			}
			//�A���J�E���g���Z
			chain++;
		}
	}
}

void Block::AddScore() {
	//�X�R�A�v�Z
	//(��b�X�R�A �~ �ʏ���������u���b�N�� + �{�[�i�X�X�R�A �~ ��v�����Ŋ������񂾃u���b�N��) �~ �A����
	score += (add * deleteBlockNum + bonus * involvementBlockNum) * chain;
	//�n�C�X�R�A�X�V���Ă���X�V
	if (hiScore < score) {
		hiScore = score;
	}
	//���Z�b�g
	deleteBlockNum = 0;
	involvementBlockNum = 0;
}

void Block::AllReset() {
	//�u���b�N������
	for (int i = 0; i < blockNum; i++) {
		block[i].posX = 0.0f;
		block[i].posY = 0.0f;
		block[i].colorPattern = 0;
		block[i].isFall = false;
		block[i].isControl = false;
		block[i].appearingNow = false;
		block[i].isDelete = false;
		block[i].doubleMutch = false;
		block[i].involvement = false;
		for (int j = 0; j < connectNum; j++) {
			block[i].connectionStatus[j] = false;
		}
	}

	//�^�C�}�[������
	deleteTimer = maxTimer;
	countStart = false;

	//�X�R�A������
	hiScore = 0;
	score = 0;
	chain = 0;
	canChain = false;
	deleteBlockNum = 0;
	involvementBlockNum = 0;
}