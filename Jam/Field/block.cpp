#include "block.h"

void Block::Initialize(int windowWidth, int windowHeight) {
	//画像読み込み
	fieldHandle = LoadGraph("Resource/field/field_kari.png");
	//画像サイズ取得
	GetGraphSize(fieldHandle,&fieldSizeX,&fieldSizeY);
	//フィールド座標入力
	fieldPosX[0] = windowWidth / 2 - fieldSizeX / 2;
	fieldPosY[0] = windowHeight / 2 - fieldSizeY / 2;
}

void Block::Draw() {
	DrawGraph(fieldPosX[0], fieldPosY[0], fieldHandle, true);
}