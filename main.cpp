#include "DxLib.h"
#include "Menu.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib_Init();   // DXライブラリ初期化処


	Menu();//メニュー画面

	DxLib_End();    // DXライブラリ終了処理
	return 0;
}//全体のかっこ

