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
	LoadDivGraph("Resource/menu/menu_back.png", 4, 4, 1, 400, 100, cancelHandle);
	GetGraphSize(menuHandle[0], &barSizeX, &barSizeY);
	for (int i = 0; i < menuNum; i++) {
		//barPosX[i] = windowWidth / 4 - barSizeX / 2;
		barPosX[i] = -barSizeX;
		barPosY[i] = 150 + barSizeY * 1.5 * i;
		moveStart[i] = false;
		coolTimer[i] = 0;
		endMove[i] = false;
	}
	canControl = false;
	moveStartTimer = 5;
	startCounter = 0;
	startorEnd = false;	 //初期状態は登場
	menuBlinlingTimer = 0;

	//BACK
	GetGraphSize(cancelHandle[0], &cancelSize[0], &cancelSize[1]);
	cancelPos[0] = 0;
	cancelPos[1] = windowHeight;
	isCancel = false;

	//項目全体
	for (int i = 0; i < allTabNum; i++) {
		wachiBlinling[i] = false;
	}

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

	//ナビ
	LoadDivGraph("Resource/menu/press.png", 2, 2, 1, 920, 300, naviTitleHandle);
	GetGraphSize(naviTitleHandle[0], &naviTitleSize[0], &naviTitleSize[1]);
	naviTitlePosX = windowWidth / 2 - naviTitleSize[0] / 2;
	naviTitlePosY = windowHeight - naviTitleSize[1] * 1.2;
	blinkingTimer = 0;
	blinkingCount = 0;
}

void Menu::Update(char* keys, char* oldkeys) {

	if (scene == 0) {
		//登場退場処理
		InOutTitle();

		if (canControl) {
			blinkingTimer++;
			if (blinkingTimer > 90) {
				blinkingTimer = 0;
			}
			if (keys[KEY_INPUT_SPACE] || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2)) {
				logoEndMove = true;
				canControl = false;
				blinkingTimer = 28;
			}
		}

	}
	else if (scene == 1) {
		//登場退場処理
		InOutMenu();

		//シーンチェンジのテスト
		if (canControl) {
			if (keys[KEY_INPUT_SPACE] || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2)) {
				scene = 2;
			}
			if (keys[KEY_INPUT_UP] && !oldkeys[KEY_INPUT_UP] || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) && !oldInput[0]) {
				barNum--;
				if (barNum < 0) {
					barNum = 4;
				}
			}
			else if (keys[KEY_INPUT_DOWN] && !oldkeys[KEY_INPUT_DOWN] || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) && !oldInput[1]) {
				barNum++;
				if (barNum > 4) {
					barNum = 0;
				}
			}
			else if (keys[KEY_INPUT_LSHIFT] && !oldkeys[KEY_INPUT_LSHIFT] || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1)) {
				startorEnd = true;
				canControl = false;
				wachiBlinling[5] = true;
				isCancel = true;
			}
		}
	}

	//背景処理
	for (int i = 0; i < 2; i++) {
		backPosX[i]--;
		if (backPosX[i] < -backSizeX) {
			backPosX[i] = backSizeX - 1;
		}
	}

	//直前の入力状態読み込み
	oldInput[0] = (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP);
	oldInput[1] = (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN);
}

void Menu::Draw() {
	DrawGraph(backPosX[0], 0, backHandle01[barNum], true);
	DrawGraph(backPosX[1], 0, backHandle02[barNum], true);
	if (scene == 0) {
		DrawGraph(logoPosX, logoPosY, logoHandle, true);
		if (blinkingTimer > 30) {
			if (GetJoypadNum() > 0) {
				DrawGraph(naviTitlePosX, naviTitlePosY, naviTitleHandle[1], true);
			}
			else {
				DrawGraph(naviTitlePosX, naviTitlePosY, naviTitleHandle[0], true);
			}
		}
	}
	else if (scene == 1) {
		for (int i = 0; i < menuNum; i++) {
			if (barNum == i && canControl) {
				DrawExtendGraph(barPosX[i] - 20, barPosY[i] - 20, barPosX[i] + barSizeX + 19, barPosY[i] + barSizeY, menuHandle[i * 2 + 1], true);
			}
			else {
				if (!wachiBlinling[i] || wachiBlinling[i] && menuBlinlingTimer < 3) {
					DrawGraph(barPosX[i], barPosY[i], menuHandle[i * 2], true);
				}
			}
		}
		if (!wachiBlinling[5] || wachiBlinling[5] && menuBlinlingTimer < 3) {
			if (GetJoypadNum() > 0) {
				DrawGraph(cancelPos[0], cancelPos[1], cancelHandle[1], true);
			}
			else {
				DrawGraph(cancelPos[0], cancelPos[1], cancelHandle[0], true);
			}
		}
	}
	DrawFormatString(10, 10, GetColor(0, 0, 0), "blinkingTimer : %d", blinkingTimer);
	DrawFormatString(10, 25, GetColor(0, 0, 0), "canControl : %d", canControl);
	DrawFormatString(10, 40, GetColor(0, 0, 0), "startorEnd : %d", startorEnd);
	DrawFormatString(10, 55, GetColor(0, 0, 0), "logoPosY : %d", logoPosY);
	DrawFormatString(10, 70, GetColor(0, 0, 0), "scene : %d", scene);
	DrawFormatString(10, 85, GetColor(0, 0, 0), "back00 : {%d ,%d}", backPosX[0], 0);
	DrawFormatString(10, 100, GetColor(0, 0, 0), "back01 : {%d ,%d}", backPosX[1],0);
}

void Menu::InOutTitle() {
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
			if (blinkingCount < 10) {
				blinkingTimer++;
			}
			if (blinkingTimer > 32) {
				blinkingTimer = 28;
				blinkingCount++;
			}
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
			blinkingTimer = 0;
			blinkingCount = 0;
		}
	}
}

void Menu::InOutMenu() {
	//登場処理
	if (!canControl) {
		moveStartTimer--;
		if (moveStartTimer < 0) {
			moveStartTimer = 5;
			if (!startorEnd) {
				moveStart[startCounter] = true;
			}
			else {
				endMove[startCounter] = true;
			}
			if (startCounter < 4) {
				startCounter++;
			}
		}
		menuBlinlingTimer++;
		if (menuBlinlingTimer > 5) {
			menuBlinlingTimer = 0;
		}
	}
	for (int i = 0; i < menuNum; i++) {
		if (moveStart[i] || endMove[i]) {
			if (coolTimer[i] < 60) {
				coolTimer[i]++;
			}
			if (moveStart[i]) {
				barPosX[i] = EASE::OutQuad(winWidth / 4 + barSizeX / 2, -barSizeX, 60, coolTimer[i]);
				//BACK
				if (i == 4) {
					cancelPos[1] = EASE::OutQuad(-cancelSize[1], winHeight, 60, coolTimer[i]);
				}
			}
			else if (endMove[i]) {
				if (scene < 2) {
					barPosX[i] = EASE::InQuad(-barSizeX * 2, winWidth / 4 - barSizeX / 2, 60, coolTimer[i]);
					//BACK
					if (i == 4) {
						cancelPos[1] = EASE::InQuad(+cancelSize[1], winHeight - cancelSize[1], 60, coolTimer[i]);
					}
				}
			}
		}
	}
	if (coolTimer[4] >= 60) {
		canControl = true;
		for (int i = 0; i < menuNum; i++) {
			coolTimer[i] = 0;
			moveStart[i] = false;
			startCounter = 0;
			moveStartTimer = 15;
		}
		if (startorEnd) {
			canControl = false;
			for (int i = 0; i < menuNum; i++) {
				coolTimer[i] = 0;
				endMove[i] = false;
				startCounter = 0;
				moveStartTimer = 15;
				startorEnd = false;
			}
			if (isCancel) {
				scene--;
				isCancel = false;
			}
			for (int i = 0; i < allTabNum; i++) {
				if (wachiBlinling[i]) {
					wachiBlinling[i] = false;
				}
			}
			menuBlinlingTimer = 0;
		}
		else {
			barNum = 0;
		}
	}
}