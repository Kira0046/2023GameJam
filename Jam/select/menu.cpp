#include "menu.h"
#include "easing.h"

void Menu::Initialize(int windowWidth, int windowHeight) {
	//シーンチェンジ
	//※タイトル→メニュー→ゲーム画面を考慮して初期値を1にしておきます
	//本番リリース時は0にしておく
	scene = 2;

	//画面サイズ格納
	winWidth = windowWidth;
	winHeight = windowHeight;

	//メニュー初期化
	barNum = 0;
	LoadDivGraph("Resource/menu/menu_flame.png", 10, 10, 1, 612, 87, menuHandle);
	LoadDivGraph("Resource/menu/backGround.png", 5, 5, 1, 1600, 900, backHandle01);
	LoadDivGraph("Resource/menu/backGround.png", 5, 5, 1, 1600, 900, backHandle02);
	LoadDivGraph("Resource/menu/menu_back.png", 4, 4, 1, 400, 100, cancelHandle);
	hydeHandle = LoadGraph("Resource/menu/taremaku.png");
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

	//垂れ幕
	GetGraphSize(hydeHandle, &hydeSize[0], &hydeSize[1]);
	hydePos[0] = 0;
	hydePos[1] = -hydeSize[1];
	hydeStart = false;
	hydeEnd = false;
	hydeTimer = 0;

	//項目全体
	for (int i = 0; i < allTabNum; i++) {
		wachiBlinling[i] = false;
	}

	//タブ（説明）
	LoadDivGraph("Resource/menu/tabs.png", 5, 5, 1, 750, 750, tabHandle);
	GetGraphSize(tabHandle[0], &tabSize[0], &tabSize[1]);
	tabPos[0] = windowWidth / 2 * 1.05;
	tabPos[1] = windowHeight / 2 * 1.1 - tabSize[1] / 2;

	//操作ナビ
	LoadDivGraph("Resource/menu/navi_ud.png", 4, 4, 1, 96, 192, selectNaviHandle);
	LoadDivGraph("Resource/menu/arrow.png", 2, 2, 1, 96, 96, arrowHandle);
	GetGraphSize(selectNaviHandle[0], &selectNaviSize[0], &selectNaviSize[1]);
	GetGraphSize(arrowHandle[0], &arrowSize[0], &arrowSize[1]);
	selectNaviPos[0] = windowWidth / 2 - selectNaviSize[0] + selectNaviSize[0] / 4;
	selectNaviPos[1] = windowHeight / 2 - selectNaviSize[1] / 2;
	arrowPos[0][0] = selectNaviPos[0];
	arrowPos[0][1] = selectNaviPos[1];
	arrowPos[1][0] = selectNaviPos[0];
	arrowPos[1][1] = selectNaviPos[1];
	changeTimer = 0;
	arrowMoveTimer = 0;

	//背景座標など
	backPosX[0] = 0;
	backPosX[1] = backSizeX;
	LoadDivGraph("Resource/menu/upber.png", 5, 5, 1, 1600, 100, upBarHandle);
	GetGraphSize(upBarHandle[0], &upBarSize[0], &upBarSize[1]);
	upBarPosY = -upBarSize[1];

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
		InHyde();

		//シーンチェンジのテスト
		if (canControl) {
			if (keys[KEY_INPUT_SPACE] || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2)) {
				if (barNum == 0) {
					hydeStart = true;
					canControl = false;
				}
			}
			if (keys[KEY_INPUT_UP] && !oldkeys[KEY_INPUT_UP] || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) && !oldInput[0] || keys[KEY_INPUT_W] && !oldkeys[KEY_INPUT_W]) {
				barNum--;
				if (barNum < 0) {
					barNum = 4;
				}
			}
			else if (keys[KEY_INPUT_DOWN] && !oldkeys[KEY_INPUT_DOWN] || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) && !oldInput[1] || keys[KEY_INPUT_S] && !oldkeys[KEY_INPUT_S]) {
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
			changeTimer++;
			if (changeTimer > 120) {
				changeTimer = 0;
			}
			
			if (arrowMoveTimer < 30) {
				arrowMoveTimer++;
			}
			else {
				arrowMoveTimer = 0;
			}
			arrowPos[0][1] = EASE::OutQuad(-arrowSize[1] / 4, selectNaviPos[1] - arrowSize[1], 30, arrowMoveTimer);
			arrowPos[1][1] = EASE::OutQuad(arrowSize[1] / 4, selectNaviPos[1] + selectNaviSize[1], 30, arrowMoveTimer);
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
		if (canControl) {
			DrawGraph(tabPos[0], tabPos[1], tabHandle[barNum], true);
			if (GetJoypadNum() > 0) {
				if (changeTimer < 60) {
					DrawGraph(selectNaviPos[0], selectNaviPos[1], selectNaviHandle[2], true);
				}
				else {
					DrawGraph(selectNaviPos[0], selectNaviPos[1], selectNaviHandle[3], true);
				}
			}
			else {
				if (changeTimer < 60) {
					DrawGraph(selectNaviPos[0], selectNaviPos[1], selectNaviHandle[0], true);
				}
				else {
					DrawGraph(selectNaviPos[0], selectNaviPos[1], selectNaviHandle[1], true);
				}
			}
			DrawGraph(arrowPos[0][0], arrowPos[0][1], arrowHandle[0], true);
			DrawGraph(arrowPos[1][0], arrowPos[1][1], arrowHandle[1], true);
		}

		if (!wachiBlinling[5] || wachiBlinling[5] && menuBlinlingTimer < 3) {
			if (GetJoypadNum() > 0) {
				DrawGraph(cancelPos[0], cancelPos[1], cancelHandle[1], true);
			}
			else {
				DrawGraph(cancelPos[0], cancelPos[1], cancelHandle[0], true);
			}
		}
		DrawGraph(0, upBarPosY, upBarHandle[barNum], true);
	}
	/*DrawFormatString(10, 10, GetColor(0, 0, 0), "blinkingTimer : %d", blinkingTimer);
	DrawFormatString(10, 25, GetColor(0, 0, 0), "canControl : %d", canControl);
	DrawFormatString(10, 40, GetColor(0, 0, 0), "startorEnd : %d", startorEnd);
	DrawFormatString(10, 55, GetColor(0, 0, 0), "logoPosY : %d", logoPosY);
	DrawFormatString(10, 70, GetColor(0, 0, 0), "scene : %d", scene);
	DrawFormatString(10, 85, GetColor(0, 0, 0), "arrow: {%d ,%d}", arrowPos[0][0], arrowPos[0][1]);
	DrawFormatString(10, 100, GetColor(0, 0, 0), "back01 : {%d ,%d}", backPosX[1],0);*/
}

void Menu::InOutTitle() {
	if (!canControl && !logoEndMove && !hydeStart) {
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
	if (!canControl && !hydeStart) {
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
				if (i == 4) {
					cancelPos[1] = EASE::OutQuad(-cancelSize[1], winHeight, 60, coolTimer[i]);	//キャンセル
					upBarPosY = EASE::OutQuad(upBarSize[1], -upBarSize[1], 60, coolTimer[i]);	//アップバー
				}
			}
			else if (endMove[i]) {
				if (scene < 2) {
					barPosX[i] = EASE::InQuad(-barSizeX * 2, winWidth / 4 - barSizeX / 2, 60, coolTimer[i]);
					if (i == 4) {
						cancelPos[1] = EASE::InQuad(+cancelSize[1], winHeight - cancelSize[1], 60, coolTimer[i]);	//キャンセル
						upBarPosY = EASE::InQuad(-upBarSize[1], 0, 60, coolTimer[i]);	//アップバー

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
		changeTimer = 0;
		arrowMoveTimer = 0;
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

void Menu::InHyde() {
	if (hydeStart && !hydeEnd) {
		if (hydeTimer < 60) {
			hydeTimer++;
		}
		else {
			hydeEnd = true;
			hydeTimer = 0;
			hydeStart = false;
			scene = 2;
		}
		hydePos[1] = EASE::OutQuad(hydeSize[1], -hydeSize[1], 60, hydeTimer);
	}
}

void Menu::OutHyde() {
	if (hydeEnd) {
		hydePos[1] = EASE::InQuad(-hydeSize[1], 0, 60, hydeTimer);
		if (hydeTimer < 60) {
			hydeTimer++;
		}
		else {
			hydeEnd = false;
			hydeTimer = 0;
			hydePos[1] = -hydeSize[1];
		}
	}
}

void Menu::HydeDraw() {
	DrawGraph(hydePos[0], hydePos[1], hydeHandle, true);
}