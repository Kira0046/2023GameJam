#pragma once
#include "DxLib.h"

class BlueBlock
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="x">�����ʒuX</param>
	/// <param name="y">�����ʒuY</param>
	/// <param name="pattern">�͗l</param>
	BlueBlock(int x, int y, int pattern);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void MoveY();

	/// <summary>
	/// �Z�b�^�[
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
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
	/// �Q�b�^�[
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
	//�͗l  1: 2:
	int pattern = 0;
	//�������W
	int x = 0;
	int y = 0;
	//�傫��
	int size = 24;

	int Number = 0;
};

