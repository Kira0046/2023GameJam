#pragma once
#include "DxLib.h"

class GreenBlock
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="x">�����ʒuX</param>
	/// <param name="y">�����ʒuY</param>
	/// <param name="pattern">�͗l</param>
	GreenBlock(int x, int y, int pattern, bool center);

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

	void SetHit(bool hit) {

		this->hit = hit;
	}

	void SetCenter(bool center) {
		this->center = center;
	}

	//u����Ad�����Al�����Ar���E�̈�	0���F��1����
	void SetMatch(bool u, bool d, bool l, bool r, int num);

	void SetDelete(bool deleteFlag, bool doubkeMuctchFlag, bool involvement);

	void GoDeleete() { delete this; }

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	int GetPositionX() { return x; }	//X���W
	int GetPositionY() { return y; }	//Y���W
	int GetSize() { return size; }		//�T�C�Y
	int GetPattern() { return pattern; }//��
	bool GetIsDelete() { return isDelete; }//�폜�t���O
	bool GetDoubleMutch() { return doubleMutch; }	//����v�t���O
	bool GetInvolvement() { return involvement; }	//�������݃t���O
	bool GetCenter() { return center; }	//���S�t���O

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
	//�͗l  1: 2:
	int pattern = 0;
	//�������W
	int x = 0;
	int y = 0;
	//�傫��
	int size = 24;

	//�摜�\���p
	const int blockSizeX = 48;
	const int blockSizeY = 48;
	int blockHandle[6];
	//�ڑ��m�F�p�摜�n���h��
	int connectHandle[6];
	int doubleHandle[6];
	int involvementHnadle[6];

	//�ڑ�����
	bool up[2] = { false,false };
	bool down[2] = { false,false };
	bool left[2] = { false,false };
	bool right[2] = { false,false };

	//���Ŕ���
	bool isDelete = false;
	bool doubleMutch = false;	//����v����
	bool involvement = false;	//�������ݔ���

	bool center = false;
};

