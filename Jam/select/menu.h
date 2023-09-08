#pragma once
#include "DxLib.h"

class Menu {
public:
	//初期化
	void Initialize();
	//更新
	void Update(char *keys);
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
};
