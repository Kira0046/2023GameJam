#include "GameScene.h"

void GameScene::Initialize() {
	// 最新のキーボード情報用
	keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	oldkeys[256] = { 0 };


	redBlockList.push_back(new RedBlock(800, 450, 1));
	redBlockList.push_back(new RedBlock(600, 450, 1));
	greenBlockList.push_back(new GreenBlock(1000, 450, 1));
	blueBlockList.push_back(new BlueBlock(1200, 450, 1));
}

void GameScene::Update() {
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; ++i) {
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);


	if (fallphase == 0) {
		centerX = spawnpointX;
		centerY = spawnpointY;
		fallphase = 1;
	}
	if (fallphase == 1) {
		fallphase = 2;
	}
	if (fallphase == 2) {
		BlockOperation();
		FallingCalc();
	}

}

void GameScene::Draw() {
	//赤ブロック描画
	for (auto redblockitr = redBlockList.begin(); redblockitr != redBlockList.end(); ++redblockitr) {
		(*redblockitr)->Draw();
	}

	//緑ブロック描画
	for (auto greenblockitr = greenBlockList.begin(); greenblockitr != greenBlockList.end(); ++greenblockitr) {
		(*greenblockitr)->Draw();
	}

	//青ブロック描画
	for (auto blueblockitr = blueBlockList.begin(); blueblockitr != blueBlockList.end(); ++blueblockitr) {
		(*blueblockitr)->Draw();
	}
	DrawBox(centerX - 24, centerY - 24, centerX + 24, centerY + 24, GetColor(255, 255, 0), true);
}

void GameScene::BlockOperation() {
	if (keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0) {
		centerX -= amountmovement;
	}
	if (keys[KEY_INPUT_D] == 1 && oldkeys[KEY_INPUT_D] == 0) {
		centerX += amountmovement;
	}
}

void GameScene::FallingCalc() {
	fallupdatetime -= 1;
	if (fallupdatetime == 0) {
		centerY += amountmovement;
		fallupdatetime = 60;
	}
}
