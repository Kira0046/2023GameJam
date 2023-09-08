#pragma once
#include "DxLib.h"

class Menu {
public:
	//������
	void Initialize(int windowWidth, int windowHeight);
	//�X�V
	void Update(char *keys,char *oldkeys);
	//�`��
	void Draw();
	//�V�[���ԍ����M
	void SendSceneNum(int num);

	//�V�[���ԍ��擾
	int GetSceneNum() {
		return scene;
	}
private:
	//�V�[���ԍ�
	int scene;
	//���j���[�o�[�n���h��
	int menuHandle[10];
	//���j���[�ԍ�
	int barNum;
	//���j���[�e���W
	int barPosX[5];
	int barPosY[5];
	//���j���[��
	const int menuNum = 5;
	//���j���[�T�C�Y
	int barSizeX;
	int barSizeY;
};
