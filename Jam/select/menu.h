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
	//�o�ꏈ���E�ޏꏈ��
	void InOutTitle();
	void InOutMenu();

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
	//����\�܂ł̃^�C�}�[
	int coolTimer[5];
	int moveStartTimer;	//��C�ɗ�������̂ł͂Ȃ�����������邽�߂̃^�C�}�[
	bool moveStart[5];	//�o��t���O
	bool endMove[5];	//�ޏ�t���O
	bool startorEnd;	//�o��ޏ�ǂ����Ȃ̂����ʗp
	int startCounter;
	//����\��
	bool canControl;

	//�L�����Z��
	int cancelHandle[2];
	//���W
	int cancelPos[2];
	//�T�C�Y
	int cancelSize[2];

	//��ʃT�C�Y�A���ł��g���̂Ŋi�[
	int winWidth;
	int winHeight;

	//�w�i
	int backHandle01[5];
	int backHandle02[5];
	int backPosX[2];
	const int backSizeX = 1600;

	//�^�C�g��
	int logoHandle;	//�摜�f�[�^�i�[�n���h��
	int logoPosX;	//X���W
	int logoPosY;	//Y���W
	int logoSizeX;	//X�T�C�Y
	int logoSizeY;	//Y�T�C�Y
	bool logoMoveStart;	//�o��t���O
	int logoCoolTimer;	//�o�ߎ���
	bool logoEndMove;	//�ޏ�t���O

	//�i�r
	int naviTitleHandle[2];
	int naviTitlePosX;
	int naviTitlePosY;
	int naviTitleSize[2];
	int blinkingTimer;
	int blinkingCount;

	//�W���C�p�b�h
	int oldInput[2];	//�Ƃ肠�����㉺
};
