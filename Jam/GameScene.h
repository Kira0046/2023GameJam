#pragma once
#include "DxLib.h"
#include "RedBlock.h"
#include "GreenBlock.h"
#include "BlueBlock.h"
#include <list>


class GameScene {
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();

	/// <summary>
	/// XV
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw();
private:
	int spawnpointX = 800;
	int spawnpointY = -48;

	std::list <RedBlock*> redBlockList;
	std::list <BlueBlock*> blueBlockList;
	std::list <GreenBlock*> greenBlockList;
};