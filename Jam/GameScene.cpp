#include "GameScene.h"
#include <ctime>

void GameScene::Initialize() {
	// �ŐV�̃L�[�{�[�h���p
	keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	oldkeys[256] = { 0 };

	srand((unsigned)time(NULL));

	redBlockList.push_back(new RedBlock(800, 450, 1));
	redBlockList.push_back(new RedBlock(600, 450, 1));
	greenBlockList.push_back(new GreenBlock(1000, 450, 1));
	blueBlockList.push_back(new BlueBlock(1200, 450, 1));
}

void GameScene::Update() {
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; ++i) {
		oldkeys[i] = keys[i];
	}
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);

	//�u���b�N�z�u�ҋ@(���Z�b�g)
	if (fallphase == 0) {
		centerX = spawnpointX;
		centerY = spawnpointY;
		fallphase = 1;
	}
	//�u���b�N�z�u
	if (fallphase == 1) {
		BlockLayoutSetting();
		fallphase = 2;
	}
	//����
	if (fallphase == 2) {
		BlockOperation();
		FallingCalc();
	}


}

void GameScene::Draw() {
	//�ԃu���b�N�`��
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		(*redblockitr)->Draw();
	}

	//�΃u���b�N�`��
	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		(*greenblockitr)->Draw();
	}

	//�u���b�N�`��
	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		(*blueblockitr)->Draw();
	}
	DrawBox(centerX - blockspawnsize, centerY - blockspawnsize, centerX + blockspawnsize, centerY + blockspawnsize, GetColor(255, 255, 0), true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "LH:%d\n%d\nRH:%d\n%d\nRL:%d\n%d\nLL:%d\n%d",
		blocklayoutposition[0].blocklayoutcolor, blocklayoutposition[0].blocklayoutpattern,
		blocklayoutposition[1].blocklayoutcolor, blocklayoutposition[1].blocklayoutpattern,
		blocklayoutposition[2].blocklayoutcolor, blocklayoutposition[2].blocklayoutpattern,
		blocklayoutposition[3].blocklayoutcolor, blocklayoutposition[3].blocklayoutpattern);
}

void GameScene::BlockLayoutSetting() {
	//�z�u�ꏊ  i=0:���� 1:�E�� 2:�E�� 3:����
	for (int i = 0; i < 4; i++) {
		//�F���� 0:�z�u���Ȃ��@1:�ԁ@2:��  3:��
		blocklayoutposition[i].blocklayoutcolor = rand() % 4;
		//�͗l���� 1: 2:
		blocklayoutposition[i].blocklayoutpattern = rand() % 2 + 1;

		if (blocklayoutposition[i].blocklayoutcolor == 0) {

		}
		//��ver
		if (blocklayoutposition[i].blocklayoutcolor == 1) {
			//�͗l1
			if (blocklayoutposition[i].blocklayoutpattern == 1) {
				//����
				if (i == 0) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY - blockspawnsize, 1));
				}
				//�E��
				if (i == 1) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
				}
				//�E��
				if (i == 2) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
				}
				//����
				if (i == 3) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
				}
			}
			//�͗l2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//����
				if (i == 0) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
				}
				//�E��
				if (i == 1) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
				}

				if (i == 2) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
				}
				if (i == 3) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY + blockspawnsize, 2));
				}
			}
		}
		//��ver
		if (blocklayoutposition[i].blocklayoutcolor == 2) {
			//�͗l1
			if (blocklayoutposition[i].blocklayoutpattern == 1) {
				//����
				if (i == 0) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY - blockspawnsize, 1));
				}
				//�E��
				if (i == 1) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
				}
				//�E��
				if (i == 2) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
				}
				//����
				if (i == 3) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
				}
			}
			//�͗l2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//����
				if (i == 0) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
				}
				//�E��
				if (i == 1) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
				}
				//�E��
				if (i == 2) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
				}
				//����
				if (i == 3) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY + blockspawnsize, 2));
				}
			}
		}
		//��ver
		if (blocklayoutposition[i].blocklayoutcolor == 3) {
			//�͗l1
			if (blocklayoutposition[i].blocklayoutpattern == 1) {
				//����
				if (i == 0) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY - blockspawnsize, 1));
				}
				//�E��
				if (i == 1) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
				}
				//�E��
				if (i == 2) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
				}
				//����
				if (i == 3) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
				}
			}
			//�͗l2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//����
				if (i == 0) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
				}
				//�E��
				if (i == 1) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
				}
				//�E��
				if (i == 2) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
				}
				//����
				if (i == 3) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY + blockspawnsize, 2));
				}
			}
		}
	}


}

void GameScene::BlockOperation() {
	if (keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0) {
		centerX -= amountmovement;
	}
	if (keys[KEY_INPUT_D] == 1 && oldkeys[KEY_INPUT_D] == 0) {
		centerX += amountmovement;
	}
}

void GameScene::FallingCalc() {
	fallupdatetime -= 1;
	if (fallupdatetime == 0) {
		centerY += amountmovement;
		fallupdatetime = 60;
	}
}
