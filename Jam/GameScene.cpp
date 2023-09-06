#include "GameScene.h"

void GameScene::Initialize() {
	redBlockList.push_back(new RedBlock(800, 450, 1));
	redBlockList.push_back(new RedBlock(600, 450, 1));
}

void GameScene::Update() {
}

void GameScene::Draw() {
	for (auto itr = redBlockList.begin(); itr != redBlockList.end(); ++itr) {
		(*itr)->Draw();
	}
}
