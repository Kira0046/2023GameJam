#pragma once
#include "DxLib.h"

class RedBlock
{
public:
	RedBlock(int x, int y, int pattern);

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

private:
	//模様  
	int pattern = 0;
	//中央座標
	int x = 0;
	int y = 0;
	//大きさ
	int size = 24;
};

