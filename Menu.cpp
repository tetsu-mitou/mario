#include "DxLib.h"
#include "PlayAndMakeGame.h"

static int key[256]; // �L�[��������Ă���t���[�������i�[����

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

void MenuShow(int);//���j���[��ʂ̕\��

void SelectMakeOrPlayGame(int &, int &, int &, int &);//��邱�Ƃ�I��������

void SelectByMouce(int &, int &, int &, int &);//�}�E�X�ɂ���đI��

void SelectByKey(int &, int &);//�L�[�ɂ���đI��


//�S�̂̃��j���[�̏���
void Menu() {
	int button;//�{�^���������ꂽ���ǂ��� 
	int x;//�I������Ă���X���W
	int y;//�I������Ă���Y���W
	int select = 1;//�I������Ă���ꏊ
	while (ScreenFlip() == 0 && ProcessMessage() == 0 ){
		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}
		MenuShow(select);
		SelectByMouce(button,x,y,select);
		SelectByKey(select,button);
		SelectMakeOrPlayGame(button,x,y,select);
	}
}

//���j���[�̃f�[�^��\������
void MenuShow(int select) {
	int red = GetColor(255, 0, 0);//�ԐF
	int white = GetColor(-1, -1, -1);//���F
	int black = GetColor(0, 0, 0);//���F
	int yellow = GetColor(255, 255, 0);//���F
	int background = LoadGraph("�摜/�w�i.jpg");//�w�i�̉摜

	ClearDrawScreen();

	DrawExtendGraph(-2, -1, 650, 500, background, FALSE);
	SetFontSize(60);

	// �^�C�g���ƁA�I���̕`��
	DrawString(80, 100, "�X�[�p�[�}���I", red);
	SetFontSize(15);
	DrawString(80, 80, "���w���������", red);
	DrawString(380, 160, "�{�X�e�[�W�݌v", red);
	DrawBox(230, 290, 370, 320, yellow, TRUE);
	DrawString(240, 300, "�����ѕ��̐���", black);
	DrawBox(230, 340, 370, 370, yellow, TRUE);
	DrawString(240, 350, "�X�e�[�W�Â���", black);
	DrawBox(230, 390, 370, 420, yellow, TRUE);
	DrawString(240, 400, "�v���C�X�e�[�W", black);

	//�I�����Ă���l�p�̕`��
	DrawBox(230, 240 + select * 50, 370, 270 + select * 50, red, FALSE);

	ScreenFlip();
}


//��邱�Ƃ�I��������
//�@�@�@�@�@�@�@�@�@�@�@�i�{�^���������ꂽ���ǂ����A�I�����Ă�����W�A�I�΂�Ă�����́j
void SelectMakeOrPlayGame(int &button, int &x, int &y, int &select) {
	if (button == 1) {
		SetFontSize(16);
		if (select == 1) {
			Manual();//�}�j���A�����J��
		}
		else if (select == 2) {
			while (1) {
				if (ProcessMessage() != 0) { // ���b�Z�[�W����
					break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
				}
				MakeStage();//�X�e�[�W�Â��������
				gpUpdatekey();
				if (key[KEY_INPUT_ESCAPE] >= 1)break;//�G�X�P�[�v�L�[��������Ă���΁A��߂�
				PlayingGame();//�Q�[��������
			}
		}
		else if (select == 3) {
			PlayingGame();//�Q�[��������
		}
	}
}


//�}�E�X�ŁA��邱�Ƃ�I��
//�@�@�@�@�@�@�@�@�i�{�^���������ꂽ���ǂ����A�I�����Ă�����W�A�I�΂�Ă�����́j
void SelectByMouce(int &button, int &x, int &y, int &select) {
	button = 0;
	GetMouseInputLog(&button, &x, &y, TRUE);
	if (button == 1 && x >= 230 && x <= 370) {
		if (y >= 290 && y <= 320) {//��ԏ��I�񂾎�
			select = 1;
		}
		else if (y >= 340 && y <= 370) {//�^�񒆂�I�񂾎�
			select = 2;
		}
		else if (y >= 390 && y <= 420) {//��ԉ���I�񂾎�
			select = 3;
		}
		else button = 0;
	}
	else button = 0;
}


//�{�^���ŁA��邱�Ƃ�I��
//            �i�I�΂�Ă�����́A�{�^���������ꂽ���ǂ����j
void SelectByKey(int &select, int &button) {
	gpUpdatekey();
	if (key[KEY_INPUT_UP] %3 == 1 && select > 1) {//��̂ق���I��
		select--;
	}
	if (key[KEY_INPUT_DOWN] %3 == 1 && select < 3) {//���̂ق���I��
		select++;
	}
	if (key[KEY_INPUT_RETURN] == 1) {//�I������
		button = 1;
	}
}
