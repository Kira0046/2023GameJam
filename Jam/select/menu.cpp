#include "menu.h"

void Menu::Initialize() {
	//シーンチェンジ
	//※タイトル→メニュー→ゲーム画面を考慮して初期値を1にしておきます
	//本番リリース時は0にしておく
	scene = 1;
}

void Menu::Update(char *keys) {
	//シーンチェンジのテスト
	if (keys[KEY_INPUT_SPACE]) {
		scene = 2;
	}
}