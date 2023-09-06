#pragma once
#include "DxLib.h"

struct BlockData {
	float posX;
	float posY;
	bool connectionStatus[8];	//接続状態
	bool isFall;	//落下状態
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
	//フィールドハンドル
	int fieldHandle;
	//フィールド座標
	int fieldPosX[2];
	int fieldPosY[2];
	//Fieldサイズ
	int fieldSizeX;
	int fieldSizeY;
};