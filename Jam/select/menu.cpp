#include "menu.h"

void Menu::Initialize() {
	//�V�[���`�F���W
	//���^�C�g�������j���[���Q�[����ʂ��l�����ď����l��1�ɂ��Ă����܂�
	//�{�ԃ����[�X����0�ɂ��Ă���
	scene = 1;
}

void Menu::Update(char *keys) {
	//�V�[���`�F���W�̃e�X�g
	if (keys[KEY_INPUT_SPACE]) {
		scene = 2;
	}
}