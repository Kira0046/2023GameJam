#pragma once
#include "DxLib.h"

class Menu {
public:
	//初期化
	void Initialize(int windowWidth, int windowHeight);
	//更新
	void Update(char *keys,char *oldkeys);
	//描画
	void Draw();
	//シーン番号送信
	void SendSceneNum(int num);

	//シーン番号取得
	int GetSceneNum() {
		return scene;
	}
private:
	//シーン番号
	int scene;
	//メニューバーハンドル
	int menuHandle[10];
	//メニュー番号
	int barNum;
	//メニュー各座標
	int barPosX[5];
	int barPosY[5];
	//メニュー個数
	const int menuNum = 5;
	//メニューサイズ
	int barSizeX;
	int barSizeY;
	//操作可能までのタイマー
	int coolTimer[5];
	int moveStartTimer;	//一気に来させるのではなく一個ずつ来させるためのタイマー
	bool moveStart[5];
	int startCounter;
	//操作可能権
	bool canControl;

	//画面サイズ、他でも使うので格納
	int winWidth;
};
