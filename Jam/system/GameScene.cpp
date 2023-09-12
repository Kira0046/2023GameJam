#include "GameScene.h"
#include <ctime>



void GameScene::Initialize() {
	// �ŐV�̃L�[�{�[�h���p
	keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	oldkeys[256] = { 0 };

	srand((unsigned)time(NULL));

	//redBlockList.push_back(new RedBlock(680, 264, 1));
	////redBlockList.push_back(new RedBlock(600, 450, 1));
	//greenBlockList.push_back(new GreenBlock(824, 264, 1));
	//blueBlockList.push_back(new BlueBlock(968, 264, 1));

	//�t�B�[���h
	//�摜�ǂݍ���
	fieldHandle = LoadGraph("Resource/field/field_kari.png");
	//�摜�T�C�Y�擾
	GetGraphSize(fieldHandle, &fieldSizeX, &fieldSizeY);
	//�t�B�[���h���W����
	fieldPosX[0] = 1600 / 2 - fieldSizeX / 2;
	fieldPosY[0] = 900 / 2 - fieldSizeY / 2;

	centerX = fieldPosX[0] + fieldSizeX / 2 + fieldFlameSizeX;
	centerY = fieldPosY[0] + fieldFlameSizeY;
	spawnpointY = fieldPosY[0] + fieldFlameSizeY;
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

		PiledBlock();

		CheckConnect();

		PileBlockToLand();
		/*if (centerY == 816) {

			SetBlockToFallFalse();

			fallphase = 0;
		}*/
		//�ڑ��m�F
	}

	if (fallphase == 3) {

	}

}

void GameScene::Draw() {
	DrawGraph(fieldPosX[0], fieldPosY[0], fieldHandle, true);

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
	//DrawBox(centerX - blockspawnsize, centerY - blockspawnsize, centerX + blockspawnsize, centerY + blockspawnsize, GetColor(255, 255, 0), true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "LH:%d\n%d\nRH:%d\n%d\nRL:%d\n%d\nLL:%d\n%d\nred:%d\ngreen:%d\nblue:%d\n%d %d\nR%d %d\nG%d %d\nB%d %d",
		blocklayoutposition[0].blocklayoutcolor, blocklayoutposition[0].blocklayoutpattern,
		blocklayoutposition[1].blocklayoutcolor, blocklayoutposition[1].blocklayoutpattern,
		blocklayoutposition[2].blocklayoutcolor, blocklayoutposition[2].blocklayoutpattern,
		blocklayoutposition[3].blocklayoutcolor, blocklayoutposition[3].blocklayoutpattern,
		createredblock,
		creategreenblock,
		createblueblock,
		centerX,
		centerY,
		redblocklefthit,
		redblockrighthit,
		greenblocklefthit,
		greenblockrighthit,
		blueblocklefthit,
		blueblockrighthit);
}

void GameScene::BlockLayoutSetting() {
	//�z�u�ꏊ  i=0:���� 1:�E�� 2:�E�� 3:����

	//�F���� 0:�z�u���Ȃ��@1:�ԁ@2:��  3:��
	blocklayoutposition[0].blocklayoutcolor = rand() % 3 + 1;
	blocklayoutposition[1].blocklayoutcolor = 0;
	blocklayoutposition[2].blocklayoutcolor = 0;
	blocklayoutposition[3].blocklayoutcolor = rand() % 3 + 1;
	for (int i = 0; i < 4; i++) {

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

	{
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
					if ((*itr)->hitleft == true) {
						redblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						redblockrighthit = true;
					}

				}
				if (redBlockList.size() >= 3) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						redblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						redblockrighthit = true;
					}
				}
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						redblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						redblockrighthit = true;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitleft == true) {
						redblocklefthit = true;
					}

					if (redBlockList.back()->hitright == true) {
						redblockrighthit = true;;
					}

				}
			}

			//3��
			if (createredblock == 3) {
				if (redBlockList.size() >= 3) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						redblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						redblockrighthit = true;
					}
				}
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						redblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						redblockrighthit = true;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitleft == true) {
						redblocklefthit = true;
					}

					if (redBlockList.back()->hitright == true) {
						redblockrighthit = true;;
					}
				}
			}

			//�Q��
			if (createredblock == 2) {
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						redblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						redblockrighthit = true;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitleft == true) {
						redblocklefthit = true;
					}

					if (redBlockList.back()->hitright == true) {
						redblockrighthit = true;;
					}
				}
			}

			//�P��
			if (createredblock == 1) {
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitleft == true) {
						redblocklefthit = true;
					}

					if (redBlockList.back()->hitright == true) {
						redblockrighthit = true;;
					}
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
					if ((*itr)->hitleft == true) {
						greenblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						greenblockrighthit = true;
					}
				}
				if (greenBlockList.size() >= 3) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						greenblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						greenblockrighthit = true;
					}
				}
				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						greenblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						greenblockrighthit = true;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitleft == true) {
						greenblocklefthit = true;
					}

					if (greenBlockList.back()->hitright == true) {
						greenblockrighthit = true;;
					}
				}
			}

			//3��
			if (creategreenblock == 3) {

				if (greenBlockList.size() >= 3) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						greenblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						greenblockrighthit = true;
					}
				}
				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						greenblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						greenblockrighthit = true;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitleft == true) {
						greenblocklefthit = true;
					}

					if (greenBlockList.back()->hitright == true) {
						greenblockrighthit = true;;
					}
				}
			}

			//2��
			if (creategreenblock == 2) {

				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						greenblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						greenblockrighthit = true;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitleft == true) {
						greenblocklefthit = true;
					}

					if (greenBlockList.back()->hitright == true) {
						greenblockrighthit = true;;
					}
				}
			}

			//1��
			if (creategreenblock == 1) {

				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitleft == true) {
						greenblocklefthit = true;
					}

					if (greenBlockList.back()->hitright == true) {
						greenblockrighthit = true;;
					}
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
					if ((*itr)->hitleft == true) {
						blueblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						blueblockrighthit = true;
					}
				}
				if (blueBlockList.size() >= 3) {

					auto itr = blueBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						blueblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						blueblockrighthit = true;
					}
				}
				if (blueBlockList.size() >= 2) {

					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						blueblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						blueblockrighthit = true;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitleft == true) {
						blueblocklefthit = true;
					}

					if (blueBlockList.back()->hitright == true) {
						blueblockrighthit = true;;
					}
				}
			}

			//3��
			if (createblueblock == 3) {

				if (blueBlockList.size() >= 3) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						blueblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						blueblockrighthit = true;
					}
				}
				if (blueBlockList.size() >= 2) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						blueblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						blueblockrighthit = true;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitleft == true) {
						blueblocklefthit = true;
					}

					if (blueBlockList.back()->hitright == true) {
						blueblockrighthit = true;;
					}
				}
			}

			//2��
			if (createblueblock == 2) {
				if (blueBlockList.size() >= 2) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitleft == true) {
						blueblocklefthit = true;
					}
					if ((*itr)->hitright == true) {
						blueblockrighthit = true;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitleft == true) {
						blueblocklefthit = true;
					}

					if (blueBlockList.back()->hitright == true) {
						blueblockrighthit = true;;
					}
				}
			}

			//1��
			if (createblueblock == 1) {
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitleft == true) {
						blueblocklefthit = true;
					}

					if (blueBlockList.back()->hitright == true) {
						blueblockrighthit = true;;
					}
				}
			}
		}
	}
	if (redblocklefthit == false && greenblocklefthit == false && blueblocklefthit == false) {
		if (keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0) {
			if (centerX > fieldPosX[0] + fieldFlameSizeX + 24 + 48) {
				centerX -= amountmovement;
				{
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
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (redBlockList.size() >= 3) {
								auto itr = redBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (redBlockList.size() >= 2) {
								auto itr = redBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (!redBlockList.empty()) {

								redBlockList.back()->SetPosition(-amountmovement, 0);
							}
						}

						//3��
						if (createredblock == 3) {
							if (redBlockList.size() >= 3) {
								auto itr = redBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (redBlockList.size() >= 2) {
								auto itr = redBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (!redBlockList.empty()) {

								redBlockList.back()->SetPosition(-amountmovement, 0);
							}
						}

						//�Q��
						if (createredblock == 2) {
							if (redBlockList.size() >= 2) {
								auto itr = redBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (!redBlockList.empty()) {

								redBlockList.back()->SetPosition(-amountmovement, 0);
							}
						}

						//�P��
						if (createredblock == 1) {
							if (!redBlockList.empty()) {

								redBlockList.back()->SetPosition(-amountmovement, 0);
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
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (greenBlockList.size() >= 3) {
								auto itr = greenBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (greenBlockList.size() >= 2) {
								auto itr = greenBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (!greenBlockList.empty()) {

								greenBlockList.back()->SetPosition(-amountmovement, 0);
							}
						}

						//3��
						if (creategreenblock == 3) {

							if (greenBlockList.size() >= 3) {
								auto itr = greenBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (greenBlockList.size() >= 2) {
								auto itr = greenBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (!greenBlockList.empty()) {

								greenBlockList.back()->SetPosition(-amountmovement, 0);
							}
						}

						//2��
						if (creategreenblock == 2) {

							if (greenBlockList.size() >= 2) {
								auto itr = greenBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (!greenBlockList.empty()) {

								greenBlockList.back()->SetPosition(-amountmovement, 0);
							}
						}

						//1��
						if (creategreenblock == 1) {

							if (!greenBlockList.empty()) {

								greenBlockList.back()->SetPosition(-amountmovement, 0);
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
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (blueBlockList.size() >= 3) {

								auto itr = blueBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (blueBlockList.size() >= 2) {

								auto itr = blueBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (!blueBlockList.empty()) {

								blueBlockList.back()->SetPosition(-amountmovement, 0);
							}
						}

						//3��
						if (createblueblock == 3) {

							if (blueBlockList.size() >= 3) {
								auto itr = blueBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (blueBlockList.size() >= 2) {
								auto itr = blueBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (!blueBlockList.empty()) {

								blueBlockList.back()->SetPosition(-amountmovement, 0);
							}
						}

						//2��
						if (createblueblock == 2) {
							if (blueBlockList.size() >= 2) {
								auto itr = blueBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(-amountmovement, 0);
							}
							if (!blueBlockList.empty()) {

								blueBlockList.back()->SetPosition(-amountmovement, 0);
							}
						}

						//1��
						if (createblueblock == 1) {
							if (!blueBlockList.empty()) {

								blueBlockList.back()->SetPosition(-amountmovement, 0);
							}
						}
					}
				}
			}
		}
	}

	if (redblockrighthit == false && greenblockrighthit == false && blueblockrighthit == false) {
		if (keys[KEY_INPUT_D] == 1 && oldkeys[KEY_INPUT_D] == 0) {
			if (centerX < fieldPosX[0] + fieldSizeX - fieldFlameSizeX - 24) {
				centerX += amountmovement;
				{
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
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (redBlockList.size() >= 3) {
								auto itr = redBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (redBlockList.size() >= 2) {
								auto itr = redBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (!redBlockList.empty()) {

								redBlockList.back()->SetPosition(amountmovement, 0);
							}
						}

						//3��
						if (createredblock == 3) {
							if (redBlockList.size() >= 3) {
								auto itr = redBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (redBlockList.size() >= 2) {
								auto itr = redBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (!redBlockList.empty()) {

								redBlockList.back()->SetPosition(amountmovement, 0);
							}
						}

						//�Q��
						if (createredblock == 2) {
							if (redBlockList.size() >= 2) {
								auto itr = redBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (!redBlockList.empty()) {

								redBlockList.back()->SetPosition(amountmovement, 0);
							}
						}

						//�P��
						if (createredblock == 1) {
							if (!redBlockList.empty()) {

								redBlockList.back()->SetPosition(amountmovement, 0);
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
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (greenBlockList.size() >= 3) {
								auto itr = greenBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (greenBlockList.size() >= 2) {
								auto itr = greenBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (!greenBlockList.empty()) {

								greenBlockList.back()->SetPosition(amountmovement, 0);
							}
						}

						//3��
						if (creategreenblock == 3) {

							if (greenBlockList.size() >= 3) {
								auto itr = greenBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (greenBlockList.size() >= 2) {
								auto itr = greenBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (!greenBlockList.empty()) {

								greenBlockList.back()->SetPosition(amountmovement, 0);
							}
						}

						//2��
						if (creategreenblock == 2) {

							if (greenBlockList.size() >= 2) {
								auto itr = greenBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (!greenBlockList.empty()) {

								greenBlockList.back()->SetPosition(amountmovement, 0);
							}
						}

						//1��
						if (creategreenblock == 1) {

							if (!greenBlockList.empty()) {

								greenBlockList.back()->SetPosition(amountmovement, 0);
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
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (blueBlockList.size() >= 3) {

								auto itr = blueBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (blueBlockList.size() >= 2) {

								auto itr = blueBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (!blueBlockList.empty()) {

								blueBlockList.back()->SetPosition(amountmovement, 0);
							}
						}

						//3��
						if (createblueblock == 3) {

							if (blueBlockList.size() >= 3) {
								auto itr = blueBlockList.end();
								--itr;
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (blueBlockList.size() >= 2) {
								auto itr = blueBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (!blueBlockList.empty()) {

								blueBlockList.back()->SetPosition(amountmovement, 0);
							}
						}

						//2��
						if (createblueblock == 2) {
							if (blueBlockList.size() >= 2) {
								auto itr = blueBlockList.end();
								--itr;
								--itr;
								(*itr)->SetPosition(amountmovement, 0);
							}
							if (!blueBlockList.empty()) {

								blueBlockList.back()->SetPosition(amountmovement, 0);
							}
						}

						//1��
						if (createblueblock == 1) {
							if (!blueBlockList.empty()) {

								blueBlockList.back()->SetPosition(amountmovement, 0);
							}
						}
					}
				}
			}
		}
	}
}

void GameScene::FallingCalc() {
	fallupdatetime -= 1;
	FallingCollision();
	if (fallupdatetime == 0) {
		centerY += amountmovement;
		fallupdatetime = maxUpdateTime;
		FallBlockCalc();
		for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
			(*redblockitr)->SetHitUp(false);
			(*redblockitr)->SetHitDown(false);
			(*redblockitr)->SetHitRight(false);
			(*redblockitr)->SetHitLeft(false);
		}
		for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
			(*greenblockitr)->SetHitUp(false);
			(*greenblockitr)->SetHitDown(false);
			(*greenblockitr)->SetHitRight(false);
			(*greenblockitr)->SetHitLeft(false);
		}

		for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
			(*blueblockitr)->SetHitUp(false);
			(*blueblockitr)->SetHitDown(false);
			(*blueblockitr)->SetHitRight(false);
			(*blueblockitr)->SetHitLeft(false);
		}
		redblocklefthit = false;
		redblockrighthit = false;
		greenblocklefthit = false;
		greenblockrighthit = false;
		blueblocklefthit = false;
		blueblockrighthit = false;
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

void GameScene::FallingCollision() {
	//�ԁA��
	if (redBlockList.size() >= 2) {
		for (auto itr = redBlockList.begin(); itr != std::prev(redBlockList.end()); ++itr) {
			for (auto itr2 = std::next(redBlockList.begin()); itr2 != redBlockList.end(); ++itr2) {

				//1��
				//����
				int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//�E��
				int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//�E��
				int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
				//����
				int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

				//2��
				//����
				int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
				int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//�E��
				int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//�E��
				int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
				//����
				int LLX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
				int LLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();

				if ((*itr)->GetIsFall() == false || (*itr2)->GetIsFall() == false) {
					if (LLX1 == LHX2 && LLY1 == LHY2 && RLX1 == RHX2 && RLY1 == RHY2) {
						(*itr)->SetHitDown(true);
						(*itr2)->SetHitUp(true);

					}
					if (LLX2 == LHX1 && LLY2 == LHY1 && RLX2 == RHX1 && RLY2 == RHY1) {
						(*itr)->SetHitUp(true);
						(*itr2)->SetHitDown(true);

					}
					if (RHX1 == LHX2 && RHY1 == LHY2 && RLX1 == LLX2 && RLY1 && LLY2) {
						(*itr)->SetHitRight(true);
						(*itr2)->SetHitLeft(true);

					}


					if (RHX2 == LHX1 && RHY2 == LHY1 && RLX2 == LLX1 && RLY2 && LLY1) {
						(*itr)->SetHitLeft(true);
						(*itr2)->SetHitRight(true);

					}
				}
			}
		}
	}



	//�΁A��
	if (greenBlockList.size() >= 2) {
		for (auto itr = greenBlockList.begin(); itr != std::prev(greenBlockList.end()); ++itr) {
			for (auto itr2 = std::next(greenBlockList.begin()); itr2 != greenBlockList.end(); ++itr2) {

				//1��
				//����
				int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//�E��
				int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//�E��
				int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
				//����
				int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

				//2��
				//����
				int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
				int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//�E��
				int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//�E��
				int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
				//����
				int LLX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
				int LLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();

				if ((*itr)->GetIsFall() == false || (*itr2)->GetIsFall() == false) {
					if (LLX1 == LHX2 && LLY1 == LHY2 && RLX1 == RHX2 && RLY1 == RHY2) {
						(*itr)->SetHitDown(true);
						(*itr2)->SetHitUp(true);
					}
					if (LLX2 == LHX1 && LLY2 == LHY1 && RLX2 == RHX1 && RLY2 == RHY1) {
						(*itr)->SetHitUp(true);
						(*itr2)->SetHitDown(true);
					}
					if (RHX1 == LHX2 && RHY1 == LHY2 && RLX1 == LLX2 && RLY1 && LLY2) {
						(*itr)->SetHitRight(true);
						(*itr2)->SetHitLeft(true);
					}

					if (RHX2 == LHX1 && RHY2 == LHY1 && RLX2 == LLX1 && RLY2 && LLY1) {
						(*itr)->SetHitLeft(true);
						(*itr2)->SetHitRight(true);
					}
				}
			}
		}
	}


	//�A��
	if (blueBlockList.size() >= 2) {
		for (auto itr = blueBlockList.begin(); itr != std::prev(blueBlockList.end()); ++itr) {
			for (auto itr2 = std::next(blueBlockList.begin()); itr2 != blueBlockList.end(); ++itr2) {

				//1��
				//����
				int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//�E��
				int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//�E��
				int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
				//����
				int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

				//2��
				//����
				int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
				int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//�E��
				int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//�E��
				int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
				//����
				int LLX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
				int LLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();

				if ((*itr)->GetIsFall() == false || (*itr2)->GetIsFall() == false) {
					if (LLX1 == LHX2 && LLY1 == LHY2 && RLX1 == RHX2 && RLY1 == RHY2) {
						(*itr)->SetHitDown(true);
						(*itr2)->SetHitUp(true);
					}
					if (LLX2 == LHX1 && LLY2 == LHY1 && RLX2 == RHX1 && RLY2 == RHY1) {
						(*itr)->SetHitUp(true);
						(*itr2)->SetHitDown(true);
					}
					if (RHX1 == LHX2 && RHY1 == LHY2 && RLX1 == LLX2 && RLY1 && LLY2) {
						(*itr)->SetHitRight(true);
						(*itr2)->SetHitLeft(true);
					}

					if (RHX2 == LHX1 && RHY2 == LHY1 && RLX2 == LLX1 && RLY2 && LLY1) {
						(*itr)->SetHitLeft(true);
						(*itr2)->SetHitRight(true);
					}
				}
			}
		}
	}

	//�ԁA��
	if (redBlockList.size() >= 1) {
		if (greenBlockList.size() >= 1) {
			for (auto itr = redBlockList.begin(); itr != redBlockList.end(); ++itr) {
				for (auto itr2 = greenBlockList.begin(); itr2 != greenBlockList.end(); ++itr2) {

					//1��
					//����
					int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//�E��
					int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//�E��
					int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
					//����
					int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

					//2��
					//����
					int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
					int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//�E��
					int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//�E��
					int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
					//����
					int LLX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
					int LLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();

					if ((*itr)->GetIsFall() == false || (*itr2)->GetIsFall() == false) {
						if (LLX1 == LHX2 && LLY1 == LHY2 && RLX1 == RHX2 && RLY1 == RHY2) {
							(*itr)->SetHitDown(true);
							(*itr2)->SetHitUp(true);
						}
						if (LLX2 == LHX1 && LLY2 == LHY1 && RLX2 == RHX1 && RLY2 == RHY1) {
							(*itr)->SetHitUp(true);
							(*itr2)->SetHitDown(true);
						}
						if (RHX1 == LHX2 && RHY1 == LHY2 && RLX1 == LLX2 && RLY1 && LLY2) {
							(*itr)->SetHitRight(true);
							(*itr2)->SetHitLeft(true);
						}

						if (RHX2 == LHX1 && RHY2 == LHY1 && RLX2 == LLX1 && RLY2 && LLY1) {
							(*itr)->SetHitLeft(true);
							(*itr2)->SetHitRight(true);
						}
					}
				}
			}
		}
	}

	//�ԁA��
	if (redBlockList.size() >= 1) {
		if (blueBlockList.size() >= 1) {
			for (auto itr = redBlockList.begin(); itr != redBlockList.end(); ++itr) {
				for (auto itr2 = blueBlockList.begin(); itr2 != blueBlockList.end(); ++itr2) {

					//1��
					//����
					int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//�E��
					int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//�E��
					int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
					//����
					int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

					//2��
					//����
					int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
					int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//�E��
					int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//�E��
					int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
					//����
					int LLX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
					int LLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();

					if ((*itr)->GetIsFall() == false || (*itr2)->GetIsFall() == false) {
						if (LLX1 == LHX2 && LLY1 == LHY2 && RLX1 == RHX2 && RLY1 == RHY2) {
							(*itr)->SetHitDown(true);
							(*itr2)->SetHitUp(true);
						}
						if (LLX2 == LHX1 && LLY2 == LHY1 && RLX2 == RHX1 && RLY2 == RHY1) {
							(*itr)->SetHitUp(true);
							(*itr2)->SetHitDown(true);
						}
						if (RHX1 == LHX2 && RHY1 == LHY2 && RLX1 == LLX2 && RLY1 && LLY2) {
							(*itr)->SetHitRight(true);
							(*itr2)->SetHitLeft(true);
						}

						if (RHX2 == LHX1 && RHY2 == LHY1 && RLX2 == LLX1 && RLY2 && LLY1) {
							(*itr)->SetHitLeft(true);
							(*itr2)->SetHitRight(true);
						}
					}
				}
			}
		}
	}

	//�΁A��
	if (greenBlockList.size() >= 1) {
		if (blueBlockList.size() >= 1) {
			for (auto itr = greenBlockList.begin(); itr != greenBlockList.end(); ++itr) {
				for (auto itr2 = blueBlockList.begin(); itr2 != blueBlockList.end(); ++itr2) {

					//1��
					//����
					int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//�E��
					int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//�E��
					int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
					//����
					int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

					//2��
					//����
					int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
					int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//�E��
					int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//�E��
					int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
					//����
					int LLX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
					int LLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();

					if ((*itr)->GetIsFall() == false || (*itr2)->GetIsFall() == false) {
						if (LLX1 == LHX2 && LLY1 == LHY2 && RLX1 == RHX2 && RLY1 == RHY2) {
							(*itr)->SetHitDown(true);
							(*itr2)->SetHitUp(true);
						}
						if (LLX2 == LHX1 && LLY2 == LHY1 && RLX2 == RHX1 && RLY2 == RHY1) {
							(*itr)->SetHitUp(true);
							(*itr2)->SetHitDown(true);
						}

						if (RHX1 == LHX2 && RHY1 == LHY2 && RLX1 == LLX2 && RLY1 && LLY2) {
							(*itr)->SetHitRight(true);
							(*itr2)->SetHitLeft(true);
						}


						if (RHX2 == LHX1 && RHY2 == LHY1 && RLX2 == LLX1 && RLY2 && LLY1) {
							(*itr)->SetHitLeft(true);
							(*itr2)->SetHitRight(true);
						}
					}
				}
			}
		}
	}

}

void GameScene::PiledBlock() {

	{
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
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (redBlockList.size() >= 3) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}

				}
			}

			//3��
			if (createredblock == 3) {
				if (redBlockList.size() >= 3) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
			}

			//�Q��
			if (createredblock == 2) {
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
			}

			//�P��
			if (createredblock == 1) {
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
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
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (greenBlockList.size() >= 3) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}

				}
			}

			//3��
			if (creategreenblock == 3) {

				if (greenBlockList.size() >= 3) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}

				}
			}

			//2��
			if (creategreenblock == 2) {

				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
			}

			//1��
			if (creategreenblock == 1) {

				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
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
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (blueBlockList.size() >= 3) {

					auto itr = blueBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (blueBlockList.size() >= 2) {

					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
			}

			//3��
			if (createblueblock == 3) {

				if (blueBlockList.size() >= 3) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (blueBlockList.size() >= 2) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
			}

			//2��
			if (createblueblock == 2) {
				if (blueBlockList.size() >= 2) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}
				}
			}

			//1��
			if (createblueblock == 1) {
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitdown == true) {
						SetBlockToFallFalse();

						fallphase = 0;
					}

				}
			}
		}
	}
}

void GameScene::SetBlockToFallFalse() {
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		(*redblockitr)->SetFall(false);
	}

	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		(*greenblockitr)->SetFall(false);
	}

	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		(*blueblockitr)->SetFall(false);
	}
}

void GameScene::PileBlockToLand() {
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		if ((*redblockitr)->fall == true) {
			if ((*redblockitr)->GetPositionY() == 834 + 24) {
				SetBlockToFallFalse();

				fallphase = 0;
			}
		}
	}

	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		if ((*greenblockitr)->fall == true) {
			if ((*greenblockitr)->GetPositionY() == 834 + 24) {
				SetBlockToFallFalse();

				fallphase = 0;
			}
		}
	}

	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		if ((*blueblockitr)->fall == true) {
			if ((*blueblockitr)->GetPositionY() == 834 + 24) {
				SetBlockToFallFalse();

				fallphase = 0;
			}
		}
	}
}

//�ڑ��`�F�b�N
void GameScene::CheckConnect() {
	//�e��u���b�N�ɂ���
	//������Ԃł͂Ȃ����Ƃ̃`�F�b�N
	//��
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		if (!(*redblockitr)->GetIsFall()) {
			//�ڑ��m�F
			//�אڂ����u���b�N�̍��W�擾
			float connectPos[8];
			//��
			connectPos[0] = (*redblockitr)->GetPositionX();// -fieldFlameSizeX;
			connectPos[1] = (*redblockitr)->GetPositionY() - (*redblockitr)->GetSize() - halfSize;
			//��
			connectPos[2] = (*redblockitr)->GetPositionX();// -fieldFlameSizeX;
			connectPos[3] = (*redblockitr)->GetPositionY() + (*redblockitr)->GetSize() + halfSize;
			//��
			connectPos[4] = (*redblockitr)->GetPositionX() - (*redblockitr)->GetSize() - halfSize;
			connectPos[5] = (*redblockitr)->GetPositionY();
			//�E
			connectPos[6] = (*redblockitr)->GetPositionX() + (*redblockitr)->GetSize() + halfSize;
			connectPos[7] = (*redblockitr)->GetPositionY();
			//��v�����ꍇ�̂݃J�E���g�A2�ȏ�ŏ�����
			int matchCount[2][2] = { { 0,0 },{0,0} };	//{{�c�F,���F},{�c��,����}}

			//�e�F���Ƃɐڑ��m�F
			//��
			for (auto redblockitr2 = redBlockList.begin(); redblockitr2 != redBlockList.end(); ++redblockitr2) {
				//�������g�͒e��
				if (redblockitr != redblockitr2) {
					for (int i = 0; i < 8; i) {
						//�㉺���E�̏��Őڑ��`�F�b�N
						if (connectPos[i] == (*redblockitr2)->GetPositionX() && connectPos[i + 1] == (*redblockitr2)->GetPositionY()) {
							//�����F�͊m��Ȃ̂ŏ������򂳂���K�v�Ȃ�
							if (i < 4) {
								matchCount[0][0]++;
							}
							else if (i > 3) {
								matchCount[0][1]++;
							}
							//����v�m�F
							if ((*redblockitr)->GetPattern() == (*redblockitr2)->GetPattern()) {
								if (i < 4) {
									matchCount[1][0]++;
								}
								else if (i > 3) {
									matchCount[1][1]++;
								}
							}
						}
						i += 2;
					}
				}
			}
			//��
			for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
				for (int i = 0; i < 8; i) {
					//�㉺���E�̏��Őڑ��`�F�b�N
					if (connectPos[i] == (*blueblockitr)->GetPositionX() && connectPos[i + 1] == (*blueblockitr)->GetPositionY()) {
						//����v�m�F
						if ((*redblockitr)->GetPattern() == (*blueblockitr)->GetPattern()) {
							if (i < 4) {
								matchCount[1][0]++;
							}
							else if (i > 3) {
								matchCount[1][1]++;
							}
						}
					}
					i += 2;
				}
			}
			//��
			for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
				for (int i = 0; i < 8; i) {
					//�㉺���E�̏��Őڑ��`�F�b�N
					if (connectPos[i] == (*greenblockitr)->GetPositionX() && connectPos[i + 1] == (*greenblockitr)->GetPositionY()) {
						//����v�m�F
						if ((*redblockitr)->GetPattern() == (*greenblockitr)->GetPattern()) {
							if (i < 4) {
								matchCount[1][0]++;
							}
							else if (i > 3) {
								matchCount[1][1]++;
							}
						}
					}
					i += 2;
				}
			}
			//�J�E���g���������ꍇ����
			for (int i = 0; i < 2; i++) {
				//��
				for (auto redblockitr2 = redBlockList.begin(); redblockitr2 != redBlockList.end(); ++redblockitr2) {
					if (matchCount[i][0] > deleteConnectNum) {
						(*redblockitr)->SetDelete(true, false, false);
						if ((*redblockitr2)->GetPositionX() == connectPos[0] && (*redblockitr2)->GetPositionY() == connectPos[1]) {
							(*redblockitr2)->SetDelete(true, false, false);
						}
						if ((*redblockitr2)->GetPositionX() == connectPos[2] && (*redblockitr2)->GetPositionY() == connectPos[3]) {
							(*redblockitr2)->SetDelete(true, false, false);
						}
					}
					if (matchCount[i][1] > deleteConnectNum) {
						(*redblockitr)->SetDelete(true, false, false);
						if ((*redblockitr2)->GetPositionX() == connectPos[4] && (*redblockitr2)->GetPositionY() == connectPos[5]) {
							(*redblockitr2)->SetDelete(true, false, false);
						}
						if ((*redblockitr2)->GetPositionX() == connectPos[6] && (*redblockitr2)->GetPositionY() == connectPos[7]) {
							(*redblockitr2)->SetDelete(true, false, false);
						}
					}
				}
				//��
				for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
					//����v�̂�
					if (matchCount[i][1] > deleteConnectNum) {
						(*redblockitr)->SetDelete(true, false, false);
						if ((*blueblockitr)->GetPositionX() == connectPos[4] && (*blueblockitr)->GetPositionY() == connectPos[5]) {
							(*blueblockitr)->SetDelete(true, false, false);
						}
						if ((*blueblockitr)->GetPositionX() == connectPos[6] && (*blueblockitr)->GetPositionY() == connectPos[7]) {
							(*blueblockitr)->SetDelete(true, false, false);
						}
					}
				}
				//��
				for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
					//����v�̂�
					if (matchCount[i][1] > deleteConnectNum) {
						(*redblockitr)->SetDelete(true, false, false);
						if ((*greenblockitr)->GetPositionX() == connectPos[4] && (*greenblockitr)->GetPositionY() == connectPos[5]) {
							(*greenblockitr)->SetDelete(true, false, false);
						}
						if ((*greenblockitr)->GetPositionX() == connectPos[6] && (*greenblockitr)->GetPositionY() == connectPos[7]) {
							(*greenblockitr)->SetDelete(true, false, false);
						}
					}
				}
			}
			//����v�`�F�b�N
			//�㉺
			if (matchCount[0][0] > deleteConnectNum && matchCount[1][0] > deleteConnectNum) {
				//��
				for (auto redblockitr2 = redBlockList.begin(); redblockitr2 != redBlockList.end(); ++redblockitr2) {
					(*redblockitr)->SetDelete(true, true, false);
					if ((*redblockitr2)->GetPositionX() == connectPos[0] && (*redblockitr2)->GetPositionY() == connectPos[1]) {
						(*redblockitr2)->SetDelete(true, true, false);
					}
					if ((*redblockitr2)->GetPositionX() == connectPos[2] && (*redblockitr2)->GetPositionY() == connectPos[3]) {
						(*redblockitr2)->SetDelete(true, true, false);
					}
				}
			}
			//���E
			if (matchCount[0][1] > deleteConnectNum && matchCount[1][1] > deleteConnectNum) {
				//��
				for (auto redblockitr2 = redBlockList.begin(); redblockitr2 != redBlockList.end(); ++redblockitr2) {
					(*redblockitr)->SetDelete(true, true, false);
					if ((*redblockitr2)->GetPositionX() == connectPos[4] && (*redblockitr2)->GetPositionY() == connectPos[5]) {
						(*redblockitr2)->SetDelete(true, true, false);
					}
					if ((*redblockitr2)->GetPositionX() == connectPos[6] && (*redblockitr2)->GetPositionY() == connectPos[7]) {
						(*redblockitr2)->SetDelete(true, true, false);
					}
				}
			}
		}
	}
	//��
	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		if (!(*blueblockitr)->GetIsFall()) {
			//�ڑ��m�F
			//�אڂ����u���b�N�̍��W�擾
			float connectPos[8];
			//��
			connectPos[0] = (*blueblockitr)->GetPositionX();
			connectPos[1] = (*blueblockitr)->GetPositionY() - (*blueblockitr)->GetSize() - halfSize;
			//��
			connectPos[2] = (*blueblockitr)->GetPositionX();
			connectPos[3] = (*blueblockitr)->GetPositionY() + (*blueblockitr)->GetSize() + halfSize;
			//��
			connectPos[4] = (*blueblockitr)->GetPositionX() - (*blueblockitr)->GetSize() - halfSize;
			connectPos[5] = (*blueblockitr)->GetPositionY();
			//�E
			connectPos[6] = (*blueblockitr)->GetPositionX() + (*blueblockitr)->GetSize() + halfSize;
			connectPos[7] = (*blueblockitr)->GetPositionY();
			//��v�����ꍇ�̂݃J�E���g�A2�ȏ�ŏ�����
			int matchCount[2][2] = { { 0,0 },{0,0} };	//{{�c�F,���F},{�c��,����}}

			//�e�F���Ƃɐڑ��m�F
			//��
			for (auto blueblockitr2 = blueBlockList.begin(); blueblockitr2 != blueBlockList.end(); ++blueblockitr2) {
				//�������g�͒e��
				if (blueblockitr != blueblockitr2) {
					for (int i = 0; i < 8; i) {
						//�㉺���E�̏��Őڑ��`�F�b�N
						if (connectPos[i] == (*blueblockitr2)->GetPositionX() && connectPos[i + 1] == (*blueblockitr2)->GetPositionY()) {
							//�����F�͊m��Ȃ̂ŏ������򂳂���K�v�Ȃ�
							if (i < 4) {
								matchCount[0][0]++;
							}
							else if (i > 3) {
								matchCount[0][1]++;
							}
							//����v�m�F
							if ((*blueblockitr)->GetPattern() == (*blueblockitr2)->GetPattern()) {
								if (i < 4) {
									matchCount[1][0]++;
								}
								else if (i > 3) {
									matchCount[1][1]++;
								}
							}
						}
						i += 2;
					}
				}
			}
			//��
			for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
				for (int i = 0; i < 8; i) {
					//�㉺���E�̏��Őڑ��`�F�b�N
					if (connectPos[i] == (*redblockitr)->GetPositionX() && connectPos[i + 1] == (*redblockitr)->GetPositionY()) {
						//����v�m�F
						if ((*blueblockitr)->GetPattern() == (*redblockitr)->GetPattern()) {
							if (i < 4) {
								matchCount[1][0]++;
							}
							else if (i > 3) {
								matchCount[1][1]++;
							}
						}
					}
					i += 2;
				}
			}
			//��
			for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
				for (int i = 0; i < 8; i) {
					//�㉺���E�̏��Őڑ��`�F�b�N
					if (connectPos[i] == (*greenblockitr)->GetPositionX() && connectPos[i + 1] == (*greenblockitr)->GetPositionY()) {
						//����v�m�F
						if ((*blueblockitr)->GetPattern() == (*greenblockitr)->GetPattern()) {
							if (i < 4) {
								matchCount[1][0]++;
							}
							else if (i > 3) {
								matchCount[1][1]++;
							}
						}
					}
					i += 2;
				}
			}
			//�J�E���g���������ꍇ����
			for (int i = 0; i < 2; i++) {
				//��
				for (auto blueblockitr2 = blueBlockList.begin(); blueblockitr2 != blueBlockList.end(); ++blueblockitr2) {
					if (matchCount[i][0] > deleteConnectNum) {
						(*blueblockitr)->SetDelete(true, false, false);
						if ((*blueblockitr2)->GetPositionX() == connectPos[0] && (*blueblockitr2)->GetPositionY() == connectPos[1]) {
							(*blueblockitr2)->SetDelete(true, false, false);
						}
						if ((*blueblockitr2)->GetPositionX() == connectPos[2] && (*blueblockitr2)->GetPositionY() == connectPos[3]) {
							(*blueblockitr2)->SetDelete(true, false, false);
						}
					}
					if (matchCount[i][1] > deleteConnectNum) {
						(*blueblockitr)->SetDelete(true, false, false);
						if ((*blueblockitr2)->GetPositionX() == connectPos[4] && (*blueblockitr2)->GetPositionY() == connectPos[5]) {
							(*blueblockitr2)->SetDelete(true, false, false);
						}
						if ((*blueblockitr2)->GetPositionX() == connectPos[6] && (*blueblockitr2)->GetPositionY() == connectPos[7]) {
							(*blueblockitr2)->SetDelete(true, false, false);
						}
					}
				}
				//��
				for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
					//����v�̂�
					if (matchCount[i][1] > deleteConnectNum) {
						(*blueblockitr)->SetDelete(true, false, false);
						if ((*redblockitr)->GetPositionX() == connectPos[4] && (*redblockitr)->GetPositionY() == connectPos[5]) {
							(*redblockitr)->SetDelete(true, false, false);
						}
						if ((*redblockitr)->GetPositionX() == connectPos[6] && (*redblockitr)->GetPositionY() == connectPos[7]) {
							(*redblockitr)->SetDelete(true, false, false);
						}
					}
				}
				//��
				for (auto greenblockitr = redBlockList.begin(); greenblockitr != redBlockList.end(); ++greenblockitr) {
					//����v�̂�
					if (matchCount[i][1] > deleteConnectNum) {
						(*blueblockitr)->SetDelete(true, false, false);
						if ((*greenblockitr)->GetPositionX() == connectPos[4] && (*greenblockitr)->GetPositionY() == connectPos[5]) {
							(*greenblockitr)->SetDelete(true, false, false);
						}
						if ((*greenblockitr)->GetPositionX() == connectPos[6] && (*greenblockitr)->GetPositionY() == connectPos[7]) {
							(*greenblockitr)->SetDelete(true, false, false);
						}
					}
				}
			}
			//����v�`�F�b�N
			//�㉺
			if (matchCount[0][0] > deleteConnectNum && matchCount[1][0] > deleteConnectNum) {
				//��
				for (auto blueblockitr2 = blueBlockList.begin(); blueblockitr2 != blueBlockList.end(); ++blueblockitr2) {
					(*blueblockitr)->SetDelete(true, true, false);
					if ((*blueblockitr2)->GetPositionX() == connectPos[0] && (*blueblockitr2)->GetPositionY() == connectPos[1]) {
						(*blueblockitr2)->SetDelete(true, true, false);
					}
					if ((*blueblockitr2)->GetPositionX() == connectPos[2] && (*blueblockitr2)->GetPositionY() == connectPos[3]) {
						(*blueblockitr2)->SetDelete(true, true, false);
					}
				}
			}
			//���E
			if (matchCount[0][1] > deleteConnectNum && matchCount[1][1] > deleteConnectNum) {
				//��
				for (auto blueblockitr2 = blueBlockList.begin(); blueblockitr2 != blueBlockList.end(); ++blueblockitr2) {
					(*blueblockitr)->SetDelete(true, true, false);
					if ((*blueblockitr2)->GetPositionX() == connectPos[4] && (*blueblockitr2)->GetPositionY() == connectPos[5]) {
						(*blueblockitr2)->SetDelete(true, true, false);
					}
					if ((*blueblockitr2)->GetPositionX() == connectPos[6] && (*blueblockitr2)->GetPositionY() == connectPos[7]) {
						(*blueblockitr2)->SetDelete(true, true, false);
					}
				}
			}
		}
	}
	//��
	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		if (!(*greenblockitr)->GetIsFall()) {
			//�ڑ��m�F
			//�אڂ����u���b�N�̍��W�擾
			float connectPos[8];
			//��
			connectPos[0] = (*greenblockitr)->GetPositionX();
			connectPos[1] = (*greenblockitr)->GetPositionY() - (*greenblockitr)->GetSize() - halfSize;
			//��
			connectPos[2] = (*greenblockitr)->GetPositionX();
			connectPos[3] = (*greenblockitr)->GetPositionY() + (*greenblockitr)->GetSize() + halfSize;
			//��
			connectPos[4] = (*greenblockitr)->GetPositionX() - (*greenblockitr)->GetSize() - halfSize;
			connectPos[5] = (*greenblockitr)->GetPositionY();
			//�E
			connectPos[6] = (*greenblockitr)->GetPositionX() + (*greenblockitr)->GetSize() + halfSize;
			connectPos[7] = (*greenblockitr)->GetPositionY();
			//��v�����ꍇ�̂݃J�E���g�A2�ȏ�ŏ�����
			int matchCount[2][2] = { { 0,0 },{0,0} };	//{{�c�F,���F},{�c��,����}}

			//�e�F���Ƃɐڑ��m�F
			//��
			for (auto greenblockitr2 = greenBlockList.begin(); greenblockitr2 != greenBlockList.end(); ++greenblockitr2) {
				//�������g�͒e��
				if (greenblockitr != greenblockitr2) {
					for (int i = 0; i < 8; i) {
						//�㉺���E�̏��Őڑ��`�F�b�N
						if (connectPos[i] == (*greenblockitr2)->GetPositionX() && connectPos[i + 1] == (*greenblockitr2)->GetPositionY()) {
							//�����F�͊m��Ȃ̂ŏ������򂳂���K�v�Ȃ�
							if (i < 4) {
								matchCount[0][0]++;
							}
							else if (i > 3) {
								matchCount[0][1]++;
							}
							//����v�m�F
							if ((*greenblockitr)->GetPattern() == (*greenblockitr2)->GetPattern()) {
								if (i < 4) {
									matchCount[1][0]++;
								}
								else if (i > 3) {
									matchCount[1][1]++;
								}
							}
						}
						i += 2;
					}
				}
			}
			//��
			for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
				for (int i = 0; i < 8; i) {
					//�㉺���E�̏��Őڑ��`�F�b�N
					if (connectPos[i] == (*redblockitr)->GetPositionX() && connectPos[i + 1] == (*redblockitr)->GetPositionY()) {
						//����v�m�F
						if ((*greenblockitr)->GetPattern() == (*redblockitr)->GetPattern()) {
							if (i < 4) {
								matchCount[1][0]++;
							}
							else if (i > 3) {
								matchCount[1][1]++;
							}
						}
					}
					i += 2;
				}
			}
			//��
			for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
				for (int i = 0; i < 8; i) {
					//�㉺���E�̏��Őڑ��`�F�b�N
					if (connectPos[i] == (*blueblockitr)->GetPositionX() && connectPos[i + 1] == (*blueblockitr)->GetPositionY()) {
						//����v�m�F
						if ((*greenblockitr)->GetPattern() == (*blueblockitr)->GetPattern()) {
							if (i < 4) {
								matchCount[1][0]++;
							}
							else if (i > 3) {
								matchCount[1][1]++;
							}
						}
					}
					i += 2;
				}
			}
			//�J�E���g���������ꍇ����
			for (int i = 0; i < 2; i++) {
				//��
				for (auto greenblockitr2 = greenBlockList.begin(); greenblockitr2 != greenBlockList.end(); ++greenblockitr2) {
					if (matchCount[i][0] > deleteConnectNum) {
						(*greenblockitr)->SetDelete(true, false, false);
						if ((*greenblockitr2)->GetPositionX() == connectPos[0] && (*greenblockitr2)->GetPositionY() == connectPos[1]) {
							(*greenblockitr2)->SetDelete(true, false, false);
						}
						if ((*greenblockitr2)->GetPositionX() == connectPos[2] && (*greenblockitr2)->GetPositionY() == connectPos[3]) {
							(*greenblockitr2)->SetDelete(true, false, false);
						}
					}
					if (matchCount[i][1] > deleteConnectNum) {
						(*greenblockitr)->SetDelete(true, false, false);
						if ((*greenblockitr2)->GetPositionX() == connectPos[4] && (*greenblockitr2)->GetPositionY() == connectPos[5]) {
							(*greenblockitr2)->SetDelete(true, false, false);
						}
						if ((*greenblockitr2)->GetPositionX() == connectPos[6] && (*greenblockitr2)->GetPositionY() == connectPos[7]) {
							(*greenblockitr2)->SetDelete(true, false, false);
						}
					}
				}
				//��
				for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
					//����v�̂�
					if (matchCount[i][1] > deleteConnectNum) {
						(*greenblockitr)->SetDelete(true, false, false);
						if ((*redblockitr)->GetPositionX() == connectPos[4] && (*redblockitr)->GetPositionY() == connectPos[5]) {
							(*redblockitr)->SetDelete(true, false, false);
						}
						if ((*redblockitr)->GetPositionX() == connectPos[6] && (*redblockitr)->GetPositionY() == connectPos[7]) {
							(*redblockitr)->SetDelete(true, false, false);
						}
					}
				}
				//��
				for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
					//����v�̂�
					if (matchCount[i][1] > deleteConnectNum) {
						(*blueblockitr)->SetDelete(true, false, false);
						if ((*greenblockitr)->GetPositionX() == connectPos[4] && (*blueblockitr)->GetPositionY() == connectPos[5]) {
							(*blueblockitr)->SetDelete(true, false, false);
						}
						if ((*blueblockitr)->GetPositionX() == connectPos[6] && (*blueblockitr)->GetPositionY() == connectPos[7]) {
							(*blueblockitr)->SetDelete(true, false, false);
						}
					}
				}
			}
			//����v�`�F�b�N
			//�㉺
			if (matchCount[0][0] > deleteConnectNum && matchCount[1][0] > deleteConnectNum) {
				for (auto greenblockitr2 = greenBlockList.begin(); greenblockitr2 != greenBlockList.end(); ++greenblockitr2) {
					(*greenblockitr)->SetDelete(true, true, false);
					if ((*greenblockitr2)->GetPositionX() == connectPos[0] && (*greenblockitr2)->GetPositionY() == connectPos[1]) {
						(*greenblockitr2)->SetDelete(true, true, false);
					}
					if ((*greenblockitr2)->GetPositionX() == connectPos[2] && (*greenblockitr2)->GetPositionY() == connectPos[3]) {
						(*greenblockitr2)->SetDelete(true, true, false);
					}
				}
			}
			//���E
			if (matchCount[0][1] > deleteConnectNum && matchCount[1][1] > deleteConnectNum) {
				for (auto greenblockitr2 = greenBlockList.begin(); greenblockitr2 != greenBlockList.end(); ++greenblockitr2) {
					(*greenblockitr)->SetDelete(true, true, false);
					if ((*greenblockitr2)->GetPositionX() == connectPos[4] && (*greenblockitr2)->GetPositionY() == connectPos[5]) {
						(*greenblockitr2)->SetDelete(true, true, false);
					}
					if ((*greenblockitr2)->GetPositionX() == connectPos[6] && (*greenblockitr2)->GetPositionY() == connectPos[7]) {
						(*greenblockitr2)->SetDelete(true, true, false);
					}
				}
			}
		}
	}

	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		if ((*redblockitr)->GetIsDelete()) {
			countStart = true;
		}
	}
	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		if ((*blueblockitr)->GetIsDelete()) {
			countStart = true;
		}
	}
	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		if ((*greenblockitr)->GetIsDelete()) {
			countStart = true;
		}

	}
	//�������݊m�F
	//��
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		if ((*redblockitr)->GetDoubleMutch()) {
			for (auto redblockitr2 = redBlockList.begin(); redblockitr2 != redBlockList.end(); ++redblockitr2) {
				if ((*redblockitr2)->GetPattern() == (*redblockitr)->GetPattern()) {
					if (!(*redblockitr2)->GetIsDelete()) {
						(*redblockitr2)->SetDelete(false, false, true);
					}
				}
			}
		}
	}
	//��
	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		if ((*blueblockitr)->GetDoubleMutch()) {
			for (auto blueblockitr2 = blueBlockList.begin(); blueblockitr2 != blueBlockList.end(); ++blueblockitr2) {
				if ((*blueblockitr2)->GetPattern() == (*blueblockitr)->GetPattern()) {
					if (!(*blueblockitr2)->GetIsDelete()) {
						(*blueblockitr2)->SetDelete(false, false, true);
					}
				}
			}
		}
	}
	//��
	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		if ((*greenblockitr)->GetDoubleMutch()) {
			for (auto greenblockitr2 = greenBlockList.begin(); greenblockitr2 != greenBlockList.end(); ++greenblockitr2) {
				if ((*greenblockitr2)->GetPattern() == (*greenblockitr)->GetPattern()) {
					if (!(*greenblockitr2)->GetIsDelete()) {
						(*greenblockitr2)->SetDelete(false, false, true);
					}
				}
			}
		}
	}
}