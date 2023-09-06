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

private:
	//�͗l
	int pattern = 0;
	//�������W
	int x = 0;
	int y = 0;
	//�傫��
	int size = 24;
};

