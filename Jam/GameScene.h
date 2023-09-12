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


	void BlockLayoutSetting();

	/// <summary>
	/// �u���b�N����
	/// </summary>
	void BlockOperation();

	/// <summary>
	/// �������v�Z
	/// </summary>
	void FallingCalc();

	/// <summary>
	/// �u���b�N�����v�Z
	/// </summary>
	void FallBlockCalc();

	/// <summary>
	/// �u���b�N�c������
	/// </summary>
	void FallingCollision();

	/// <summary>
	/// �u���b�N�ςݏグ����
	/// </summary>
	void PiledBlock();

	/// <summary>
	/// �S�u���b�N�Œ艻
	/// </summary>
	void SetBlockToFallFalse();

	/// <summary>
	/// �u���b�N�n�ʒ��n
	/// </summary>
	void PileBlockToLand();

	void SetBlockonLand();


	/// <summary>
	/// 
	/// </summary>
	void BlockFallProcess();

	/// <summary>
	/// �u���b�N������
	/// </summary>
	void BlockFallSetting();

	/// <summary>
	/// 
	/// </summary>
	void BlockToFall();

	void BackToReset();

private: //�\����
	//��������̃u���b�N�z�u�ʒu�@ 0:���� 1:�E�� 2:�E�� 3:����
	struct BlockLayoutPosition {
		//�z�u����u���b�N�̐F�@0:�z�u���� 1:�ԁ@2:�� 3:��
		int blocklayoutcolor = 0;
		//�z�u����u���b�N�̖͗l  1: 2:
		int blocklayoutpattern = 0;
	};

private:
	//�����t�F�[�Y 0:�z�u�ҋ@ 1:�z�u 2:�����@3:�u���b�N����
	int fallphase = 0;
	//�����X�V�ҋ@����
	int fallupdatetime = 60;
	//�u���b�N�����X�V�Ҋ�����
	int blockfallupdatetime = 10;
	//�ړ���
	int amountmovement = 48;

	//�������W
	int centerX = 0;
	int centerY = 0;

	//�����o���ʒu
	int spawnpointX = 800;
	int spawnpointY = 96;//-48;
	//��������̃u���b�N�o����
	int blockspawnsize = 24;


	//�e��u���b�N���X�g
	std::list <RedBlock*> redBlockList;
	std::list <BlueBlock*> blueBlockList;
	std::list <GreenBlock*> greenBlockList;
	//�\���̂̔z��錾
	BlockLayoutPosition blocklayoutposition[4];

	//�쐬���ꂽ�u���b�N�̌�
	int createredblock = 0;
	int creategreenblock = 0;
	int createblueblock = 0;

	bool redblocklefthit = false;
	bool redblockrighthit = false;
	bool greenblocklefthit = false;
	bool greenblockrighthit = false;
	bool blueblocklefthit = false;
	bool blueblockrighthit = false;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256];
	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256];
};