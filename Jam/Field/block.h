#pragma once
#include "DxLib.h"

//ブロック一個一個の内部データ
struct BlockData {
	float posX;
	float posY;
	bool connectionStatus[8];	//接続状態
	bool isControl;	//操作状態
	bool isFall;	//落下状態
	bool appearingNow;	//出現中か
	int colorPattern;	//色と柄
	bool isDelete;	//消える？
	bool doubleMutch;	//両一致判定
	bool involvement;	//巻き込み判定
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
	void IsConnect(int num);
	//巻き込みチェック※優先順位は通常消し > 巻き込み
	void CheckInvolvement(int num);
	//ブロック消去
	void DeleteBlock();
	//スコア加算
	void AddScore();

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
	//接続確認用画像ハンドル
	int connectHandle[6];
	int doubleHandle[6];
	int involvementHnadle[6];

	//接続->消えるまでの待機時間
	const int maxTimer = 60;
	int deleteTimer;
	bool countStart;	//カウント開始変数

	//スコア
	int score;
	//最大スコア
	int hiScore;
	//加算スコア
	const int add = 20;
	const int bonus = 30;
	//連鎖数
	int chain;
	//連鎖可能フラグ
	bool canChain;
	//削除ブロックカウント
	int deleteBlockNum;
	int involvementBlockNum;
};