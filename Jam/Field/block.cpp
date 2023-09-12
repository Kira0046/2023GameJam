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
		block[i].center = false;
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

	//����n��
	isControl = false;
	speed = 1.0f;
	level = 1.0f;
	rotateNum = 0;	//0����㍶�E���̏�

	isDelete = false;

	for (int i = 0; i < 28; i++) {
		oldInput[i] = false;
	}

	////�e�X�g�ݒu
	//int numX = 0;
	//int numY = 1;
	//for (int i = 0; i < 142; i++) {
	//	block[i].posX = float(fieldPosX[0]) + float(fieldFlameSizeX) + blockSizeX * numX;
	//	block[i].posY = float(fieldPosY[0]) + fieldSizeY - float(fieldFlameSizeX) - blockSizeY * numY;
	//	block[i].appearingNow = true;
	//	block[i].colorPattern = GetRand(5);
	//	numX++;
	//	if (numX > 8) {
	//		numX = 0;
	//		numY++;
	//	}
	//}
}

void Block::Update(char* keys, char* oldkeys) {
	//����
	FallBlock(keys, oldkeys);

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

//����
void Block::FallBlock(char* keys, char* oldkeys) {
	//���쒆�u���b�N���Ȃ��Ȃ�
	if (!isControl && !isDelete) {
		int counter = 0;
		//�t���[�̃u���b�N��T��
		for (int i = 0; i < blockNum; i++) {
			if (!block[i].appearingNow) {
				block[i].appearingNow = true;
				block[i].isControl = true;
				block[i].colorPattern = GetRand(5);
				if (counter < 1) {
					block[i].center = true;	//���S�̌���
					block[i].posX = fieldPosX[0] + fieldFlameSizeX + blockSizeX * 4;
					block[i].posY = fieldPosY[0] + fieldFlameSizeY;
					centerPos[0] = block[i].posX;
					centerPos[1] = block[i].posY;
				}
				counter++;	//2�T������E�o
				if (counter > 1) {
					block[i].posX = fieldPosX[0] + fieldFlameSizeX + blockSizeX * 4;
					block[i].posY = fieldPosY[0] + fieldFlameSizeY - blockSizeY;
					break;
				}
			}
		}
		isControl = true;
	}

	for (int i = 0; i < blockNum; i++) {
		if (block[i].isControl) {
			block[i].posY += speed * level;
		}
		if (block[i].center) {	//���S�u���b�N�̍��W����Ɏ擾
			centerPos[0] = block[i].posX;
			centerPos[1] = block[i].posY;
		}
	}
	//��]
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) && !oldInput[5] || keys[KEY_INPUT_LEFT] && !oldkeys[KEY_INPUT_LEFT]) {
		rotateNum++;
		if (rotateNum > 3) {
			rotateNum = 0;
		}
	}
	else if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) && !oldInput[4] || keys[KEY_INPUT_RIGHT] && !oldkeys[KEY_INPUT_RIGHT]) {
		rotateNum--;
		if (rotateNum < 0) {
			rotateNum = 3;
		}
	}

	//���ړ�
	if (isControl) {
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) && !oldInput[0] || keys[KEY_INPUT_W] && !oldkeys[KEY_INPUT_W]) {
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) && !oldInput[1] || keys[KEY_INPUT_A] && !oldkeys[KEY_INPUT_A]) {
			for (int i = 0; i < blockNum; i++) {
				if (block[i].isControl) {
					block[i].posX -= blockSizeX;
					if (block[i].posX < fieldPosX[0] + fieldFlameSizeX) {
						block[i].posX += blockSizeX;
					}
					else if (rotateNum == 1 && block[i].posX - blockSizeX < fieldPosX[0] + fieldFlameSizeX) {
						block[i].posX += blockSizeX;
					}
				}
			}
		}
		else if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) && !oldInput[3] || keys[KEY_INPUT_D] && !oldkeys[KEY_INPUT_D]) {
			for (int i = 0; i < blockNum; i++) {
				if (block[i].isControl) {
					block[i].posX += blockSizeX;
					if (block[i].posX + blockSizeX > fieldPosX[0] + fieldSizeX - fieldFlameSizeX) {
						block[i].posX -= blockSizeX;
					}
					else if (rotateNum == 3 && block[i].posX + blockSizeX * 2 > fieldPosX[0] + fieldSizeX - fieldFlameSizeX) {
						block[i].posX -= blockSizeX;
					}
				}
			}
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) || keys[KEY_INPUT_S]) {
			//�N�C�b�N�h���b�v
			for (int i = 0; i < blockNum; i++) {
				if (block[i].isControl) {
					block[i].posY += speed * 16 * level;
					if (block[i].center) {	//���S�u���b�N�̍��W����Ɏ擾
						centerPos[0] = block[i].posX;
						centerPos[1] = block[i].posY;
					}
				}
			}
		}

		//�ԍ��ɍ��킹�ău���b�N�̈ʒu�ύX���㍶���E�̏�
		if (rotateNum == 0) {
			for (int i = 0; i < blockNum; i++) {
				if (!block[i].center && block[i].isControl) {
					block[i].posX = centerPos[0];
					block[i].posY = centerPos[1] - blockSizeY;
				}
			}
		}
		else if (rotateNum == 1) {
			for (int i = 0; i < blockNum; i++) {
				if (!block[i].center && block[i].isControl) {
					block[i].posX = centerPos[0] - blockSizeX;
					block[i].posY = centerPos[1];
				}
			}
		}
		else if (rotateNum == 2) {
			for (int i = 0; i < blockNum; i++) {
				if (!block[i].center && block[i].isControl) {
					block[i].posX = centerPos[0];
					block[i].posY = centerPos[1] + blockSizeY;
				}
			}
		}
		else if (rotateNum == 3) {
			for (int i = 0; i < blockNum; i++) {
				if (!block[i].center && block[i].isControl) {
					block[i].posX = centerPos[0] + blockSizeX;
					block[i].posY = centerPos[1];
				}
			}
		}
	}

	//�߂荞�݉��
	for (int i = 0; i < blockNum; i++) {
		if (block[i].center) {
			if (rotateNum == 1 && block[i].posX == fieldPosX[0] + fieldFlameSizeX) {
				block[i].posX += blockSizeX;
			}
			if (rotateNum == 3 && block[i].posX + blockSizeX == fieldPosX[0] + fieldSizeX - fieldFlameSizeX) {
				block[i].posX -= blockSizeX;
			}
		}
	}

	//���n����
	for (int i = 0; i < blockNum; i++) {
		if (block[i].isControl) {
			if (block[i].posY + blockSizeY > fieldPosY[0] + fieldSizeY - fieldFlameSizeY) {
				block[i].posY = fieldPosY[0] + fieldSizeY - fieldFlameSizeY - blockSizeY;
				if (block[i].center && rotateNum == 0) {
					for (int j = 0; j < blockNum; j++) {
						if (block[j].isControl) {
							block[j].isControl = false;
						}
					}
				}
				else if (!block[i].center && rotateNum == 2) {
					for (int j = 0; j < blockNum; j++) {
						if (block[j].center) {
							block[j].center = false;
						}
					}
				}
				block[i].isControl = false;
				block[i].center = false;
				isControl = false;
				//i++;
			}
		}
	}
	for (int i = 0; i < blockNum; i++) {
		if (block[i].isControl) {
			for (int j = 0; j < blockNum; j++) {
				if (block[j].appearingNow && !block[j].isControl) {
					if (block[i].posX == block[j].posX) {
						if (block[i].posY + blockSizeY == block[j].posY) {
							block[i].posY = block[j].posY - blockSizeY;
							block[i].isControl = false;
							block[i].center = false;
							isControl = false;
						}
					}
				}
			}
		}
	}

	CheckOldInput();
}

//�ڑ��`�F�b�N
void Block::CheckConnect() {
	//�S�u���b�N�ɂ���
	for (int i = 0; i < blockNum; i++) {
		//�t�B�[���h�ɂ��邩�`�F�b�N
		if (block[i].appearingNow) {
			//������Ԃł͂Ȃ����Ƃ̃`�F�b�N
			if (!block[i].isFall && !block[i].isControl) {
				//�ڑ��m�F
				IsConnect(i);
				if (block[i].isDelete) {
					countStart = true;
					isDelete = true;
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
		isDelete = false;
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

void Block::CheckOldInput() {
	oldInput[0] = (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP);
	oldInput[1] = (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT);
	oldInput[2] = (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN);
	oldInput[3] = (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT);
	oldInput[4] = (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A);
	oldInput[5] = (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B);
}