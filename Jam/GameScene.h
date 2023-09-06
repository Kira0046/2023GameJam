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

	/// <summary>
	/// ブロック操作
	/// </summary>
	void BlockOperation();

	/// <summary>
	/// 落下中計算
	/// </summary>
	void FallingCalc();
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
	int spawnpointY = -48;
	//中央からのブロック出現幅
	int blockspawnsize = 24;

	//各種ブロックリスト
	std::list <RedBlock*> redBlockList;
	std::list <BlueBlock*> blueBlockList;
	std::list <GreenBlock*> greenBlockList;


	// 最新のキーボード情報用
	char keys[256];
	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256];
};