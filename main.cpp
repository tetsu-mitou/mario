#include "DxLib.h"
#include "Menu.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib_Init();   // DX���C�u������������


	Menu();//���j���[���

	DxLib_End();    // DX���C�u�����I������
	return 0;
}//�S�̂̂�����

