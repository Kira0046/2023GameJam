#pragma once
#include "DxLib.h"
#include "RedBlock.h"
#include "GreenBlock.h"
#include "BlueBlock.h"

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
private:
	RedBlock* redBlock = nullptr;

};