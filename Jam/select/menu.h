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
	//登場処理・退場処理
	void InOutTitle();
	void InOutMenu();

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
	bool moveStart[5];	//登場フラグ
	bool endMove[5];	//退場フラグ
	bool startorEnd;	//登場退場どっちなのか判別用
	int startCounter;
	//操作可能権
	bool canControl;

	//キャンセル
	int cancelHandle[4];
	//座標
	int cancelPos[2];
	//サイズ
	int cancelSize[2];
	//フラグ
	bool isCancel;
	//表示時間
	int menuBlinlingTimer;
	bool wachiBlinling[6];
	const int allTabNum = 6;	//点滅用の全ての項目の番号（キャンセル含む）

	//画面サイズ、他でも使うので格納
	int winWidth;
	int winHeight;

	//アップバー
	int upBarHandle[5];
	int upBarPosY;
	int upBarSize[2];

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

	//ルール説明
	int tabHandle[5];
	int tabPos[2];
	int tabSize[2];

	//操作UI
	int selectNaviHandle[4];
	int changeTimer;
	int arrowHandle[2];
	int arrowMoveTimer;
	int selectNaviPos[2];
	int selectNaviSize[2];
	int arrowPos[2][2];
	int arrowSize[2];

	//ジョイパッド
	int oldInput[2];	//とりあえず上下
};
