#include "GameScene.h"
#include <ctime>

void GameScene::Initialize() {
	// 最新のキーボード情報用
	keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	oldkeys[256] = { 0 };

	srand((unsigned)time(NULL));

	redBlockList.push_back(new RedBlock(800, 450, 1));
	redBlockList.push_back(new RedBlock(600, 450, 1));
	greenBlockList.push_back(new GreenBlock(1000, 450, 1));
	blueBlockList.push_back(new BlueBlock(1200, 450, 1));
}

void GameScene::Update() {
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; ++i) {
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);

	//ブロック配置待機(リセット)
	if (fallphase == 0) {
		centerX = spawnpointX;
		centerY = spawnpointY;
		fallphase = 1;
	}
	//ブロック配置
	if (fallphase == 1) {
		BlockLayoutSetting();
		fallphase = 2;
	}
	//落下
	if (fallphase == 2) {
		BlockOperation();
		FallingCalc();
	}


}

void GameScene::Draw() {
	//赤ブロック描画
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		(*redblockitr)->Draw();
	}

	//緑ブロック描画
	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		(*greenblockitr)->Draw();
	}

	//青ブロック描画
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
	//配置場所  i=0:左上 1:右上 2:右下 3:左下
	for (int i = 0; i < 4; i++) {
		//色決定 0:配置しない　1:赤　2:緑  3:青
		blocklayoutposition[i].blocklayoutcolor = rand() % 4;
		//模様決定 1: 2:
		blocklayoutposition[i].blocklayoutpattern = rand() % 2 + 1;

		if (blocklayoutposition[i].blocklayoutcolor == 0) {

		}
		//赤ver
		if (blocklayoutposition[i].blocklayoutcolor == 1) {
			//模様1
			if (blocklayoutposition[i].blocklayoutpattern == 1) {
				//左上
				if (i == 0) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY - blockspawnsize, 1));
				}
				//右上
				if (i == 1) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
				}
				//右下
				if (i == 2) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
				}
				//左下
				if (i == 3) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
				}
			}
			//模様2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//左上
				if (i == 0) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
				}
				//右上
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
		//緑ver
		if (blocklayoutposition[i].blocklayoutcolor == 2) {
			//模様1
			if (blocklayoutposition[i].blocklayoutpattern == 1) {
				//左上
				if (i == 0) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY - blockspawnsize, 1));
				}
				//右上
				if (i == 1) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
				}
				//右下
				if (i == 2) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
				}
				//左下
				if (i == 3) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
				}
			}
			//模様2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//左上
				if (i == 0) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
				}
				//右上
				if (i == 1) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
				}
				//右下
				if (i == 2) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
				}
				//左下
				if (i == 3) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY + blockspawnsize, 2));
				}
			}
		}
		//青ver
		if (blocklayoutposition[i].blocklayoutcolor == 3) {
			//模様1
			if (blocklayoutposition[i].blocklayoutpattern == 1) {
				//左上
				if (i == 0) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY - blockspawnsize, 1));
				}
				//右上
				if (i == 1) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
				}
				//右下
				if (i == 2) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
				}
				//左下
				if (i == 3) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
				}
			}
			//模様2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//左上
				if (i == 0) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
				}
				//右上
				if (i == 1) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
				}
				//右下
				if (i == 2) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
				}
				//左下
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
