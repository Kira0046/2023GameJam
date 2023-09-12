#pragma once
#include "DxLib.h"

//�u���b�N���̓����f�[�^
struct BlockData {
	float posX;
	float posY;
	bool connectionStatus[8];	//�ڑ����
	bool isControl;	//������
	bool isFall;	//�������
	bool appearingNow;	//�o������
	int colorPattern;	//�F�ƕ�
	bool isDelete;	//������H
	bool doubleMutch;	//����v����
	bool involvement;	//�������ݔ���
	bool center;	//���쒆�u���b�N�̒��S
};

class Block {
public:
	//������
	void Initialize(int windowWidth,int windowHeight);
	//�X�V
	void Update(char* keys, char* oldkeys);
	//�`��
	void Draw();
	//���Z�b�g
	void AllReset();
private:
	//����
	void FallBlock(char* keys, char* oldkeys);
	//���O�̑���ǂݍ���
	void CheckOldInput();

	//�ڑ���ԃ`�F�b�N
	void CheckConnect();
	void IsConnect(int num);
	//�������݃`�F�b�N���D�揇�ʂ͒ʏ���� > ��������
	void CheckInvolvement(int num);
	//�u���b�N����
	void DeleteBlock();
	//�X�R�A���Z
	void AddScore();

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

	//�u���b�N�f�[�^
	const int blockNum = 180;
	BlockData block[180];
	//�u���b�N�̉摜�n���h��
	int blockHandle[6];
	//�u���b�N�̃T�C�Y
	const int blockSizeX = 48;
	const int blockSizeY = 48;
	//�ڑ���Ԑ�
	const int connectNum = 8;
	//�ڑ��m�F�p�摜�n���h��
	int connectHandle[6];
	int doubleHandle[6];
	int involvementHnadle[6];

	//�ڑ�->������܂ł̑ҋ@����
	const int maxTimer = 60;
	int deleteTimer;
	bool countStart;	//�J�E���g�J�n�ϐ�

	//���쒆�u���b�N�̗L���̕ϐ�
	bool isControl;

	//�X�s�[�h
	float speed;
	float level;	//���x���i�G���h���X�p�j

	//��]�p
	int rotateNum;
	float centerPos[2];	//���S�u���b�N�̍��W

	//�X�R�A
	int score;
	//�ő�X�R�A
	int hiScore;
	//���Z�X�R�A
	const int add = 20;
	const int bonus = 30;
	//�A����
	int chain;
	//�A���\�t���O
	bool canChain;
	//�폜�u���b�N�J�E���g
	int deleteBlockNum;
	int involvementBlockNum;
	//�������Ă܂���[���ăt���O
	bool isDelete;

	//�W���C�p�b�h
	int oldInput[28];	
};