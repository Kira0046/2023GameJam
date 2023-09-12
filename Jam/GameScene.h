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
	/// 当たり判定
	/// </summary>
	void FallingCollision();



private: //構造体
	//中央からのブロック配置位置　 0:左上 1:右上 2:右下 3:左下
	struct BlockLayoutPosition {
		//配置するブロックの色　0:配置無し 1:赤　2:緑 3:青
		int blocklayoutcolor = 0;
		//配置するブロックの模様  1: 2:
		int blocklayoutpattern = 0;
	};

private:
	//落下フェーズ 0:配置待機 1:配置 2:落下
	int fallphase = 0;
	//落下更新待機時間
	int fallupdatetime = 60;
	//移動量
	int amountmovement = 48;

	//中央座標
	int centerX = 0;
	int centerY = 0;

	//中央出現位置
	int spawnpointX = 800;
	int spawnpointY = 96;//-48;
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
};