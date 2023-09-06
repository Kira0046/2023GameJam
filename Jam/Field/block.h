#pragma once
#include "DxLib.h"

//ブロック一個一個の内部データ
struct BlockData {
	float posX;
	float posY;
	bool connectionStatus[8];	//接続状態
	bool isFall;	//落下状態
	bool appearingNow;	//出現中か
	int color;	//色
	int patten;	//柄
};

class Block {
public:
	//初期化
	void Initialize(int windowWidth,int windowHeight);
	//更新
	void Update();
	//描画
	void Draw();
private:


private:
	//フィールドハンドル
	int fieldHandle;
	//フィールド座標
	int fieldPosX[2];
	int fieldPosY[2];
	//Fieldサイズ
	int fieldSizeX;
	int fieldSizeY;

	//ブロックデータ
	const int blockNum = 180;
	BlockData block[180];
};