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
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();
private:
	//�t�B�[���h
	int fieldHandle;
};