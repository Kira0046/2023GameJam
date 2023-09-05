#include "GameScene.h"

void GameScene::Initialize(){
	redBlock = new RedBlock();
}

void GameScene::Update(){
}

void GameScene::Draw(){
	redBlock->Draw();
}
