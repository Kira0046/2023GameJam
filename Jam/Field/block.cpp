#include "block.h"

void Block::Initialize(int windowWidth, int windowHeight) {
	//フィールド
	//画像読み込み
	fieldHandle = LoadGraph("Resource/field/field_kari.png");
	//画像サイズ取得
	GetGraphSize(fieldHandle, &fieldSizeX, &fieldSizeY);
	//フィールド座標入力
	fieldPosX[0] = windowWidth / 2 - fieldSizeX / 2;
	fieldPosY[0] = windowHeight / 2 - fieldSizeY / 2;

	//ブロック
	//画像読み込み
	LoadDivGraph("Resource/field/color_block_800.png", 6, 6, 1, blockSizeX, blockSizeY, blockHandle);
	LoadDivGraph("Resource/field/color_block_connect.png", 6, 6, 1, blockSizeX, blockSizeY, connectHandle);
	LoadDivGraph("Resource/field/color_block_double.png", 6, 6, 1, blockSizeX, blockSizeY, doubleHandle);
	LoadDivGraph("Resource/field/color_block_Involvement.png", 6, 6, 1, blockSizeX, blockSizeY, involvementHnadle);
	//ブロック初期化
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

	//タイマー初期化
	deleteTimer = maxTimer;
	countStart = false;

	//スコア初期化
	hiScore = 0;
	score = 0;
	chain = 0;
	canChain = false;
	deleteBlockNum = 0;
	involvementBlockNum = 0;

	//操作系列
	isControl = false;
	speed = 1.0f;
	level = 1.0f;
	rotateNum = 0;	//0から上左右下の順

	isDelete = false;

	for (int i = 0; i < 28; i++) {
		oldInput[i] = false;
	}

	////テスト設置
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
	//操作
	FallBlock(keys, oldkeys);

	//接続確認
	CheckConnect();

	//ブロック消去
	DeleteBlock();

	//スコア加算
	AddScore();
}

void Block::Draw() {
	//フィールド描画
	DrawGraph(fieldPosX[0], fieldPosY[0], fieldHandle, true);
	//ブロック描画
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

	//デバッグテキスト
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Score : %d", score);
	DrawFormatString(10, 25, GetColor(255, 255, 255), "HIScore : %d", hiScore);
	DrawFormatString(10, 40, GetColor(255, 255, 255), "DeleteTimer : %d", deleteTimer);
}

//操作
void Block::FallBlock(char* keys, char* oldkeys) {
	//操作中ブロックがないなら
	if (!isControl && !isDelete) {
		int counter = 0;
		//フリーのブロックを探す
		for (int i = 0; i < blockNum; i++) {
			if (!block[i].appearingNow) {
				block[i].appearingNow = true;
				block[i].isControl = true;
				block[i].colorPattern = GetRand(5);
				if (counter < 1) {
					block[i].center = true;	//中心の決定
					block[i].posX = fieldPosX[0] + fieldFlameSizeX + blockSizeX * 4;
					block[i].posY = fieldPosY[0] + fieldFlameSizeY;
					centerPos[0] = block[i].posX;
					centerPos[1] = block[i].posY;
				}
				counter++;	//2個探したら脱出
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
		if (block[i].center) {	//中心ブロックの座標を常に取得
			centerPos[0] = block[i].posX;
			centerPos[1] = block[i].posY;
		}
	}
	//回転
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

	//横移動
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
			//クイックドロップ
			for (int i = 0; i < blockNum; i++) {
				if (block[i].isControl) {
					block[i].posY += speed * 16 * level;
					if (block[i].center) {	//中心ブロックの座標を常に取得
						centerPos[0] = block[i].posX;
						centerPos[1] = block[i].posY;
					}
				}
			}
		}

		//番号に合わせてブロックの位置変更※上左下右の順
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

	//めり込み回避
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

	//着地処理
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

//接続チェック
void Block::CheckConnect() {
	//全ブロックについて
	for (int i = 0; i < blockNum; i++) {
		//フィールドにあるかチェック
		if (block[i].appearingNow) {
			//落下状態ではないことのチェック
			if (!block[i].isFall && !block[i].isControl) {
				//接続確認
				IsConnect(i);
				if (block[i].isDelete) {
					countStart = true;
					isDelete = true;
				}
			}
		}
	}
	for (int i = 0; i < blockNum; i++) {
		//巻き込み確認
		CheckInvolvement(i);
	}
}

void Block::IsConnect(int num) {
	//隣接したブロックの座標取得
	float connectPos[8];
	//上
	connectPos[0] = block[num].posX;
	connectPos[1] = block[num].posY - blockSizeY;
	//下
	connectPos[2] = block[num].posX;
	connectPos[3] = block[num].posY + blockSizeY;
	//左
	connectPos[4] = block[num].posX - blockSizeX;
	connectPos[5] = block[num].posY;
	//右
	connectPos[6] = block[num].posX + blockSizeX;
	connectPos[7] = block[num].posY;
	//一致した場合のみカウント、2以上で消える
	int matchCount[2][2] = { { 0,0 },{0,0} };	//{{縦色,横色},{縦柄,横柄}}
	//一致したブロックの番号
	int upNum = 0;
	int downNum = 0;
	int leftNum = 0;
	int rightNum = 0;

	//座標と一致してるブロックがあるか精査
	for (int i = 0; i < blockNum; i++) {
		for (int j = 0; j < 8; j) {
			//上下左右の順で接続チェック
			if (connectPos[j] == block[i].posX && connectPos[j + 1] == block[i].posY) {

				//色一致確認
				if (block[i].colorPattern / 2 == block[num].colorPattern / 2) {
					block[num].connectionStatus[j] = true;	//色一致
					//上下一致の場合
					if (j < 4) {
						matchCount[0][0]++;
						if (j < 2) {
							upNum = i;
						}
						else {
							downNum = i;
						}
					}
					//左右一致の場合
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
				//柄一致確認
				if (block[i].colorPattern % 2 == block[num].colorPattern % 2) {
					block[num].connectionStatus[j + 1] = true;	//柄一致
					//上下一致の場合
					if (j < 4) {
						matchCount[1][0]++;
						if (j < 2) {
							upNum = i;
						}
						else {
							downNum = i;
						}
					}
					//左右一致の場合
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
	//カウントが超えた場合消す
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
	//両一致チェック
	//上下
	if (matchCount[0][0] > 1 && matchCount[1][0] > 1) {
		block[num].doubleMutch = true;
		block[upNum].doubleMutch = true;
		block[downNum].doubleMutch = true;
	}
	//左右
	if (matchCount[0][1] > 1 && matchCount[1][1] > 1) {
		block[num].doubleMutch = true;
		block[leftNum].doubleMutch = true;
		block[rightNum].doubleMutch = true;
	}
}

void Block::CheckInvolvement(int num) {
	//同じ種類のブロックに巻き込み付与
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
	//カウントスタートフラグがオンだったらタイマーを動かして一定時間後に消滅
	if (countStart == true) {
		deleteTimer--;
		if (deleteTimer < 0) {
			countStart = false;
			deleteTimer = maxTimer;
			for (int i = 0; i < blockNum; i++) {
				//通常と巻き込みで加算分け
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
			//連鎖カウント加算
			chain++;
		}
		isDelete = false;
	}
}

void Block::AddScore() {
	//スコア計算
	//(基礎スコア × 通常消ししたブロック数 + ボーナススコア × 一致消しで巻き込んだブロック数) × 連鎖数
	score += (add * deleteBlockNum + bonus * involvementBlockNum) * chain;
	//ハイスコア更新してたら更新
	if (hiScore < score) {
		hiScore = score;
	}
	//リセット
	deleteBlockNum = 0;
	involvementBlockNum = 0;
}

void Block::AllReset() {
	//ブロック初期化
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

	//タイマー初期化
	deleteTimer = maxTimer;
	countStart = false;

	//スコア初期化
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