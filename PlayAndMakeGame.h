#include "Dxlib.h"

static int make = 1;

//�摜�̖��O�̃Z�b�g
static int backgroundImg;//�w�i
static int beforeHalfFlagImg;//���Ԃ̊��Ƃ�O
static int AfterHalfFlagImg;//���Ԃ̊��Ƃ��
static int halfFlagImg;//���Ԃ̊��Ƃ�O
static int marioImg;//�}���I
static int upkinokoImg;//�����i�b�v�L�m�R
static int kinokoImg;//�X�[�p�[�L�m�R
static int fireflowerImg;//�t�@�C���[�t�����[
static int siroImg;//��
static int brickImg;//�����K
static int hatenablockImg;//�n�e�i�u���b�N
static int normalblockImg;//��̃n�e�i�u���b�N
static int floarImg;//�n��
static int floarupImg;//���̂���n��
static int dokanupImg;//��̓y��
static int dokandownImg;//���̓y��
static int skyImg;//��̉摜
				  //���ʃ}���I
static int jumpmarioImg;//�W�����v�̃}���I
static int deathmarioImg;//���񂾃}���I
						 //�X�[�p�[�}���I
static int RjumpsupermarioImg;//�W�����v�̃X�[�p�[�}���I�E
static int LjumpsupermarioImg;//�W�����v�̃X�[�p�[�}���I��
static int RsupermarioImg;//�E�̃X�[�p�[�}���I
static int LsupermarioImg;//���̃X�[�p�[�}���I
static int RmovemarioImg1;
static int LmovemarioImg1;
static int RmovemarioImg2;
static int LmovemarioImg2;

						  //�X�[�p�[�}���I
static int RjumpfiremarioImg;//�W�����v�̃X�[�p�[�}���I�E
static int LjumpfiremarioImg;//�W�����v�̃X�[�p�[�}���I��
static int RfiremarioImg;//�E�̃X�[�p�[�}���I
static int LfiremarioImg;//���̃X�[�p�[�}���I

						 //�}���I�I���
static int coinImg;//�R�C��
static int kuriImg;//�N���{�[
static int RnokoImg;//�m�R�m�R�E
static int LnokoImg;//�m�R�m�R��
static int koraImg;//�b��
static int RtogezoImg;//�g�Q�]�[�E
static int LtogezoImg;//�g�Q�]�[��
static int packunImg;//�p�b�N���t�����[
static int spineImg;//�g�Q
static int dosunImg;//�h�b�X��
static int RteresaImg;//�e���T�E
static int LteresaImg;//�e���T��
static int RtereteresaImg;//�Ƃ�e���T�E
static int LtereteresaImg;//�Ƃ�e���T��
static int blackpackunImg;//���p�b�N���t�����[
static int hodaiImg;//�C��
static int RkillerImg;//�L���[�E
static int LkillerImg;//�L���[��
static int flagImg;//�S�[���̊�
static int castleImg;//�S�[���̏�
static int fireballImg;//�t�@�C���[�{�[��


int MakeStage();//�X�e�[�W�Â���
void PlayingGame();//�v���C�Q�[��
void Manual();//�}�j���A��


