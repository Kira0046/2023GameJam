#pragma once
#include "DxLib.h"

class Menu {
public:
	//������
	void Initialize();
	//�X�V
	void Update(char *keys);
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
};
