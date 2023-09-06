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
	//ブロック初期化
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

	//テスト設置
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
	//フィールド描画
	DrawGraph(fieldPosX[0], fieldPosY[0], fieldHandle, true);
	//ブロック描画
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

//接続チェック
void Block::CheckConnect() {
	//全ブロックについて
	for (int i = 0; i < blockNum; i++) {
		//フィールドにあるかチェック
		if (block[i].appearingNow) {
			//落下状態ではないことのチェック
			if (!block[i].isFall) {
				//接続確認
				IsConnect(i);
			}
		}

	}
}

void Block::IsConnect(int num) {
	//ブロックの中央座標取得
	//float centerPosX = block[num].posX + blockSizeX / 2;
	//float centerPosY = block[num].posY + blockSizeY / 2;
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
	int matchCount[2][2] = { { 0,0 },{0,0} };	//色一致数,柄一致数
	//一致したブロックの番号
	int upNum = 0;
	int downNum = 0;
	int leftNum = 0;
	int rightNum = 0;

	//座標と一致してるブロックがあるか精査
	for (int i = 0; i < 180; i++) {
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
}