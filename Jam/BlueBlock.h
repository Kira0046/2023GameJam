#pragma once
#include "DxLib.h"

class BlueBlock
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="x">初期位置X</param>
	/// <param name="y">初期位置Y</param>
	/// <param name="pattern">模様</param>
	BlueBlock(int x, int y, int pattern);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void MoveY();

	/// <summary>
	/// セッター
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	void SetPosition(int x, int y) {
		this->x += x;
		this->y += y;
	}

	void SetHitUp(bool hitup) {
		this->hitup = hitup;
	}

	void SetHitDown(bool hitdown) {
		this->hitdown = hitdown;
	}

	void SetHitLeft(bool hitleft) {
		this->hitleft = hitleft;
	}

	void SetHitRight(bool hitright) {
		this->hitright = hitright;
	}


	void SetFall(bool fall) {
		this->fall = fall;
	}

	void SetNumber(int num) {
		this->Number = num;
	}

	void SetDelete(bool isdelete) {
		this->isdelete = isdelete;
	}

	/// <summary>
	/// ゲッター
	/// </summary>
	int GetPositionX() {
		return x;
	}

	int GetPositionY() {
		return y;
	}

	int GetSize() {
		return size;
	}

	int GetNumber() {
		return Number;
	}

	const bool& GetIshitUp() const { return hitup; }

	const bool& GetIshitDown() const { return hitdown; }

	const bool& GetIshitLeft() const { return hitleft; }

	const bool& GetIshitRight() const { return hitright; }

	const bool& GetIsFall() const { return fall; }

	bool fall = true;

	bool hitup = false;

	bool hitdown = false;

	bool hitleft = false;

	bool hitright = false;

	bool isdelete = false;

private:
	//模様  1: 2:
	int pattern = 0;
	//中央座標
	int x = 0;
	int y = 0;
	//大きさ
	int size = 24;

	int Number = 0;
};

