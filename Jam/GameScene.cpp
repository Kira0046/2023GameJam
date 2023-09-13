#include "GameScene.h"
#include <ctime>



void GameScene::Initialize() {
	// 最新のキーボード情報用
	keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	oldkeys[256] = { 0 };

	srand((unsigned)time(NULL));

	//redBlockList.push_back(new RedBlock(2000, 264, 1));
	//redBlockList.push_back(new RedBlock(600, 450, 1));
	//greenBlockList.push_back(new GreenBlock(824, 264, 1));
	//blueBlockList.push_back(new BlueBlock(968, 264, 1));
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
		//出現位置リセット
		centerX = spawnpointX;
		centerY = spawnpointY;
		//作成ブロック個数リセット
		createredblock = 0;
		creategreenblock = 0;
		createblueblock = 0;

		fallupdatetime = 60;
		blockfallupdatetime = 1;
		blockfallupdatecount = 0;

		fallphase = 1;
	}
	//ブロック配置
	if (fallphase == 1) {
		BlockLayoutSetting();
		fallphase = 2;
	}
	//落下
	if (fallphase == 2) {
		FallingCalc();
		BlockOperation();

		PiledBlock();

		PileBlockToLand();
		/*if (centerY == 816) {

			SetBlockToFallFalse();

			fallphase = 0;
		}*/
	}

	if (fallphase == 3) {
		BlockFallProcess();
	}

	if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0) {
		fallphase = 0;
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
	//DrawBox(centerX - blockspawnsize, centerY - blockspawnsize, centerX + blockspawnsize, centerY + blockspawnsize, GetColor(255, 255, 0), true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "LH:%d\n%d\nRH:%d\n%d\nRL:%d\n%d\nLL:%d\n%d\nred:%d\ngreen:%d\nblue:%d\n%d %d\nR%d %d\nG%d %d\nB%d %d\n%d\n%d\n%d\n%d %d %d\n%d %d",
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
		blueblockrighthit,
		fallphase,
		blockfallupdatetime,
		blockfallupdatecount,
		allcreateredblock,
		allcreategreenblock,
		allcreateblueblock,
		test,
		test2);
}

void GameScene::BlockLayoutSetting() {
	//配置場所  i=0:左上 1:右上 2:右下 3:左下
	for (int i = 0; i < 4; i++) {
		//色決定 0:配置しない　1:赤　2:緑  3:青
		blocklayoutposition[i].blocklayoutcolor = rand() % 4;
		//模様決定 1: 2:
		blocklayoutposition[i].blocklayoutpattern = rand() % 2 + 1;

		if (blocklayoutposition[0].blocklayoutcolor == 0) {
			if (blocklayoutposition[1].blocklayoutcolor == 0) {
				if (blocklayoutposition[2].blocklayoutcolor == 0) {
					if (blocklayoutposition[3].blocklayoutcolor == 0) {
						fallphase = 0;
					}
				}
			}
		}
		//赤ver
		if (blocklayoutposition[i].blocklayoutcolor == 1) {
			//模様1
			if (blocklayoutposition[i].blocklayoutpattern == 1) {
				//左上
				if (i == 0) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY - blockspawnsize, 1));
					createredblock++;
					allcreateredblock++;
				}
				//右上
				if (i == 1) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
					createredblock++;
					allcreateredblock++;
				}
				//右下
				if (i == 2) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
					createredblock++;
					allcreateredblock++;
				}
				//左下
				if (i == 3) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
					createredblock++;
					allcreateredblock++;
				}
			}
			//模様2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//左上
				if (i == 0) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
					createredblock++;
					allcreateredblock++;
				}
				//右上
				if (i == 1) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
					createredblock++;
					allcreateredblock++;
				}

				if (i == 2) {
					redBlockList.push_back(new RedBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
					createredblock++;
					allcreateredblock++;
				}
				if (i == 3) {
					redBlockList.push_back(new RedBlock(centerX - blockspawnsize, centerY + blockspawnsize, 2));
					createredblock++;
					allcreateredblock++;
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
					creategreenblock++;
					allcreategreenblock++;
				}
				//右上
				if (i == 1) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
					creategreenblock++;
					allcreategreenblock++;
				}
				//右下
				if (i == 2) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
					creategreenblock++;
					allcreategreenblock++;
				}
				//左下
				if (i == 3) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
					creategreenblock++;
					allcreategreenblock++;
				}
			}
			//模様2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//左上
				if (i == 0) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
					creategreenblock++;
					allcreategreenblock++;
				}
				//右上
				if (i == 1) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
					creategreenblock++;
					allcreategreenblock++;
				}
				//右下
				if (i == 2) {
					greenBlockList.push_back(new GreenBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
					creategreenblock++;
					allcreategreenblock++;
				}
				//左下
				if (i == 3) {
					greenBlockList.push_back(new GreenBlock(centerX - blockspawnsize, centerY + blockspawnsize, 2));
					creategreenblock++;
					allcreategreenblock++;
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
					createblueblock++;
					allcreateblueblock++;
				}
				//右上
				if (i == 1) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY - blockspawnsize, 1));
					createblueblock++;
					allcreateblueblock++;
				}
				//右下
				if (i == 2) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY + blockspawnsize, 1));
					createblueblock++;
					allcreateblueblock++;
				}
				//左下
				if (i == 3) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY + blockspawnsize, 1));
					createblueblock++;
					allcreateblueblock++;
				}
			}
			//模様2
			if (blocklayoutposition[i].blocklayoutpattern == 2) {
				//左上
				if (i == 0) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY - blockspawnsize, 2));
					createblueblock++;
					allcreateblueblock++;
				}
				//右上
				if (i == 1) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY - blockspawnsize, 2));
					createblueblock++;
					allcreateblueblock++;
				}
				//右下
				if (i == 2) {
					blueBlockList.push_back(new BlueBlock(centerX + blockspawnsize, centerY + blockspawnsize, 2));
					createblueblock++;
					allcreateblueblock++;
				}
				//左下
				if (i == 3) {
					blueBlockList.push_back(new BlueBlock(centerX - blockspawnsize, centerY + blockspawnsize, 2));
					createblueblock++;
					allcreateblueblock++;
				}
			}
		}
	}


}

void GameScene::BlockOperation() {

	{
		///赤
		if (createredblock > 0) {
			//4つ
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

			//3つ
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

			//２つ
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

			//１つ
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

		///緑
		if (creategreenblock > 0) {
			//4つ
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

			//3つ
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

			//2つ
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

			//1つ
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

		///青
		if (createblueblock > 0) {
			//4つ
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

			//3つ
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

			//2つ
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

			//1つ
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
			centerX -= amountmovement;
			{
				///赤
				if (createredblock > 0) {
					//4つ
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

					//3つ
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

					//２つ
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

					//１つ
					if (createredblock == 1) {
						if (!redBlockList.empty()) {

							redBlockList.back()->SetPosition(-amountmovement, 0);
						}
					}

				}

				///緑
				if (creategreenblock > 0) {
					//4つ
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

					//3つ
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

					//2つ
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

					//1つ
					if (creategreenblock == 1) {

						if (!greenBlockList.empty()) {

							greenBlockList.back()->SetPosition(-amountmovement, 0);
						}
					}
				}

				///青
				if (createblueblock > 0) {
					//4つ
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

					//3つ
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

					//2つ
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

					//1つ
					if (createblueblock == 1) {
						if (!blueBlockList.empty()) {

							blueBlockList.back()->SetPosition(-amountmovement, 0);
						}
					}
				}
			}
		}
	}

	if (redblockrighthit == false && greenblockrighthit == false && blueblockrighthit == false) {
		if (keys[KEY_INPUT_D] == 1 && oldkeys[KEY_INPUT_D] == 0) {
			centerX += amountmovement;
			{
				///赤
				if (createredblock > 0) {
					//4つ
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

					//3つ
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

					//２つ
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

					//１つ
					if (createredblock == 1) {
						if (!redBlockList.empty()) {

							redBlockList.back()->SetPosition(amountmovement, 0);
						}
					}

				}

				///緑
				if (creategreenblock > 0) {
					//4つ
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

					//3つ
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

					//2つ
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

					//1つ
					if (creategreenblock == 1) {

						if (!greenBlockList.empty()) {

							greenBlockList.back()->SetPosition(amountmovement, 0);
						}
					}
				}

				///青
				if (createblueblock > 0) {
					//4つ
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

					//3つ
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

					//2つ
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

					//1つ
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

void GameScene::FallingCalc() {
	fallupdatetime -= 1;
	FallingCollision();
	if (fallupdatetime == 0) {
		centerY += amountmovement;
		fallupdatetime = 60;
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
	///赤
	if (createredblock > 0) {
		//4つ
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

		//3つ
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

		//２つ
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

		//１つ
		if (createredblock == 1) {
			if (!redBlockList.empty()) {

				redBlockList.back()->SetPosition(0, amountmovement);
			}
		}

	}

	///緑
	if (creategreenblock > 0) {
		//4つ
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

		//3つ
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

		//2つ
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

		//1つ
		if (creategreenblock == 1) {

			if (!greenBlockList.empty()) {

				greenBlockList.back()->SetPosition(0, amountmovement);
			}
		}
	}

	///青
	if (createblueblock > 0) {
		//4つ
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

		//3つ
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

		//2つ
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

		//1つ
		if (createblueblock == 1) {
			if (!blueBlockList.empty()) {

				blueBlockList.back()->SetPosition(0, amountmovement);
			}
		}
	}
}

void GameScene::FallingCollision() {
	//赤、赤
	if (redBlockList.size() >= 2) {
		for (auto itr = redBlockList.begin(); itr != std::prev(redBlockList.end()); ++itr) {
			for (auto itr2 = std::next(redBlockList.begin()); itr2 != redBlockList.end(); ++itr2) {

				//1つ目
				//左上
				int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//右上
				int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//右下
				int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
				//左下
				int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

				//2つ目
				//左上
				int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
				int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//右上
				int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//右下
				int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
				//左下
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



	//緑、緑
	if (greenBlockList.size() >= 2) {
		for (auto itr = greenBlockList.begin(); itr != std::prev(greenBlockList.end()); ++itr) {
			for (auto itr2 = std::next(greenBlockList.begin()); itr2 != greenBlockList.end(); ++itr2) {

				//1つ目
				//左上
				int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//右上
				int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//右下
				int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
				//左下
				int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

				//2つ目
				//左上
				int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
				int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//右上
				int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//右下
				int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
				//左下
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


	//青、青
	if (blueBlockList.size() >= 2) {
		for (auto itr = blueBlockList.begin(); itr != std::prev(blueBlockList.end()); ++itr) {
			for (auto itr2 = std::next(blueBlockList.begin()); itr2 != blueBlockList.end(); ++itr2) {

				//1つ目
				//左上
				int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//右上
				int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
				//右下
				int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
				int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
				//左下
				int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
				int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

				//2つ目
				//左上
				int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
				int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//右上
				int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
				//右下
				int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
				int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
				//左下
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

	//赤、緑
	if (redBlockList.size() >= 1) {
		if (greenBlockList.size() >= 1) {
			for (auto itr = redBlockList.begin(); itr != redBlockList.end(); ++itr) {
				for (auto itr2 = greenBlockList.begin(); itr2 != greenBlockList.end(); ++itr2) {

					//1つ目
					//左上
					int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//右上
					int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//右下
					int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
					//左下
					int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

					//2つ目
					//左上
					int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
					int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//右上
					int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//右下
					int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
					//左下
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

	//赤、青
	if (redBlockList.size() >= 1) {
		if (blueBlockList.size() >= 1) {
			for (auto itr = redBlockList.begin(); itr != redBlockList.end(); ++itr) {
				for (auto itr2 = blueBlockList.begin(); itr2 != blueBlockList.end(); ++itr2) {

					//1つ目
					//左上
					int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//右上
					int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//右下
					int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
					//左下
					int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

					//2つ目
					//左上
					int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
					int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//右上
					int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//右下
					int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
					//左下
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

	//緑、青
	if (greenBlockList.size() >= 1) {
		if (blueBlockList.size() >= 1) {
			for (auto itr = greenBlockList.begin(); itr != greenBlockList.end(); ++itr) {
				for (auto itr2 = blueBlockList.begin(); itr2 != blueBlockList.end(); ++itr2) {

					//1つ目
					//左上
					int LHX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//右上
					int RHX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RHY1 = (*itr)->GetPositionY() - (*itr)->GetSize();
					//右下
					int RLX1 = (*itr)->GetPositionX() + (*itr)->GetSize();
					int RLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();
					//左下
					int LLX1 = (*itr)->GetPositionX() - (*itr)->GetSize();
					int LLY1 = (*itr)->GetPositionY() + (*itr)->GetSize();

					//2つ目
					//左上
					int LHX2 = (*itr2)->GetPositionX() - (*itr2)->GetSize();
					int LHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//右上
					int RHX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RHY2 = (*itr2)->GetPositionY() - (*itr2)->GetSize();
					//右下
					int RLX2 = (*itr2)->GetPositionX() + (*itr2)->GetSize();
					int RLY2 = (*itr2)->GetPositionY() + (*itr2)->GetSize();
					//左下
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
		///赤
		if (createredblock > 0) {
			//4つ
			if (createredblock == 4) {
				if (redBlockList.size() >= 4) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (redBlockList.size() >= 3) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}

				}
			}

			//3つ
			if (createredblock == 3) {
				if (redBlockList.size() >= 3) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//２つ
			if (createredblock == 2) {
				if (redBlockList.size() >= 2) {
					SetNumber();
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//１つ
			if (createredblock == 1) {
				if (!redBlockList.empty()) {

					if (redBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

		}

		///緑
		if (creategreenblock > 0) {
			//4つ
			if (creategreenblock == 4) {

				if (greenBlockList.size() >= 4) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (greenBlockList.size() >= 3) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}

				}
			}

			//3つ
			if (creategreenblock == 3) {

				if (greenBlockList.size() >= 3) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}

				}
			}

			//2つ
			if (creategreenblock == 2) {

				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//1つ
			if (creategreenblock == 1) {

				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}
		}

		///青
		if (createblueblock > 0) {
			//4つ
			if (createblueblock == 4) {

				if (blueBlockList.size() >= 4) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (blueBlockList.size() >= 3) {

					auto itr = blueBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (blueBlockList.size() >= 2) {

					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//3つ
			if (createblueblock == 3) {

				if (blueBlockList.size() >= 3) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (blueBlockList.size() >= 2) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//2つ
			if (createblueblock == 2) {
				if (blueBlockList.size() >= 2) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//1つ
			if (createblueblock == 1) {
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->hitdown == true) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
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

	{
		///赤
		if (createredblock > 0) {
			//4つ
			if (createredblock == 4) {
				if (redBlockList.size() >= 4) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (redBlockList.size() >= 3) {
					SetNumber();
					auto itr = redBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}

				}
			}

			//3つ
			if (createredblock == 3) {
				if (redBlockList.size() >= 3) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//２つ
			if (createredblock == 2) {
				if (redBlockList.size() >= 2) {
					auto itr = redBlockList.end();
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!redBlockList.empty()) {

					if (redBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//１つ
			if (createredblock == 1) {
				if (!redBlockList.empty()) {

					if (redBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

		}

		///緑
		if (creategreenblock > 0) {
			//4つ
			if (creategreenblock == 4) {

				if (greenBlockList.size() >= 4) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (greenBlockList.size() >= 3) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}

				}
			}

			//3つ
			if (creategreenblock == 3) {

				if (greenBlockList.size() >= 3) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}

				}
			}

			//2つ
			if (creategreenblock == 2) {

				if (greenBlockList.size() >= 2) {
					auto itr = greenBlockList.end();
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//1つ
			if (creategreenblock == 1) {

				if (!greenBlockList.empty()) {

					if (greenBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}
		}

		///青
		if (createblueblock > 0) {
			//4つ
			if (createblueblock == 4) {

				if (blueBlockList.size() >= 4) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (blueBlockList.size() >= 3) {

					auto itr = blueBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (blueBlockList.size() >= 2) {

					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//3つ
			if (createblueblock == 3) {

				if (blueBlockList.size() >= 3) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (blueBlockList.size() >= 2) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//2つ
			if (createblueblock == 2) {
				if (blueBlockList.size() >= 2) {
					auto itr = blueBlockList.end();
					--itr;
					--itr;
					if ((*itr)->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}
				}
			}

			//1つ
			if (createblueblock == 1) {
				if (!blueBlockList.empty()) {

					if (blueBlockList.back()->GetPositionY() == 840) {
						SetNumber();
						SetBlockonLand();
						SetBlockToFallFalse();

						redNumber = 0;
						greenNumber = 0;
						blueNumber = 0;

						fallphase = 3;
					}

				}
			}
		}
	}
}

void GameScene::SetBlockonLand() {
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		if ((*redblockitr)->isdelete == false) {
			if ((*redblockitr)->GetPositionY() == 840) {
				(*redblockitr)->SetHitDown(true);
			}
		}
	}

	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		if ((*greenblockitr)->isdelete == false) {
			if ((*greenblockitr)->GetPositionY() == 840) {
				(*greenblockitr)->SetHitDown(true);
			}
		}
	}

	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		if ((*blueblockitr)->isdelete == false) {
			if ((*blueblockitr)->GetPositionY() == 840) {
				(*blueblockitr)->SetHitDown(true);
			}
		}
	}
}

void GameScene::BlockFallProcess() {
	blockfallupdatetime -= 1;
	SetBlockonLand();
	FallingCollision();
	DeleteBlockMove();
	if (blockfallupdatetime == 0) {
		BlockFallSetting();
		BlockToFall();
		//BackToReset();
		for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
			(*redblockitr)->SetHitDown(false);
		}
		for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
			(*greenblockitr)->SetHitDown(false);
		}

		for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
			(*blueblockitr)->SetHitDown(false);
		}

		blockfallupdatecount += 1;
		blockfallupdatetime = 1;
	}
	if (blockfallupdatecount == 19) {
		DeleteBlock();
	}
	if (blockfallupdatecount > 20) {
		BackToReset();
	}
	if (blockfallupdatecount > 90) {
		fallphase = 0;
	}
}

void GameScene::BlockFallSetting() {
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		if ((*redblockitr)->GetIshitDown() == false) {
			(*redblockitr)->SetFall(true);
		}
		if ((*redblockitr)->GetIshitDown() == true) {
			(*redblockitr)->SetFall(false);
		}
	}

	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		if ((*greenblockitr)->GetIshitDown() == false) {
			(*greenblockitr)->SetFall(true);
		}
		if ((*greenblockitr)->GetIshitDown() == true) {
			(*greenblockitr)->SetFall(false);
		}
	}

	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		if ((*blueblockitr)->GetIshitDown() == false) {
			(*blueblockitr)->SetFall(true);
		}
		if ((*blueblockitr)->GetIshitDown() == true) {
			(*blueblockitr)->SetFall(false);
		}
	}
}

void GameScene::BlockToFall() {
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		if ((*redblockitr)->GetIsFall() == true) {
			(*redblockitr)->SetPosition(0, amountmovement);
		}
	}

	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		if ((*greenblockitr)->GetIsFall() == true) {
			(*greenblockitr)->SetPosition(0, amountmovement);
		}
	}

	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		if ((*blueblockitr)->GetIsFall() == true) {
			(*blueblockitr)->SetPosition(0, amountmovement);
		}
	}
}

void GameScene::BackToReset() {
	int redcheck = 0;
	int greencheck = 0;
	int bluecheck = 0;


	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		if ((*redblockitr)->GetIsFall() == false) {
			redcheck = 1;
		}
	}

	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		if ((*greenblockitr)->GetIsFall() == false) {
			greencheck = 1;
		}
	}

	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		if ((*blueblockitr)->GetIsFall() == false) {
			bluecheck = 1;
		}
	}

	if (redBlockList.size() == 0) {
		redcheck = 1;
	}

	if (greenBlockList.size() == 0) {
		greencheck = 1;
	}

	if (blueBlockList.size() == 0) {
		bluecheck = 1;
	}

	if (redcheck == 1 && greencheck == 1 && bluecheck == 1) {
		fallphase = 0;
	}
}

void GameScene::DeleteBlock() {
	//赤
	if (redBlockList.size() >= 2) {
		for (auto itr = redBlockList.begin(); itr != redBlockList.end(); ++itr) {
			for (auto itr2 = redBlockList.begin(); itr2 != redBlockList.end(); ++itr2) {
				for (auto itr3 = redBlockList.begin(); itr3 != redBlockList.end(); ++itr3) {
					if (((*itr)->GetPositionX() + 48) == (*itr2)->GetPositionX() && ((*itr2)->GetPositionX() + 48) == (*itr3)->GetPositionX() && (*itr)->GetPositionY() == (*itr2)->GetPositionY()) {
						if ((*itr)->isdelete == false && (*itr2)->isdelete == false && (*itr3)->isdelete == false) {
							(*itr)->SetDelete(true);
							(*itr2)->SetDelete(true);
							(*itr3)->SetDelete(true);
							blockfallupdatecount = 0;
						}
					}
				}
			}

		}
	}
	//緑
	if (greenBlockList.size() >= 2) {
		for (auto itr = greenBlockList.begin(); itr != greenBlockList.end(); ++itr) {
			for (auto itr2 = greenBlockList.begin(); itr2 != greenBlockList.end(); ++itr2) {
				for (auto itr3 = greenBlockList.begin(); itr3 != greenBlockList.end(); ++itr3) {
					if (((*itr)->GetPositionX() + 48) == (*itr2)->GetPositionX() && ((*itr2)->GetPositionX() + 48) == (*itr3)->GetPositionX() && (*itr)->GetPositionY() == (*itr2)->GetPositionY()) {
						if ((*itr)->isdelete == false && (*itr2)->isdelete == false && (*itr3)->isdelete == false) {
							(*itr)->SetDelete(true);
							(*itr2)->SetDelete(true);
							(*itr3)->SetDelete(true);
							blockfallupdatecount = 0;
						}
					}
				}
			}
		}
	}
	//青
	if (blueBlockList.size() >= 2) {
		for (auto itr = blueBlockList.begin(); itr != blueBlockList.end(); ++itr) {
			for (auto itr2 = blueBlockList.begin(); itr2 != blueBlockList.end(); ++itr2) {
				for (auto itr3 = blueBlockList.begin(); itr3 != blueBlockList.end(); ++itr3) {
					if (((*itr)->GetPositionX() + 48) == (*itr2)->GetPositionX() && ((*itr2)->GetPositionX() + 48) == (*itr3)->GetPositionX() && (*itr)->GetPositionY() == (*itr2)->GetPositionY()) {
						if ((*itr)->isdelete == false && (*itr2)->isdelete == false && (*itr3)->isdelete == false) {
							(*itr)->SetDelete(true);
							(*itr2)->SetDelete(true);
							(*itr3)->SetDelete(true);
							blockfallupdatecount = 0;
						}
					}
				}
			}
		}
	}
}

void GameScene::SetNumber() {
	for (auto itr = redBlockList.begin(); itr != redBlockList.end(); ++itr) {
		(*itr)->SetNumber(redNumber++);
	}
	for (auto itr = greenBlockList.begin(); itr != greenBlockList.end(); ++itr) {
		(*itr)->SetNumber(greenNumber++);
	}
	for (auto itr = blueBlockList.begin(); itr != blueBlockList.end(); ++itr) {
		(*itr)->SetNumber(blueNumber++);
	}
}

void GameScene::DeleteBlockMove() {
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		if ((*redblockitr)->isdelete == true) {
			(*redblockitr)->MoveY();
		}
	}
	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		if ((*greenblockitr)->isdelete == true) {
			(*greenblockitr)->MoveY();
		}
	}
	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		if ((*blueblockitr)->isdelete == true) {
			(*blueblockitr)->MoveY();
		}
	}
}

