#include "DxLib.h"
#include "PlayAndMakeGame.h"

static int key[256]; // �L�[��������Ă���t���[�������i�[����
#define FontSize  20
					 // �L�[�̓��͏�Ԃ��X�V����
static int gpUpdatekey() {
	char tmpkey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpkey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpkey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

int MoveToManual(int &);//�}�j���A�����ړ�����

void ShowMoveToManual(int);//�}�j���A���̈ړ��̐���

void MakeStageAboutKey();//�X�e�[�W�Â���̃L�[�̐���

void MakeStageHowTo();//�X�e�[�W�Â���̂����̐���

void PlayStageAboutKey();//�v���C���̃L�[�ɂ��Ă̐���

void PlayStageHowTo();//�v���C���̂����̐���


//�}�j���A���̂܂Ƃ�
void Manual() {
	key[KEY_INPUT_RETURN] = 2;
	int red = GetColor(255, 0, 0);//��
	int white = GetColor(-1, -1, -1);//��
	int black = GetColor(0, 0, 0);//��
	int yellow = GetColor(255, 255, 0);//���F
	int select = 1;//�I�΂�Ă���}�j���A��
	while (ScreenFlip() == 0  ) {
		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}

		ClearDrawScreen();

		DrawBox(0, 0, 650, 500, white, TRUE);
		SetFontSize(20);

		// ������̕`��

		if (MoveToManual(select) == 1) {//�}�j���A���̈ړ�
			break;
		}

		if (select == 1) {
			MakeStageHowTo();//�X�e�[�W�̍���
		}
		else if (select == 2) {
			MakeStageAboutKey();//�X�e�[�W�����Ƃ��́A�L�[�ɂ���
		}
		else if (select == 3) {
			PlayStageHowTo();//�Q�[���̂���
		}
		else if (select == 4) {
			PlayStageAboutKey();//�V�Ԏ��̃L�[�ɂ���
		}

		ShowMoveToManual(select);//�}�j���A���̈ړ��ɂ��Ă�������

		ScreenFlip();//�\������
	}
}


//�}�j���A���̈ړ��ɂ��Ă̂��Ƃ�������
//�@�@�@�@�@�@�@�@�i���̃}�j���A���j
void ShowMoveToManual(int select) {
	int black = GetColor(0, 0, 0);//��
	DrawString(10, 450, "���a�`�b�j", black);//�߂肩���̕\��
	if(select == 1)DrawString(120, 450, "�^�C�g����", black);//�^�C�g���ɖ߂��Ƃ��̕\��
	DrawFormatString(300,450,black,"%dP",select);//�y�[�W���̕\��
	DrawString(500, 450, "�d�m�s�d�q��", black);//�i�ݕ��̕\��
}


//�}�j���A�����ړ�����
//�@�@�@�@�@�@�i���̃}�j���A���j
int MoveToManual(int &select) {
	gpUpdatekey();
	if (key[KEY_INPUT_RETURN] == 1 && select < 5) {//�G���^�[�L�[�������ꂽ�Ƃ�
		select++;//�}�j���A������i�߂�
		if (select > 4)select = 1;//���E�܂Ői�߂���A�ŏ��ɖ߂�
	}
	if (key[KEY_INPUT_BACK] == 1 && select > 0) {//�o�b�N�X�y�[�X�L�[�������ꂽ�Ƃ�
		select--;//�}�j���A������߂�
		if (select < 1)return 1;//���E�܂Ŗ߂�����A���j���[��ʂɖ߂�
	}
	return 0;
}

//�X�e�[�W�Â���̐���
void MakeStageHowTo() {
	SetFontSize(FontSize);
	int x = 10;//�\������X���W
	int y = 20;//�\������Y���W
	int black = GetColor(0, 0, 0);//��
	int blue = GetColor(0, 0, 255);//��
	DrawString(x, 5, "�X�e�[�W�Â���̕��@", GetColor(255, 0, 0));
	DrawString(x, y += FontSize + 5, "�����̉�ʁE�E�E��蒆�̃X�e�[�W��\������B", blue);
	DrawString(x, y += FontSize + 5, "�E�[�̉�ʁE�E�E�X�e�[�W��ɒu�����̂�\������B", blue);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�@�@�@�����ŃN���b�N�������̂�u����悤�ɂȂ�B", blue);
	DrawString(x, y += FontSize + 5, "�����X�^�[�E�E�E�X�e�[�W��ɒu���ƁA�Q�[���J�n��ɏo������B", black);
	DrawString(x, y += FontSize + 5, "�A�C�e���E�E�E���̂܂܃X�e�[�W�ɒu�����Ƃ��ł��Ȃ����A", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�@�@�n�e�i�u���b�N�Ȃǂɓ���邱�Ƃ��ł���B", black);
	DrawString(x, y += FontSize + 5, "�u���b�N�ȂǁE�E�E�X�e�[�W��ɒu���ƃQ�[���J�n��ɏo������B", black);
	DrawString(x, y += FontSize + 5, "�H�u���b�N�E�E�E�����X�^�[���A�C�e�������̏�ɒu���ƁA", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�@�@�@�����X�^�[���A�C�e�������邱�Ƃ��ł���B", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�@�@�@�����͂����ĂȂ��Ƃ��A�R�C��������", black);
	DrawString(x, y += FontSize + 5, "�C��E�E�E�����X�^�[���A�C�e��������ƁA", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�Q�[�����ɂ��ꂪ�C�䂩��o������B", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@���������ĂȂ��Ƃ��A�R�C�����o������", black);
	DrawString(x, y += FontSize + 5, "�y�ǁE�E�E��ɕ\�������̂����̓y�ǂ̔ԍ��ŁA", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@���ɕ\�������̂��ړ���̔ԍ��ŁA", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�E�V�t�g�L�[�ňړ���͕ύX�ł���B", black);
}

//�X�e�[�W�Â���̎��̃L�[�̂���
void MakeStageAboutKey() {
	SetFontSize(FontSize);
	int x = 10;//�\���̎���X���W
	int y = 20;//�\���̎���Y���W
	int black = GetColor(0,0,0);//��
	int blue = GetColor(0, 0, 255);//��
	DrawString(x, 5, "�X�e�[�W�Â���̎��̃L�[�̐���", GetColor(255, 0, 0));
	DrawString(x, y += FontSize + 5, "�d�r�b�`�o�d�L�[�E�E�E�^�C�g���ɖ߂�", blue);
	DrawString(x, y += FontSize + 5, "�G���^�[�L�[�E�E�E�Q�[���̃v���C��ʂɈړ�����", blue);
	DrawString(x, y += FontSize + 5, "�C���T�[�g�L�[(INS)�E�E�E���X�e�[�W����i�߂�", black);
	DrawString(x, y += FontSize + 5, "�f���[�g�L�[(DEL)�E�E�E���X�e�[�W����߂�", black);
	DrawString(x, y += FontSize + 5, "�X�y�[�X�L�[�E�E�E�N���b�N�Ɠ���", black);
	DrawString(x, y += FontSize + 5, "�a�`�b�j�L�[�L�[�E�E�E�I�����Ă���ꏊ�̂��̂�����", blue);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�y�ǂ̏�ɉ����u���Ƃ��́A�����Ă��炶��Ȃ��Ɩ���", blue);
	DrawString(x, y += FontSize + 5, "���L�[�E�E�E���̕����Ɉړ�����", black);
	DrawString(x, y += FontSize + 5, "���R���g���[���L�[�{���L�[�E�E�E�����ړ�����", black);
	DrawString(x, y += FontSize + 5, "�E�R���g���[���L�[�{���L�[�E�E�E�������ړ�����", black);
	DrawString(x, y += FontSize + 5, "�r�L�[�E�E�E���̃X�e�[�W�f�[�^��ۑ�����", blue);
	DrawString(x, y += FontSize + 5, "���V�t�g�L�[�E�E�E�X�e�[�W��ʂ��A�I����ʂɈړ�����B", black);
	DrawString(x, y += FontSize + 5, "�E�V�t�g�L�[�E�E�E�y�ǂ̈ړ�������ύX����", black);
	DrawString(x, y += FontSize + 5, "Ctrl + Alt + Back�E�E�E���̃X�e�[�W��S������", blue);
	DrawString(x, y += FontSize + 5, "Ctrl + Alt + C�E�E�E���̃X�e�[�W���R�s�[����", black);
	DrawString(x, y += FontSize + 5, "Ctrl + Alt + P�E�E�E�R�s�[�����X�e�[�W�𒣂�t����", black);
}


//�ǂ�����ėV�Ԃ�
void PlayStageHowTo() {

	SetFontSize(FontSize);
	int x = 10;//�\������X���W
	int y = 20;//�\������X���W
	int black = GetColor(0, 0, 0);//��
	int blue = GetColor(0, 0, 255);//��
	DrawString(x, 5, "�v���C���@", GetColor(255, 0, 0));
	DrawString(x, y += FontSize + 5, "�ŏ��E�E�E��������̃L�[�������ƃQ�[�����n�܂�܂��B", blue);
	y += FontSize;
	DrawString(x, y += FontSize + 5, "�N���A�����E�E�E�X�e�[�W�E�[�ɂ���A", blue);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�@�@�@�S�[���̊��܂ōs���ƃS�[���ł��B", blue);
	DrawString(x, y += FontSize + 5, "�N���A��E�E�E��������̃L�[�������Ǝ��ɐi�݂܂�", blue);
	DrawString(x, y += FontSize + 5, "���s�����E�E�E�n�ʂ̌��ɗ����邩�A", blue);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�@�@���у}���I�̎��Ƀ����X�^�[�ɓ����������ł��B", blue);
	DrawString(x, y += FontSize + 5, "�Q�[���I�[�o�[�����E�E�E����̎c��O�ɂȂ�����", blue);
	DrawString(x, y += FontSize + 5, "�����K�E�E�E�X�[�p�[�}���I�ȏ�̎��A�����Ԃ���Ə����܂��B", black);
	DrawString(x, y += FontSize + 5, "�H�u���b�N�E�E�E�����Ԃ���ƁA�����Ă���̂��o�Ă��܂��B", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�@�@�@�����A�����b���͕��ʂ��x���ł��B", black);
	DrawString(x, y += FontSize + 5, "�y�ǁE�E�E���̏�ŉ����������ƁA�Ⴄ�ꏊ�Ɉړ����܂��B", black);
	DrawString(x, y += FontSize + 5, "�C��E�E�E���Ԋu�ŉ��������˂���܂��B", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�����A�����b���͕��ʂ��x���ł��B", black);
	DrawString(x, y += FontSize + 5, "���Ⴊ�ށE�E�E���Ⴊ�ނ��Ƃ͂ł��܂���B", black);
	DrawString(x, y += FontSize + 5, "�W�����v�E�E�E���̏ォ�A�����X�^�[�𓥂ނƂł��܂��B", black);
	y += FontSize + 5;

}


//�Q�[��������Ƃ��́A�L�[�̂���
void PlayStageAboutKey() {
	SetFontSize(FontSize);
	int x = 10;//�\������X���W
	int y = 40;//�\������Y���W
	int black = GetColor(0, 0, 0);//��
	int blue = GetColor(0, 0, 255);//��
	
	DrawString(x, 5, "�v���C���̃L�[�̐���", GetColor(255, 0, 0));
	DrawString(x, y += FontSize + 5, "�ړ��E�E�E���E���L�[", blue);
	DrawString(x, y += FontSize + 5, "�W�����v�E�E�E����L�[", blue);
	DrawString(x, y += FontSize + 5, "���V�t�g�L�[�{���L�[�E�E�E�_�b�V��(�s���S)", black);
	DrawString(x, y += FontSize + 5, "�E�V�t�g�L�[�E�E�E�X�[�p�[�}���I�Ȃ�}���I�e�A", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�@�@�@�t�@�C���[�}���I�Ȃ�t�@�C���[�{�[�����o��", blue);
	DrawString(x, y += FontSize + 5, "���E�R���g���[���L�[�E�E�E���Ԃ��~�߂���B", black);
	DrawString(x, y += FontSize + 5, "�@�@�@�@�@�@�@�@�@�@�@�@�@�������A�P�O�O�O�X�R�A������", black);
	DrawString(x, y += FontSize + 5, "�G�X�P�[�v�L�[�E�E�E���Q����(�X�e�[�W�Â���ƈႤ)", blue);
	DrawString(x, y += FontSize + 5, "�o�b�N�X�y�[�X�L�[�E�E�E�Q�[������߂�(�X�e�[�W�Â���ƈႤ)", blue);
	
}



