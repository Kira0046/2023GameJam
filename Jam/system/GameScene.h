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
private:
	//接続状態チェック
	void CheckConnect();
	void IsConnect();
	//巻き込みチェック※優先順位は通常消し > 巻き込み
	void CheckInvolvement(int num);
	//ブロック消去
	void DeleteBlock();
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
	int fallupdatetime = 5;
	//更新時間
	const int maxUpdateTime = 5;
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

	//接続->消えるまでの待機時間
	const int maxTimer = 60;
	int deleteTimer = 0;;
	bool countStart = false;;	//カウント開始変数
	const int halfSize = 24;
	int deleteConnectNum = 1;	//消えるのに必要な数
};