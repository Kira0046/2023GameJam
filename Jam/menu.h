#pragma once
#include "DxLib.h"
class Menu {
public:
	//初期化
	void Initialize(int windowWidth, int windowHeight);
	//更新
	void Update(char* keys, char* oldkeys);
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
	int winHeight;
	//背景
	int backHandle01[5];
	int backHandle02[5];
	int backPosX[2];
	const int backSizeX = 1600;

	//タイトル
	int logoHandle;	//画像データ格納ハンドル
	int logoPosX;	//X座標
	int logoPosY;	//Y座標
	int logoSizeX;	//Xサイズ
	int logoSizeY;	//Yサイズ
	bool logoMoveStart;	//登場フラグ
	int logoCoolTimer;	//経過時間
	bool logoEndMove;	//退場フラグ
	//ナビ
	int naviTitleHandle[2];
	int naviTitlePosX;
	int naviTitlePosY;
	int naviTitleSize[2];
	int blinkingTimer;
	int blinkingCount;
};