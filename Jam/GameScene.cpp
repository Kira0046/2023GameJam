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
		//�o���ʒu���Z�b�g
		centerX = spawnpointX;
		centerY = spawnpointY;
		//�쐬�u���b�N�����Z�b�g
		createredblock = 0;
		creategreenblock = 0;
		createblueblock = 0;

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

	DrawFormatString(0, 0, GetColor(255, 255, 255), "LH:%d\n%d\nRH:%d\n%d\nRL:%d\n%d\nLL:%d\n%d\nred:%d\ngreen:%d\nblue:%d",
		blocklayoutposition[0].blocklayoutcolor, blocklayoutposition[0].blocklayoutpattern,
		blocklayoutposition[1].blocklayoutcolor, blocklayoutposition[1].blocklayoutpattern,
		blocklayoutposition[2].blocklayoutcolor, blocklayoutposition[2].blocklayoutpattern,
		blocklayoutposition[3].blocklayoutcolor, blocklayoutposition[3].blocklayoutpattern,
		createredblock,
		creategreenblock,
		createblueblock);
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
					createredblock++;
				}
				//�E��
				if (i == 1) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
					createredblock++;
				}
				//�E��
				if (i == 2) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
					createredblock++;
				}
				//����
				if (i == 3) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
					createredblock++;
				}
			}
			//�͗l2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//����
				if (i == 0) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
					createredblock++;
				}
				//�E��
				if (i == 1) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
					createredblock++;
				}

				if (i == 2) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
					createredblock++;
				}
				if (i == 3) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY + blockspawnsize, 2));
					createredblock++;
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
					creategreenblock++;
				}
				//�E��
				if (i == 1) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
					creategreenblock++;
				}
				//�E��
				if (i == 2) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
					creategreenblock++;
				}
				//����
				if (i == 3) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
					creategreenblock++;
				}
			}
			//�͗l2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//����
				if (i == 0) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
					creategreenblock++;
				}
				//�E��
				if (i == 1) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
					creategreenblock++;
				}
				//�E��
				if (i == 2) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
					creategreenblock++;
				}
				//����
				if (i == 3) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY + blockspawnsize, 2));
					creategreenblock++;
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
					createblueblock++;
				}
				//�E��
				if (i == 1) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
					createblueblock++;
				}
				//�E��
				if (i == 2) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
					createblueblock++;
				}
				//����
				if (i == 3) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
					createblueblock++;
				}
			}
			//�͗l2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//����
				if (i == 0) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
					createblueblock++;
				}
				//�E��
				if (i == 1) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
					createblueblock++;
				}
				//�E��
				if (i == 2) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
					createblueblock++;
				}
				//����
				if (i == 3) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY + blockspawnsize, 2));
					createblueblock++;
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
		FallBlockCalc();
	}
}

void GameScene::FallBlockCalc() {
	///��
	if (createredblock > 0) {
		//4��
		if (createredblock == 4) {
			if (redBlockList.size() >= 4) {
				auto itr = redBlockList.end();
				--itr;
				--itr;
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (redBlockList.size() >= 3) {
				auto itr = redBlockList.end();
				--itr;
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (redBlockList.size() >= 2) {
				auto itr = redBlockList.end();
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (!redBlockList.empty()) {

				redBlockList.back()->SetPosition(0, amountmovement);
			}
		}

		//3��
		if (createredblock == 3) {
			if (redBlockList.size() >= 3) {
				auto itr = redBlockList.end();
				--itr;
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (redBlockList.size() >= 2) {
				auto itr = redBlockList.end();
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (!redBlockList.empty()) {

				redBlockList.back()->SetPosition(0, amountmovement);
			}
		}

		//�Q��
		if (createredblock == 2) {
			if (redBlockList.size() >= 2) {
				auto itr = redBlockList.end();
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (!redBlockList.empty()) {

				redBlockList.back()->SetPosition(0, amountmovement);
			}
		}

		//�P��
		if (createredblock == 1) {
			if (!redBlockList.empty()) {

				redBlockList.back()->SetPosition(0, amountmovement);
			}
		}

	}

	///��
	if (creategreenblock > 0) {
		//4��
		if (creategreenblock == 4) {

			if (greenBlockList.size() >= 4) {
				auto itr = greenBlockList.end();
				--itr;
				--itr;
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (greenBlockList.size() >= 3) {
				auto itr = greenBlockList.end();
				--itr;
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (greenBlockList.size() >= 2) {
				auto itr = greenBlockList.end();
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (!greenBlockList.empty()) {

				greenBlockList.back()->SetPosition(0, amountmovement);
			}
		}

		//3��
		if (creategreenblock == 3) {

			if (greenBlockList.size() >= 3) {
				auto itr = greenBlockList.end();
				--itr;
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (greenBlockList.size() >= 2) {
				auto itr = greenBlockList.end();
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (!greenBlockList.empty()) {

				greenBlockList.back()->SetPosition(0, amountmovement);
			}
		}

		//2��
		if (creategreenblock == 2) {

			if (greenBlockList.size() >= 2) {
				auto itr = greenBlockList.end();
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (!greenBlockList.empty()) {

				greenBlockList.back()->SetPosition(0, amountmovement);
			}
		}

		//1��
		if (creategreenblock == 1) {

			if (!greenBlockList.empty()) {

				greenBlockList.back()->SetPosition(0, amountmovement);
			}
		}
	}

	///��
	if (createblueblock > 0) {
		//4��
		if (createblueblock == 4) {

			if (blueBlockList.size() >= 4) {
				auto itr = blueBlockList.end();
				--itr;
				--itr;
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (blueBlockList.size() >= 3) {

				auto itr = blueBlockList.end();
				--itr;
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (blueBlockList.size() >= 2) {

				auto itr = blueBlockList.end();
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (!blueBlockList.empty()) {

				blueBlockList.back()->SetPosition(0, amountmovement);
			}
		}

		//3��
		if (createblueblock == 3) {

			if (blueBlockList.size() >= 3) {
				auto itr = blueBlockList.end();
				--itr;
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (blueBlockList.size() >= 2) {
				auto itr = blueBlockList.end();
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (!blueBlockList.empty()) {

				blueBlockList.back()->SetPosition(0, amountmovement);
			}
		}

		//2��
		if (createblueblock == 2) {
			if (blueBlockList.size() >= 2) {
				auto itr = blueBlockList.end();
				--itr;
				--itr;
				(*itr)->SetPosition(0, amountmovement);
			}
			if (!blueBlockList.empty()) {

				blueBlockList.back()->SetPosition(0, amountmovement);
			}
		}

		//1��
		if (createblueblock == 1) {
			if (!blueBlockList.empty()) {

				blueBlockList.back()->SetPosition(0, amountmovement);
			}
		}
	}
}
