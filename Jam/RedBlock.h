#pragma once
#include "DxLib.h"

class RedBlock
{
public:
	RedBlock(int x, int y, int pattern);

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

