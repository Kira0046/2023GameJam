#pragma once
#include "DxLib.h"

struct BlockData {
	float posX;
	float posY;
	bool connectionStatus[8];	//�ڑ����
	bool isFall;	//�������
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
	//�t�B�[���h�n���h��
	int fieldHandle;
	//�t�B�[���h���W
	int fieldPosX[2];
	int fieldPosY[2];
	//Field�T�C�Y
	int fieldSizeX;
	int fieldSizeY;
};