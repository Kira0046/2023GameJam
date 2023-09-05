#pragma once
#include "DxLib.h"
#include "RedBlock.h"
#include "GreenBlock.h"
#include "BlueBlock.h"

class GameScene {
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
	RedBlock* redBlock = nullptr;

};