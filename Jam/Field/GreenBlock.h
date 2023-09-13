#pragma once
#include "DxLib.h"

class GreenBlock
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="x">初期位置X</param>
	/// <param name="y">初期位置Y</param>
	/// <param name="pattern">模様</param>
	GreenBlock(int x, int y, int pattern, bool center);

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

	void SetHit(bool hit) {

		this->hit = hit;
	}

	void SetCenter(bool center) {
		this->center = center;
	}

	//uが上、dが下、lが左、rが右の意	0が色で1が柄
	void SetMatch(bool u, bool d, bool l, bool r, int num);

	void SetDelete(bool deleteFlag, bool doubkeMuctchFlag, bool involvement);

	void GoDeleete() { delete this; }

	/// <summary>
	/// ゲッター
	/// </summary>
	int GetPositionX() { return x; }	//X座標
	int GetPositionY() { return y; }	//Y座標
	int GetSize() { return size; }		//サイズ
	int GetPattern() { return pattern; }//柄
	bool GetIsDelete() { return isDelete; }//削除フラグ
	bool GetDoubleMutch() { return doubleMutch; }	//両一致フラグ
	bool GetInvolvement() { return involvement; }	//巻き込みフラグ
	bool GetCenter() { return center; }	//中心フラグ

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

	bool hit = false;

private:
	//模様  1: 2:
	int pattern = 0;
	//中央座標
	int x = 0;
	int y = 0;
	//大きさ
	int size = 24;

	//画像表示用
	const int blockSizeX = 48;
	const int blockSizeY = 48;
	int blockHandle[6];
	//接続確認用画像ハンドル
	int connectHandle[6];
	int doubleHandle[6];
	int involvementHnadle[6];

	//接続判定
	bool up[2] = { false,false };
	bool down[2] = { false,false };
	bool left[2] = { false,false };
	bool right[2] = { false,false };

	//消滅判定
	bool isDelete = false;
	bool doubleMutch = false;	//両一致判定
	bool involvement = false;	//巻き込み判定

	bool center = false;
};

