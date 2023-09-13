#include "DxLib.h"
#include "GameScene.h"
#include "block.h"
#include "menu.h"
#pragma warning(disable:4819)

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "カラガラ";

// ウィンドウ横幅
const int WIN_WIDTH = 1600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 900;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	//クラス
	Block block;	//ゲーム内のブロック処理
	Menu menu;		//メニュー処理
	//初期化
	block.Initialize(WIN_WIDTH,WIN_HEIGHT);
	menu.Initialize(WIN_WIDTH,WIN_HEIGHT);

	// ゲームループで使う変数の宣言
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理	メニューの番号に応じて表示、更新するものを変更する
		if (menu.GetSceneNum() < 3) {
			menu.Update(keys,oldkeys);
		}
		if (menu.GetSceneNum() == 2) {
			gameScene->Update();
			menu.OutHyde();
			//block.Update();
		}
		// 描画処理
		if (menu.GetSceneNum() < 3) {
			menu.Draw();
		}
		if (menu.GetSceneNum() == 2) {
			//block.Draw();
			gameScene->Draw();
		}
		menu.HydeDraw();

		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}


		// 更新処理
		

		// 描画処理
		

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
