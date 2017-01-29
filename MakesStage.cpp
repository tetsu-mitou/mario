#include "Dxlib.h"
#include "PlayAndMakeGame.h"

//�u���b�N
#define EMPTY (0)//��
#define BRICK (1)//�����K
#define HATENA_KNOCKED (2)//��̃n�e�i�u���b�N
#define COINBLOCK (3)//�R�C���u���b�N
#define DOKANUP (4)//��̓y��
#define DOKANDOWN (5)//���̓y��
#define FLOOR (6)//�n��
#define GRASS (7)//���̂���n��
#define HALFFLAG1 (8)//����ĂȂ���
#define HALFFLAG2 (9)//���ꂽ��
#define HATENA (20)//�n�e�i�u���b�N
#define DOKANUP_MOVE (100)//�ړ��ł���y��

//�����X�^�[
#define FIREFLOWER (-3)//�t�@�C���[�t�����[
#define ONE_UP_KINOKO (-2)//�����i�b�v�L�m�R
#define SUPER_KINOKO (-1)//�X�[�p�[�L�m�R
#define COIN (0)//�R�C��
#define KURIBO (1)//�N���{�[
#define NOKONOKO (2)//�m�R�m�R
#define STOP_KORA (3)//�~�܂��Ă�b��
#define MOVE_KORA (4)//�����Ă�b��
#define TOGEZO (5)//�g�Q�]�[
#define PAKKUN (6)//�p�b�N���t�����[
#define BLACK_PAKKUN (7)//���p�b�N���t�����[
#define STOP_SPINE (8)//�����ĂȂ��g�Q
#define MOVE_SPINE (20)//�����Ă�g�Q
#define STOP_DOSSUN (9)//�~�܂��Ă�h�b�X��
#define FALL_DOSSUN (21)//�����Ă�h�b�X��
#define MOVE_TERESA (10)//�����Ă�e���T
#define STOP_TERESA (22)//�~�܂��Ă�e���T
#define KILLER (11)//�L���[
#define HODAI (100)//�C��

#define ITEM (10)//�A�C�e�����n�e�i�u���b�N���Ȃ񂩂ɓ����Ƃ��́A�A�C�e�����̗P�\

#define MONSTER (10000)




//������Ă���X�e�[�W

int makesta[26][100][25];//�X�e�[�W�S��

int dempty[26][10];//�ǂ̓y�ǂ���
int dokango[26];//�ǂ̓y�ǂ�u���Ă�����

int choicestage[100][25];//�R�s�[����X�e�[�W

int flagpoint = 90;

int key[256]; // �L�[��������Ă���t���[�������i�[����

			  // �L�[�̓��͏�Ԃ��X�V����
int gpUpdatekey() {
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

struct StageData {
	int makesta[26][100][25];
	int dempty[26][10];
	int dokango[26];
};
StageData Data;

//�摜�̃f�[�^�̃Z�b�g
void ImageDataSetToPlayGame();


//�X�e�[�W�f�[�^���J���āA�������
void OpenSave();

//�X�e�[�W�f�[�^���Z�[�u�f�[�^�ɋL������
void Save();



//�X�e�[�W�ɒu���ꂽ�u���b�N��G�̕\��

//�����X�^�[��I�ԂƂ�
void SelectMonster(int &, int &, int , int , int , int );

//�u���b�N��I�񂾎�
void SelectBlock(int &, int &, int , int , int , int );

//����u���̂���I�ԕ��̂܂Ƃ�
void SelectItem(int &, int &, int , int , int , int );

//�y�ǂ̏�ɉ����u���Ƃ�
void PutOnDokan(int , int , int , int );

//�y�ǂ�u���Ƃ�
void PutDokan(int , int , int );

//�n�e�i�u���b�N�̏�ɒu���Ƃ�
void PutOnHatenaBlock(int , int , int , int );

//�C��̏�ɒu���Ƃ�
void PutOnHodai(int , int , int , int );

//���ʂɉ�����u���Ƃ�
void PutOther(int , int , int , int );

//�u���b�N��G��u�����̃f�[�^�̌v�Z
void PutItemData(int &, int &, int &, int &, int &, int );

//�I�����Ă���ꏊ���A�E�Ɉړ�����Ƃ�
void MoveRight(int , int &, int &, int &);

//�I�����Ă���ꏊ���A���Ɉړ�����Ƃ�
void MoveLeft(int , int &, int &, int &);


//�}���I���A���E�Ɉړ�����
void MoveRightAndLeft(int &, int &, int &, int &);


//�I�����Ă���Ƃ�����A�X�e�[�W���A�A����u������I�ԉ�ʂ��Ɉړ�����
void MoveToSelectMonitor(int &, int &, int );

//�㉺�Ɉړ�����
void MoveUpAndDown(int &, int &, int );

//�y�ǂ̈ړ�����ړ�����
void ChangeDokan(int &, int , int , int );

//�X�e�[�W��̂��̂������Ƃ�
void BlockDisappear(int &, int , int );

//�X�e�[�W��̑S���ɂ��āA�ς���
void ChangeAllByKey();

//�X�e�[�W��ς���Ƃ�
void ChangeStage(int &, int &, int &);

//�N���b�N���L�[�łł���Ƃ��j
void PutThing(int &, int &);

//�L�[�{�[�h����͂����Ƃ��̓���̌v�Z
int KeyInputData(int &, int &, int &, int &, int &, int &, int &, int &);

//�}�E�X�̌v�Z
void MouseInputData(int &, int &, int &, int &, int &, int &, int &, int &, int );

//�X�e�[�W�ɂ�����̂�\������
void MakeStageImageShow(int , int );

//�����X�^�[��A�A�C�e���̕\��
void MakeStageMonsterShow(int , int , int , int , int );


//�u�����߂̃u���b�N��A�G�Ȃǂ�I�ԕ����̕\��
void MakePutItemShow(int , int );

//�X�e�[�W�Â���̎��̃f�[�^��\������
void MakeStageDataShow(int , int , int , int , int );

//�摜�╶���̑S�̂̕\��
void MakeStageShow(int , int , int , int , int , int );






//��ȕϐ��̎n�܂�ƁA�������ƁA�S�̂̂܂Ƃ�
int MakeStage() {
	int choice = 0;//����I��ł��邩
	int button = 0;//�N���b�N�������ǂ���
	int touch = 0;//�N���b�N�������́A�N���b�N�Ɠ��Ӗ��̃L�[����͂������ǂ���
	int touchX = 30;//�I������Ă���X���W
	int touchY = 120;//�I������Ă���Y���W
	int mon = 0;//�I������Ă���̂��A�����X�^�[���ǂ���
	int flagpoint = 90;//�S�[���̊��̈ʒu
	int tate = 410;//�}���I��Y���W
	int yoko = 25;//�}���I��X���W
	int pace = 2;//�L�[�𓮂�����y�[�X
	int p = 0;//�}�E�X���N���b�N�����Ƃ���X���W
	int r = 0;//�}�E�X���N���b�N�����Ƃ���Y���W
	int dselect = 0;//�y�ǂ̈ړ���̔ԍ�
	int dchosing = 0;//�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A
	int black = GetColor(0, 0, 0);//��
	int white = GetColor(-1, -1, -1);//��
	int stmove = 0;//�X�N���[�����Ă��钷��
	key[KEY_INPUT_RETURN] = 2;

	for (int h = 0; h <= 25; h++) {
		for (int i = 0; i <= 99; i++) {
			choicestage[i][h] = EMPTY;
		}
	}

	OpenSave();//�Z�[�u���J��

	ImageDataSetToPlayGame();//�摜�̃f�[�^���Z�b�g����

	while (ProcessMessage() == 0 && gpUpdatekey() == 0) {
		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}
		MakeStageShow(choice, touchX, touchY, dchosing,stmove, mon);//�\���̑S��

		MouseInputData(p, r, button, touch, dchosing, touchX, touchY, dselect,stmove);//�}�E�X�̃f�[�^��ǂݍ���

		if (KeyInputData(dchosing, dselect, touch, touchX, touchY,stmove,make,pace) == 1) {//�L�[�̃f�[�^��ǂݍ���
			break;
		}

		PutItemData(touch, touchX, touchY, choice, mon,stmove);//�����X�^�[��A�u���b�N��u��

		Sleep(30);
	}
	return 0;
}





//�摜�̃f�[�^�̃Z�b�g
void ImageDataSetToPlayGame() {
	halfFlagImg = LoadGraph("�摜/���Ԃ̊��O.png");
	marioImg = LoadGraph("�摜/�}���I����.png");
	upkinokoImg = LoadGraph("�摜/�����i�b�v���̂�.png");
	kinokoImg = LoadGraph("�摜/�L�m�R.png");
	fireflowerImg = LoadGraph("�摜/�t�@�C���[�t�����[.png");
	siroImg = LoadGraph("�摜/�l�p.png");
	brickImg = LoadGraph("�摜/�����ƃ����K.jpg");
	hatenablockImg = LoadGraph("�摜/�H�u���b�N.png");
	normalblockImg = LoadGraph("�摜/���Ȃ��u���b�N.png");
	floarImg = LoadGraph("�摜/�n��.png");
	floarupImg = LoadGraph("�摜/���u���b�N.png");
	dokanupImg = LoadGraph("�摜/�y�Ǐ�.png");
	dokandownImg = LoadGraph("�摜/�y�ǉ�.png");
	skyImg = LoadGraph("�摜/����.jpg");
	//���ʃ}���I
	jumpmarioImg = LoadGraph("�摜/�}���I�W�����v.png");
	deathmarioImg = LoadGraph("�摜/����}���I.png");
	//�X�[�p�[�}���I
	RjumpsupermarioImg = LoadGraph("�摜/�X�[�p�[�}���I�W�����v�E.png");
	LjumpsupermarioImg = LoadGraph("�摜/�X�[�p�[�}���I�W�����v��.png");
	RsupermarioImg = LoadGraph("�摜/�X�[�p�[�}���I�ӂ��E.png");
	LsupermarioImg = LoadGraph("�摜/�X�[�p�[�}���I�ӂ���.jpg");

	//�X�[�p�[�}���I
	RjumpfiremarioImg = LoadGraph("�摜/�t�@�C���[�}���I�W�����v�E.png");
	LjumpfiremarioImg = LoadGraph("�摜/�t�@�C���[�}���I�W�����v��.png");
	RfiremarioImg = LoadGraph("�摜/�t�@�C���[�}���I�ӂ��E.png");
	LfiremarioImg = LoadGraph("�摜/�t�@�C���[�}���I�ӂ���.png");

	//�}���I�I���
	coinImg = LoadGraph("�摜/�R�C��.png");
	kuriImg = LoadGraph("�摜/�N���{�[.png");
	RnokoImg = LoadGraph("�摜/�m�R�m�R�E.png");//��������
	koraImg = LoadGraph("�摜/�b��.png");
	RtogezoImg = LoadGraph("�摜/�g�Q�]�[�E.png");
	packunImg = LoadGraph("�摜/�p�b�N��.png");
	spineImg = LoadGraph("�摜/�Ƃ�.png");
	dosunImg = LoadGraph("�摜/�h�b�X��.png");
	RteresaImg = LoadGraph("�摜/�e���T�E.png");
	LteresaImg = LoadGraph("�摜/�e���T��.png");
	RtereteresaImg = LoadGraph("�摜/�Ƃ�e���T�E.png");
	LtereteresaImg = LoadGraph("�摜/�Ƃ�e���T��.png");
	blackpackunImg = LoadGraph("�摜/���p�b�N��.png");
	hodaiImg = LoadGraph("�摜/�L���[�C��.png");
	RkillerImg = LoadGraph("�摜/�L���[�E.png");
	LkillerImg = LoadGraph("�摜/�L���[��.png");
	flagImg = LoadGraph("�摜/�}���I��.png");
	castleImg = LoadGraph("�摜/��.png");
	fireballImg = LoadGraph("�摜/�t�@�C���[�{�[��.png");
}


//�X�e�[�W�f�[�^���J���āA�������
void OpenSave() {

	int i, h, g;
	//�Z�[�u�f�[�^���J��
	FILE *fp = fopen("�Z�[�u�f�[�^.dat", " r b");
	if (fp == NULL) {
		DrawFormatString(250, 250, GetColor(0, 0, 0), "�Z�[�u�f�[�^���J���܂���ł����B");
		ScreenFlip();
		WaitKey();
	}
	fread(&Data, sizeof(Data), 1, fp);
	fclose(fp);



	for (g = 0; g <= 25; g++) {//�ۑ�����Ă���X�e�[�W�f�[�^��������
		for (i = 0; i <= 99; i++) {
			for (h = 0; h <= 24; h++) {
				makesta[g][i][h] = Data.makesta[g][i][h];
			}
		}
	}
	for (i = 0; i <= 25; i++) {
		dokango[i] = Data.dokango[i];
	}
	for (h = 0; h <= 24; h++) {
		for (i = 0; i <= 9; i++) {
			dempty[h][i] = Data.dempty[h][i];
		}
	}
	//�J�����Z�[�u�f�[�^�̒l��������	
}


//�X�e�[�W�f�[�^���Z�[�u�f�[�^�ɋL������
void Save() {
	int i, h, g;

	//�X�e�[�W�̏���ݒ肷��B

	for (g = 0; g <= 25; g++) {//�f�[�^��ۑ�����Ƃ��A�n�ʂ̃u���b�N���A�f�[�^��́A��ԉ��܂œ����ɂ���
		for (h = 0; h <= 4; h++) {
			for (i = 0; i <= 99; i++) {
				if (makesta[g][i][5] < 100) {
					makesta[g][i][h] = makesta[g][i][5];
				}
				else {
					makesta[g][i][h] = DOKANDOWN;
				}
			}
		}
	}

	//�X�e�[�W�̃f�[�^���\���̂ɓ����
	for (g = 0; g <= 25; g++) {
		for (h = 0; h <= 24; h++) {
			for (i = 0; i <= 99; i++) {
				Data.makesta[g][i][h] = makesta[g][i][h];
			}
		}
	}

	//�y�ǂ̒u���ꏊ���\���̂ɓ����
	for (i = 0; i <= 24; i++) {
		Data.dokango[i] = dokango[i];
	}

	//�y�ǂ̋󂫏ꏊ���\���̂ɓ����
	for (h = 0; h <= 24; h++) {
		for (i = 0; i <= 9; i++) {
			Data.dempty[h][i] = dempty[h][i];
		}
	}

	//�\���̂�ۑ����A�ۑ���������������\������B
	ClearDrawScreen();
	DrawBox(0, 0, 650, 500, GetColor(-1, -1, -1), TRUE);
	FILE  *fp = fopen("�Z�[�u�f�[�^.dat", "wb");
	if (fp == NULL) {
		DrawFormatString(250, 250, GetColor(0, 0, 0), "�Z�[�u�ł��܂���ł����B");
	}
	fwrite(&Data, sizeof(Data), 1, fp);
	fclose(fp);
	DrawFormatString(250, 220, GetColor(0, 0, 0), "�Z�[�u���܂����B");
	ScreenFlip();
	Sleep(500);
}


//�X�e�[�W�ɒu���ꂽ�u���b�N��G�̕\��


//�����X�^�[��I�ԂƂ�
//                (����I��ł邩�A�I�񂾂̂������X�^�[���ǂ����A�N���b�N�������A�I�����Ă�����W�A�X�N���[����)
void SelectMonster(int &choice, int &mon, int touch, int touchX, int touchY, int stmove) {
	if (touch == 1 && (touchX - stmove + 30) / 30 == 19) {//�A�C�e���������X�^�[��I�񂾎�
		choice = touchY / 30 * -1 + 6;
		if (choice >= 0) {//�A�C�e����I�񂾎�
			choice = 3 - choice ;
		}
		else if (choice < - KILLER && choice >= - HODAI) {//�����Ȃ��Ƃ����I�񂾎�
			choice = EMPTY;
		}
		mon = 1;//�I�΂�Ă���̂��A�A�C�e�����Ƃ������Ƃ�\��
	}
}

//�u���b�N��I�񂾎�
//�@�@�@�@�@�@�i�I�񂾂̂������X�^�[���ǂ����A����I�񂾂��A�N���b�N�������ǂ����A�I�����Ă�����W�A�X�N���[�����j
void SelectBlock(int &mon, int &choice, int touch, int touchX, int touchY, int stmove) {
	if (touch == 1 && (touchX - stmove + 30) / 30 == 20) {//�u�����̂Ƃ��āA�u���b�N��I�񂾎�
		mon = 0;
		choice = touchY / 30 - 4 + 1;
		if (choice == 4) choice = HATENA;//�n�e�i�u���b�N��I��񂾂Ƃ�
		if (choice == 6) choice = DOKANUP;//�ړ��ł��Ȃ��y�ǂ�I�񂾎�
		if (choice == 7) choice = DOKANUP_MOVE;//�ړ�����y�ǂ�I�񂾎�
		if (choice == 8) choice = FLOOR;//�n�ʂ�I�񂾎�
		if (choice == 9) choice = GRASS;//���̂���n�ʂ�I�񂾎�
		if (choice == 10) choice = - HODAI;//�C���I�񂾎�
		if (choice == 11) choice = HALFFLAG1;//���Ԃ̊���I�񂾎�
		if ((choice > HALFFLAG1 && choice != HATENA && choice < DOKANUP_MOVE) || choice >= 1000) {//�󔒂�I�񂾎�
			choice = 0;//�����I��łȂ����ƂɂȂ�
		}
	}
}


//����u���̂���I�ԕ��̂܂Ƃ�
//�@�@�@�@�@�@�i�I�񂾂̂������X�^�[���ǂ����A����I�񂾂��A�N���b�N�������ǂ����A�I�����Ă�����W�A�X�N���[�����j
void SelectItem(int &mon, int &choice, int touch, int touchX, int touchY, int stmove) {
	SelectMonster(choice, mon, touch, touchX, touchY, stmove);//�����X�^�[��I�񂾎�
	SelectBlock(mon, choice, touch, touchX, touchY, stmove);//�u���b�N��I�񂾎�
}


//�y�ǂ̏�ɉ����u���Ƃ�
//�@�@�@�@�@�@�i����I�񂾂��A�I�񂾂̂������X�^�[���ǂ����A�u�����W�j
void PutOnDokan(int choice, int mon, int x, int y) {
	if ((choice > 0 || mon == 1 && choice < 0) && makesta[make][x][y] >= DOKANUP_MOVE) {//�y�ǂ̏�ɉ�����u���Ƃ�
		dempty[(make - 1) / 2 + 1][makesta[make][x][y] % 100 / 10] = EMPTY;//���̓y�ǂ̔ԍ�����ɂ���
		for (int i = 0; i <= 9; i++) {//�I�ׂ�y�ǂ�ς���
			if (dempty[(make - 1) / 2 + 1][i] == EMPTY) {
				dokango[(make - 1) / 2 + 1] = i;//���A�I���ł���y�ǂ�����
				break;
			}
			else if (i == 9)dokango[(make - 1) / 2 + 1] = 10;//�y�ǂ��A�P�O��葽���Ƃ��A�u���Ȃ�����
		}

	}
}


//�y�ǂ�u���Ƃ�
//�@�@�@�@�i����I�񂾂��A�u���ꏊ�̍��W�j
void PutDokan(int choice, int x, int y) {
	if (choice == DOKANUP_MOVE) {//�u���̂��A�y�ǂ̎�
		if (dokango[(make - 1) / 2 + 1] >= 10) {//�y�ǂ����łɂP�O�ȏ゠���āA�u���Ȃ��Ƃ�
			makesta[make][x][y] = DOKANUP;//���ʂ̓y�ǂɂȂ�
			choice = DOKANUP;//�I�񂾂̂��A���ʂ̓y�ǂɂȂ�
		}
		else {//�y�ǂ��A�P�O�ȉ��̎�
			makesta[make][x][y] = DOKANUP_MOVE + dokango[(make - 1) / 2 + 1] * 10;//�y�ǂɁA�y�ǂ̔ԍ�������
			dempty[(make - 1) / 2 + 1][dokango[(make - 1) / 2 + 1]] = 1;//�u�����y�ǂ̔ԍ��𖞂���
			for (int i = 0; i <= 9; i++) {
				if (dempty[(make - 1) / 2 + 1][i] == EMPTY) {
					dokango[(make - 1) / 2 + 1] = i;//���ɒu����y�ǂ̔ԍ������߂�
					break;
				}
				else if (i == 9)dokango[(make - 1) / 2 + 1] = 10;//�y�ǂ��S�����܂��Ă�����A�y�ǂ�u���Ȃ�����
			}
		}
	}
}


//�n�e�i�u���b�N�̏�ɒu���Ƃ�
//�@�@�@�@�@�@�@�@�i�u���ꏊ�̍��W�A�I�񂾂̂������X�^�[���ǂ����A����I�񂾂��j
void PutOnHatenaBlock(int x, int y, int mon, int choice) {
	if (makesta[make][x][y] >= HATENA && makesta[make][x][y] < DOKANUP_MOVE && mon == 1) {//�n�e�i�u���b�N�̏�ɒu���Ƃ�,�����X�^�[���A�A�C�e���Ȃ�A�n�e�i�u���b�N�ɓ����
		if (choice>0)makesta[make][x][y] = HATENA + choice;
		else if (choice<0)makesta[make][x][y] = HATENA + ITEM + choice*-1;
	}
}

//�C��̏�ɒu���Ƃ�
//�@�@�@�@�@�@�@�i�u���ꏊ�̍��W�A�I�񂾂̂������X�^�[���ǂ����A����I�񂾂��j
void PutOnHodai(int x, int y, int mon, int choice) {
	if (makesta[make][x][y] <= -HODAI && mon == 1) {//�C��̏�ɒu���Ƃ��A�����X�^�[���A�A�C�e���Ȃ�A�C��̒��ɓ����
		if (choice > 0)makesta[make][x][y] = -HODAI - choice;
		else if (choice < 0)makesta[make][x][y] = -(HODAI + ITEM) + choice;
	}
}


//���ʂɉ�����u���Ƃ�
//�@�@�@�@�@�@�i�u���ꏊ�̍��W�A�I�񂾂̂������X�^�[���ǂ����A����I�񂾂��j
void PutOther(int x, int y, int mon, int choice) {
	if (makesta[make][x][y] < HATENA && makesta[make][x][y] > - HODAI && choice != 0
		&& !(mon == 1 && choice > 0) && choice != -11) {//�u���ꏊ���A�C��ł��A�n�e�i�u���b�N�ł��A�y�ǂł��Ȃ��Ƃ�
		makesta[make][x][y] = choice;//�I�񂾂��̂��A�X�e�[�W�ɒu��
	}
}

//�u���b�N��G��u�����̃f�[�^�̌v�Z
//�@�@�@�@�@�@�@�i�N���b�N�������ǂ����A�I�����Ă�����W�A����I�񂾂��A�I�񂾂̂������X�^�[���ǂ����A�X�N���[�����j
void PutItemData(int &touch, int &touchX, int &touchY, int &choice, int &mon, int stmove) {


	int x = touchX / 30;//�I�����Ă���X���W
	int y = 24 - touchY / 30;//�I�����Ă���Y���W

	SelectItem(mon, choice, touch, touchX, touchY, stmove);//����u���̂���I��

	if (touch == 1 && x <= 17 + stmove / 30 - 1) {//�X�e�[�W��ɉ��������u���Ƃ�
		PutOnDokan(choice, mon, x, y);//�y�ǂ̏�ɒu���Ƃ�

		PutDokan(choice, x, y);//�y�ǂ�u���Ƃ�

		PutOnHatenaBlock(x, y, mon, choice);//�n�e�i�u���b�N�̏�ɒu���Ƃ�

		PutOnHodai(x, y, mon, choice);//�C��̏�ɒu���Ƃ�

		PutOther(x, y, mon, choice);//���ʂɂ��̂�u���Ƃ�
	}
	if (touch == 1 && (touchX - stmove + 30) / 30 == 21 && touchY / 30 == 19) {
		choice = EMPTY;//����u���̂���I�ԂƂ��ɁA�󔒂̕������N���b�N������A�����I��łȂ����ƂɂȂ�
	}
}


//�I�����Ă���ꏊ���A�E�Ɉړ�����Ƃ�
//�@�@�@�@�@�@�i�ړ�����y�[�X�A�I�����Ă���X���W�A�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A�X�N���[�����j
void MoveRight(int pace, int &touchX, int &dchosing, int &stmove) {
	if (key[KEY_INPUT_RIGHT] % pace == 0 && key[KEY_INPUT_RIGHT] != 0 && key[KEY_INPUT_LEFT] == 0) {//���{�^���͉�����ĂȂ��āA�E�{�^���������ꂽ�Ƃ�
		if ((touchX / 30 < 98 || (touchX - stmove) / 30 > 16 )&& (touchX - stmove) / 30  < 20) {//�I�����Ă���X���W���A�E�[�ɂȂ��āA����u�����̑I����ʂɂ��Ȃ��Ƃ�
			if ((touchX - stmove) / 30 > 7 && (touchX - stmove) / 30 < 17 && stmove / 30 < 98 - 16)stmove += 30;//�I�����Ă���X���W���^�񒆂��炢�ɂ���Ƃ��A�E�ɃX�N���[������
			touchX += 30;//�I�����Ă���X���W���E�Ɉړ�����
			dchosing = 0;//�y�ǂ̈ړ���̔ԍ���ς��Ă��Ȃ��Ƃ���
		}
	}
}

//�I�����Ă���ꏊ���A���Ɉړ�����Ƃ�
//          �i�ړ�����y�[�X�A�I�����Ă���X���W�A�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A�X�N���[�����j
void MoveLeft(int pace, int &touchX, int &dchosing, int &stmove) {
	if (key[KEY_INPUT_LEFT] % pace == 0 && key[KEY_INPUT_LEFT] != 0 && key[KEY_INPUT_RIGHT] == 0) {//�E�{�^���͉�����ĂȂ��āA���{�^���������ꂽ�Ƃ�
		if (touchX > 0 && (touchX - stmove) / 30 != 17) {//�I�����Ă���X���W���A���[�ɂȂ��āA����u�����̑I����ʂɂ��Ȃ��Ƃ�
			if ((touchX - stmove) / 30 < 9 && stmove > 0)stmove -= 30;//
			touchX -= 30;
			dchosing = 0;
		}
	}
}


//�}���I���A���E�Ɉړ�����
//�@�@�@�@�@�@�@�@�i�I�����Ă���X���W�A�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A�ړ�����y�[�X�j
void MoveRightAndLeft(int &touchX, int &dchosing, int &stmove, int &pace) {
	pace = 2;
	if (key[KEY_INPUT_LCONTROL] >= 1) {//���̃R���g���[���L�[�������Ă���Ƃ��A�����y�[�X�ňړ�����
		pace = 1;
	}
	else if (key[KEY_INPUT_RCONTROL] >= 1) {//�E�̃R���g���[���L�[�������Ă���Ƃ��A�������ړ�����
		pace = 3;
	}
	MoveLeft(pace, touchX, dchosing, stmove);//���Ɉړ�����
	MoveRight(pace, touchX, dchosing, stmove);//�E�Ɉړ�����
}


//�I�����Ă���Ƃ�����A�X�e�[�W���A�A����u������I�ԉ�ʂ��Ɉړ�����
void MoveToSelectMonitor(int &touchX, int &touchY, int stmove) {
	if (key[KEY_INPUT_LSHIFT] == 1) {//���V�t�g�L�[�������ꂽ�Ƃ�
		if ((touchX - stmove) / 30 < 17) {//�I�����Ă���X���W���A�X�e�[�W��ɂ���Ƃ�
			touchX = 18 * 30 + stmove;//����u������I�ԉ�ʂɈړ�����
			touchY = 4 * 30;
		}
		else  {//�I�����Ă���X���W���A����u������I�ԉ�ʂɂ���Ƃ�
			touchX = stmove;//�X�e�[�W��ʂɈړ�����
			touchY = 4 * 30;
		}
	}
}

//�㉺�Ɉړ�����
//�@�@�@�@�@�@�@�@�i�I�����Ă���y���W�A�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A�ړ�����y�[�X�j
void MoveUpAndDown(int &touchY, int &dchosing, int pace) {
	if (key[KEY_INPUT_UP] %2 == 0 && key[KEY_INPUT_UP] != 0 && key[KEY_INPUT_DOWN] == 0 && touchY / 30 > 4) {//��{�^�����������Ƃ�
		touchY -= 30;//��Ɉړ�����
		dchosing = 0;

		//����������Ƃ��A�E�{�^���ƍ��{�^����������悤�ɂȂ�
		if (key[KEY_INPUT_LEFT] >= 1)key[KEY_INPUT_LEFT] = pace;
		else if (key[KEY_INPUT_RIGHT] >= 1)key[KEY_INPUT_RIGHT] = pace;
	}
	else if (key[KEY_INPUT_DOWN] %2 == 0 && key[KEY_INPUT_DOWN] != 0 && key[KEY_INPUT_UP] == 0 && touchY / 30 < 19) {//���{�^�����������Ƃ�
		touchY += 30;//��Ɉړ�����
		dchosing = 0;

		//�����������Ƃ��A�E�{�^���ƍ��{�^����������悤�ɂȂ�
		if (key[KEY_INPUT_LEFT] >= 1)key[KEY_INPUT_LEFT] = pace;
		else if (key[KEY_INPUT_RIGHT] >= 1)key[KEY_INPUT_RIGHT] = pace;
	}
}


//�y�ǂ̈ړ�����ړ�����
//�@�@�@�@�@�@�@�i�ړ������̓y�ǂ̔ԍ��A�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A�I�����Ă�����W�j
void ChangeDokan(int &dselect, int dchosing, int touchX, int touchY) {

	if (dchosing == 1 && key[KEY_INPUT_RSHIFT] % 5 == 2) {//�E�V�t�g�L�[�������Ă���Ƃ�
		dselect++;//�ړ���������i�߂�
		if (dselect >= 10)dselect = 0;//�ړ������̔ԍ����P�O�ȏ�̎��A�ړ���̔ԍ��O�ɂ���
		makesta[make][touchX / 30][24 - touchY / 30] = makesta[make][touchX / 30][24 - touchY / 30] / 10 * 10 + dselect;
	}
}

//�X�e�[�W��̂��̂������Ƃ�
//�@�@�@�@�@�@�@�@�i�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A�I�����Ă�����W�j
void BlockDisappear(int &dchosing, int touchX, int touchY) {
	if (key[KEY_INPUT_BACK] >= 1) {//�o�b�N�X�y�[�X���������Ƃ�
		dchosing = 0;//�y�ǂ̈ړ���̔ԍ���ς��Ă��Ȃ�
		if (makesta[make][touchX / 30][24 - touchY / 30] >= 100) {//�y�ǂ������Ƃ�
			dempty[(make - 1) / 2 + 1][makesta[make][touchX / 30][24 - touchY / 30] % 100 / 10] = 0;//�����y�ǂ̔ԍ�����ɂ���
			for (int i = 0; i <= 9; i++) {
				if (dempty[(make - 1) / 2 + 1][i] == EMPTY) {
					dokango[(make - 1) / 2 + 1] = i;//�I�ׂ�悤�ɂȂ�y�ǂ�ς���
					break;
				}
				else if (i == 9)dokango[(make - 1) / 2 + 1] = 10;
			}

		}
		makesta[make][touchX / 30][24 - touchY / 30] = EMPTY;//����
	}
}

void ChangeAllByKey() {
	int i;
	int h;
	if ((key[KEY_INPUT_LCONTROL] >= 1 || key[KEY_INPUT_RCONTROL] >= 1) &&
		(key[KEY_INPUT_LALT] >= 1 || key[KEY_INPUT_RALT] >= 1)) {
		if (key[KEY_INPUT_BACK] == 1) {
			for (h = 0; h <= 24; h++) {
				for (i = 0; i <= 99; i++) {
					makesta[make][i][h] = EMPTY;
				}
			}
		}
		if (key[KEY_INPUT_C] == 1) {
			for (h = 0; h <= 24; h++) {
				for (i = 0; i <= 99; i++) {
					choicestage[i][h] = makesta[make][i][h];
				}
			}
		}
		if (key[KEY_INPUT_P] == 1) {
			for (h = 0; h <= 24; h++) {
				for (i = 0; i <= 99; i++) {
					makesta[make][i][h] = choicestage[i][h];
				}
			}
		}
	}
}


//�X�e�[�W��ς���Ƃ�
//�@�@�@�@�@�@�@�i�N���b�N�����Ƃ��A�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A������Ă���X�e�[�W�j
void ChangeStage(int &touch, int &dchosing,int &make) {
	if (key[KEY_INPUT_INSERT] == 1 && make < 24) {//�C���T�[�g�L�[���������Ƃ�
		make++;//�X�e�[�W����i�߂�
		touch = 0;
		dchosing = 0;
	}
	else if (key[KEY_INPUT_DELETE] == 1 && make > 1) {//�f���[�g�L�[���������Ƃ�
		make--;//�X�e�[�W����߂�
		touch = 0;
		dchosing = 0;
	}
}

//�N���b�N���L�[�łł���Ƃ�
//�@�@�@�@�@�@�i�N���b�N�������ǂ����A�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����j
void PutThing(int &touch, int &dchosing) {
	if (key[KEY_INPUT_SPACE] >= 1) {
		touch = 1;
		dchosing = 0;
	}
}


//�L�[�{�[�h����͂����Ƃ��̓���̌v�Z
//�@�@�@�@�@�@�@�i�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A�ړ���̓y�ǂ̔ԍ��A�N���b�N�������ǂ����A�I�����Ă�����W�A�X�N���[�����A������Ă���X�e�[�W�A�ړ�����y�[�X�j
int KeyInputData(int &dchosing, int &dselect, int &touch, int &touchX, int &touchY, int &stmove,int &make,int &pace) {

	ChangeDokan(dselect, dchosing, touchX, touchY);//�y�ǂ̈ړ���̔ԍ���ς���

	BlockDisappear(dchosing, touchX, touchY);//�u���b�N������

	ChangeStage(touch, dchosing,make);//�X�e�[�W��ς���

	MoveUpAndDown(touchY, dchosing, pace);//�㉺������

	MoveRightAndLeft(touchX, dchosing, stmove,pace);//���E�ɓ�����

	PutThing(touch, dchosing);//�N���b�N����

	MoveToSelectMonitor(touchX, touchY, stmove);//����Ă��郂�j�^�[��ς���

	ChangeAllByKey();//�X�e�[�W�S�̂ɂ��Ă��

	if (key[KEY_INPUT_S] >= 1) {//�Z�[�u����
		Save();
	}
	else if (key[KEY_INPUT_ESCAPE] == 1 || key[KEY_INPUT_RETURN] == 1) {//�X�e�[�W�Â������߂�
		return 1;
	}

	return 0;
}



//�}�E�X�̌v�Z
//�@�@�@�@�@�@�@�@�@�i�}�E�X�ɂ���Ċl���������W�A�N���b�N�������ǂ����A�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A�I�����Ă�����W�A�y�ǂ̈ړ���̔ԍ��A�X�N���[�����j
void MouseInputData(int &p, int &r, int &button, int &touch, int &dchosing, int &touchX, int &touchY, int &dselect, int stmove) {
	button = 0;//�N���b�N�������ǂ���
	GetMouseInputLog(&button, &p, &r, TRUE);//�}�E�X�̃f�[�^������
	if (button != 0) {//�N���b�N���ꂽ�Ƃ�
		dchosing = 0;//�y�ǂ̈ړ���̔ԍ���ς��Ă��Ȃ�
		touch = 1;//�^�b�`���ꂽ
		touchY = r + 120;//���W�̒���
		touchX = p + stmove;
	}
	else if (button == 0) {//�N���b�N����Ȃ������Ƃ�
		touch = 0;//�N���b�N����ĂȂ�
	}

	//�E�̃V�t�g�{�^���������ꂽ�Ƃ��A�y�ǂ̈ړ����ύX�ł���悤�ɂȂ�
	if ((touch == 1 || key[KEY_INPUT_RSHIFT] == 1) && makesta[make][touchX / 30][24 - touchY / 30] >= 100 && dchosing == 0 && dokango[(make - 1) / 2 + 1]<10) {
		dselect = 0;
		dchosing = 1;
	}
}

//�X�e�[�W�ɂ�����̂�\������
//�@�@�@�@�@�@�@�@�@�@�i�X�N���[�����A����I�񂾂��j
void MakeStageImageShow(int stmove,int choice) {


	int black = GetColor(0, 0, 0);//��
	int white = GetColor(-1, -1, -1);//��

	int i, h;
	DrawBox(0, 0, 510, 480, white, TRUE);//�����h��Ԃ�


	//��Ɗ��ƃ}���I�̍ŏ��̏ꏊ�̕\��
	DrawRotaGraph(100 + (flagpoint - 2) * 30 - stmove, 300, 1, 0.0, flagImg, TRUE);//�S�[���̊��̕\��
	DrawRotaGraph(90 + (flagpoint + 3) * 30 - stmove, 360, 1, 0.0, castleImg, TRUE);//��̕\��
	DrawExtendGraph(50 - stmove - 10, 430,	50 - stmove + 5, 430 + 20,	RsupermarioImg, TRUE);//�ŏ��̃}���I�̈ʒu�̕\��

	//�X�e�[�W�̕\��
	int x;//�\������Ƃ��̉E�[��X���W
	int y;//�\������Ƃ��̏㑤��Y���W
	int a;//�ǂ��̏ꏊ��\�����邩
	for (h = 0; h <= 24; h++) {
		for (i = stmove / 30; i <= 19 + stmove / 30; i++) {
			x = i * 30 - stmove;
			y = (20 - h) * 30;
			a = makesta[make][i][h];
			if (a == EMPTY) continue;//�����Ȃ��������A�߂�
			//�u���b�N�̕\��
			MakeStageMonsterShow(a, x, y ,0, 1);//�����X�^�[��\������
		}
	}
}

//�����X�^�[��A�A�C�e���̕\��
//�@�@�@�@�@�@�@�@�@�@�@�i�\�����邩�ǂ������ׂ�Ƃ���A������X���W�A������Y���W�A�����X�^�[��I�񂾂��ǂ����A�X�e�[�W�ɕ\�����邩�ǂ����j
void MakeStageMonsterShow(int a,int x,int y,int mon,int type) {
	int black = GetColor(0, 0, 0);

	//�u���b�N�ƖC��̕\��
	if (a >= HATENA&&a < 100)DrawExtendGraph(x, y , x + 30, y + 30, hatenablockImg, FALSE);//�n�e�i�u���b�N
	else if (a == HATENA_KNOCKED && mon == 0) DrawExtendGraph(x, y , x + 30, y + 30, normalblockImg, FALSE);//��̃n�e�i�u���b�N
	else if (a == BRICK && mon == 0) DrawExtendGraph(x, y , x + 30, y + 30, brickImg, FALSE);//�����K�u���b�N
	else if (a == COINBLOCK && mon == 0) DrawExtendGraph(x, y , x + 30, y + 30, coinImg, TRUE);//�R�C��
	else if (a == FLOOR) DrawExtendGraph(x, y , x + 30, y + 30, floarImg, TRUE);//�n��
	else if (a == GRASS) DrawExtendGraph(x, y , x + 30, y + 30, floarupImg, TRUE);//���̂���n��
	else if (a >= DOKANUP_MOVE || a == DOKANUP) DrawExtendGraph(x - 2, y , x + 32, y + 31, dokanupImg, TRUE);//��̓y��
	else if (a == DOKANDOWN) DrawExtendGraph(x, y , x + 30, y + 30, dokandownImg, TRUE);//���̓y��
	else if (a == HALFFLAG1) DrawExtendGraph(x, y , x + 30, y + 30, halfFlagImg, TRUE);//���Ԃ̊�
	else if (a <= - HODAI) DrawExtendGraph(x, y , x + 30, y + 30, hodaiImg, TRUE);//�C��

	//�G�Ȃǂ̕\��
	int b;//�n�e�i�u���b�N�ɓ����Ă���
	int c;//�C��ɓ����Ă���

	if (a < HATENA + ITEM)b = a - HATENA;
	else b = -(a - HATENA - ITEM);
	if (a > -(HODAI + ITEM))c = -(a + HODAI);
	else c = a + HODAI + ITEM;

	if ((a == -SUPER_KINOKO && mon == 1) || b == -SUPER_KINOKO || c == -SUPER_KINOKO)
		DrawExtendGraph(x, y , x + 30, y + 30 , kinokoImg, TRUE);//�X�[�p�[�L�m�R
	else if ((a == -ONE_UP_KINOKO && mon == 1) || b == -ONE_UP_KINOKO || c == -ONE_UP_KINOKO)
		DrawExtendGraph(x, y , x + 30, y + 30, upkinokoImg, TRUE);//�����i�b�v�L�m�R
	else if ((a == -FIREFLOWER && mon == 1) || b == -FIREFLOWER || c == -FIREFLOWER)
		DrawExtendGraph(x, y , x + 30, y + 30, fireflowerImg, TRUE);//�t�@�C���[�t�����[
	else if (a == - KURIBO || b == -KURIBO || c == -KURIBO) DrawExtendGraph(x, y , x + 30, y + 30, kuriImg, TRUE);//�N���{�[
	else if (a == - NOKONOKO || b == -NOKONOKO || c == -NOKONOKO) DrawExtendGraph(x, y, x + 30, y + 30, RnokoImg, TRUE);//�m�R�m�R
	else if (a == -STOP_KORA || b == -STOP_KORA || c == -STOP_KORA) DrawExtendGraph(x, y , x + 30, y + 30, koraImg, TRUE);//�~�܂��Ă���b��
	else if (a == -MOVE_KORA || b == -MOVE_KORA || c == -MOVE_KORA) DrawExtendGraph(x, y , x + 30, y + 30, koraImg, TRUE);//�����Ă���b��
	else if (a == -TOGEZO || b == -TOGEZO || c == -TOGEZO) DrawExtendGraph(x, y , x + 30, y + 30, RtogezoImg, TRUE);//�g�Q�]�[
	else if (a == -PAKKUN || b == -PAKKUN  || c == -PAKKUN) DrawExtendGraph(x, y , x + 30, y + 30, packunImg, TRUE);//�p�b�N���t�����[
	else if (a == -BLACK_PAKKUN || b == -BLACK_PAKKUN || c == -BLACK_PAKKUN) DrawExtendGraph(x, y , x + 30, y + 30, blackpackunImg, TRUE);//�u���b�N�p�b�N���t�����[
	else if (a == - STOP_SPINE|| b == -STOP_SPINE || c == - STOP_SPINE) DrawExtendGraph(x, y , x + 30, y + 30, spineImg, TRUE);//�g�Q
	else if (a == - STOP_DOSSUN || b == - STOP_DOSSUN|| c == - STOP_DOSSUN) DrawExtendGraph(x, y , x + 30, y + 30, dosunImg, TRUE);//�h�b�X��
	else if (a == -MOVE_TERESA || b == - MOVE_TERESA || c == - MOVE_TERESA) DrawExtendGraph(x, y , x + 30, y + 30, RteresaImg, TRUE);//�e���T
	else if (a == -KILLER || b == - KILLER || c == - KILLER) DrawExtendGraph(x, y , x + 30, y + 30, RkillerImg, TRUE);//�L���[

	//�����̕\��
	if (a >= DOKANUP_MOVE && type == 1) {//�y�ǂ̔ԍ��ƁA�ړ���̕\��
		DrawFormatString(x + 11, y - 20, black, "%d", a % 100 / 10);//���̓y�ǂ̔ԍ�
		DrawFormatString(x + 7, y - 5, black, "��");
		DrawFormatString(x + 11, y + 10, black, "%d", a % 10);//�ړ���̔ԍ�
	}
	else if (a >= DOKANUP_MOVE && type == 0) {//�y�ǂ́A���̖��
		DrawFormatString(x + 7, y + 10, black, "��");
	}
	else if (a == -MOVE_KORA || b == - MOVE_KORA || c == - MOVE_KORA) {//�ړ�����b���́A�ړ����邱�Ƃ��������
		DrawFormatString(x + 7, y + 5, black, "��");
	}
}




//�u�����߂̃u���b�N��A�G�Ȃǂ�I�ԕ����̕\��
//�@�@�@�@�@�@�@�@�@�i����I��ł��邩�A�I��ł���̂������X�^�[���ǂ����j
void MakePutItemShow(int choice ,int mon) {

	int black = GetColor(0, 0, 0);//��
	int white = GetColor(-1, -1, -1);

	DrawBox(510, 0, 640, 500, white, TRUE);//�I�΂�镔���𔒂��h��Ԃ�

	int x = 570;//���[�̍��W
	int a;//�\���������
	for (int i = 1; i <= 11; i++) {
		if (i == 4) a = HATENA;//�n�e�i�u���b�N��I��񂾂Ƃ�
		else if (i == 6) a = DOKANUP;//�ړ��ł��Ȃ��y�ǂ�I�񂾎�
		else if (i == 7) a = DOKANUP_MOVE;//�ړ�����y�ǂ�I�񂾎�
		else if (i == 8) a = FLOOR;//�n�ʂ�I�񂾎�
		else if (i == 9) a = GRASS;//���̂���n�ʂ�I�񂾎�
		else if (i == 10) a = -HODAI;
		else if (i == 11) a = HALFFLAG1;//���Ԃ̊���I�񂾎�
		else a = i;
		MakeStageMonsterShow(a, x, (i - 1) * 30 , 0,0);//�I�Ԃ��̂̕\��
	}

	//�u�����̂�I�ԂƂ���̃u���b�N�̕\��

	
	
	x = 540;//���[�̍��W
	for (int i = -3; i <= 11; i++) {
		if (i <= 0) {//�A�C�e����I�Ԏ�
			a = 3 + i;
		}
		else if (i < -11 && i >= -100) {//�����X�^�[��I�Ԏ�
			a = 0;
		}
		else a = -i;

		MakeStageMonsterShow(a, x, (i + 2) * 30, 1, 0);//�I�Ԃ��̂̕\��
	}
	//�u�����̂�I�ԂƂ���̓G�Ȃǂ̕\��


	//����I�����Ă��邩�̕\��
	DrawString(20 * 30 - 3, 15 * 30 - 30, "�I��", black);
	DrawBox(20 * 30 - 5, 15 * 30 - 5, 20 * 30 + 30 + 5, 15 * 30 + 30 + 5 , black, FALSE);//�I�����Ă�����̂��͂��l�p
	if (choice == 0) {
		DrawLine(20 * 30 - 5, 15 * 30 - 5, 20 * 30 + 30 + 5, 15 * 30 + 30 + 5, black, 1);//�����I��łȂ��Ƃ��A�ΐ���\������
	}
	else {
		MakeStageMonsterShow(choice, 20 * 30, 15 * 30, mon,0);//�I�񂾂��̂̕\��
	}

	DrawLine(510, 0, 510, 600, black);//�X�e�[�W�Ƃ̋�؂�̕\��
}



//�X�e�[�W�Â���̎��̃f�[�^��\������
//�@�@�@�@�@�@�@�@�@�@�i����I��ł��邩�A�I�����Ă�����W�A�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A�X�N���[�����j
void MakeStageDataShow(int choice, int touchX, int touchY, int dchosing, int stmove) {
	int black = GetColor(0, 0, 0);

	DrawBox(touchX / 30 * 30 - stmove + 1, (touchY / 30 - 4) * 30 + 1, (touchX / 30 + 1) * 30 - stmove - 1, (touchY / 30 - 3) * 30 - 1, GetColor(0, 0, 255), FALSE);
	DrawBox(touchX / 30 * 30 - stmove, (touchY / 30 - 4) * 30, (touchX / 30 + 1) * 30 - stmove, (touchY / 30 - 3) * 30, GetColor(0, 0, 255), FALSE);
	DrawBox(touchX / 30 * 30 - stmove + 1, (touchY / 30 - 4) * 30 + 1, (touchX / 30 + 1) * 30 - stmove - 1, (touchY / 30 - 3) * 30 - 1, GetColor(0, 0, 255), FALSE);
	DrawFormatString(0, 0, black, "%d - %d �@%d�X�e�[�W", ((make - 1) / 2) / 3 + 1, ((make - 1) % 6) / 2 + 1, 2 - make % 2);
}


//�摜�╶���̑S�̂̕\��
//�@�@�@�@�@�@�@�@�i����I��ł��邩�A�I�����Ă�����W�A�y�ǂ̈ړ���̔ԍ���ς��Ă��邩�ǂ����A�X�N���[�����A�I��ł���̂������X�^�[���ǂ����j
void MakeStageShow(int choice, int touchX, int touchY, int dchosing, int stmove, int mon) {

	ClearDrawScreen(); // ��ʂ�����

					   //�X�e�[�W��ɂ���G��u���b�N�̕\��
	MakeStageImageShow(stmove,choice);

	//�X�e�[�W��ɂ��ꂩ��u�����̂�I�Ԃ��̂̕\��
	MakePutItemShow(choice ,mon);

	//�X�e�[�W�Â���̎��́A�f�[�^�̕\��
	MakeStageDataShow(choice, touchX, touchY, dchosing, stmove);

	ScreenFlip();
}

