#include "menu.h"
#include "easing.h"

void Menu::Initialize(int windowWidth, int windowHeight) {
	//シーンチェンジ
	//※タイトル→メニュー→ゲーム画面を考慮して初期値を1にしておきます
	//本番リリース時は0にしておく
	scene = 0;

	//画面サイズ格納
	winWidth = windowWidth;
	winHeight = windowHeight;

	//メニュー初期化
	barNum = 0;
	LoadDivGraph("Resource/menu/menu_flame.png", 10, 10, 1, 612, 87, menuHandle);
	LoadDivGraph("Resource/menu/backGround.png", 5, 5, 1, 1600, 900, backHandle01);
	LoadDivGraph("Resource/menu/backGround.png", 5, 5, 1, 1600, 900, backHandle02);
	GetGraphSize(menuHandle[0], &barSizeX, &barSizeY);
	for (int i = 0; i < menuNum; i++) {
		//barPosX[i] = windowWidth / 4 - barSizeX / 2;
		barPosX[i] = -barSizeX;
		barPosY[i] = 150 + barSizeY * 1.5 * i;
		moveStart[i] = false;
		coolTimer[i] = 0;
	}
	canControl = false;
	moveStartTimer = 5;
	startCounter = 0;
	//背景座標など
	backPosX[0] = 0;
	backPosX[1] = backSizeX;

	//タイトルロゴ
	logoHandle = LoadGraph("Resource/menu/logo.png");
	GetGraphSize(logoHandle, &logoSizeX, &logoSizeY);
	logoPosX = windowWidth / 2 - logoSizeX / 2;
	logoPosY = -logoSizeY;
	logoMoveStart = false;
	logoCoolTimer = 0;
	logoEndMove = false;
}

void Menu::Update(char* keys, char* oldkeys) {
	if (scene == 0) {
		if (!canControl && !logoEndMove) {
			moveStartTimer--;
			if (moveStartTimer < 0) {
				logoMoveStart = true;
			}
		}
		if (logoMoveStart || logoEndMove) {
			if (logoCoolTimer < 90) {
				logoCoolTimer++;
			}
			if (logoMoveStart) {
				logoPosY = EASE::OutQuad(winHeight / 4 + logoSizeY / 2, -logoSizeY, 90, logoCoolTimer);
			}
			else if (logoEndMove) {
				logoPosY = EASE::InQuad(-logoSizeY - logoSizeY / 2, winHeight / 4 - logoSizeY / 2, 90, logoCoolTimer);
			}
		}
		if (logoCoolTimer >= 90) {
			logoMoveStart = false;
			logoCoolTimer = 0;
			canControl = true;
			moveStartTimer = 15;
			if (logoEndMove) {
				logoEndMove = false;
				canControl = false;
				scene = 1;
			}
		}
		if (canControl) {
			if (keys[KEY_INPUT_SPACE]) {
				logoEndMove = true;
				canControl = false;
			}
		}

	}
	else if (scene == 1) {
		//登場処理
		if (!canControl) {
			moveStartTimer--;
			if (moveStartTimer < 0) {
				moveStartTimer = 5;
				moveStart[startCounter] = true;
				startCounter++;
			}
		}
		for (int i = 0; i < menuNum; i++) {
			if (moveStart[i]) {
				if (coolTimer[i] < 60) {
					coolTimer[i]++;
				}
				barPosX[i] = EASE::OutQuad(winWidth / 4 + barSizeX / 2, -barSizeX, 60, coolTimer[i]);
			}
		}
		if (coolTimer[4] >= 60) {
			canControl = true;
			for (int i = 0; i < menuNum; i++) {
				coolTimer[i] = 0;
				moveStart[i] = false;
				startCounter = 0;
				moveStartTimer = 5;
			}
		}

		//シーンチェンジのテスト
		if (canControl) {
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
	}

	//背景処理
	for (int i = 0; i < 2; i++) {
		backPosX[i]--;
		if (backPosX[i] < -backSizeX) {
			backPosX[i] = backSizeX;
		}
	}
}

void Menu::Draw() {
	DrawGraph(backPosX[0], 0, backHandle01[barNum], true);
	DrawGraph(backPosX[1], 0, backHandle02[barNum], true);
	if (scene == 0) {
		DrawGraph(logoPosX, logoPosY, logoHandle, true);
	}
	else if (scene == 1) {
		for (int i = 0; i < menuNum; i++) {
			if (barNum == i && canControl) {

				DrawExtendGraph(barPosX[i] - 20, barPosY[i] - 20, barPosX[i] + barSizeX + 19, barPosY[i] + barSizeY, menuHandle[i * 2 + 1], true);
			}
			else {
				DrawGraph(barPosX[i], barPosY[i], menuHandle[i * 2], true);
			}
		}
	}
	DrawFormatString(10, 10, GetColor(0, 0, 0), "CoolTimer[4] : %d", coolTimer[4]);
	DrawFormatString(10, 25, GetColor(0, 0, 0), "canControl : %d", canControl);
	DrawFormatString(10, 40, GetColor(0, 0, 0), "logoPosY : %d", logoPosY);
}