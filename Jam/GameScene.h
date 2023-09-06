#pragma once
#include "DxLib.h"
#include "RedBlock.h"
#include "GreenBlock.h"
#include "BlueBlock.h"
#include <list>


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

	/// <summary>
	/// �u���b�N����
	/// </summary>
	void BlockOperation();

	/// <summary>
	/// �������v�Z
	/// </summary>
	void FallingCalc();
private:
	//�����t�F�[�Y 0:�z�u�ҋ@ 1:�z�u 2:����
	int fallphase = 0;
	//�����X�V�ҋ@����
	int fallupdatetime = 60;
	//�ړ���
	int amountmovement = 48;

	//�������W
	int centerX = 0;
	int centerY = 0;

	//�����o���ʒu
	int spawnpointX = 800;
	int spawnpointY = -48;
	//��������̃u���b�N�o����
	int blockspawnsize = 24;

	//�e��u���b�N���X�g
	std::list <RedBlock*> redBlockList;
	std::list <BlueBlock*> blueBlockList;
	std::list <GreenBlock*> greenBlockList;


	// �ŐV�̃L�[�{�[�h���p
	char keys[256];
	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256];
};