#include "DxLib.h"
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

#define ITEM (10)

#define MONSTER (10000)//�����X�^�[�̌��E��





int Key[256]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

struct stagedata {
	int makesta[26][100][25];
	int dempty[26][10];
	int dokango[26];
};
stagedata Data;

static int stage[100][25];//�v���C���̃X�e�[�W�́A����p�B
//�P�̓����K�A2�͋�́H�u���b�N�A�R�̓R�C���A4�͏�̓y�ǁA5�͉��̓y�ǁA6�͒n�ʁA7�͑�������n�ʁA20�ȏ�100�����́H�u���b�N�A100�ȏ�͈ړ��̓y��

static int dstage[26][100][25];//�S�X�e�[�W��ۑ�����

static int bulletY[200];//�e��Y���W
static int bulletX[200];//�e��X���W
static int Bside[200];//�e�̌���
static double Bnuton[200];//�e�̏d��
static int Btype[200];//�e�̎��


static int Mtype[MONSTER];//�����X�^�[�̎��
//-3�̓t�@�C���[�t�����[�A-2�̓����i�b�v�L�m�R�A-1�̓X�[�p�[�L�m�R�A0�̓R�C���A1�̓N���{�[�A2�̓m�R�m�R�A3�͎~�܂��Ă���b���A4�͓����b���A
//5�̓g�Q�]�[�A6�̓p�b�N���t�����[�A7�͍��p�b�N���t�����[�A�W�͓����Ȃ��Ƃ��A9�͗����Ă��Ȃ��h�b�X���A10�͕��ʂ̃e���T�A20�͏オ���Ă����Ƃ��A
//21�͗����Ă���h�b�X���A22�͏Ƃ�e���T�A100�ȏ�͖C��

static int monMove[MONSTER];//�����X�^�[�̓�������
static int monY[MONSTER];//�����X�^�[��Y���W
static int monX[MONSTER];//�����X�^�[��X���W
static int crol[MONSTER];//������
static int monSide[MONSTER];//�����X�^�[�̌���
static int monTime[MONSTER];//�����X�^�[�̈ړ�
static int monEnd[MONSTER];//�����X�^�[������ł��邩�ǂ���
static int monHP[MONSTER];//�����X�^�[��HP
//�����X�^�[�̕\��


int black = GetColor(0, 0, 0);//��
int white = GetColor(-1, -1, -1);//��





//�v���g�^�C�v�錾�n�܂�



//�摜�̃f�[�^�̃Z�b�g
void ImageDataSetToMakeStage();

//���ׂĂ̕ϐ��̏�����
void FirstPlayDataSet(int &, int &, int &, long &, int &, int &, int &, int &, int &, double &, double &, double &,
	int &,int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, 
	int &, int &, int &,int &, int &, int &, int &, int &, int &, int &);


//�����X�^�[�̃f�[�^�̏�����
void MonsterPlayDataSet(int &);

//�e�̏�����
void BulletPlayDataSet(int &);

//�X�e�[�W�f�[�^�̑���
void StagePlayDataSet(int &, int , int , int );

//�����X�^�[���o��������
void MonsterAppear(int &, int , int , int , int);

//�X�e�[�W��Ƀ����X�^�[���o��������
void MonsterAppearOnStage(int &);

//�y�ǂɓ����Ĉړ�����
void DokanMove(int , int &, int &, int &, int &, int &, int &, int &, int );

//�}���I���A�y�ǂɂ���Ĉړ�����
void MarioMovedByDokan(int &, int &, int &, int &, int &, int &, int &, int &, int &,
	int &, int , int );

//�v���C����Ƃ��̃X�^�[�g���
int GameStartShow(int , int &, int &, int &, int &, int &, int &, int &, int &,int &, int &, int&);

//�N���A�����Ƃ��̃f�[�^�̏�����
void DataSetByClear(int , int &, int &, int &, int &, int &, int &);

//���񂾂��Ƃɂ���Ă��鏉����
void DataSetByDeath(int &, int , int &, int &, int &, int &, int &);

//���Ԃ̊��ɂ���Ĉړ�����
void MoveByFlag(int , int , int , int , int , int , int &, int &, int &, int &);

//������Ԃ̃}���I�̏ꏊ�̐ݒ�
void MarioPointDataSet(int , int , int , int , int &, int &, int &, int &);


//�X�e�[�W�̃f�[�^���Z�b�g����
void StageDataSet(int &, int , int , int , int );


//���񂾌�̏�����
int SecondPlayDataSet(int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &,
	int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, 
	int &, int &, int &, int &, int &, int &);

//�}���I���R�C���ɐG�ꂽ�Ƃ�
void CoinGet(int , int , int , int , int , int &, int &);

//�}���I�����Ԃ̊��ɐG�ꂽ�Ƃ�
void FlagGet(int &, int &, int &, int , int &, int ,
	int &, int &, int &, int &, int &);


//�e������
void BulletDisappear(int , int &, int );

//�e���ړ�����
void BulletMove(int , int &, int );


//�t�@�C���[�{�[���������X�^�[�ɓ���������
int FireTouchMonster(int , int , long &, int &, int );

//�t�@�C���[�{�[�����n�ʂɓ���������
int FireTouchFloor(int , double , int );

//�t�@�C���[�{�[���������Ȃ��Ȃ鎞
int FireMoveStop(int, int , int , int , int &, int &, int , long &, double );

//�t�@�C���[�{�[��������
void FireMove(int , int , int &, long &, int &);

//�e�̏����S��
void BulletDataChange(long &, int &, int &, int &);

//�����X�^�[�������Ƃ�
int MonsterDelete(int &, int &);

//�e�������X�^�[�ɓ���������
void BulletAttackMonster(int , int &, int );

//�����X�^�[��������Ƃ�
int MonsterFall(int , int , int );

//�L���[���ړ�������
void KillerGo(int );

//�Ƃ����A��~��������������ς���
void SpineChange(int , int , int ,int);

//�Ƃ�����ɏオ��
void SpineUp(int , int , int , int , int , int &);


//�h�b�X���̓��Ƀh�b�X�������邩�ǂ���
int DossunHeadTouch(int , int );

//�h�b�X�����A��ɏオ�邩�A���ɗ�����悤�ɕς�邩
void DossunUpOrChange(int , int , int , int );

//�h�b�X����������Ƃ�
void DossunFall(int , int );

//�C�䂪�����X�^�[���o��������
void MosterAppearByHodai(int , int &, int );


//�C�䂪�����X�^�[���o�������鎞�ԂȂ�
void HodaiCreate(int , int , int , int , int , int , int &, int &, int );


//�ړ����Ă���b���Ƀu���b�N������������
void KoraTouchBlock(long &, int &, int &, int &, int , int , int , int );



//�����X�^�[���u���b�N�ɓ���������
void MonsterTouchBlock(int , long &, int &, int &, int &, int &);


//�����X�^�[���ق��̃����X�^�[�ɓ���������
int MonterTouchOtherMonster(int , int , long &, int &);

//�C��ɓ����������A������ς���
int MonsterTouchHodai(int , int);

//�����X�^�[�������Ƃ�
void MonsterMove(int , int &, int , int ,int,int);

//�b����������Ƃ�
void KoraDisappear(int , int );

//�}���I���A�C�e�����l�������Ƃ�
void MarioLevelUp(int , int &, int &, int &, int &, int &, int &, int &, long &);

//�����X�^�[���}���I�ɓ���������
void MonsterTouchMario(int , int &, int &, int &, int &, int &, int &, int &, int &, long &);

//�}���I�������X�^�[�𓥂񂾎�
int  MarioStampMonster(long &, double , double , double , int & , int &, int &, int &,
	int &, int &, int &, int &, int &, int &, int , int );

//�e���T���e���T�ɓ���������
int TeresaTouchTeresa(int , int &, int , int , int , int );

//�e���T�����ɓ���
void TeresaMoveX(int , int , int , int , int &, int &, int , int , int &);


//�e���T���c�Ɉړ�����
void TeresaMoveY(int , int , int , int , int , int , int &, int &, int &);


//�e���T������
void TeresaMoveToMario(int , int , int , int , int &, long&, int &);


//�e���T���A�������Ƃ�Ă����ԂɂȂ邩
void TeresaTypeChange(int , int , int );

//�e���T�ɂ��Ă̂���
void AboutTeresa(int , int , int , int , int &, long&, int &);


//�����X�^�[�ɂ��Ă̑S���̏���
void MonsterDataSet(int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &,
	int &, int &, int &, int &, double &, double &,
	double &, long &, int &, int &, int &, int &, int ,int);
//�����܂œG�̏���




//�}���I�̉E���ɏ�Q�����Ȃ��i�ނƂ�
void MarioRightMoveSafely(int , int , int &, int &);

//�}���I�̉E���Ƀu���b�N�����邩�ǂ���
int  MarioRightMoveStopByBlock(int , int , int , int , int );


//�}���I�̉E���ɖC�䂪���邩�ǂ���
int MarioRightMoveStopByHodai(int , int , int , int , int );


//�}���I���E�ɓ����邩�ǂ���
void MarioRightMoveStop(long &, int &, int &, int &, int &, int &, int &, int , int &,
	int , int , int , int , int &, int &, int &, int &, int &);

//�E�ɓ�������̂܂Ƃ�
void MarioRightMove(long &, int &, int &, int &, int &, int &,
	int , int &, int, int &, int &, int , int &, int &, int , int , int ,
	int , int , int , int , int &, int &, int &, int &);

//�E�֐i�ޓ���



//���ɁA��Q�����Ȃ��i�ނƂ�
void MarioLeftMoveSafely(int &, int , int );

//�}���I�ɍ��Ƀu���b�N�����邩�ǂ���
int  MarioLeftMoveStopByBlock(int , int , int , int , int );

//�}���I�̍����ɖC�䂪���邩�ǂ���
int MarioLeftMoveStopByHodai(int , int , int , int , int );

//�}���I�����ɓ����邩�ǂ���
void MarioLeftMoveStop(int &, int &, int &, int &, int &, int , int &, int , int &,
	int &, int &, int &, int &, int &, int &, int &);

//�}���I�����ɓ�������̂܂Ƃ�

//�E�ɓ�������ƍ��ɓ�������̂܂Ƃ�
void LeftAndRightMove(long &, int &, int &, int &, int &, int &,
	int , int &, int , int &, int &, int , int &, int &, int , int , int , int , int , int , int &,
	int &, int &, int &);


//�}���I���C��ɗ����Ă��邩�ǂ���
int  MarioTouchToHodai(int , int , int , int , int , int );


//�}���I���n�ʂɗ����Ă��邩�ǂ���
int MarioTouchFloor(int , int , int , int , int );

//�}���I��������Ƃ�
void MarioFall(int , int &, int , int &, int &, int , int , int &, int &, int &, int &,
	int &, int &, long &, double & , double & , double &, int &, int , int , int &, int &,
	int &, int &);

//�}���I���W�����v����Ƃ��́A�f�[�^���Z�b�g����
void MarioJumpStartDataSet(double &, double &, double &, int &, int &, int &, double );

//�}���I���A�����X�^�[�𓥂ނ��ƂŃW�����v����Ƃ�
int MarioJumpStartOnMonster(long &, double &, double &, double &, int &, int &, int &, int &,
	int &, int &, int &, int &, int &, int &, int , int );


//�}���I���W�����v���n�߂�
void MarioJumpStart(long &, int &, int &, int &, int &, double &, double &, double &, int &,
	int &, int , int &, int &, int &, int , int &, int , int , int , int &,
	int &, int &, int &, int );


//�n�ʂɂ��āA�W�����v����߂�Ƃ�
int MarioJumpStop(int , int &, int , int , int , int &, int &);


//�P�t���[�����̃W�����v�����I������Ƃ�
int OneFrameJumpEnd(int , int , int , double , double );


//�W�����v���̍ŏ��̃f�[�^����
void MarioJumpDataSet(double &, double , double , int &, int &, int &, int &, int , int );


//�}���I�̃W�����v���̏����̂܂Ƃ�
void MarioJumping(long &, int &, int & , int &, int , int &, int &, int &, double &, double &,
	double &, int &, int &, int &, int &, int &, int &,
	int &, int &, int , int &, int &, int , int , int &, int , int , int , int &,
	int &, int &, int &);

//�ړ��H���I���


//�y�ǂɓ��邩�ǂ���
void DokanGetIntoStart(int &, int &, int &, int &, int &, int , int , int , int , int ,
	int , int );


//�}���I���y�ǂɂ͂��蒆�̎�
int DokanGettingInto(int &, int &, int , int , int );

//�y�ǂɓ���Ƃ��̏����̂܂Ƃ�
int  DokanGetInto(int &, int &, int &, int &, int &, int &, int , int , int , int , int ,
	int , int , int , int );


//�y�ǂ���o��
void DokanGetOut(int &, int&, int &, int );


//�{�^���������āA�X�e�[�W��ς�����A��߂��肷��
int StageChange(int &, int &, int &, int &, int &, int &, int &, int &, int &, int & ,int &);

//�{�^���������āA���ł���
void MarioKillMyself(int &, int &);

//�{�^���������āA�X�R�A������āA���Ԃ��~�߂����ǂ���
void TimeStop(int &, long &);

//�}���I������ł���Ƃ�
int  MarioDying(int &, int , int &, int , int &);


//�}���I���_���[�W���󂯂��Ƃ�
int MarioDamage(int &, int &, int &, double &, int &, int &, int &, int &, int &, int &,
	int );
//�n�e�i�u���b�N�̏�ɂ���ז��ȃ����X�^�[���ǂ���
void MonsterUpByBlock(int,int,int);

//�}���I�̓����u���b�N�ɓ���������
void MarioHeadHitBlock(int , int , int , int , int , int &, int &);

//�}���I���N���A�����Ƃ�
int  MairoGameClear(long &, double &, int &, int &, int &, int &, int &, int , int , int ,
	int &, int , int , int , int );



//�Z�[�u�f�[�^��ǂݍ���
void SaveInput();

//�e���o��������
void BulletAppear(long &, int &, int , int , int , int , int , int , int );



//�����X�^�[�ƃA�C�e����\������
void PlayStageMonsterShow(int , int );

//�u���b�N��\������
void PlayStageBlockShow(int , int , int);

//�}���I�ƁA�S�[���̊��ƁA��̕\��
void PlayStageMarioShow(int ,int , int , int , int , int , int , int , int , int , int ,int );

//���̑��̂��̂�\������
void PlayStageOtherShow(int , int , int , int , int , int , int , int ,
	int , int , int );

//�\���ɂ��Ă̂܂Ƃ�
void PlayStageShow(int , int , int , int , int , int , int , int , int , int , int ,
	int , int , int , int , int ,int);
//���ʂ܂ł́A�Q�[���̃��[�v
void PlayingGameByDeath(int &, int &, int &, int &, int &, int &, int &, int &, int &, int & , int &, int &, int &, long &,
	int &, int &, int &, int &, int &, double &, double &, double &, int &, int &, int &, int &, int &, int &,
	int &, int &, int &, int &, int &, int &, int &, int &, int &,
	int &, int &, int &);




//�v���g�^�C�v�錾�I���








//�S�̂̂܂Ƃ�
void PlayingGame() {
	int mario;//�}���I�̎c��
	int coin;//�R�C����
	int mon;//�����X�^�[�̑���
	long score;//�X�R�A
	int flagpoint;//�S�[���̊��̏ꏊ
	int count ;//����
	int clear;//�N���A�������ǂ���
	int dpla;//������ꏊ�����C���X�e�[�W���T�u�X�e�[�W��
	int stmove;//�ǂ�قǃX�N���[�����Ă��邩
	double nuton;//�d�͉����x�ɂ���ĕύX���Ă����āA��񕪂̃W�����v�̍�����\��
	double nutonLV;//�d�͉����x
	double nutonmax;//�d�͉����x�́A���߂̒l
	int stop;//���Ԃ��~�܂��Ă��邩�ǂ���
	int last;//���낢��ȁA����
	int place;//���v���C���Ă���X�e�[�W
	int dokanchange;//�y�ǂňړ����Ă��邩�ǂ���
	int dokan;//�ړ���̓y�ǂ̔ԍ�
	int black;//��
	int white;//��
	int marioLV;//�}���I�̏�ԁB�P�̎��A���у}���I�A�Q�̎��A�X�[�p�[�}���I�A�R�̎��A�t�@�C���[�}���I
	int moving;//�X�N���[�����邩�ǂ���
	int superplus;//���у}���I���A�X�[�p�[�}���I��A�t�@�C���[�}���I�ɂȂ������ɁA�}���I��Y���W�̕���ǉ�����
	int bullet;//���A�X�e�[�W�ɂ���e�̑��� - 1
	int num;//���A�X�e�[�W�ɂ��郂���X�^�[�̑��� - 1
	int jump;//�W�����v���Ă��邩�ǂ���
	int marioDirection;//�}���I�̌���
	int MariowideX;//�}���I�̉��̕�
	int MariowideY;//�}���I�̏c�̕�
	int move;//�ړ��ł��邩�ǂ���
	int end;//�}���I���A�_���[�W���󂯂����ǂ���
	int marioY;//�}���I�̏㑤��Y���W
	int marioX;//�}���I�̍�����X���W
	int monWide;//�����X�^�[�̕�
	int monstop;//�����X�^�[�������Ă��邩�ǂ���
	int Ydokan;//�ړ���̓y�ǂ�X���W
	int Xdokan;//�ړ���̓y�ǂ�Y���W
	int dying;//�}���I������ł��邩�ǂ���
	int suke;//�}���I�̖��G����
	int jumping;//�����X�^�[�ɂ���ăW�����v�������ǂ���,���ݗ��R�́A���ʂ̃W�����v�́A��{�^���������ĂȂ��ƁA�W�����v����߂Ă��܂�����
	int flag;//���Ԃ̊����l���������ǂ���
	int flagStage;//���Ԃ̊����l�������Ƃ���̏ꏊ,���C���X�e�[�W���A�T�u�X�e�[�W��
	int flagX;//���Ԃ̊����l�������Ƃ���́AX���W
	int flagY;//���Ԃ̊����l�������Ƃ��́AY���W
	

	ImageDataSetToMakeStage();//�摜�f�[�^��ǂݍ���

	SaveInput();//�Z�[�u�f�[�^��ǂݍ���

	FirstPlayDataSet(mario, coin, mon,  score, flagpoint, count, clear, dpla, stmove, nuton, nutonLV, nutonmax, stop, last,  place,
		dokanchange, dokan, black, white, marioLV, moving, superplus, bullet, num, jump, marioDirection, MariowideX, MariowideY, move, end, monWide,
		flag,flagStage,flagX,flagY);//�ŏ��̏�����

	//���񂾂Ƃ��̃��[�v
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}

		int check = SecondPlayDataSet(dying, count, stop, move, dokanchange, dokan, coin, superplus, clear, monstop, flagpoint, marioLV, num, bullet, end, mario, place,
			marioImg, marioY, marioX, stmove, moving, dpla, Xdokan, Ydokan, suke ,jumping, MariowideX,flag,flagStage,flagX,flagY);
		//�f�[�^�̃Z�b�g

		if (check == 1)break;//�o�b�N�X�y�[�X��������Ă����A�Q�[������߂�
		else if (check == 2)continue;//�X�e�[�W���ړ����Ă����A�Q�[������蒼��

		PlayingGameByDeath(mario,num,bullet,dpla,flagpoint,stmove,dying,marioY,marioX, marioDirection,jump,marioLV,suke,score,
			coin,place,Ydokan,Xdokan,superplus,nutonmax,nutonLV,nuton,stop,MariowideX,MariowideY,moving,move,monWide,
			monstop,last,jumping,end,dokan,dokanchange,count,clear, flag,flagStage, flagX, flagY);//���ʂ܂ŃQ�[��������

		if (Key[KEY_INPUT_BACK] >= 1) {//��߂�Ƃ�
			break;
		}
		//�Q�[�����̃��[�v
		Sleep(1000);
	}
	//���񂾎��̂��߂̃��[�v
	ClearDrawScreen();
	DrawFormatString(250, 200, white, "GAME OVER");
	Sleep(1000);
	WaitKey();
}




//�摜�̏�����
void ImageDataSetToMakeStage() {
	beforeHalfFlagImg = LoadGraph("�摜/���Ԃ̊��O.png");
	AfterHalfFlagImg = LoadGraph("�摜/���Ԃ̊���.png");
	backgroundImg = LoadGraph("�摜/�w�i.jpg");
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
	RmovemarioImg1 = LoadGraph("�摜/�����P�E.png");
	LmovemarioImg1 = LoadGraph("�摜/�����P��.png");
	RmovemarioImg2 = LoadGraph("�摜/�����Q�E.png");
	LmovemarioImg2 = LoadGraph("�摜/�����Q��.png");
	deathmarioImg = LoadGraph("�摜/����}���I.png");
	//�X�[�p�[�}���I
	RjumpsupermarioImg = LoadGraph("�摜/�X�[�p�[�}���I�W�����v�E.png");
	LjumpsupermarioImg = LoadGraph("�摜/�X�[�p�[�}���I�W�����v��.png");
	RsupermarioImg = LoadGraph("�摜/�X�[�p�[�}���I�ӂ��E.png");
	LsupermarioImg = LoadGraph("�摜/�X�[�p�[�}���I�ӂ���.png");

	//�X�[�p�[�}���I
	RjumpfiremarioImg = LoadGraph("�摜/�t�@�C���[�}���I�W�����v�E.png");
	LjumpfiremarioImg = LoadGraph("�摜/�t�@�C���[�}���I�W�����v��.png");
	RfiremarioImg = LoadGraph("�摜/�t�@�C���[�}���I�ӂ��E.png");
	LfiremarioImg = LoadGraph("�摜/�t�@�C���[�}���I�ӂ���.png");

	//�}���I�I���
	coinImg = LoadGraph("�摜/�R�C��.png");
	kuriImg = LoadGraph("�摜/�N���{�[.png");
	RnokoImg = LoadGraph("�摜/�m�R�m�R�E.png");
	LnokoImg = LoadGraph("�摜/�m�R�m�R��.png");
	koraImg = LoadGraph("�摜/�b��.png");
	RtogezoImg = LoadGraph("�摜/�g�Q�]�[�E.png");
	LtogezoImg = LoadGraph("�摜/�g�Q�]�[��.png");
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

//���ׂĂ̕ϐ��̏�����
void FirstPlayDataSet(int &mario, int &coin, int &mon, long &score, int &flagpoint, int &count, int &clear, int &dpla, int &stmove, double &nuton, double &nutonLV, double &nutonmax, int &stop, 
	int &last, int &place,int &dokanchange, int &dokan, int &black, int &white, int &marioLV, int &moving, int &superplus, int &bullet, int &num, int &jump, int &marioDirection, int &MariowideX, int &MariowideY, 
	int &move, int &end,  int &monWide,int &flag,int &flagStage,int &flagX,int &flagY) {

	monWide = 0;
	place = (make - 1) / 2 + 1;
	mario = 5;
	coin = 0;
	mon = -1;
	score = 0;
	flagpoint = 90;
	count = 0;
	clear = 0;
	dpla = 0;
	stmove = 0;
	nuton = 0;
	nutonLV = 0;
	nutonmax = 0;
	stop = 0;
	last = 0;
	dokanchange = 0;
	dokan = 0;

	marioLV = 1;
	moving = 1;
	superplus = 0;
	bullet = -1;
	num = -1;
	jump = 0;
	marioDirection = 1;
	MariowideX = 20;
	MariowideY = 20;
	move = 0;
	end = 0;
	flag = 0;
	flagStage = 0;
	flagX = 0;
	flagY = 0;
}


//�����X�^�[�̃f�[�^�̏�����
//�@�@�@�@�@�@�@�@�@�@�i�����X�^�[�̔ԍ��j
void MonsterPlayDataSet(int &num) {
	int i;
	for (i = 0; i <= num; i++) {
		Mtype[i] = 0;
		monY[i] = 0;
		monX[i] = 0;
		monMove[i] = 0;
		crol[i] = 0;
		monSide[i] = 0;
		monEnd[i] = 0;
		monTime[i] = 0;
		monHP[i] = 0;
	}
	num = -1;
}

//�e�̏�����
//�@�@�@�@�@�@�@�@�@�@�i�e�̔ԍ��j
void BulletPlayDataSet(int &bullet) {
	int i;
	for (i = 0; i <= bullet; i++) {
		bullet++;
		bulletY[i] = 0;
		bulletX[i] = 0;
		Btype[i] = 0;
		Bside[i] = 0;
		Bnuton[i] = 0;
	}
	bullet = -1;
}

//�X�e�[�W�f�[�^�̑���
//�@�@�@�@�@�@�@�@�@�i�y�ǂɓ����Ă��邩�ǂ����j
void StagePlayDataSet(int &dying,int clear,int flag,int dokanchange) {
	if (clear == 1||dying == 1 || (flag == 0 && dokanchange == 0)) {
		int i, h;
		for (int g = 0; g <= 25; g++) {
			for (h = 0; h <= 24; h++) {
				for (i = 0; i <= 99; i++) {
					dstage[g][i][h] = Data.makesta[g][i][h];
				}
			}
		}
	}
	dying = 0;
}

//�����X�^�[���o��������
//                (�����X�^�[�̔ԍ�, �����X�^�[�̎��, ���W, ����(1�`2))
void MonsterAppear(int &num, int AppearType, int AppearX, int AppearY, int AppearDirection) {
	if (num < MONSTER) {
		num++;
		Mtype[num] = AppearType;//�����X�^�[�̎��
		monX[num] = AppearX + 2;//�����X�^�[��X���W
		monY[num] = AppearY;//�����X�^�[��Y���W
		monMove[num] = 1;//�����X�^�[�̓�������
		if (Mtype[num] == MOVE_KORA)monMove[num] = 5;//�����b���͑�������
		else if (Mtype[num] == FIREFLOWER || Mtype[num] == STOP_KORA || (Mtype[num] >= PAKKUN && Mtype[num] <= STOP_DOSSUN) || Mtype[num] >= HODAI) {
			monMove[num] = 0;//�����Ȃ�
		}
		crol[num] = 0;
		monSide[num] = AppearDirection;//�����X�^�[�̌���
		monMove[num] = abs(monMove[num]) * monSide[num];
		monTime[num] = 0;//�����X�^�[�̓��ʂȍs��������܂ł̎���
		monEnd[num] = 0;//�����X�^�[�̐���
		monHP[num] = 3;//�����X�^�[��HP
	}
}

//�X�e�[�W��Ƀ����X�^�[���o��������
//�@�@�@�@�@�@�@�@�@�@�@�@�i�����X�^�[�̑����j
void MonsterAppearOnStage(int &num) {
	int i, h;
	for (h = 0; h <= 24; h++) {
		for (i = 0; i <= 99; i++) {
			if (stage[i][h] < 0) {
				int Direction = -1;
				if (stage[i][h] == -MOVE_KORA)Direction = 1;//����	�b�����o������Ƃ��A�E�Ɉړ�����
				MonsterAppear(num, stage[i][h] * -1, 30 * i, (20 - h) * 30 + 2, Direction);//�����X�^�[���o��������
				stage[i][h] = 0;//�o���������Ƃ���͏���
			}
		}
	}
}

//�y�ǂɓ����Ĉړ�����
//�@�@�@�@�@�@�i���̃X�e�[�W�̔ԍ�,�y�ǂɓ��������ǂ���,�ړ���̓y�ǂ̍��W,Y,�}���I��Y���W,�X�N���[��,�s��̃X�e�[�W�̔ԍ�,�ړ���̓y�ǂ̔ԍ��j
void DokanMove(int place, int &dokanchange, int &Xdokan, int &Ydokan, int &marioX, int &marioY, int &stmove, int &dpla, int dokan) {
	int last = 0;
	for (int g = place * 2 - 1; g <= place * 2; g++) {
		for (int h = 0; h <= 25; h++) {
			for (int i = 0; i <= 99; i++) {
				if (dstage[g][i][h] >= 101 &&
					dstage[g][i][h] % 100 / 10 == dokan) {//�ړ���̓y�ǂ�����������
					//�ǂ��Ɉړ����邩��ݒ肷��
					last = 1;
					Xdokan = i;
					Ydokan = h;
					dpla = g;
					break;
				}
			}
			if (last == 1)break;
		}
		if (last == 1)break;
	}
	if (last == 1) {
		//�ړ���̓y�ǂɁA�}���I�ƃX�N���[�����Z�b�g����
		marioY = (20 - Ydokan) * 30;
		marioX = Xdokan * 30 + 5;
		stmove = Xdokan * 30 - 300;
		if (stmove >= 78 * 30 - 10)stmove = 78 * 30 - 10;
		else if (stmove <= 0)stmove = 0;
	}

	dokanchange = 2;
}

//�}���I���A�y�ǂɂ���Ĉړ�����
//�@�@�@�@�@�@�@�@�@�@�i�X�N���[����,�}���I�̍��W,�ǉ��̃}���I��Y���W,�S�[���̊��̈ʒu,�X�N���[�����邩�ǂ���,�ꏊ�̔ԍ��A�y�ǂ̍��W,�y�ǂɓ��������ǂ���,�X�e�[�W�̔ԍ��A�ړ���̓y�ǂ̔ԍ��j
void MarioMovedByDokan(int &stmove, int &marioX, int &marioY, int &superplus, int &flagpoint, int &moving, int &dpla, int &Xdokan, int &Ydokan, int &dokanchange, int place, int dokan) {
	if (dokanchange == 1) {
		DokanMove(place, dokanchange, Xdokan, Ydokan, marioX, marioY, stmove, dpla, dokan);//�y�ǂɓ����Ĉړ�����
	}
}

//�v���C����Ƃ��̃X�^�[�g���
//               �i�y�ǂňړ����邩�ǂ����A�X�e�[�W�̔ԍ��A�}���I�̎c��A�X�N���[�����A���Ԃ̊����Ƃ������ǂ����A���Ԃ̊��̍��W�A
//�@�@�@�@�@�@�@�@�}���I�̒ǉ���Y���W�A�}���I�̏�ԁA�}���I�̉��̕��A�}���I�̃_���[�W�j
int GameStartShow(int dokanchange, int &place, int &mario, int &stmove, int &flag, int &flagStage, int &flagX, int &flagY, int &superplus, 
	int &marioLV ,int &MariowideX,int &end) {
	if (dokanchange == 0) {
		ClearDrawScreen();
		DrawFormatString(280, 200, white, "%d�[%d", (place - 1) / 3 + 1, (place - 1) % 3 + 1);//���ʂɂ��邩��\��
		DrawFormatString(300, 250, white, "�~%d", mario);//�}���I�̎c���\��
		DrawRotaGraph(280, 260, 0.20, 0.0, marioImg, TRUE);//�}���I�̎c���\��
		ScreenFlip();
		gpUpdateKey();
		WaitKey();
		gpUpdateKey();

		//�L�[����
		if (Key[KEY_INPUT_BACK] >= 1) {//�Q�[������߂�
			return 1;
		}
		else if (Key[KEY_INPUT_INSERT] >= 1 && place < 12) {//�X�e�[�W��i�߂�
			place++;
			mario = 5;
			stmove = 0;
			flag = 0;
			flagStage = 0;
			flagX = 0;
			flagY = 0;
			superplus = 0;
			marioLV = 1;
			MariowideX = 20;
			end = 0;
			return 2;
		}
		else if (Key[KEY_INPUT_DELETE] >= 1 && place > 1) {//�X�e�[�W��߂�
			place--;
			mario = 5;
			stmove = 0;
			flag = 0;
			flagStage = 0;
			flagX = 0;
			flagY = 0;
			superplus = 0;
			marioLV = 1;
			MariowideX = 20;
			end = 0;
			return 2;
		}
		else return 0;
	}
	return 0;
}


//�N���A�����Ƃ��̃f�[�^�̏�����
//�@�@�@�@�@�@�@�i�N���A�������ǂ����A�}���I�̎c��A���Ԃ̊����Ƃ������ǂ����A���̏ꏊ�̔ԍ��A���Ԃ̊��̍��W�j
void DataSetByClear(int clear,int &mario,int &flag,int &flagStage,int &flagX,int &flagY,int &stmove) {
	if (clear == 1) {
		mario = 5;
		stmove = 0;
		flag = 0;
		flagStage = 0;
		flagX = 0;
		flagY = 0;
	}
}

//���񂾂��Ƃɂ���Ă��鏉����
//�@�@�@�@�@�@�@�@�i���񂾂��ǂ����A�y�ǂňړ����邩�ǂ����A�}���I�̒ǉ���Y���W�A�}���I�̎c��A�}���I�̏�ԁA�}���I�̉��̕��j
void DataSetByDeath(int &end,int dokanchange,int &superplus,int &mario,int &marioLV,int &MariowideX,int &stmove) {
	if (end == 1 && dokanchange == 0) {
		superplus = 0;
		stmove = 0;
		mario--;
		marioLV = 1;
		MariowideX = 20;
		end = 0;
	}
}

//���Ԃ̊��ɂ���Ĉړ�����
//             (���ňړ����邩�ǂ����A�N���A�������ǂ����A�y�ǂňړ����邩�ǂ����A���Ԃ̊��̍��W�A���̏ꏊ�̔ԍ��A�}���I�̍��W�A�X�N���[�����A�ꏊ�̔ԍ�)
void MoveByFlag(int flag,int clear,int dokanchange,int flagX,int flagY,int flagStage,int &marioX,int &marioY,int &stmove,int &dpla) {
	if (flag == 1 && clear == 0 && dokanchange == 0) {
		marioX = flagX * 30;
		marioY = (20 - flagY) * 30;
		stmove = (flagX - 8) * 30;
		dpla = flagStage;
		if (stmove < 0)stmove = 0;
		dstage[dpla][flagX][flagY] = HALFFLAG2;//�ړ���̒��Ԃ̊����A�������̊��ɕς���
	}
}

//������Ԃ̃}���I�̏ꏊ�̐ݒ�
//�@�@�@�@�@�@�@�@�@�@�i�y�ǂňړ����邩�ǂ����A���Ԃ̊��ňړ����邩�ǂ����A�}���I�̒ǉ���Y���W�A�}���I�̍��W�A�N���A�̊��̍��W�A�X�N���[�����邩�ǂ����j
void MarioPointDataSet(int dokanchange,int flag,int stmove,int superplus,int &marioX,int &marioY,int &flagpoint,int &moving) {
	if (dokanchange == 0) {
		if (flag == 0) {
			stmove = 0;
			marioY = 420 - superplus;
			marioX = 30;
		}
		flagpoint = 90;
		moving = 1;
	}
}


//�X�e�[�W�̃f�[�^���Z�b�g����
//�@�@�@�@�@�@�@�i�ꏊ�̔ԍ��A�N���A�������ǂ����A�y�ǂňړ����邩�ǂ����A���Ԃ̊��ňړ����邩�ǂ����j
void StageDataSet(int &dpla,int clear,int dokanchange,int place,int flag) {
	if (clear == 1 || (clear == 0 && dokanchange == 0 && flag == 0)) {
		dpla = place * 2 - 1;
	}
	for (int h = 0; h <= 24; h++) {
		for (int i = 0; i <= 99; i++) {
			stage[i][h] = dstage[dpla][i][h];
		}
	}
}


//���񂾌�̏�����
int SecondPlayDataSet(int &dying, int &count, int &stop, int &move, int &dokanchange, int &dokan, int &coin, int &superplus, int &clear, int &monstop, int &flagpoint, int &marioLV,
	int &num, int &bullet,int &end, int &mario, int &place, int &marioImg, int &marioY, int &marioX, int &stmove, int &moving, int &dpla, int &Xdokan, int &Ydokan, int &suke,  
	int &jumping, int &MariowideX,int &flag,int &flagStage,int &flagX,int &flagY) {
	int i, h;
	int white = GetColor(-1, -1, -1);
	for (h = 0; h <= 24; h++) {
		for (i = 0; i <= 99; i++) {
			stage[i][h] = EMPTY;
		}
	}
	for (i = 0; i <= 199; i++)Btype[i] = 0;

	

	suke = 0;//���G���Ԃ��O�ɂ���
	jumping = 0;//�W�����v���ĂȂ��悤�ɂ���
	count = 0;//���Ԃ��O�ɂ���
	stop = 0;//���Ԃ��~�܂��ĂȂ��悤�ɂȂ�
	move = 0;//������悤�ɂȂ�
	monstop = 0;//�����X�^�[�͓�����
	flagpoint = 90;//�S�[���̊��̈ʒu�̐ݒ�

	MonsterPlayDataSet(num);//�����X�^�[�̃f�[�^������������

	BulletPlayDataSet(bullet);//�e�̃f�[�^������������

	StagePlayDataSet(dying,clear,flag,dokanchange);//�X�e�[�W�f�[�^������������

	DataSetByClear(clear, mario, flag, flagStage, flagX, flagY, stmove);//�N���A�������Ƃł̃f�[�^������������

	DataSetByDeath(end, dokanchange, superplus, mario, marioLV, MariowideX,stmove);//���񂾂��Ƃł̃f�[�^������������

	if (mario <= 0)return 1;//�c��Ȃ��Ƃ��A��߂�


	int check = GameStartShow(dokanchange, place, mario, stmove, flag, flagStage, flagX, flagY, superplus,marioLV, MariowideX, end);
	//�Q�[���̎n�܂��\������

	if (check != 0) {
		return check;
	}

	MarioMovedByDokan(stmove, marioX, marioY, superplus, flagpoint, moving, dpla, Xdokan, Ydokan, dokanchange, place, dokan);
	//�y�ǂňړ�����Ƃ�

	MoveByFlag(flag, clear, dokanchange, flagX, flagY, flagStage, marioX, marioY, stmove, dpla);
	//���Ԃ̊��ɂ���Ĉړ�����Ƃ�

	MarioPointDataSet(dokanchange, flag, stmove, superplus, marioX, marioY, flagpoint, moving);
	//�}���I�̏ꏊ���Z�b�g����

	StageDataSet(dpla, clear, dokanchange, place, flag);
	//�X�e�[�W�̃f�[�^���Z�b�g����

	MonsterAppearOnStage(num);
	//�X�e�[�W�̏�Ƀ����X�^�[���o��
	
	if(dpla %2 == 1)stage[flagpoint][6] = HATENA_KNOCKED;//���̕����̃u���b�N

	clear = 0;

	return 0;
}

//�}���I���R�C���ɐG�ꂽ�Ƃ�
//          �i�}���I�̍��W�A�}���I�̕��A�}���I�̒ǉ���Y���W�A�R�C���̐��A�}���I�̎c��j
void CoinGet(int marioX, int marioY, int MariowideX, int MariowideY, int superplus, int &coin, int &mario) {
	for (int i = marioX - 1; i <= marioX + MariowideX + 1; i++) {
		for (int h = (marioY - 1) / 30; h <= (marioY + MariowideY + superplus + 5) / 30; h++) {
			if (stage[i / 30][20 - h] == COINBLOCK) {
				stage[i / 30][20 - h] = EMPTY;
				coin++;
				if (coin >= 100) {//�R�C�����P�O�O�ɂȂ�����A�c��������
					coin = 0;
					if (mario < 99) {
						mario++;
					}
				}
			}//�}���I���R�C���ɐG��Ă���Ƃ���if

		}//�}���I��X���W�ł̃��[�v

	}//�}���I��Y���W�ł̃��[�v
}

//�}���I�����Ԃ̊��ɐG�ꂽ�Ƃ�
//�@�@�@�@�@�i�}���I�̍��W�A�}���I�̕��A�}���I�̒ǉ���Y���W�A�ꏊ�̔ԍ�,���Ԃ̊��̔���A���Ԃ̊��̏ꏊ�A���Ԃ̊��̍��W�A�}���I�̏�ԁj
void FlagGet(int &marioX, int &marioY, int &MariowideX, int MariowideY, int &superplus,int dpla,int &flag,int &flagStage,int &flagX, int &flagY,int &marioLV) {
	for (int i = marioX - 1; i <= marioX + MariowideX + 1; i++) {
		for (int h = (marioY - 1) / 30; h <= (marioY + MariowideY + superplus + 5) / 30; h++) {
			if (stage[i / 30][20 - h] == HALFFLAG1) {
				stage[i / 30][20 - h] = HALFFLAG2;
				//���Ԃ̊��̏ꏊ��������
				flag = 1;
				flagStage = dpla;
				flagX = i / 30;
				flagY = 20 - h;
				if (marioLV == 1) {//���у}���I�Ȃ�A�X�[�p�[�}���I�ɂȂ�
					marioLV = 2;
					superplus = 15;
					marioY -= 16;
					MariowideX = 25;
					marioX -= 10;
				}
			}//�}���I�����ɐG��Ă���Ƃ���if

		}//�}���I��X���W�ł̃��[�v

	}//�}���I��Y���W�ł̃��[�v
}


//�e������
//                  �i�������Ă���e�̔ԍ��A�e�̑����A�X�N���[�����j
void BulletDisappear(int i, int &bullet, int stmove) {
	if (Btype[i] == 0 || bulletX[i] - stmove <= 0 || bulletX[i] - stmove >= 660 ||
		stage[(bulletX[i] + Bside[i] * 5) / 30][20 - (bulletY[i] + Bside[i] * 5) / 30] > EMPTY) {
		Btype[i] = 0;
		bulletX[i] = bulletX[bullet];
		bulletY[i] = bulletY[bullet];
		Btype[i] = Btype[bullet];
		Bside[i] = Bside[bullet];
		Bnuton[i] = Bnuton[bullet];
		bullet--;
	}
}

//�e���ړ�����
//�@�@�@�@�i���ݏ������Ă���e�̔ԍ��A�e�̑����A�X�N���[�����j
void BulletMove(int i, int &bullet, int stmove) {
	for (int h = 0; h != 10 * Bside[i]; h += Bside[i]) {//�e���ǂɓ������ĂȂ��Ƃ��ړ�����
		if (stage[(bulletX[i] + Bside[i] * 5) / 30][20 - (bulletY[i] + Bside[i] * 5) / 30] == EMPTY) {
			bulletX[i] += Bside[i];//�e���A�e�̌����̂ق��ɓ�����
		}
		else {
			BulletDisappear(i, bullet, stmove);//�e������
			break;
		}
	}
}


//�t�@�C���[�{�[���������X�^�[�ɓ���������
//�@�@�@�@�i�������Ă���e�̔ԍ��A�����X�^�[�̑����A�X�R�A�A�e�̑����A�X�N���[�����j
int FireTouchMonster(int i, int num, long &score, int &bullet, int stmove) {
	//�e�ƃ����X�^�[�̂�����
	int last = 0;
	for (int h = 0; h <= num; h++) {
		if (monEnd[h] == 1)continue;
		if (bulletX[i] <= monX[h] + 25 && bulletX[i] >= monX[h] &&
			bulletY[i] <= monY[h] + 25 && bulletY[i] >= monY[h]) {//�e�������X�^�[�ɓ���������
			if (Mtype[h] != COIN)Btype[i] = 0;//���������̂��A�R�C���łȂ��Ƃ��A�e�͏�����
			BulletDisappear(i, bullet, stmove);//�e������

			//�t�@�C���[�{�[���Ŏ��ʃ����X�^�[�������Ƃ�
			if (Mtype[h] >= KURIBO && Mtype[h] <= PAKKUN  || Mtype[h] == KILLER || Mtype[h] == STOP_TERESA || Mtype[h] == MOVE_TERESA) {
				monHP[h] -= 3;
				if (monHP[h] <= 0) {//�����X�^�[������
					score += 100;
					monEnd[h] = 1;
				}
			}
			last = 1;
			break;
		}
	}
	if (last == 1) {
		return 1;
	}
	else {
		return 0;
	}
	//�e�ƃ����X�^�[�̂����蔻��
}

//�t�@�C���[�{�[�����n�ʂɓ���������
//             �i�������Ă���e�̔ԍ��A�e�̏d�͉����x�̏���A�e���㉺�ɓ��������j
int FireTouchFloor(int i, double Bnutonmax, int plus) {
	//�e�Ə��̂����蔻��

	bulletY[i] -= plus;
	if (stage[bulletX[i] / 30][20 - (bulletY[i] + 10) / 30] > EMPTY && stage[(bulletX[i]) / 30][20 - (bulletY[i] + 10) / 30] > EMPTY) {
		//�n�ʂɓ����������A�d�͉����x�����Z�b�g����
		Bnuton[i] = 0;
		return 1;
	}
	else return 0;
	//�e�Ə��̂����蔻��
}

//�t�@�C���[�{�[���������Ȃ��Ȃ鎞
int FireMoveStop(int plus, int h, int i, int BaseBulletY, int &num, int &bullet, int stmove, long &score, double Bnutonmax) {
	if (plus == -1) {//�P�񕪂̃t�@�C���[�{�[���̉����肪�I�������
		if (h < BaseBulletY + Bnutonmax - Bnuton[i]) {
			return 1;
		}
	}
	else if (plus == 1) {//�P�񕪂̃t�@�C���[�{�[���̏�肪�I�������
		if (h > BaseBulletY + Bnutonmax + Bnuton[i]) {
			return 1;
		}
	}
	if (FireTouchFloor(i, Bnutonmax, plus) == 1) {//�t�@�C���[�{�[�����n�ʂɐG�ꂽ�Ƃ�
		return 1;
	}

	if (FireTouchMonster(i, num, score, bullet, stmove) == 1) {//�t�@�C���[�{�[���������X�^�[�ɂ���������
		return 1;
	}
	return 0;
}

//�t�@�C���[�{�[��������
//�@�@�@�@�@�i�������Ă���e�̔ԍ��A�����X�^�[�̑����A�e�̑����A�X�R�A�A�X�N���[�����j
void FireMove(int i, int num, int &bullet, long &score, int &stmove) {
	//���̋ʂ̎���if
	double BnutonLV = 3;
	double Bnutonmax = 5;
	if (Btype[i] == 2) {
		BulletMove(i, bullet, stmove);
		Bnuton[i] += BnutonLV;//�e�̏㉺�̑�����ω�������
		int h = bulletY[i];
		int plus;
		if (Bnutonmax - Bnuton[i] > 0) {//�e�͏�ɏオ��
			plus = 1;
		}
		else plus = -1;//�e�͉��ɉ�����
		int BaseBulletY = bulletY[i];
		Bnuton[i] += BnutonLV;
		for (;;) {
			if (FireMoveStop(plus, h, i, BaseBulletY, num, bullet, stmove, score, Bnutonmax) == 1) {//�t�@�C���[�{�[����������Ƃ�
				break;
			}
			h += plus;
		}

	}
	//���̋ʂ̎���if
}

//�e�̏����S��
//�@�@�@�@�@�@�@�@�@�i�X�R�A�A�e�̑����A�X�N���[�����A�����X�^�[�̑����j
void BulletDataChange(long &score, int &bullet, int &stmove, int &num) {
	for (int i = 0; i <= bullet; i++) { //�e�̏���
		BulletDisappear(i, bullet, stmove);//�e��������

		BulletMove(i, bullet, stmove);//�e������

		FireMove(i, num, bullet, score, stmove);//�t�@�C���[�{�[��������
	}
}


//�����X�^�[�������Ƃ�
//        (�������Ă��郂���X�^�[�̔ԍ��A�����X�^�[�̑���)
int MonsterDelete(int &i, int &num) {
	if (monEnd[i] == 1) {
		Mtype[i] = Mtype[num];
		monY[i] = monY[num];
		monX[i] = monX[num];
		monMove[i] = monMove[num];
		crol[i] = crol[num];
		monSide[i] = monSide[num];
		monTime[i] = monTime[num];
		monHP[i] = monHP[num];
		monEnd[i] = monEnd[num];
		//����
		i--;
		num--;
		return 1;
	}
	else return 0;
}

//�e�������X�^�[�ɓ���������
//�@�@�@�@�@�@�@�@�i�������Ă���e�̔ԍ��A�e�̑����j
void BulletAttackMonster(int i, int &bullet,int stmove) {
	int h;
	for (h = 0; h <= bullet; h++) {
		if (Btype[h] == 1 && Mtype[i] != BLACK_PAKKUN && abs(bulletY[h] - monY[i]) < 25 && abs(bulletX[h] - monX[i]) < 25) {//�e�������X�^�[�̓���������
			Btype[h] = 0;
			if (Mtype[i] >= KURIBO && Mtype[i] <= PAKKUN)monHP[i]--;//�����X�^�[��HP�����炷
			if (monHP[i] == 0)monEnd[i] = 1;//HP���O�Ȃ�A������
			BulletDisappear(i, bullet, stmove);//���������e�͏�����
		}
	}
}

//�����X�^�[��������Ƃ�,������Ƃ��P�A�����Ȃ��Ƃ��O
//�@�@�@�@�i�������Ă��郂���X�^�[�̔ԍ��A���Ԃ��~�܂��Ă��邩�ǂ����A�����X�^�[�̑����j
int MonsterFall(int i, int stop, int num) {
	int h;
	int g;

	int a;// �����X�^�[�̍����̏ꏊ
	int b;//�����X�^�[�̉E���̏ꏊ
	int last = 0;
	for (h = 0; h <= num; h++) {
		a = stage[(monX[i] - 1) / 30][20 - (monY[i] + 25) / 30];//�����X�^�[�̍����̏ꏊ
		b = stage[(monX[i] + 25 + 1) / 30][20 - (monY[i] + 25) / 30];//�����X�^�[�̉E���̏ꏊ
		if (Mtype[i] != MOVE_TERESA && Mtype[i] != STOP_TERESA && Mtype[i] != STOP_DOSSUN && Mtype[i] != KILLER //���ɗ����郂���X�^�[�ŁA
			&& (stop == 0 || Mtype[i] <= SUPER_KINOKO) && (a == EMPTY || a == COINBLOCK) && (b == EMPTY || b == COINBLOCK)) {//�����R�C�����A��̎�
			if (Mtype[h] != STOP_TERESA && Mtype[h] != MOVE_TERESA && monX[i] + 24 >= monX[h] && monX[i] <= monX[h] + 24 &&
				monY[i] + 25 == monY[h]) {//���Ƀ����X�^�[������Ƃ�
				if (Mtype[i] == MOVE_KORA && Mtype[h] < HODAI && Mtype[i] != BLACK_PAKKUN) {//�����b������ɂ���Ƃ�
					monEnd[h] = 1;//���̃����X�^�[�͏�����
				}
				last = 1;
				return 0;
			}
		}
		else {//�����u���b�N�̎�
			last = 1;//�������Ȃ�
			return 0;
		}
	}
	if (last == 0) {
		monY[i]++;//���Ƀ����X�^�[�����Ȃ��Ƃ�
		return 1;
	}
	else return 0;;
	//���ɗ������Ƃ�
	
}

//�L���[���ړ�������
//           (�������Ă��郂���X�^�[�̔ԍ�)
void KillerGo(int i) {
	int h;
	if (Mtype[i] == KILLER) {
		for (h = 0; h<5; h++) monX[i] += monSide[i];
	}
}

//�Ƃ����A��~��������������ς���
//�@�@�@�@�@�@�@�i�������Ă��郂���X�^�[�̔ԍ��A�}���I�̍��W�A�}���I�̏c�̕��j
void SpineChange(int i, int marioX, int marioY,int MwideY) {
	if (Mtype[i] == STOP_SPINE && marioY + MwideY <= monY[i] && abs(marioX - monX[i]) <= 25 + 5) {
		Mtype[i] = MOVE_SPINE;
	}
}


//�Ƃ�����ɏオ��
//�@�@�@�@�@�i�������Ă��郂���X�^�[�̔ԍ��A�}���I�̉����A�}���I�̍��W�A�}���I�̒ǉ��̍��W�A�}���I�̃_���[�W�j
void SpineUp(int i, int MariowideX, int marioX, int marioY, int superplus, int &end) {
	int h;
	if (Mtype[i] == MOVE_SPINE) {
		for (h = 0; h<3; h++) {
			monY[i] -= 5;
			if (marioY + superplus >= monY[i] && marioY <= monY[i] + 25 &&
				marioX + MariowideX + 1>= monX[i] && marioX <= monX[i] + 25 - 1) {//�Ƃ����}���I�ɓ���������_���[�W���󂯂�
				end = 1;
			}
		}
	}
}


//�h�b�X���̓��Ƀh�b�X�������邩�ǂ���
//�@�@�@�@�@�@�@�@�@�i�������Ă��郂���X�^�[�̔ԍ��A�����X�^�[�̑����j
int DossunHeadTouch(int i,int num) {
	for (int h = 0; h <= num; h++) {
		if (i != h && Mtype[h] == STOP_DOSSUN && abs(monX[i] - monX[h]) < 23 && abs(monY[i] - monY[h]) < 30) {//�h�b�X���̓��Ƀh�b�X�������邩�ǂ���
			return 1;
		}
	}
	return 0;
}

//�h�b�X�����A��ɏオ�邩�A���ɗ�����悤�ɕς�邩
//                  (�������Ă��郂���X�^�[�̔ԍ��A�}���I�̍��W�A�����X�^�[�̑���)
void DossunUpOrChange(int i, int marioX, int marioY,int num) {
	if (Mtype[i] == STOP_DOSSUN) {

		int a = stage[(monX[i] + 1)/ 30][20 - (monY[i] / 30)];//�h�b�X���̍���̏ꏊ
		int b = stage[(monX[i] + 25 - 1) / 30][20 - (monY[i]) / 30];//�h�b�X���̉E��̏ꏊ

		if ((a == EMPTY || a == COINBLOCK) && (b == EMPTY || b == COINBLOCK) && DossunHeadTouch(i, num) == 0) {//�h�b�X���̏�Ƀh�b�X�����u���b�N���Ȃ��Ƃ�
			monY[i]--;
		}
		if (marioY >= monY[i] && abs(marioX - monX[i]) <= 25 &&( b != COINBLOCK && b > EMPTY || DossunHeadTouch(i, num) == 1)) {//�}���I�����ɂ��鎞
			Mtype[i] = FALL_DOSSUN;//���Ɍ������Ă����悤�ɂȂ�
		}
	}
}

//�h�b�X����������Ƃ�
//�@�@�@�@�@�@�i�������Ă��郂���X�^�[�̔ԍ��A�����X�^�[�̑����j
void DossunFall(int i,int num) {

	int x1 = monX[i] / 30;//�����X�^�[�̍���X���W

	int x2 = (monX[i] + 25) / 30;//�����X�^�[�̉E��X���W

	int y = 20 - (monY[i] + 30) / 30;//�����X�^�[�̉���Y���W
	if (Mtype[i] == FALL_DOSSUN) {
		if (stage[x1][y] == BRICK) {
			stage[x1][y] = EMPTY;
		}
		//�h�b�X���̍����Ƀ����K�u���b�N������Ƃ�	

		if (stage[x2][y] == BRICK) {
			stage[x2][y] = EMPTY;
		}
		//�h�b�X���̉E���Ƀ����K�u���b�N������Ƃ�

		//�h�b�X���̉��ɁA�R�C���łȂ��u���b�N���Ȃ��Ƃ�
		if ((stage[x1][y] == EMPTY || stage[x1][y] == COINBLOCK) && (stage[x2][y] == EMPTY || stage[x2][y] == COINBLOCK)) {
			monY[i] += 5;//���ɗ�����
		}
		else {//�h�b�X���̉����R�C���łȂ��u���b�N�̎�
			Mtype[i] = STOP_DOSSUN;//�h�b�X�����A��ɏオ��悤�ɂȂ�
		}
	}
}


//�C�䂪�����X�^�[���o��������
//�@�@�@�@�@�@�@�@�@�@�@�i�������Ă��郂���X�^�[�̔ԍ��A�����X�^�[�̑����C��̌����j
void MosterAppearByHodai(int i, int &num, int hodaiDirection) {
	int last = 0;//�o���ł��邩�ǂ���
	int kora = 1;//�b�����o��������Ƃ��̌���
	for (int h = 0; h <= num; h++) {
		if (abs(monX[i] + 30 * hodaiDirection - monX[h]) < 25 && abs(monY[i] - 5 - monY[h]) < 25) {//�C��ׂ̗Ƀ����X�^�[������Ƃ�
			last = 1;
			break;
		}
	}
	if (last == 0) {//�C�䂩��o��������Ƃ��̃f�[�^�̏���
		int AppearType;
		if (Mtype[i] % 100 < ITEM) {//�A�C�e�����o��������Ƃ�
			AppearType = Mtype[i] % 100 * -1;
		}
		else {//�����X�^�[���o��������Ƃ�
			AppearType = Mtype[i] % 100 - ITEM;
			if (AppearType == 4)kora = -1;//�b���Ȃ�B�������ς��
		}
		MonsterAppear(num, AppearType, monX[i] + 30 * hodaiDirection, monY[i] - 5, hodaiDirection * kora);//�����X�^�[���o��������
	}
}


//�C�䂪�����X�^�[���o�������鎞�ԂȂ�
//�@�@�@�@�@�@�@�i�������Ă��郂���X�^�[�̔ԍ��A�}���I�̕��A�}���I�̍��W�A�}���I�̒ǉ���Y���W�A�}���I���ړ����Ă��邩�ǂ����A�����X�^�[�̑����X�N���[�����j
void HodaiCreate(int i, int MariowideX, int MariowideY, int marioX, int marioY, int superplus, int &move, int &num ,int stmove) {
	if (Mtype[i] >= 100) {
		monTime[i] ++;//���Ԃ̕����₵�Ă���
		if (monTime[i] % 50 == 0 && monX[i] - stmove < 600) {//�����X�^�[���o��������^�C�~���O�ɂȂ�A�C�䂪��ʏ�ɂ���Ƃ�
			int x1 = (monX[i] + 40) / 30;//�C��̉E�̂ق��̍��W
			int x2 = (monX[i] - 10) / 30;//�C��̍��̂ق��̍��W
			int y1 = 20 - (monY[i] + 1) / 30;//�C��̏�̍��W
			int y2 = 20 - (monY[i] + 25 - 1) / 30;//�C��̉��̍��W

			if (marioX > monX[i] + 30 && stage[x1][y1] == EMPTY && stage[x1][y2] == EMPTY) {//�ׂɃu���b�N���Ȃ��A�����Ƀ}���I������Ƃ�
				MosterAppearByHodai(i, num, 1);//�����X�^�[�̏o��
			}
			else if (marioX + MariowideX < monX[i] && stage[x2][y1] == EMPTY && stage[x2][y2] == EMPTY) {//�ׂɃu���b�N���Ȃ��A�E�Ƀ}���I������Ƃ�
				MosterAppearByHodai(i, num, -1);//�����X�^�[�̏o��
			}
		}
	}
}


//�ړ����Ă���b���Ƀu���b�N������������
//�@�@�@�@�@�@�@�@�i�X�R�A�A�R�C�����A�}���I�̎c��A�����X�^�[�̑����������Ă��郂���X�^�[�̔ԍ��A�����X�^�[�̍��W�A�}���I�̌����j
void KoraTouchBlock(long &score, int &coin, int &mario, int &num, int i, int x, int y, int marioDirection) {
	if (Mtype[i] == MOVE_KORA && stage[x][y] > EMPTY) {
		if (stage[x][y] == BRICK) {//�����K�ɓ����������A�j�󂷂�
			stage[x][y] = EMPTY;
		}
		else if (stage[x][y] >= HATENA && stage[x][y] < DOKANUP_MOVE) {//�H�u���b�N�ɓ����������A�H�u���b�N���璆�g���o��������
			int AppearType;
			if ((stage[x][y] - HATENA) < ITEM) {//�A�C�e�����o���Ƃ�
				AppearType = (stage[x][y] - HATENA) * -1;
			}
			else {//�����X�^�[���o���Ƃ�
				AppearType = (stage[x][y] - HATENA) - ITEM;
			}
			MonsterAppear(num, AppearType, x * 30, (20 - y - 1) * 30, marioDirection);//�����X�^�[���o��������
			stage[x][y] = HATENA_KNOCKED;

		}
		else if (stage[x][y] == COINBLOCK) {//�b�����R�C���ɓ����������A�������
			stage[x][y] = EMPTY;
			score += 100;
			coin++;
			if (coin == 100)coin = 0, mario++;
		}

	}
}



//�����X�^�[���u���b�N�ɓ���������
//�@�@�@�@�@�@�@�@�@�@�i�������Ă��郂���X�^�[�̔ԍ��A�X�R�A�A�R�C�����A�}���I�̎c��A�����X�^�[�̕��A�����X�^�[�̑����j
void MonsterTouchBlock(int i, long &score, int &coin, int &mario, int &monWide, int &num) {
	if (monMove[i] > 0)monWide = 24; else monWide = 0;//�����X�^�[���E�ɓ����Ă���Ƃ��A�����X�^�[�̕����l������
	int x = (monX[i] + monWide + monMove[i]) / 30;//�����X�^�[���ړ�������X���W
	int y1 = 20 - monY[i] / 30;//�����X�^�[�̏��Y���W
	int y2 = 20 - (monY[i] + 25 - 1) / 30;//�����X�^�[�̉���Y���W

	if (stage[x][y1] > EMPTY) {//�㑤���u���b�N�ɓ���������
		if (stage[x][y1] != COINBLOCK && Mtype[i] != KILLER)monMove[i] *= -1, monSide[i] *= -1;//�����𔽓]����
	}
	else if (stage[x][y2] > EMPTY) {//�������u���b�N�ɓ���������
		if (stage[x][y2] != COINBLOCK && Mtype[i] != KILLER)monMove[i] *= -1, monSide[i] *= -1;//�����𔽓]����
	}

	KoraTouchBlock(score, coin, mario, num, i, x, y1, 1);//�b���̏�̕������u���b�N�ɓ���������

	KoraTouchBlock(score, coin, mario, num, i, x, y2, -1);//�b���̉��̕������u���b�N�ɓ���������

}


//�����X�^�[���ق��̃����X�^�[�ɓ���������
//�@�@�@�@�@�@�@�@�@�@�@�@�i�������Ă��郂���X�^�[�̔ԍ��A�����X�^�[�̑����X�R�A�A�����X�^�[���~�܂��Ă��邩�ǂ����j
int MonterTouchOtherMonster(int i, int num, long &score, int &monstop) {
	int touch = 0;
	for (int h = 0; h <= num; h++) {
		if (monEnd[h] == 1)continue;//������ꂽ��������ł������A�߂�
		if (i != h&&monY[i] + 24 >= monY[h] && monY[i] <= monY[h] + 24 &&
			monX[i] + 25 + monMove[i] >= monX[h] && monX[i] + monMove[i] <= monX[h] + 25) {//�����X�^�[���ق��̃����X�^�[�ɓ���������
			if (Mtype[i] != MOVE_KORA && Mtype[i] != KILLER && Mtype[h] != KILLER) {//�����鑤���b���A�L���[�A�����鑤���L���[�łȂ��Ƃ�
				touch = 1;
				monMove[i] *= -1;//�����𔽓]����
				monSide[i] *= -1;
				monstop++;
			}
			else if (Mtype[i] == 4) {//�����鑤���b���̎�
				if (Mtype[h] == STOP_KORA || Mtype[h] == MOVE_KORA) {//�b�����b���ɓ������Ăǂ�����������
					monEnd[i] = 1;
					monEnd[h] = 1;
					score += 100;
				}
				else if (Mtype[h] >= KURIBO  && Mtype[h] <= PAKKUN || Mtype[h] == KILLER) {//�b���ɓ�����ꂽ�����X�^�[�͏�����
					monEnd[h] = 1;
					score += 100;
				}
				else if (Mtype[h] > HODAI) {//�C��ɓ����������͍b���͌�����ς���
					monMove[i] *= -1;
					monSide[i] *= -1;
				}
				//�����łȂ��Ƃ��́A�b���̓����X�^�[��ʉ߂���
			}
		}
	}
	return 0;
}

//�C��ɓ����������A������ς���
int MonsterTouchHodai(int i,int num) {
	for (int h = 0; h <= num; h++) {
		if (Mtype[h] >= HODAI && abs(monX[i] - monX[h]) < 25 && abs(monY[i] - monY[h]) < 25) {//�C��ɓ���������
			monMove[i] *= -1;//������ς���
			monSide[i] *= -1;//������ς���
			monX[i] += monSide[i];//�C��ɐG��Ă��Ȃ��悤�ɂ��炷
			return 1;
		}
	}
	return 0;
}

//�����X�^�[�������Ƃ�
//�@�@�@�@�@�@�@�i�������Ă��郂���X�^�[�̔ԍ��A�����X�^�[�̕��A�����X�^�[���~�܂��Ă��邩�ǂ����A���Ԃ��~�܂��Ă��邩�ǂ���,�����X�^�[�̑����A
//              �}���I�����������Ƃ����邩�ǂ����j
void MonsterMove(int i, int &monWide, int monstop, int stop,int num,int fall) {
	int x1;//�����X�^�[�̈ړ����X���W
	int x2;
	int y1 = 20 - (monY[i] + 1) / 30;//�����X�^�[�̏㑤��Y���W
	int y2 = 20 - (monY[i] + 25 - 1) / 30;//�����X�^�[�̉�����Y���W

	

	//���ʂ̃����X�^�[���ړ�����Ƃ��ŁA�ړ���Ƀu���b�N���Ȃ��Ƃ�
	if (monstop <= 1 && (stop == 0 || Mtype[i] <= SUPER_KINOKO)) {
		for (int h = 1; h <= abs(monMove[i]); h++) {
			if (monSide[i] > 0)monWide = 24; else monWide = 0;//�����X�^�[���E�ɓ����Ă���Ƃ��A�����X�^�[�̕����l������
			x1 = (monX[i] + monWide + monSide[i]) / 30;//�����X�^�[�̈ړ����X���W

			if(fall == 0)MonsterFall(i, stop, num);//�܂����������Ƃ��Ȃ��Ƃ��A�����X�^�[�����ɗ����邩�ǂ����𔻒f

			if (Mtype[i] != KILLER && Mtype[i] != MOVE_TERESA && Mtype[i] != STOP_TERESA &&//���������X�^�[�ŁA�u���b�N�ɓ����炸������Ƃ�
				(stage[x1][y1] == EMPTY || stage[x1][y1] == COINBLOCK) && (stage[x1][y2] == EMPTY || stage[x1][y2] == COINBLOCK)) {

				if (MonsterTouchHodai(i, num) == 0) {//�C��ɓ�����Ȃ������Ƃ�
					monX[i] += monSide[i];//����
				}
			}
			else break;
		}
	}
}

//�b����������Ƃ�
//                (�������Ă��郂���X�^�[�̔ԍ��A�X�N���[����)
void KoraDisappear(int i, int stmove) {
	if (Mtype[i] == MOVE_KORA && (monX[i] - stmove < -100 || monX[i] - stmove > 660)) {//�b�����A��ʊO�ɏo���Ƃ�
		//������
		monEnd[i] = 1;
		monMove[i] = 0;
	}
}

//�}���I���A�C�e�����l�������Ƃ�
//              (�������Ă��郂���X�^�[�̔ԍ��A�R�C�����A�}���I�̎c��A�}���I�̍��W�A�}���I�̒ǉ���Y���W�A�}���I�̉��̕��A�X�R�A)
void MarioLevelUp(int i, int &coin, int &mario, int &marioLV, int &marioX,int &marioY, int &superplus, int &MariowideX, long &score) {
	if (monEnd[i] == 0) {//�A�C�e���������ĂȂ��Ƃ�
		if (Mtype[i] == COIN) {//�R�C�����l�������Ƃ�
			monEnd[i] = 1;//�R�C��������
			score += 100;
			coin++;//�R�C���𑝂₷
			if (coin == 100)mario++, coin = 0;
		}
		else if (Mtype[i] == SUPER_KINOKO) {//�X�[�p�[�L�m�R���l�������Ƃ�
			monEnd[i] = 1;//�X�[�p�[�L�m�R�������A
			score += 1000;
			if (marioLV == 1) {
				marioLV = 2;//�}���I���X�[�p�[�}���I�ɂ���
				marioY -= 20;
				superplus = 15;
				MariowideX = 25;
				marioX -= 10;
			}
		}
		else if (Mtype[i] == ONE_UP_KINOKO) {//�����i�b�v�L�m�R���l�������Ƃ�
			monEnd[i] = 1;
			score += 1000;
			if (mario < 100)mario++;//�}���I�̎c�������₷
		}
		else if (Mtype[i] == FIREFLOWER) {//�t�@�C���[�t�����[���l�������Ƃ�
			monEnd[i] = 1;
			score += 1000;
			if (marioLV == 1) {//���у}���I�Ȃ�傫����ύX����
				marioY -= 20;
				superplus = 15;
				MariowideX = 25;
				marioX -= 10;
			}
			marioLV = 3;
		}
	}
}

//�����X�^�[���}���I�ɓ���������
//(�������Ă��郂���X�^�[�̔ԍ��A�}���I�̍��W�A�}���I�̒ǉ���Y���W�A�}���I�̃_���[�W�A�R�C�����A�}���I�̏�ԁA�}���I�̉����A�X�R�A)
void MonsterTouchMario(int i,int &marioX,int &marioY,int &superplus,int &end,int &coin,int &mario,int &marioLV,int &MariowideX,long &score) {
	if (Mtype[i] < HODAI && marioY + superplus + 5 >= monY[i] && marioY + superplus <= monY[i] + 25 &&
		marioX + 19 >= monX[i] && marioX <= monX[i] + 18) {

		MarioLevelUp(i, coin, mario, marioLV, marioX,marioY, superplus, MariowideX,score);//�}���I���A�C�e�����l�������Ƃ�

		if (Mtype[i] == STOP_KORA) {//�����Ă��Ȃ��b��������������
			Mtype[i] = MOVE_KORA;//�����悤�ɂ���

			//���������߂�
			if ((marioX + 19) / 5 == monX[i] / 5) {//�E����
				monMove[i] = 10;
				monSide[i] = 1;
			}
			else if(marioX / 5 == (monX[i]+ 18) / 5){//������
				monMove[i] = -10;
				monSide[i] = -1;
			}
		}
		else if (Mtype[i] >= KURIBO && Mtype[i] < HODAI) {//�}���I�����̑��̃����X�^�[�ɓ��������Ȃ�A�}���I�̓_���[�W���󂯂�
			end = 1;
		}

	}
}

//�}���I�������X�^�[�𓥂񂾎�
//�@�i�X�R�A�A�}���I�̃W�����v�̑����A�}���I�̏d�͉����x�A�d�͉����x�̏���A�W�����v���Ă��邩�ǂ����A
//   �}���I�̃_���[�W�A�}���I�̍��W�A�}���I�̉��̕��A�R�C�����A�}���I�̎c��A�}���I�̒ǉ���Y���W�A�}���I�̏�ԁA
//  ���������Ă��郂���X�^�[�̔ԍ��A�}���I�̌����j

int  MarioStampMonster(long &score, double nuton, double nutonLV, double nutonmax, int & jumping, int &jump, int &end, int &marioX, 
	int &marioY, int &MariowideX, int &coin,int &mario, int &superplus, int &marioLV, int i, int marioDirection) {
	if (((marioY + superplus + 20) / 5 == monY[i] / 5) &&
		marioX + 23 >= monX[i] + 5 - monX[i] % 5 && marioX <= monX[i] + 5 - monX[i] % 5 + 18) {
		jumping = 0;
		if (Mtype[i] >= TOGEZO && Mtype[i] <= STOP_TERESA && Mtype[i] != KILLER) {//���ނƃ_���[�W���󂯂郂���X�^�[�𓥂񂾎�
			end = 1;
		}
		if ((Mtype[i] >= KURIBO && Mtype[i] <= MOVE_KORA) || Mtype[i] == KILLER) {//���ނƃW�����v�ł��郂���X�^�[�𓥂񂾎�
			jump = 1;
			jumping = 1;
		}
		if (Mtype[i] == KURIBO || Mtype[i] == KILLER) {//�N���{�[���L���[�𓥂񂾎�
			monEnd[i] = 1;//�����X�^�[��������
			score += 100;
		}
		else if (Mtype[i] == MOVE_KORA) {//�����b���𓥂񂾎�
			Mtype[i] = STOP_KORA;//�b���������Ȃ��Ȃ�
			monMove[i] = 0;
			score += 100;
		}
		else if (Mtype[i] == 3) {//�~�܂��Ă�b���𓥂񂾎�
			Mtype[i] = MOVE_KORA;//�b���������悤�ɂȂ�
			if (marioX + MariowideX <= monX[i] + 25) {
				monSide[i] = 1;
			}
			else monSide[i] = -1;
			monMove[i] = 10 * monSide[i];
		}
		else if (Mtype[i] == NOKONOKO) {//�m�R�m�R�𓥂񂾎�
			Mtype[i] = STOP_KORA;//�b���ɂȂ�
			crol[i] = 10;
			monMove[i] = 0;
			score += 100;
		}
		MarioLevelUp(i, coin, mario, marioLV, marioX,marioY, superplus, MariowideX, score);//�}���I���A�C�e�����l�������Ƃ�

		return jumping;
	}
	else {
		return 0;
	}
}

//�e���T���e���T�ɓ���������
//�@�@�@�@�@�@�@�@�i���������Ă��郂���X�^�[�̔ԍ��A�����X�^�[�̑����A�e���T�̍��W�j
int TeresaTouchTeresa(int i, int &num,int x1,int x2,int y1 ,int y2) {
	for (int h = 0; h <= num; h++) {
		if (monEnd[h] == 1)continue;
		if (i != h &&  y2 >= monY[h] && y1 <= monY[h] + 25 &&
			x2  >= monX[h] && x1 <= monX[h] + 25)  {//�e���T�������X�^�[�ɓ������Ă���Ƃ�
			if (Mtype[h] == MOVE_TERESA) {//�e���T���������Ă���̂��e���T�̎�
				return 1;
			}
		}
	}
	return 0;
}

//�e���T�����ɓ���
//           (���������Ă��郂���X�^�[�̔ԍ��A�}���I��X���W�A�}���I�̌����A�����X�^�[�̑����A�e���T�̍��W�A�e���T���ړ����邩�ǂ���)
void TeresaMoveX(int i,int marioX,int marioDirection,int num,int &x1,int &x2,int y1,int y2,int &moveX) {
	if (monX[i] > marioX) {//�}���I���e���T��荶�ɂ���Ƃ�
		x1 -= 2;//���ׂ�X���W���ړ���ɂ���
	}
	else if (monX[i] < marioX) {//�}���I���e���T���E�ɂ���Ƃ�
		x2 += 2;//���ׂ�X���W���ړ���ɂ���
	}
	if (TeresaTouchTeresa(i, num, x1, x2, y1, y2) == 0) {//�e���T���e���T�ɓ������ĂȂ��Ƃ�
		moveX = 1;//���ɓ������Ƃ��ł���
	}
	else {//�e���T���e���T�ɓ������Ă�����AX���W�����ɖ߂�
		x1 = monX[i];
		x2 = monX[i] + 25;
	}
	if (moveX == 1) {//�e���T���ړ��ł���Ƃ�
		if (monX[i] > marioX) {//�}���I���e���T��荶�ɂ���Ƃ�
			monSide[i] = -1;
			monX[i] -= 2;//�e���T�����Ɉړ�������
		}
		else if (monX[i] < marioX) {//�}���I���e���T���E�ɂ���Ƃ�
			monSide[i] = 1;
			monX[i] += 2;//�e���T���E�Ɉړ�������
		}
		else monSide[i] = marioDirection;//�e���T�ƃ}���I��X���W���������炢�̎��A�e���T�ƃ}���I�̌����𓯂��ɂ���
	}
	else {
		monSide[i] = marioDirection;//�}���I�Ɠ�������������

	}
}


//�e���T���c�Ɉړ�����
//            (���������Ă��郂���X�^�[�̔ԍ��A�}���I��Y���W�A�}���I�̌����A�����X�^�[�̑����A�e���T�̍��W�A�e���T���ړ��ł��邩�ǂ���)
void TeresaMoveY(int i, int marioY, int marioDirection, int num, int x1, int x2, int &y1, int &y2, int &moveY) {
	if (monY[i] > marioY) {//�}���I���e���T����ɂ���Ƃ�
		y1--;//�e���T��Y���W���ړ���ɂ���
	}
	else if (monY[i] < marioY) {//�}���I���e���T��艺�ɂ���Ƃ�
		y2++;//�e���T��Y���W���ړ���ɂ���
	}
	if (TeresaTouchTeresa(i, num, x1, x2, y1, y2) == 0) {//�e���T���e���T�ɓ������ĂȂ��Ƃ�
		moveY = 1;//�c�ɓ������Ƃ��ł���
	}
	else {//�e���T���e���T�ɓ������Ă�����
		//�e���T��Y���W�����ɖ߂�
		y1 = monY[i];
		y2 = monY[i] + 25;
	}

	if (moveY == 1) {//�����e���T���ړ��ł���Ƃ�
		if (monY[i] > marioY) {//�}���I���e���T����ɂ���Ƃ�
			monY[i] --;//�e���T����Ɉړ�������
		}
		else if (monY[i] < marioY) {//�}���I���e���T��艺�ɂ���Ƃ�
			monY[i] ++;//�e���T�����Ɉړ�������
		}
	}
}


//�e���T������
//                (���������Ă��郂���X�^�[�̔ԍ��A�}���I�̍��W�A�}���I�̌����A�����X�^�[�̑����A�X�R�A�A�����X�^�[���~�܂��Ă��邩�ǂ���)
void TeresaMoveToMario(int i, int marioX, int marioY, int marioDirection,int &num,long&score,int &monstop) {
	//�e���T
	if (Mtype[i] == MOVE_TERESA) {
		int x1 = monX[i];
		int x2 = monX[i] + 25;
		int y1 = monY[i];
		int y2 = monY[i] + 25;
		int moveX = 0;
		int moveY = 0;
		
		TeresaMoveX(i, marioX, marioDirection, num, x1, x2, y1, y2, moveX);//���ɓ���

		TeresaMoveY(i, marioY, marioDirection, num, x1, x2, y1, y2, moveY);//�c�ɓ���
		
	}
}


//�e���T���A�������Ƃ�Ă����ԂɂȂ邩
//�@�@�@�@�@�@�@�@�@�i���������Ă��郂���X�^�[�̔ԍ��A�}���I�̌����A�}���I��X���W�j
void TeresaTypeChange(int i, int marioDirection, int marioX) {
	if (Mtype[i] == MOVE_TERESA) {//���ʂɓ�����Ƃ�
		if ((marioDirection == 1 && monX[i] >= marioX) || (marioDirection == -1 && monX[i] < marioX)) {//�}���I���e���T�̂ق����������Ƃ�
			Mtype[i] = STOP_TERESA;//�Ƃ��
		}
	}
	if (Mtype[i] == STOP_TERESA) {//�e���T���Ƃ�Ă���Ƃ�
		if (monX[i] > marioX) {//�}���I���e���T��荶�ɂ���Ƃ�
			monSide[i] = -1;//��������
		}
		else if (monX[i] < marioX) {//�}���I���e���T���E�ɂ���Ƃ�
			monSide[i] = 1;//�E������
		}
		else monSide[i] = 1;
		if ((marioDirection == 1 && monX[i] <= marioX) || (marioDirection == -1 && monX[i] > marioX)) {//�}���I���e���T�̂ق��������ĂȂ��Ƃ�
			Mtype[i] = 10;//�e���T���s�ʂɓ�����悤�ɂȂ�
		}
	}
}

//�e���T�ɂ��Ă̂���
//�@�@�@�@�@�@�@�i���������Ă��郂���X�^�[�̔ԍ��A�}���I�̍��W�A�}���I�̌����A�}���I�̑����A�X�R�A�A�����X�^�[���~�܂��Ă��邩�ǂ����j
void AboutTeresa(int i, int marioX, int marioY, int marioDirection, int &num, long&score, int &monstop) {
	TeresaMoveToMario(i, marioX, marioY, marioDirection,num, score, monstop);//�e���T���A�}���I�̂ق��֓���

	TeresaTypeChange(i, marioDirection, marioX);//�e���T���A�������Ƃ�Ă����ԂɂȂ邩
}



//�����X�^�[�ɂ��Ă̑S���̏���
void MonsterDataSet(int &jumping, int &num, int &marioLV, int &end, int &bullet, int &stmove, int &coin, int &mario, int &jump, int &last, int &marioX,
	int &marioY, int &monstop, int &monWide, int &move, double &nuton, double &nutonLV,
	double &nutonmax, long &score, int &marioDirection, int &stop, int &superplus, int &MariowideX,int dying,int MariowideY) {

	int fall;//���������ǂ����A�����Ă��Ȃ�A�ړ����ɂ͗����Ȃ�

	for (int i = 0; i <= num; i++) {//�G�̏���  �G�̏����@�@�@�@�@�G�̏����@�@�@�G�̏���
		if (dying == 1)break;
		if (MonsterDelete(i, num) == 1) {
			continue;
		}
		//���񂾃����X�^�[�̃f�[�^���������鏈��

		fall = 0;//���������ǂ����A�����Ă��Ȃ�A�ړ����ɂ͗����Ȃ�

		BulletAttackMonster(i, bullet,stmove);//�e�������X�^�[�ɓ����������ǂ��������鏈��

		for (int g = 0; g<5; g++) {//�T�̕�����������
			if (MonsterFall(i, stop, num) == 1) {//�����X�^�[�������鏈��
				fall = 1;//�������Ƃ��A�������Ɛݒ肷��
			}
			else break;//�����Ȃ������Ƃ��A��߂�
		}
		


		//�����X�^�[����ʊO(�E��������)�ɏo���Ƃ��A������
		if (monX[i] + 25 - stmove < 0) {
			monEnd[i] = 1;
		}
		if (monY[i] >= 500)monEnd[i] = 1;


		KillerGo(i);//�L���[������

		SpineChange(i, marioX, marioY,MariowideY);//�Ƃ����A��Ƀ}���I������Ώ�ɏオ��悤�ɕς��

		SpineUp(i, MariowideX, marioX, marioY, superplus, end);//�Ƃ�����ɏオ��

		DossunUpOrChange(i, marioX, marioY,num);//�h�b�X�����オ�邩�A���Ƀ}���I������Ή��ɗ����Ă���悤�ɕς��

		DossunFall(i,num);//�h�b�X���������Ă���

		HodaiCreate(i, MariowideX, MariowideX, marioX, marioY, superplus, move, num, stmove);//�C�䂪�����X�^�[���o��

		MonsterTouchBlock(i, score, coin, mario, monWide, num);//�����X�^�[����Q���ɓ���������

		monstop = 0;//�����X�^�[��������

		MonterTouchOtherMonster(i, num, score, monstop);//�G���A�Ⴄ�G�ɐG�ꂽ�Ƃ�


		MonsterMove(i, monWide, monstop, stop,num,fall);//�����X�^�[�𓮂���


		KoraDisappear(i, stmove);//�b�����A�s���߂���������Ƃ��ɏ���

		MonsterTouchMario(i, marioX, marioY, superplus, end, coin, mario, marioLV, MariowideX,score);//�����X�^�[���}���I�ɓ���������


		MarioStampMonster(score, nuton, nutonLV, nutonmax, jumping, jump, end, marioX, marioY, MariowideX, coin, mario, superplus, marioLV, 
			i, marioDirection);//�}���I�������X�^�[�𓥂񂾎�

		AboutTeresa(i, marioX, marioY, marioDirection, num, score, monstop);//�e���T�ɂ��Ă̏���
	}
	//�G�̏����I���
}
//�����܂œG�̏���








//�}���I�̉E���ɏ�Q�����Ȃ��i�ނƂ�
//�@�@�@�@�@�@�@�@�@�@�@�i�����邩�ǂ����A�X�N���[�����邩�ǂ����A�}���I��X���W�A�}���I�̒ǉ���Y���W�j
void MarioRightMoveSafely(int move, int moving, int &marioX, int &stmove) {

	if (move != 1) {
		marioX += 5;//�E�ɐi��
	}
	if (marioX <= 2590 && marioX - stmove >= 300) {//�}���I����ʂ̒[�̂ق��łȂ��Ƃ�
		if (moving == 1) {
			if (move != 1)stmove += 5;//�X�N���[������
		}
	}
}

//�}���I�̉E���Ƀu���b�N�����邩�ǂ���
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�i�}���I�̍��W�A�}���I�̕��A�}���I�̒ǉ���Y���W�j
int  MarioRightMoveStopByBlock(int marioX, int marioY, int MariowideX, int MariowideY, int superplus) {
	int x = (marioX + MariowideX + 1) / 30;//�}���I�̉E����X���W
	int y;//�}���I��Y���W
	int last = 0;//�����邩�ǂ���
	for (int i = marioY + 1; i <= marioY + MariowideY + superplus - 1; i++) {
		y = 20 - i / 30;
		if (stage[x][y] > EMPTY && stage[x][y] != HALFFLAG1 && stage[x][y] != HALFFLAG2) {//�}���I�̉��ɒ��Ԃ̊��łȂ���Q��������Ƃ�
			last = 1;//�����Ȃ�
			break;
		}
	}//�}���I�̉E���ɏ�Q�������邩�ǂ���
	return last;
}


//�}���I�̉E���ɖC�䂪���邩�ǂ���
//                           (�����X�^�[�̑����A�}���I�̍��W�A�}���I�̉��̕��A�}���I�̒ǉ���Y���W)
int MarioRightMoveStopByHodai(int num, int marioX, int marioY, int MariowideX, int superplus) {
	for (int i = 0; i <= num; i++) {
		if (Mtype[i] >= 100) {//�C��̎�

			//�}���I�̉E���������悻�C��ɐG��Ă���Ƃ�
			if ((marioX + MariowideX) / 5 == monX[i] / 5 && marioY - 1 <= monY[i] + 25 && marioY + MariowideX + superplus + 1 >= monY[i]) {
				return 1;//�����Ȃ�
			}
		}

	}//�����X�^�[�S���̌Ăяo��

	return 0;
}


//�}���I���E�ɓ����邩�ǂ���
//           (�X�R�A�A�X�N���[�����A�}���I�̎c��A�R�C�����A�}���I�̍��W�A�}���I�̕��A�}���I�̒ǉ���Y���W�A�@�����邩�ǂ����A
//   �@�@�@�@�X�N���[�����邩�ǂ����A�����X�^�[�̑����A���̏ꏊ�A�����Ƃ������ǂ����A���̏ꏊ�A���̍��W�A�}���I�̏��)
void MarioRightMoveStop(long &score, int &stmove, int &mario, int &coin, int &marioX, int &marioY, int &MariowideX, int MariowideY, int &superplus,
	int move, int moving, int num,int dpla,int &flag,int &flagStage,int &flagX,int &flagY,int &marioLV) {

	
	CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);//�R�C�����l������
	FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY,marioLV);//���Ԃ̊����l������

	if (MarioRightMoveStopByBlock(marioX, marioY, MariowideX, MariowideY, superplus) == 0 &&
		MarioRightMoveStopByHodai(num, marioX, marioY, MariowideX, superplus) == 0) {//������Ƃ�

		MarioRightMoveSafely(move, moving, marioX, stmove);//�E�ɓ���
	}

}

//�E�ɓ�������̂܂Ƃ�
void MarioRightMove(long &score, int &mario, int &coin, int &marioX, int &marioY, int &move,
	int clear, int &marioLV, int end, int &marioDirection, int &MariowideX, int MariowideY, int &superplus, int &stmove, int moving, int jump, int speed, 
	int num, int dying, int dokanchange,int dpla, int &flag,int &flagStage, int &flagX, int &flagY) {

	if (dokanchange == 0 && clear == 0 && dying == 0 && Key[KEY_INPUT_RIGHT] >= 1) {//�E�{�^�����������Ƃ�
		marioDirection = 1;
		for (int h = 0; h < speed; h++) {//�����̕������i��

			MarioRightMoveStop(score, stmove, mario, coin, marioX, marioY, MariowideX, MariowideY, superplus, move, moving, num ,dpla, flag,flagStage, 
				flagX, flagY,marioLV);//�E�ɐi�߂邩�ǂ���

		}//�����̕��̌J��Ԃ�
		move = 1;
	}//�E�{�^������͂������ǂ���
}

//�E�֐i�ޓ���




//���ɁA��Q�����Ȃ��i�ނƂ�
//�@�@�@�@�@�@�@�@�@�@�i�}���I��X���W�A�X�N���[�����A�����邩�ǂ����j
void MarioLeftMoveSafely(int &marioX, int stmove, int move) {
	if (marioX >= 5 + stmove) {
		if (move != -1) {
			marioX -= 5;//���ɐi��
		}
	}
}
//�}���I�ɍ��Ƀu���b�N�����邩�ǂ���
//�@�@�@�@�@�@�@�@�@�@�@�@�i�}���I�̍��W�A�}���I�̕��A�}���I�̒ǉ���Y���W�j
int  MarioLeftMoveStopByBlock(int marioX, int marioY, int MariowideX, int MariowideY, int superplus) {
	int x = (marioX - 1) / 30;//�}���I�̍�����X���W
	int y;//�}���I��Y���W
	int last = 0;//��Q���ɐG�ꂽ���ǂ���
	for (int i = marioY + 1; i <= marioY + MariowideY + superplus - 1; i++) {
		y = 20 - i / 30;
		if (stage[x][y] > EMPTY && stage[x][y] != HALFFLAG1 && stage[x][y] != HALFFLAG2) {//�}���I�̍����ɒ��Ԃ̊��ȊO�̏�Q�������邩�ǂ���
			last = 1;
			break;
		}
	}
	return last;
}


//�}���I�̍����ɖC�䂪���邩�ǂ���
//                       (�����X�^�[�̑����A�}���I�̍��W�A�}���I�̉��̕��A�}���I�̒ǉ���Y���W)
int MarioLeftMoveStopByHodai(int num, int marioX, int marioY, int MariowideX, int superplus) {
	for (int i = 0; i <= num; i++) {
		if (Mtype[i] >= 100) {//�C��̂Ƃ�

			//�}���I�̍����������悻�C��ɐG��Ă���Ƃ�
			if ((marioX - 1)/ 5 == (monX[i] + 25) / 5 && marioY - 1 <= monY[i] + 25 && marioY + MariowideX + superplus + 1 >= monY[i]) {
				return 1;
			}
		}

	}//�����X�^�[�S���̌Ăяo��

	return 0;
}


//�}���I�����ɓ����邩�ǂ���
//�@�@�@�@�@�i�X�N���[�����A�ړ��ł��邩�ǂ����A�}���I�̍��W�A�}���I�̕��A�}���I�̒ǉ���Y���W�A�����X�^�[�̑����A�R�C�����A
//�@�@�@�@�@�@�}���I�̎c��A���̃X�e�[�W�̏ꏊ�A���Ԃ̊����Ƃ������ǂ����A���Ԃ̊��̍��W�A�}���I�̏�ԁj
void MarioLeftMoveStop( int &stmove, int &move, int &marioX,int &marioY, int &MariowideX, int MariowideY, int &superplus, int num,int &coin,
	int &mario,int &dpla,int &flag,int &flagStage,int &flagX,int &flagY,int &marioLV) {
	
	CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);//�R�C�����l������
	FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY, marioLV);//���Ԃ̊����l������

	if (MarioLeftMoveStopByBlock(marioX, marioY, MariowideX, MariowideY, superplus) == 0 &&
		MarioLeftMoveStopByHodai(num, marioX, marioY, MariowideX, superplus) == 0) {//���ɓ�����Ƃ�

		MarioLeftMoveSafely(marioX, stmove, move);//���ɓ���
	}
}

//�}���I�����ɓ�������̂܂Ƃ�
void MarioLeftMove(long &score, int &mario, int &coin, int &marioX, int &marioY, int &move, int clear, int &marioLV, int end,int &marioDirection,
	int &MariowideX, int MariowideY, int &superplus, int stmove, int moving, int jump, int speed, int num, int dying, int dokanchange,  int &dpla,
	int &flag, int &flagStage, int &flagX,int &flagY) {
	if (dokanchange == 0 && clear == 0 && dying == 0 && Key[KEY_INPUT_LEFT] >= 1) {//���{�^���������ꂽ�Ƃ�
		marioDirection = -1;
		for (int h = 0; h < speed; h++) {
			MarioLeftMoveStop( stmove, move,marioX, marioY, MariowideX, MariowideY, superplus, num, coin, mario, dpla, flag, flagStage, flagX,flagY, 
				marioLV);//���ɓ�����Γ���

		}//�����̕��̌J��Ԃ�
		move = -1;
	}//���L�[�������ꂽ���ǂ���
}


//�E�ɓ�������ƍ��ɓ�������̂܂Ƃ�
void LeftAndRightMove(long &score, int &mario, int &coin, int &marioX, int &marioY, int &move,
	int clear, int &marioLV, int end, int &marioDirection, int &MariowideX, int MariowideY, int &superplus, int &stmove, int moving, int jump, int num, 
	int dying, int dokanchange, int dpla, int &flag,int &flagStage, int &flagX, int &flagY) {

	//�W�����v���łȂ��Ƃ��ɍ��V�t�g�L�[�������ƁA�}���I�������Ȃ�
	int speed;//�ړ����鑬��
	if (jump == 0 && Key[KEY_INPUT_LSHIFT] >= 1) {
		speed = 2;
	}
	else {
		speed = 1;
	}

	
	MarioRightMove(score, mario, coin, marioX, marioY, move, clear, marioLV, end, marioDirection, MariowideX, MariowideY, superplus, stmove, moving, jump, speed, num,
		dying, dokanchange, dpla, flag,flagStage, flagX, flagY);//�E�Ɉړ�����

	MarioLeftMove(score, mario, coin, marioX, marioY, move, clear, marioLV, end, marioDirection, MariowideX, MariowideY, superplus, stmove, moving, jump, speed, num, 
		dying, dokanchange, dpla, flag, flagStage,flagX, flagY);//���Ɉړ�����
}
//���E�̈ړ��̏I���


//�}���I���C��ɗ����Ă��邩�ǂ���
//�@�@�@�@�@�@�@�@�@�i�����X�^�[�̑����A�}���I�̍��W�A�}���I�̕��A�}���I�̒ǉ���Y���W�j
int  MarioTouchToHodai(int num, int marioX, int marioY, int MariowideX, int MariowideY, int superplus) {
	for (int i = 0; i <= num; i++) {
		if (Mtype[i] >= 100) {
			if (marioX - 1 <= monX[i] + 25 && marioX + MariowideX - 1 >= monX[i]) {//�}���I�ƖC���X���W���G��Ă���Ƃ�
				if (marioY - 1 <= monY[i] + 25 && marioY + MariowideY + superplus - 1 >= monY[i]) {//�}���I�ƖC���Y���W���G��Ă���Ƃ�
					return 1;//�}���I�͖C��ɗ����ĂĂ���
				}
			}
		}
	}
	return 0;//�}���I�͖C��ɗ����Ă��Ȃ�
}


//�}���I���n�ʂɗ����Ă��邩�ǂ���
//�@�@�@�@�@�@�@�@�i�}���I�̍��W�A�}���I�̕��A�}���I�̒ǉ���Y���W�j
int MarioTouchFloor(int marioX, int marioY, int MariowideX, int MariowideY, int superplus) {
	int x1 = (marioX + 1) / 30;//�}���I�̍���X���W
	int x2 = (marioX + MariowideX - 5) / 30;//�}���I�̉E��X���W
	int y = 20 - (marioY + MariowideY + superplus) / 30;//�}���I�̉�����Y���W

	if ((stage[x1][y] == EMPTY || stage[x1][y] == HALFFLAG2) && (stage[x2][y] == EMPTY || stage[x2][y] == HALFFLAG2)) {//�}���I�����Ԃ̊��łȂ��n�ʂɗ����Ă��Ȃ��Ƃ�
		return 0;
	}
	else {//�����Ă���Ƃ�
		return 1;
	}
}

//�}���I��������Ƃ�
//�@�@�@�@�i�y�ǂňړ����邩�ǂ����A�W�����v���Ă��邩�ǂ����A�}���I�̒ǉ���Y���W�A�}���I�̕��A�N���A�������ǂ����A�}���I�̏�ԁA�}���I�̃_���[�W�A
//�@�@�@�@�}���I�̍��W�A�}���I�̎c��A�R�C�����A�X�R�A�A�j
void MarioFall(int dokanchange, int &jump, int num, int &superplus, int &MariowideX, int MariowideY, int clear, int &marioLV, int &end, int &marioX, int &marioY, 
	int &mario,int &coin, long &score, double & nuton, double & nutonmax, double &nutonLV, int &jumping, int marioDirection, int dpla, int &flag, int &flagStage,
	int &flagX, int &flagY) {


	if (clear == 0 && !(marioLV == 1 && end == 1) && jump == 0 && dokanchange == 0) {
		int last = 0;
		for (int i = 0; i < 15; i++) {

			CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);//�R�C�����l������
			FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY,marioLV);//���Ԃ̊����l������

			for (int h = 0; h <= num; h++) {
				if (MarioStampMonster(score, nuton, nutonLV, nutonmax, jumping, jump, end, 
					marioX, marioY, MariowideX, coin, mario, superplus, marioLV, h,marioDirection) == 1) {//�}���I�������X�^�[�𓥂񂾎�
					last = 1;
					break;//�}���I�͗����Ȃ�
				}
			}
			if (last == 1)break;
			if (MarioTouchFloor(marioX, marioY, MariowideX, MariowideY, superplus) == 0) {//�}���I�����ɂ��Ȃ��āA
				if (MarioTouchToHodai(num, marioX, marioY, MariowideX, MariowideY, superplus) == 0) {//�}���I���C��̏�ɂ����Ȃ��Ƃ��A
					marioY++;//�}���I�͗�����
				}
			}

		}
	}
}

//�}���I���W�����v����Ƃ��́A�f�[�^���Z�b�g����
//                    (�W�����v�̏㉺���鑬���A�d�͉����x�A�d�͉����x�̏���A�W�����v���Ă��邩�ǂ����A�����X�^�[�ɂ���ăW�����v���邩�ǂ����A
//�@�@�@�@�@�@�@�@�@�@�@�}���I��Y���W�A�W�����v�̑����⍂���̒���)
void MarioJumpStartDataSet(double &nuton, double &nutonLV, double &nutonmax, int &jump, int &jumping, int &marioY, double control) {
	jump = 1;
	nuton = 0;
	nutonLV = 1.5;
	nutonmax = 19 + control;
	marioY -= 3;
}

//�}���I���A�����X�^�[�𓥂ނ��ƂŃW�����v����Ƃ�
//         (�X�R�A�A�W�����v�̏㉺���鑬���A�d�͉����x�A�d�͉����x�̏���A�����X�^�[�ɂ���ăW�����v���Ă��邩�ǂ����A�W�����v���Ă��邩�ǂ����A
//       �}���I�̃_���[�W�A�}���I�̍��W�A�}���I�̉��̕��A�R�C�����A�}���I�̎c��A�}���I�̒ǉ���Y���W�A�}���I�̏�ԁA�����X�^�[�̑����A�}���I�̌���)
int MarioJumpStartOnMonster(long &score, double &nuton, double &nutonLV, double &nutonmax, int &jumping, int &jump, int &end, int &marioX,
	int &marioY, int &MariowideX, int &coin, int &mario,int &superplus, int &marioLV, int num, int marioDirection) {
	int last = 0;
	for (int i = 0; i <= num; i++) {//�����X�^�[�S�����Ăяo��

		//�}���I�������X�^�[�𓥂񂾎�
		if (MarioStampMonster(score,nuton,nutonLV,nutonmax,jumping,jump,end,marioX,marioY,MariowideX,coin,mario,superplus,marioLV,i,marioDirection) == 1) {
			last = 1;//�W�����v����
			break;
		}
	}
	return last;
}


//�}���I���W�����v���n�߂�
//           (�X�R�A�A�R�C�����A�}���I�̎c��A�����X�^�[�ɂ���ăW�����v�����Ƃ��A�W�����v���Ă��邩�ǂ����A�W�����v�̏㉺�̑����A�d�͉ߑ��x�̏���A
//�@�@�@�@�@�d�͉����x�A�}���I�̏�ԁA�}���I�̍��W�A�}���I�̕��A�}���I�̒ǉ���Y���W�A�����X�^�[�̑����A�}���I�̌����A�X�e�[�W�̏ꏊ�A
//�@�@�@�@�@���Ԃ̊����Ƃ������ǂ����A���Ԃ̊��̏ꏊ�A���Ԃ̊��̍��W�A�}���I������ł��邩�ǂ���)
void MarioJumpStart(long &score, int &coin, int &mario, int &jumping, int &jump, double &nuton, double &nutonmax, double &nutonLV, int &clear,
	int &marioLV,int end, int &marioX,int &marioY,  int &MariowideX, int MariowideY, int &superplus, int num, int marioDirection, int dpla, int &flag, 
	int &flagStage, int &flagX, int &flagY,int dying) {

	int x1 = (marioX + 1) / 30;//�}���I�̍���X���W
	int x2 = (marioX + MariowideX - 1) / 30;//�}���I�̉E��X���W
	int y = 20 - (marioY + superplus + MariowideY + 2) / 30;//�}���I�̉�����Y���W

	CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);//�}���I���R�C�����l������
	FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY,marioLV);//�}���I�����Ԃ̊����l������


	if (clear == 0 && dying == 0) {//����łȂ��āA�N���A�����ĂȂ��Ƃ�

		//�n�ʂɗ����Ă��āA�W�����v������Ƃ�
		if (Key[KEY_INPUT_UP] == 1 && jump == 0 && ((stage[x1][y] >= 1 && stage[x1][y] != 8 && stage[x1][y] != 9 )|| 
			(stage[x2][y] >= 1 && stage[x2][y] != 8 && stage[x2][y] != 9))){
			MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, 0);
		}
		//�C��̏�ɂ��āA�W�����v����Ƃ�
		else if (MarioTouchToHodai(num, marioX, marioY, MariowideX, MariowideY, superplus) == 1 && clear == 0 
			&& Key[KEY_INPUT_UP] == 1 && jump == 0) {//
			MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, 0);
		}
		//�����X�^�[�𓥂�ŃW�����v����Ƃ�
		else if (MarioJumpStartOnMonster(score, nuton, nutonLV, nutonmax, jumping, jump, end, marioX, marioY, MariowideX, coin, mario, superplus, marioLV, num, marioDirection) == 1) {
			if (Key[KEY_INPUT_UP] == 0) {//��{�^����������Ȃ������Ƃ�
				MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, -4);//�������W�����v���n�߂�
			}
			else {//��{�^�����������Ƃ�
				MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, 2);//�傫���W�����v���n�߂�
			}
		}
	}
	if (jump != 1)Key[KEY_INPUT_UP] = 0;

}


//�n�ʂɂ��āA�W�����v����߂�Ƃ�
//              (�}���I�̍��W�A�}���I�̒ǉ���Y���W�A�}���I�̕��A�W�����v���Ă��邩�ǂ����A�����X�^�[�ɂ���ăW�����v���Ă��邩�ǂ���)
int MarioJumpStop(int marioX, int &marioY, int superplus, int MariowideX, int MariowideY, int &jump, int &jumping) {
	int x1 = (marioX + 1) / 30;//�}���I�̍�����X���W
	int x2 = (marioX + MariowideX - 1) / 30;//�}���I�̉E����X���W
	int y = 20 - (marioY + superplus + MariowideY + (jump - 1)) / 30;//�}���I�̉�����Y���W


	//�}���I���n�ʂɗ����Ă���Ƃ�
	if (stage[x1][y] > EMPTY && stage[x1][y] != HALFFLAG1 && stage[x1][y] != HALFFLAG2 
		|| stage[x2][y] > EMPTY && stage[x2][y] != HALFFLAG1 && stage[x2][y] != HALFFLAG2) {
		//�W�����v����߂�
		jump = 0;
		jumping = 0;
		return 1;
	}
	else {
		return 0;
	}
}


//�P�t���[�����̃W�����v�����I������Ƃ�
//               (�W�����v���̃}���I��Y���W�A�W�����v��������A�W�����v����O�̃}���I��Y���W�A�W�����v�̑����A�d�͉����x�̏��)
int OneFrameJumpEnd(int h, int plus, int basemarioY, double nuton, double nutonmax) {
	if (plus == 1) {//�W�����v�ŁA�㏸��
		if (h > (basemarioY + nutonmax - nuton)) {
			return 1;
		}
	}
	else if (plus == -1) {//�W�����v�ŁA������
		if (h < (basemarioY + nutonmax - nuton)) {
			return 1;
		}
	}
	return 0;
}


//�W�����v���̍ŏ��̃f�[�^����
//                 (�W�����v�̑����A�d�͉����x�A�d�͉����x�̏���A�W�����v���Ă��邩�ǂ����A�W�����v�̌����A�W�����v����O�̃}���I��Y���W�A
//                �W�����v���̃}���I��Y���W�A�}���I��Y���W�A�����X�^�[�ɂ���ăW�����v���Ă��邩�ǂ���)
void MarioJumpDataSet(double &nuton, double nutonLV, double nutonmax, int &jump, int &plus, int &basemarioY, int &h, int marioY, int jumping) {
	nuton += nutonLV;//�d�͉����x�𑫂�
	if (jump == 1 && Key[KEY_INPUT_UP] == 0 && jumping == 0) {//�W�����v���ɏ�{�^����������ĂȂ��Ƃ�
		jump = 2;//�W�����v���A�����ɑ���
		nuton = (nutonmax + nutonmax - nuton) / 2 + 5;
	}
	if (jump == 1) {//�W�����v���㏸���̎��A
		plus = 1;
	}
	else if (jump == 2) {//�W�����v���������̎�
		plus = -1;
	}
	basemarioY = marioY;
	h = marioY;
}


//�}���I�̃W�����v���̏����̂܂Ƃ�
void MarioJumping(long &score, int &bullet, int & monWide, int &monstop, int stop, int &jump, int &marioX, int &marioY, double &nutonmax, double &nuton,
	double &nutonLV, int &superplus, int &marioDirection, int &move, int &stmove, int &coin, int &mario,
	int &MariowideX, int &MariowideY, int clear, int &marioLV, int &end, int num, int moving, int &jumping, int dying, int dokanchange, int dpla, int &flag,
	int &flagStage, int &flagX, int &flagY) {

	if (jump >= 1) {
		int last = 0;
		int h;
		int plus;
		int basemarioY;

		MarioJumpDataSet(nuton, nutonLV, nutonmax, jump, plus, basemarioY, h, marioY, jumping);

		//�W�����v�ɂ��A�ړ��̎n�܂�
		for (;;) {

			CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);//�}���I���R�C�����l������
			FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY,marioLV);//�}���I�����Ԃ̊����l������

			//1�t���[�����̃W�����v���I��������A�W�����v�𒆒f����
			if (OneFrameJumpEnd(h, plus, basemarioY, nuton, nutonmax) == 1) {
				break;
			}

			//�}���I���A�C��̏�ɗ��������A�W�����v����߂�
			if (jump == 2 && MarioTouchToHodai(num, marioX, marioY, MariowideX, MariowideY, superplus) == 1) {
				jump = 0;
				jumping = 0;
				break;
			}

			//�}���I���A�n�ʂɂ��ăW�����v����߂�Ƃ�
			if (MarioJumpStop(marioX, marioY, superplus, MariowideX, MariowideY, jump, jumping) == 1) {
				break;
			}
			else {
				marioY -= plus;//�}���I���A�W�����v�ňړ�����
			}
			
			//�W�����v�ɂ��㏸���A�ƂĂ��������Ȃ������A�W�����v�𗎉��ɕς���
			if (jump == 1 && nutonmax - nuton < 2) {
				jump = 2;
				nuton += 4;
			}


			MarioRightMove(score, mario, coin, marioX, marioY, move, clear, marioLV, end, marioDirection, MariowideX, MariowideY, superplus, stmove, moving, jump, 1, num, dying, 
				dokanchange, dpla, flag,flagStage,flagX, flagY);//�W�����v���A�E�ɓ���

			MarioLeftMove(score, mario, coin, marioX, marioY, move, clear, marioLV, end, marioDirection, MariowideX, MariowideY, superplus, stmove, moving, jump, 1, num, dying,
				dokanchange, dpla, flag, flagStage,flagX, flagY);//�W�����v���A���ɓ���

			//�}���I���A�����X�^�[�𓥂񂾎�
			if (MarioJumpStartOnMonster(score, nuton, nutonLV, nutonmax, jumping, jump, end, marioX, marioY, MariowideX, coin, mario, superplus, marioLV, num, marioDirection) == 1) {
				if (Key[KEY_INPUT_UP] == 0) {//��{�^���������Ȃ������Ƃ�
					MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, -1);//�������W�����v���n�߂�
				}
				else {//��{�^�����������Ƃ�
					MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, 3);//�傫���W�����v���n�߂�
				}
				break;
			}

			h += plus;
		}
	}
	//�W�����v�̏������I���������܂���
}

//�ړ��H���I���



//�y�ǂɓ��邩�ǂ���
//�@�@�@�@�@�@�@�@�@�i�y�ǂňړ������A�y�ǂňړ����邩�ǂ����A�y�ǂňړ����̎��ԁA�ړ���̓y�ǂ̍��W�A�}���I�̍��W�A�}���I�̕��A�N���A�������ǂ����A
//�@�@�@�@�@�@�@�@�@�@�}���I�����񂾂��ǂ����j
void DokanGetIntoStart(int &dokan, int &dokanchange, int &count, int &Xdokan, int &Ydokan, int marioX, int marioY, int MariowideY, int superplus, int MariowideX, 
	int clear, int dying) {

	int x1 = marioX  / 30;//�}���I�̍���X���W
	int x2 = (marioX + MariowideX - 10) / 30;//�}���I�̉E��X���W
	int y = 20 - (marioY + MariowideY + superplus + 1) / 30;//�}���I�̉�����Y���W

	if (dokanchange == 0 && clear == 0 && dying == 0 && Key[KEY_INPUT_DOWN] == 1 && stage[x1][y] >= DOKANUP_MOVE && stage[x2][y] >= DOKANUP_MOVE) {//�y�ǂɂ͓����Ƃ�
		//�y�ǂɂ��ړ��̃f�[�^���Z�b�g����
		dokan = stage[x1][y] % 10;
		dokanchange = 1;
		count = 0;
		Xdokan = x1;
		Ydokan = y;
	}
}


//�}���I���y�ǂɂ͂��蒆�̎�
//�@�@�@�@�@�@�@�@�i�}���I���y�ǂɂ͂����Ă��鎞�ԁA�}���I��Y���W�A�y�ǂňړ����邩�ǂ����A�}���I�̒ǉ���Y���W�A���̃X�e�[�W�̏ꏊ�j
int DokanGettingInto(int &count, int &marioY, int dokanchange, int superplus, int dpla) {
	if (dokanchange == 1) {//�y�ǂňړ�����Ƃ�
		count++;//���Ԃ�i�߂�
		marioY += 5;//�}���I�����Ɉړ�������
		if (count >= 8 + superplus / 4) {//�}���I���A�y�ǂɓ���؂�����
			for (int h = 0; h <= 24; h++) {
				for (int i = 0; i <= 99; i++) {
					if (dstage[dpla][i][h] >= EMPTY) {//���̃X�e�[�W�f�[�^��ۑ�����
						dstage[dpla][i][h] = stage[i][h];
					}
				}
			}
			count = 0;
			return 1;//�y�ǂł̈ړ���֍s��
		}
	}

	return 0;
}

//�y�ǂɓ���Ƃ��̏����̂܂Ƃ�
int  DokanGetInto(int &dokanchange, int &count, int &dokan, int &Xdokan, int &Ydokan, int &marioY, int marioX, int clear, int marioLV, int end, int MariowideX, 
	int MariowideY, int superplus, int dpla, int dying) {

	DokanGetIntoStart(dokan, dokanchange, count, Xdokan, Ydokan, marioX, marioY, MariowideY, superplus, MariowideX, clear, dying);
	//�y�ǂɓ���邩�ǂ���

	return DokanGettingInto(count, marioY, dokanchange, superplus, dpla);
	//�y�ǂɂ͂��蒆�A�I�������A�ړ���֍s��
}


//�y�ǂ���o��
//           (�y�ǂ���o�鎞�ԁA�}���I��Y���W�A�y�ǂňړ����Ă������ǂ����A�}���I�̒ǉ���Y���W)
void DokanGetOut(int &count, int&marioY, int &dokanchange, int superplus) {
	if (dokanchange == 2) {//�}���I���A�y�ǂňړ����Ă����Ƃ�
		count++;//���Ԃ�i�߂�
		marioY -= 5;//�}���I���A��ɏオ���Ă���
		if (count >= 5 + superplus / 4) {//�\���ɏオ������
			//�f�[�^���Z�b�g����
			dokanchange = 0;
			count = 0;
		}
	}
}


//�{�^���������āA�X�e�[�W��ς�����A��߂��肷��
//�@�@�@�@�@�@�@�i�ꏊ�A�}���I�̎c��A�X�N���[�����A���Ԃ̊����Ƃ������ǂ����A���Ԃ̊��̏ꏊ�A���Ԃ̊��̍��W�A�}���I�̒ǉ���Y���W�A
//�@�@�@�@�@�@�@�}���I�̉��̕��A�}���I�̃_���[�W�j
int StageChange(int &place,int &mario,int &stmove,int & flag,int &flagStage,int &flagX,int & flagY,int &superplus,int &marioLV,int & MariowideX,
	int &end) {
	if (Key[KEY_INPUT_BACK] >= 1) {
		return 1;
	}
	else if (Key[KEY_INPUT_INSERT] == 1 && place < 12) {
		place++;
		mario = 5;
		stmove = 0;
		flag = 0;
		flagStage = 0;
		flagX = 0;
		flagY = 0;
		superplus = 0;
		marioLV = 1;
		MariowideX = 20;
		end = 0;
		return 1;
	}
	else if (Key[KEY_INPUT_DELETE] == 1 && place>1) {
		place--;
		mario = 5;
		stmove = 0;
		flag = 0;
		flagStage = 0;
		flagX = 0;
		flagY = 0;
		superplus = 0;
		marioLV = 1;
		MariowideX = 20;
		end = 0;
		return 1;
	}
	else return 0;
}

//�{�^���������āA���ł���
//                 (�}���I�̏�ԁA�}���I���_���[�W���󂯂����ǂ���)
void MarioKillMyself(int &marioLV, int &end) {
	if (Key[KEY_INPUT_ESCAPE] == 1) {
		marioLV = 1;
		end = 1;
	}
}

//�{�^���������āA�X�R�A������āA���Ԃ��~�߂����ǂ���
//           (���Ԃ��~�߂����ǂ����A�X�R�A)
void TimeStop(int &stop, long &score) {
	if (Key[KEY_INPUT_LCONTROL] == 1 || Key[KEY_INPUT_RCONTROL] == 1) {//�R���g���[���L�[���������Ƃ�
		if (stop >= 1)stop = 0;//���Ԃ��~�܂��Ă������A�i�߂�
		else if (score >= 10000 && stop == 0)stop = 1, score -= 10000;//�X�R�A���P�O�O�O�ȏ゠���āA���Ԃ��~�܂��Ă��Ȃ��Ƃ��A���Ԃ��~�߂�
	}
	if (stop >= 1) {//���Ԃ��~�߂��鐧�����Ԃ̏���
		stop++;
		if (stop >= 100)stop = 0;
	}
}

//�}���I������ł���Ƃ�
//             �i�}���I������ł��鎞�ԁA���G���ԁA�}���I��Y���W�A�}���I������ł��邩�ǂ����A�}���I�̃_���[�W�j
int  MarioDying(int &count,int suke,int &marioY,int dying,int &end) {
	if (dying == 1 && suke == 0) {//����ł��āA���G���Ԃł��Ȃ��Ƃ�
		count++;//���Ԃ�i�߂�
		if (count <= 10) {//���Ԃ��P�O�ȓ��Ȃ�
			marioY -= 20 - count * 2;//��Ɉړ�����
		}
		else {//���Ԃ��P�O���傫���Ȃ�
			marioY += count * 2 - 20;//���Ɉړ�����
		}
		if (marioY >= 520 + count * 2 - 20) {//������x���ɍs������A
			count = 0;//�Q�[������߂�
			return 1;
		}
	}
	else end = 0;

	return 0;
}


//�}���I���_���[�W���󂯂��Ƃ�
//�@�@�@�@�@�@�i�}���I���_���[�W���󂯂����ǂ����A���G���Ԃ��ǂ����A�W�����v�����Ă��邩�ǂ����A�}���I������ł��邩�ǂ����A�}���I�̒ǉ���Y���W�A
//�@�@�@�@�@�@�@�}���I�̏�ԁA�}���I�̉��̕��A���ԁA�}���I��Y���W�A�y�ǂňړ����Ă��邩�ǂ����j
int MarioDamage(int &end, int &suke, int &jump, double &nuton, int &dying, int &superplus, int &marioLV, int &MariowideX, int &count, int &marioY, 
	int dokanchange) {
	if (end == 1 && suke == 0 && dokanchange == 0) {
		if (marioLV == 1) {//���у}���I�Ȃ�
			//����
			jump = 0;
			nuton = 0;
			dying = 1;
		}
		if (marioLV == 2) {//�X�[�p�[�}���I�Ȃ�
			//���у}���I�ɂȂ�
			marioLV = 1;
			superplus = 0;
			MariowideX = 20;
			suke = 1;//���G���Ԃ̎n�܂�
		}
		else if (marioLV >= 3) {//�t�@�C���[�}���I�Ȃ�
			marioLV = 2;//�X�[�p�[�}���I�ɂȂ�
			suke = 1;//���G���Ԃ̎n�܂�
		}
	}

	return  MarioDying(count, suke, marioY, dying, end);//�}���I������ł���Ƃ�
}


//���Ńn�e�i�u���b�N���烂���X�^�[���o�āA�����̃����X�^�[����ɏオ��
//�@�@�@�@�@�@�@�@�@�@�i�����X�^�[�̑����A�n�e�i�u���b�N����o�����郂���X�^�[�̍��W�j
void MonsterUpByBlock(int num,int x,int y) {

	int MX1;
	int MX2;
	int MY1;
	int MY2;
	for (int i = 0; i <= num; i++) {
		MX1 = (monX[i] + 2) / 30;//�オ����̃����X�^�[�̍���X���W
		MX2 = (monX[i] + 25 - 2) / 30;//�オ����̃����X�^�[�̉E��X���W
		MY1 = 20 - (monY[i] + 2)/ 30;//�オ����̃����X�^�[�̏��Y���W
		MY2 = 20 - (monY[i] + 25 - 2) / 30;//��������̃����X�^�[�̉���Y���W
		if ((abs(x - monX[i]) < 25 && abs(y - monY[i]) < 25  )|| //�o�����郂���X�^�[�ɐG���Ă������A�オ����̃����X�^�[���u���b�N���ɂ���Ƃ�
			!(stage[MX1][MY1] == EMPTY &&stage[MX1][MY2] == EMPTY &&stage[MX2][MY1] == EMPTY &&stage[MX2][MY2] == EMPTY)) {
			monY[i] -= 5;//��̃����X�^�[�͏�ɏオ���āA
			i--;
			continue;//�d�Ȃ�Ȃ��Ȃ�܂ŏ�ɏオ��
		}
	}
}



//�}���I�̓����u���b�N�ɓ���������
//�@�@�@�@�@�@�@�@�}���I��X���W�A�}���I�̉��̕��A�}���I��Y���W�A�}���I������ł��邩�ǂ����A�}���I�̏�ԁA�����X�^�[�̑����A�W�����v���Ă��邩�ǂ����j
void MarioHeadHitBlock(int marioX, int MariowideX, int marioY, int dying, int marioLV, int &num, int &jump) {
	int x1 = (marioX + 1) / 30;//�}���I�̍�����X���W
	int x2 = (marioX + MariowideX - 1) / 30;//�}���I�̉E����X���W
	int y = 20 - (marioY - 5) / 30;//�}���I�̏㑤��Y���W


	//����łȂ��āA�W�����v���ŁA���Ԃ̊��łȂ��u���b�N�ɂԂ�������
	if (dying == 0 && jump >= 1 && 
		(stage[x1][y] > EMPTY && stage[x1][y] != HALFFLAG1 && stage[x1][y] != HALFFLAG2 ||
			stage[x2][y] > EMPTY && stage[x2][y] != HALFFLAG1 && stage[x2][y] != HALFFLAG2)) {
		jump = 0;
		if (stage[x1][y] == 1 && marioLV >= 2) {//�X�[�p�[�}���I�Ń����K�ɂԂ�������(��)
			stage[x1][y] = EMPTY;//��
		}
		else if (stage[x2][y] == 1 && marioLV >= 2) {//�X�[�p�[�}���I�Ń����K�ɂԂ�������(�E)
			stage[x2][y] = EMPTY;//��
		}
		else if (stage[x1][y] >= HATENA && stage[x1][y] < DOKANUP_MOVE) {//�n�e�i�u���b�N�ɂԂ�������(��)
			//�n�e�i�u���b�N�ɓ����Ă��郂���X�^�[���o��������
			int AppearType;
			if (stage[x1][y] - HATENA < ITEM) {//�A�C�e�����o��Ƃ�
				AppearType = (stage[x1][y] - HATENA) * -1;
			}
			else {//�����X�^�[���o��Ƃ�
				AppearType = stage[x1][y] - HATENA - ITEM;
			}
			MonsterUpByBlock(num, x1 * 30, (20 - y - 1) * 30);//�n�e�i�u���b�N�̏�ɂ���ז��ȃ����X�^�[���ǂ���
			MonsterAppear(num, AppearType, x1 * 30, (20 - y - 1) * 30, 1);
			stage[x1][y] = HATENA_KNOCKED;//�n�e�i�u���b�N����ɂ���
		}
		else if (stage[x2][y] >= HATENA && stage[x2][y] < DOKANUP_MOVE) {//�n�e�i�u���b�N�ɂԂ�������(�E)
			//�n�e�i�u���b�N�ɓ����Ă��郂���X�^�[���o��������
			int AppearType;
			if (stage[x2][y] - HATENA < ITEM) {//�A�C�e�����o��Ƃ�
				AppearType = (stage[x2][y] - HATENA) * -1;
			}
			else {//�����X�^�[���o��Ƃ�
				AppearType = stage[x2][y] - HATENA - 10;
			}
			MonsterUpByBlock(num, x2 * 30, (20 - y - 1) * 30);//�n�e�i�u���b�N�̏�ɂ���ז��ȃ����X�^�[���ǂ���
			MonsterAppear(num, AppearType, x2 * 30, (20 - y - 1) * 30, 1);
			stage[x2][y] = HATENA_KNOCKED;//�n�e�i�u���b�N����ɂ���
		}
	}
}

//�}���I���N���A�����Ƃ�
//�@�@�@�@�@�@�@�@�i�X�R�A�A�W�����v�̑����A�N���A�������ǂ����A�W�����v���Ă��邩�ǂ����A���ԁA�ꏊ�A�}���I��Y���W�A�X�N���[�����A
//�@�@�@�@�@�@�@���̃X�e�[�W�̏ꏊ�A�����X�^�[�̑����A�}���I��X���W�A�}���I�̒ǉ���Y���W�A�}���I�̕��A�S�[���̊��̏ꏊ�j
int  MairoGameClear(long &score, double &nuton, int &clear, int &jump, int &count, int &place, int &marioY, int stmove, int dpla, int num, 
	int &marioX, int superplus, int MariowideX, int MariowideY, int flagpoint) {

	if (dpla % 2 == 1 && clear == 0 && marioX / 30 >= flagpoint) {//�N���A�����Ƃ�
		//�N���A�����Ƃ��̃f�[�^�̃Z�b�g
		for (int i = 0; i <= num; i++) {//�����X�^�[��S������
			monEnd[i] = 1;
			score += 100;
		}
		clear = 1;
		jump = 0;
		nuton = 0;
		count = 0;
	}
	if (clear == 1) {//�N���A���Ă���Ƃ�
		count++;
		int x1 = marioX / 30;//�}���I�̍���X���W
		int x2 = (marioX + MariowideX) / 30;//�}���I�̉E��X���W
		int y;//�}���I�̉��̕�����Y���W
		int last = 0;
		for (int h = 0; h < 10; h++) {
			y = 20 - (marioY + MariowideY + superplus + 1) / 30;
			if (stage[x1][y] == 0 && stage[x2][y] == 0 && marioY <= 430) {//�n�ʂɗ����Ă��Ȃ��Ƃ�
				marioY++;//���ɗ�����
				y++;
			}
			else {//�n�ʂɗ����Ă���Ƃ�
				marioX++;//�E�Ɉړ�����
				Key[KEY_INPUT_RIGHT]++;
				break;
			}
		}
		if (count == 201) {//���S�ɃN���A�����Ƃ��A�L�[���������܂œ����Ȃ��Ȃ�
			DrawFormatString(250, 200, GetColor(0, 0, 0), "GAME CLEAR!");
			ScreenFlip();
			WaitKey();
			return 1;
		}
		if (marioX  / 30 >= flagpoint + 5 || count >= 200) {//�N���A����������
			//�N���A�̕\��������
			count = 200;
			if(place < 12)place++;//�X�e�[�W����i�߂�
			else place = 1;
		}
	}
	return 0;
}








//�Z�[�u�f�[�^��ǂݍ���
void SaveInput() {
	int i, h, g;
	FILE *fp = fopen("�Z�[�u�f�[�^.dat", " r b");
	if (fp == NULL) {
		DrawFormatString(250, 250, GetColor(0, 0, 0), "�Z�[�u�ł��܂���ł����B");
		ScreenFlip();
		WaitKey();
	}
	fread(&Data, sizeof(Data), 1, fp);
	fclose(fp);

	//�X�e�[�W�f�[�^��ǂݍ���
	for (g = 0; g <= 25; g++) {
		for (i = 0; i <= 99; i++) {
			for (h = 0; h <= 24; h++) {
				dstage[g][i][h] = Data.makesta[g][i][h];
			}
		}
	}
	//�X�e�[�W�f�[�^�ǂݍ���
}

//�e���o��������
//�@�@�@�@�@�@�@�@�i�X�R�A�A�e�̑����A�N���A�������ǂ����A�}���I�̍��W�A�}���I�̒ǉ���Y���W�A�}���I�̏�ԁA�}���I�̃_���[�W�A�}���I�̌����j
void BulletAppear(long &score, int &bullet, int clear, int marioX, int marioY, int superplus, int marioLV, int end, int marioDirection) {
	if (clear == 0 && !(marioLV == 1 && end == 1)) {//�N���A���ĂȂ��āA����ł��Ȃ��Ƃ�
		if (score >= 200 && marioLV == 2 && Key[KEY_INPUT_RSHIFT] % 20 == 1) {//�X�[�p�[�}���I�ŁA�X�R�A���Q�O�O�ȏ゠���āA�V�t�g���������Ƃ�
			score -= 200;//�X�R�A���Q�O�O����A
			//�}���I�e���o��
			bullet++;
			bulletY[bullet] = marioY + 20;
			bulletX[bullet] = marioX + 5;
			Btype[bullet] = 1;
			Bside[bullet] = marioDirection;
			Bnuton[bullet] = EMPTY;
		}
		if (marioLV == 3 && Key[KEY_INPUT_RSHIFT] % 5 == 2) {//�t�@�C���[�}���I�ŁA�V�t�g���������Ƃ�
			//�t�@�C���[�{�[�����o��
			bullet++;
			bulletY[bullet] = marioY + 20;
			bulletX[bullet] = marioX + 5;
			Btype[bullet] = 2;
			Bside[bullet] = marioDirection;
			Bnuton[bullet] = EMPTY;
		}
	}
}



//�����X�^�[�ƃA�C�e����\������
//                       �i�X�N���[�����A�����X�^�[�̑����j
void PlayStageMonsterShow(int stmove, int num) {
	int i;
	for (i = 0; i <= num; i++) {
		int x1 = monX[i] - stmove;
		int x2 = x1 + 25;
		int y1 = monY[i];
		int y2 = y1 + 25;
		if (monEnd[i] == 1)continue;
		if (monX[i] - stmove < 660) {

			if (Mtype[i] == COIN) 	DrawExtendGraph(x1, y1, x2, y2, coinImg, TRUE);//�R�C��
			else if (Mtype[i] == KURIBO)	DrawExtendGraph(x1, y1, x2, y2, kuriImg, TRUE);//�N���{�[
			else if (Mtype[i] == NOKONOKO) DrawExtendGraph(x1, y1, x2, y2, (monMove[i] == 1 ? RnokoImg : LnokoImg), TRUE);//�m�R�m�R
			else if (Mtype[i] == STOP_KORA || Mtype[i] == MOVE_KORA) DrawExtendGraph(x1, y1, x2, y2, koraImg, TRUE);//�b��
			else if (Mtype[i] == TOGEZO) DrawExtendGraph(x1, y1, x2, y2, (monMove[i] == 1 ? RtogezoImg : LtogezoImg), TRUE);//�g�Q�]�[
			else if (Mtype[i] == PAKKUN) DrawExtendGraph(x1, y1, x2, y2, packunImg, TRUE);//�p�b�N���t�����[
			else if (Mtype[i] == BLACK_PAKKUN) DrawExtendGraph(x1, y1, x2, y2, blackpackunImg, TRUE);//���p�b�N���t�����[
			else if (Mtype[i] == STOP_SPINE || Mtype[i] == MOVE_SPINE) DrawExtendGraph(x1, y1, x2, y2, spineImg, TRUE);//�Ƃ�
			else if (Mtype[i] == STOP_DOSSUN || Mtype[i] == FALL_DOSSUN) DrawExtendGraph(x1, y1, x2, y1 + 30, dosunImg, TRUE);//�h�b�X��
			else if (Mtype[i] == MOVE_TERESA) DrawExtendGraph(x1, y1, x2, y2, (monSide[i] == 1 ? RteresaImg : LteresaImg), TRUE);//�e���T
			else if (Mtype[i] == STOP_TERESA) DrawExtendGraph(x1, y1, x2, y2, (monSide[i] == 1 ? RtereteresaImg : LtereteresaImg), TRUE);//�Ƃ�e���T
			else if (Mtype[i] == KILLER) DrawExtendGraph(x1, y1, x2, y2, (monSide[i] == 1 ? RkillerImg : LkillerImg), TRUE);//�L���[
			else if (Mtype[i] >= HODAI) 	DrawExtendGraph(x1, y1, x2, y2, hodaiImg, TRUE);//�C��
			
			//�A�C�e���̕\��
			else if (Mtype[i] == SUPER_KINOKO) DrawExtendGraph(x1, y1, x2, y2, kinokoImg, TRUE);//�X�[�p�[�L�m�R
			else if (Mtype[i] == ONE_UP_KINOKO) DrawExtendGraph(x1, y1, x2, y2, upkinokoImg, TRUE);//�����i�b�v�L�m�R
			else if (Mtype[i] == FIREFLOWER) DrawExtendGraph(x1, y1, x2, y2, fireflowerImg, TRUE);//�t�@�C���[�t�����[
		}
	}
}



//�u���b�N��\������
//                      (�X�N���[����)
void PlayStageBlockShow(int stmove,int dpla,int flagpoint) {
	int i, h;
	for (h = 0; h <= 20; h++) {
		for (i = stmove / 30; i <= stmove / 30 + 22; i++) {
			if (stage[i][h] == 0)continue;
			int x1 = i * 30 - stmove;//���[��X���W
			int x2 = x1 + 30;//�E�[��X���W
			int y1 = (20 - h) * 30;//�㑤��Y���W
			int y2 = y1 + 30;//������Y���W

			if (stage[i][h] >= HATENA && stage[i][h] < DOKANUP_MOVE) DrawExtendGraph(x1, y1, x2, y2, hatenablockImg, FALSE);//�n�e�i�u���b�N
			else if (stage[i][h] == HATENA_KNOCKED) DrawExtendGraph(x1, y1, x2, y2, normalblockImg, FALSE);//��̃n�e�i�u���b�N
			else if (stage[i][h] == BRICK) 	DrawExtendGraph(x1, y1, x2, y2, brickImg, FALSE);//�����K
			else if (stage[i][h] == COINBLOCK) DrawExtendGraph(x1, y1, x2, y2, coinImg, TRUE);//�R�C��
			else if (stage[i][h] == FLOOR) DrawExtendGraph(x1, y1, x2, y2, floarImg, TRUE);//�n��
			else if (stage[i][h] == GRASS) 	DrawExtendGraph(x1, y1, x2, y2, floarupImg, TRUE);//���̐������n��
			else if (stage[i][h] >= DOKANUP_MOVE || stage[i][h] == DOKANUP) DrawExtendGraph(x1 - 2, y1, x1 + 32, y2, dokanupImg, TRUE);//�y�ǂ̏㑤
			else if (stage[i][h] == DOKANDOWN) DrawExtendGraph(x1, y1, x2, y2, dokandownImg, TRUE);//�y�ǂ̉���
			else if (stage[i][h] == HALFFLAG1) DrawExtendGraph(x1, y1, x2, y2, beforeHalfFlagImg, TRUE);//�G���O�̒��Ԃ̊�
			else if (stage[i][h] == HALFFLAG2) DrawExtendGraph(x1, y1, x2, y2, AfterHalfFlagImg, TRUE);//�G�ꂽ��̒��Ԃ̊�
		}
	}

	if (dpla % 2 == 1) {//�S�[���̊��̕\��
		DrawRotaGraph(100 + (flagpoint - 2) * 30 - stmove, 300, 1, 0.0, flagImg, TRUE);
	}

}


//�}���I�ƁA�S�[���̊��ƁA��̕\��
//                    (�X�N���[�����A�}���I������ł��邩�ǂ����A�}���I�̍��W�A�}���I�̌����A�}���I�̏�ԁA�}���I���W�����v���Ă��邩�ǂ���
//                   ���G���ԁA���̃X�e�[�W�̏ꏊ�A�S�[���̊��̏ꏊ�A�N���A���Ă��邩�ǂ���)
void PlayStageMarioShow(int stmove, int dying, int marioY, int marioX, int marioDirection, int marioLV, int jump, int suke, int dpla, int flagpoint,
	int clear,int count) {

	if (dpla % 2 == 1) {//�S�[���̏�̕\��
		DrawRotaGraph(70 + (flagpoint + 3) * 30 - stmove, 360, 1, 0.0, castleImg, TRUE);
	}
	int x = marioX - stmove;
	int y = marioY;
	int right = Key[KEY_INPUT_RIGHT];//�E�̓��͐�
	int left = Key[KEY_INPUT_LEFT];//���̓��͐�
	if (right > left)left = 0;
	else right = 0;
	if (dying == 0 && !(clear == 1 && count == 200)) {//�y�ǂɓ����ĂȂ��āA�N���A�����Ă��Ȃ���
		if (marioLV == 1) {//���у}���I�̕\��
			if (jump == 0 && (right >= 1 || left >= 1))
				DrawExtendGraph(x, y, x + 15 , y + 20,
				(right >= 1 ? (right / 5 % 2 == 1?RmovemarioImg1:RmovemarioImg2) : (left / 5 % 2 == 1 ? LmovemarioImg1 : LmovemarioImg2)), TRUE);
			else DrawExtendGraph(x, y, (jump == 0 ? x + 15 : x + 20), y + 20,
				(jump == 0 ? (marioDirection == 1 ? RsupermarioImg : LsupermarioImg) :
				(marioDirection == 1 ? RjumpsupermarioImg : LjumpsupermarioImg)), TRUE);
		}
		else if (marioLV == 2) {//�X�[�p�[�}���I�̕\��
			if (jump == 0 && (right >= 1 || left >= 1))
				DrawExtendGraph(x, y, x + 20, y + 35,
				(right >= 1 ? (right / 5 % 2 == 1 ? RmovemarioImg1 : RmovemarioImg2) : (left / 5 % 2 == 1 ? LmovemarioImg1 : LmovemarioImg2)), TRUE);
			else DrawExtendGraph(x, y, (jump == 0 ? x + 20 : x + 25), y + 35,
				(jump == 0 ? (marioDirection == 1 ? RsupermarioImg : LsupermarioImg) :
				(marioDirection == 1 ? RjumpsupermarioImg : LjumpsupermarioImg)), TRUE);
		}
		else if (marioLV == 3) {//�t�@�C���[�}���I�̕\��
			DrawExtendGraph(x, y, (jump == 0 ? x + 20 : x + 25), y + 35,
				(jump == 0 ? (marioDirection == 1 ? RfiremarioImg : LfiremarioImg) : (marioDirection == 1 ? RjumpfiremarioImg : LjumpfiremarioImg)), TRUE);
		}
	}

}

//���̑��̂��̂�\������
//                 (�X�R�A�A�R�C�����A�}���I�̎c��A�e�̑����A���̃X�e�[�W�̏ꏊ�A�S�[���̊��̏ꏊ�A�X�N���[�����A����ł��邩�ǂ����A�}���I�̍��W
//�@�@�@�@�@�@�@�@�@�N���A�������ǂ���)
void PlayStageOtherShow(int score, int coin, int mario, int bullet, int dpla, int flagpoint, int stmove, int dying,
	int marioX, int marioY,int clear) {
	int i;
	int black = GetColor(0, 0, 0);
	int x = marioX - stmove;
	int y = marioY;

	for (i = 0; i <= bullet; i++) {//�e�̕\��
		if (Btype[i] == 1) {//�}���I�e
			DrawRotaGraph(bulletX[i] - stmove, bulletY[i], 0.1, 0, marioImg, TRUE);
		}
		if (Btype[i] == 2) {//�t�@�C���[�{�[��
			DrawExtendGraph(bulletX[i] - stmove, bulletY[i], bulletX[i] - stmove + 10, bulletY[i] + 10, fireballImg, TRUE);
		}
	}
	if (dying == 1) DrawExtendGraph(x, y, x + 20, y + 20, deathmarioImg, TRUE);//�}���I������ł���Ƃ�

	//�f�[�^�̕\��
	DrawFormatString(500, 0, black, "score %d", score);
	DrawFormatString(60, 0, black, "�~%d", coin);//�R�C��
	DrawExtendGraph(45, -2, 65, 18, coinImg, TRUE);
	DrawFormatString(20, 0, black, "�~%d", mario);//�}���I�̎c�@
	DrawRotaGraph(15, 10, 0.15, 0.0, marioImg, TRUE);
}



//�\���ɂ��Ă̂܂Ƃ�
void PlayStageShow(int num, int bullet,int dpla, int flagpoint, int stmove, int dying, int marioY, int marioX, int marioDirection, int marioLV, int jump, 
	int suke, int score, int coin, int mario,int clear,int count) {
	ClearDrawScreen(); // ��ʂ�����
	DrawExtendGraph(-210,-5,650,600,backgroundImg,FALSE);//�w�i�̕\��

	PlayStageMarioShow(stmove, dying, marioY, marioX, marioDirection, marioLV, jump, suke, dpla, flagpoint,clear,count);//�}���I�̕\��
	PlayStageBlockShow(stmove, dpla, flagpoint);//�u���b�N�̕\��
	PlayStageMonsterShow(stmove, num);//�����X�^�[�̕\��
	PlayStageOtherShow(score, coin, mario, bullet, dpla, flagpoint, stmove, dying, marioX, marioY,clear);//���̑��̕\��
	ScreenFlip();
}





//���ʂ܂ł́A�Q�[���̃��[�v
void PlayingGameByDeath(int &mario, int &num, int &bullet, int &dpla, int &flagpoint, int &stmove, int &dying, int &marioY, int &marioX, int & marioDirection, int &jump, 
	int &marioLV, int &suke, long &score,int &coin, int &place, int &Ydokan, int &Xdokan, int &superplus, double &nutonmax, double &nutonLV, double &nuton, int &stop, int &MariowideX,
	int &MariowideY, int &moving, int &move, int &monWide,int &monstop, int &last, int &jumping, int &end, int &dokan, int &dokanchange, int &count, int &clear,int &flag,
	int &flagStage, int &flagX, int &flagY) {

	while (ProcessMessage() == 0 ) {
		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}

		if (mario >= 100)mario = 99;//�c��P�O�O�ȏ�ɂȂ������A�X�X�ɒ���

		if (clear == 0) gpUpdateKey();//�N���A���ĂȂ��Ƃ��ɁA�L�[�̏o�͏�Ԃ��v�Z����

		//��������A���W�̈ړ��Ȃ�
		if (StageChange(place, mario,stmove,flag,flagStage,flagX,flagY,superplus,marioLV,MariowideX,end) == 1) {//�{�^���Ƀ^�b�`���āA�X�e�[�W���ς��Ƃ�
			break;
		}

		//�y�ǂɓ����āA���肫������break����B
		if (DokanGetInto(dokanchange, count, dokan, Xdokan, Ydokan, marioY, marioX, clear, marioLV, end, MariowideX, MariowideY, superplus, dpla, dying) == 1) {
			break;
		}

		//�y�ǂ���o��Ƃ�
		DokanGetOut(count, marioY, dokanchange, superplus);


		//�}���I���W�����v���n�߂�Ƃ�
		MarioJumpStart(score, coin, mario, jumping, jump, nuton, nutonmax, nutonLV, clear, marioLV,  end, marioX, marioY, MariowideX, MariowideY, superplus, 
			num, marioDirection, dpla, flag,flagStage, flagX, flagY,dying);

		//�}���I�����Q����Ƃ�
		MarioKillMyself(marioLV, end);

		//�}���I�����Ԃ��~�߂鎞
		TimeStop(stop, score);

		//�e��������
		BulletAppear(score, bullet, clear, marioX, marioY, superplus, marioLV, end, marioDirection);

		//�e�̏���
		BulletDataChange(score, bullet, stmove, num);
		
		//�N���A�����Ƃ�
		if (MairoGameClear(score, nuton, clear, jump, count, place, marioY, stmove, dpla, num, marioX, superplus, MariowideX, MariowideY, flagpoint) == 1) {
			break;
		}

		//�����X�^�[�ɂ��Ă̏���
		MonsterDataSet(jumping, num, marioLV, end, bullet, stmove, coin, mario, jump, last, marioX, marioY, monstop, monWide, move, nuton, nutonLV, nutonmax,score,
			marioDirection, stop, superplus, MariowideX,dying,MariowideY);

		//�}���I���_���[�W���󂯂��Ƃ�
		if (MarioDamage(end, suke, jump, nuton, dying, superplus, marioLV, MariowideX, count, marioY, dokanchange) == 1) break;

		//�R�C�����l������
		CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);

		//���Ԃ̊����l������
		FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY,marioLV);

		//�}���I�̓����u���b�N�ɓ���������
		MarioHeadHitBlock(marioX, MariowideX, marioY, dying, marioLV, num, jump);


		//���E�ɓ����Ƃ�
		LeftAndRightMove(score, mario, coin, marioX, marioY, move, clear, marioLV, end, marioDirection, MariowideX, MariowideY, superplus, stmove, moving, jump, num, dying,
			dokanchange, dpla, flag,flagStage, flagX, flagY);

		//�}���I��������Ƃ�
		MarioFall(dokanchange, jump, num, superplus, MariowideX, MariowideY, clear, marioLV, end, marioX, marioY, mario, coin, score,
			nuton, nutonmax, nutonLV, jumping, marioDirection, dpla, flag, flagStage, flagX, flagY);

		//�}���I���W�����v���Ă���Ƃ�
		MarioJumping(score, bullet, monWide, monstop, stop, jump, marioX, marioY, nutonmax, nuton, nutonLV, superplus, marioDirection, move, stmove, coin, mario,
			MariowideX, MariowideY, clear, marioLV, end, num, moving, jumping, dying, dokanchange, dpla, flag, flagStage, flagX, flagY);

		
		if (marioY >= 460 && dokanchange == 0) {//�}���I���������Ƃ�
			//����
			marioLV = 1;
			end = 1;
			dying = 1;
		}
		move = 0;

		//���G���Ԃɂ���
		if (suke >= 1)suke++;
		if (suke == 50)suke = 0;

		//�摜��\������
		PlayStageShow(num, bullet, dpla, flagpoint, stmove, dying, marioY, marioX, marioDirection, marioLV, jump, suke, score, coin, mario, clear,count);

		Sleep(33);
	}
}