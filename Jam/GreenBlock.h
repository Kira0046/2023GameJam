#pragma once
#include "DxLib.h"

class GreenBlock
{
public:
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
	int size;
};

