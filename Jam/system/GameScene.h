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
private:
	//�ڑ���ԃ`�F�b�N
	void CheckConnect();
	void IsConnect();
	//�������݃`�F�b�N���D�揇�ʂ͒ʏ���� > ��������
	void CheckInvolvement(int num);
	//�u���b�N����
	void DeleteBlock();
	//�X�R�A���Z
	void AddScore();


private: //�\����
	//��������̃u���b�N�z�u�ʒu�@ 0:���� 1:�E�� 2:�E�� 3:����
	struct BlockLayoutPosition {
		//�z�u����u���b�N�̐F�@0:�z�u���� 1:�ԁ@2:�� 3:��
		int blocklayoutcolor = 0;
		//�z�u����u���b�N�̖͗l  1: 2:
		int blocklayoutpattern = 0;
	};

private:
	//�t�B�[���h�n���h��
	int fieldHandle;
	//�t�B�[���h���W
	int fieldPosX[2];
	int fieldPosY[2];
	//Field�T�C�Y
	int fieldSizeX;
	int fieldSizeY;
	//�g���T�C�Y
	const int fieldFlameSizeX = 6;
	const int fieldFlameSizeY = 6;


	//�����t�F�[�Y 0:�z�u�ҋ@ 1:�z�u 2:�����@3:�u���b�N����
	int fallphase = 0;
	//�����X�V�ҋ@����
	int fallupdatetime = 5;
	//�X�V����
	const int maxUpdateTime = 5;
	//�ړ���
	int amountmovement = 48;

	//�������W
	int centerX;// = 0;
	int centerY;// = 0;

	//�����o���ʒu
	int spawnpointX = 800 + 24;
	int spawnpointY;// = 48 + 6;//-48;
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

	//�ڑ�->������܂ł̑ҋ@����
	const int maxTimer = 60;
	int deleteTimer = 0;;
	bool countStart = false;;	//�J�E���g�J�n�ϐ�
	const int halfSize = 24;
	int deleteConnectNum = 1;	//������̂ɕK�v�Ȑ�
};