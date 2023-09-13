#pragma once
#include "DxLib.h"
#include "RedBlock.h"
#include "GreenBlock.h"
#include "BlueBlock.h"
#include <list>


class GameScene {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void BlockLayoutSetting();

	/// <summary>
	/// ブロック操作
	/// </summary>
	void BlockOperation();

	/// <summary>
	/// 落下中計算
	/// </summary>
	void FallingCalc();

	/// <summary>
	/// ブロック落下計算
	/// </summary>
	void FallBlockCalc();

	/// <summary>
	/// ブロック縦横判定
	/// </summary>
	void FallingCollision();

	/// <summary>
	/// ブロック積み上げ判定
	/// </summary>
	void PiledBlock();

	/// <summary>
	/// 全ブロック固定化
	/// </summary>
	void SetBlockToFallFalse();

	/// <summary>
	/// ブロック地面着地
	/// </summary>
	void PileBlockToLand();

	void SetBlockonLand();


	/// <summary>
	/// 
	/// </summary>
	void BlockFallProcess();

	/// <summary>
	/// ブロック落下化
	/// </summary>
	void BlockFallSetting();

	/// <summary>
	/// 
	/// </summary>
	void BlockToFall();

	void BackToReset();

	void DeleteBlock();

	void SetNumber();

	void DeleteBlockMove();
private:
	//接続状態チェック
	//void CheckConnect();
	void IsConnect();
	//巻き込みチェック※優先順位は通常消し > 巻き込み
	void CheckInvolvement(int num);
	//ブロック消去
	//void DeleteBlock();
	//スコア加算
	void AddScore();


private: //構造体
	//中央からのブロック配置位置　 0:左上 1:右上 2:右下 3:左下
	struct BlockLayoutPosition {
		//配置するブロックの色　0:配置無し 1:赤　2:緑 3:青
		int blocklayoutcolor = 0;
		//配置するブロックの模様  1: 2:
		int blocklayoutpattern = 0;
	};

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


	//落下フェーズ 0:配置待機 1:配置 2:落下　3:ブロック消し
	int fallphase = 0;
	//落下更新待機時間
	int fallupdatetime = 30;
	//ブロック落下更新待期時間
	int blockfallupdatetime = 1;
	int blockfallupdatecount = 0;
	//更新時間
	int maxUpdateTime = 30;
	int defaultTime = 30;
	//移動量
	int amountmovement = 48;

	//中央座標
	int centerX;// = 0;
	int centerY;// = 0;

	//中央出現位置
	int spawnpointX = 800 + 24;
	int spawnpointY;// = 48 + 6;//-48;
	//中央からのブロック出現幅
	int blockspawnsize = 24;


	//各種ブロックリスト
	std::list <RedBlock*> redBlockList;
	std::list <BlueBlock*> blueBlockList;
	std::list <GreenBlock*> greenBlockList;
	//構造体の配列宣言
	BlockLayoutPosition blocklayoutposition[4];

	//作成されたブロックの個数
	int createredblock = 0;
	int creategreenblock = 0;
	int createblueblock = 0;

	int allcreateredblock = 0;
	int allcreategreenblock = 0;
	int allcreateblueblock = 0;

	int redNumber = 0;
	int greenNumber = 0;
	int blueNumber = 0;

	bool redblocklefthit = false;
	bool redblockrighthit = false;
	bool greenblocklefthit = false;
	bool greenblockrighthit = false;
	bool blueblocklefthit = false;
	bool blueblockrighthit = false;

	// 最新のキーボード情報用
	char keys[256];
	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256];

	int test = 0;
	int test2 = 0;

	//接続->消えるまでの待機時間
	const int maxTimer = 30;
	int deleteTimer = 30;
	bool countStart = false;;	//カウント開始変数
	const int halfSize = 24;
	int deleteConnectNum = 1;	//消えるのに必要な数

	//削除ブロックカウント
	int deleteBlockNum = 0;
	int involvementBlockNum = 0;

	//連鎖・スコア
	int chain = 0;
	//スコア
	int score;
	//最大スコア
	int hiScore;
	//加算スコア
	const int add = 60;
	const int bonus = 70;

	int scoreNumHandle[7][11];
	int hiScoreNumHandle[7][11];
	int fontSize[2];
	int fontPos[4];

	int sidebarHandele;
	int scoreFontHandle[2];
	int sidebarSize[2];
	int scoreFontSize[2];
	int sidebarPos[2];
	int scoreFontPos[4];

	//回転処理
	int rotateNum = 0;
	int centerPos[2] = { 0,0 };

	//ジョイパッド
	int oldInput[4] = {0,0,0,0};	//左右と下
	//向き
	int direction = 0;
};