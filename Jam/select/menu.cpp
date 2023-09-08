#include "menu.h"
#include "easing.h"

void Menu::Initialize(int windowWidth, int windowHeight) {
	//シーンチェンジ
	//※タイトル→メニュー→ゲーム画面を考慮して初期値を1にしておきます
	//本番リリース時は0にしておく
	scene = 1;

	//メニュー初期化
	barNum = 0;
	LoadDivGraph("Resource/menu/menu_flame.png", 10, 10, 1, 612, 87, menuHandle);
	GetGraphSize(menuHandle[0], &barSizeX, &barSizeY);
	for (int i = 0; i < menuNum; i++) {
		barPosX[i] = windowWidth / 4 - barSizeX / 2;
		barPosY[i] = 150 + barSizeY * 1.5 * i;
	}
}

void Menu::Update(char *keys, char* oldkeys) {
	//シーンチェンジのテスト
	if (keys[KEY_INPUT_SPACE]) {
		scene = 2;
	}
	if (keys[KEY_INPUT_UP] && !oldkeys[KEY_INPUT_UP]) {
		barNum--;
		if (barNum < 0) {
			barNum = 4;
		}
	}
	else if (keys[KEY_INPUT_DOWN] && !oldkeys[KEY_INPUT_DOWN]) {
		barNum++;
		if (barNum > 4) {
			barNum = 0;
		}
	}

}

void Menu::Draw() {
	for (int i = 0; i < menuNum; i++) {
		if(barNum == i){

			DrawExtendGraph(barPosX[i] - 20, barPosY[i] - 20, barPosX[i] + barSizeX + 19, barPosY[i] + barSizeY, menuHandle[i * 2 + 1], true);
		}
		else {
			DrawGraph(barPosX[i], barPosY[i], menuHandle[i * 2], true);
		}
	}
}