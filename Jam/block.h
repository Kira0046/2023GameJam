#pragma once
#include "DxLib.h"

// ブロック1個１個の内部データ
struct BlockData {
	float posX;
	float posY;
	bool connectionStatus[8];	//接続状態
	bool isFall;	//落下状態
	bool appearingNow;	//出現中か
	int colorPattern;	//色と柄
};

class Block {
public:
	//初期化
	void Initialize(int windowWidth, int windowHeight);
	//更新
	void Update();
	//描画
	void Draw();

private:

	//接続状態チェック
	void CheckConnect();

private:
	//フィールドハンドル
	int fieldHandle;
	//フィールド座標
	int fieldPosX[2];
	int fieldPosY[2];
	//Fieldサイズ
	int fieldSizeX;
	int fieldSizeY;
	//枠分サイズ
	const int fieldFlameSizeX = 6;
	const int fieldFlameSizeY = 6;
	//ブロックデータ
	const int blockNum = 180;
	BlockData block[180];
	//ブロックの画像ハンドル
	int blockHandle[6];
	//ブロックのサイズ
	const int blockSizeX = 48;
	const int blockSizeY = 48;
	//接続状態数
	const int connectNum = 8;
};