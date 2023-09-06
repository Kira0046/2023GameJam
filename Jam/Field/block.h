#pragma once
#include "DxLib.h"

//�u���b�N���̓����f�[�^
struct BlockData {
	float posX;
	float posY;
	bool connectionStatus[8];	//�ڑ����
	bool isFall;	//�������
	bool appearingNow;	//�o������
	int color;	//�F
	int patten;	//��
};

class Block {
public:
	//������
	void Initialize(int windowWidth,int windowHeight);
	//�X�V
	void Update();
	//�`��
	void Draw();
private:


private:
	//�t�B�[���h�n���h��
	int fieldHandle;
	//�t�B�[���h���W
	int fieldPosX[2];
	int fieldPosY[2];
	//Field�T�C�Y
	int fieldSizeX;
	int fieldSizeY;

	//�u���b�N�f�[�^
	const int blockNum = 180;
	BlockData block[180];
};