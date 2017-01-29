#include "DxLib.h"
#include "PlayAndMakeGame.h"

static int key[256]; // キーが押されているフレーム数を格納する

			  // キーの入力状態を更新する
static int gpUpdatekey() {
	char tmpkey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpkey); // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpkey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			key[i]++;     // 加算
		}
		else {              // 押されていなければ
			key[i] = 0;   // 0にする
		}
	}
	return 0;
}

void MenuShow(int);//メニュー画面の表示

void SelectMakeOrPlayGame(int &, int &, int &, int &);//やることを選択した後

void SelectByMouce(int &, int &, int &, int &);//マウスによって選択

void SelectByKey(int &, int &);//キーによって選択


//全体のメニューの処理
void Menu() {
	int button;//ボタンが押されたかどうか 
	int x;//選択されているX座標
	int y;//選択されているY座標
	int select = 1;//選択されている場所
	while (ScreenFlip() == 0 && ProcessMessage() == 0 ){
		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
		}
		MenuShow(select);
		SelectByMouce(button,x,y,select);
		SelectByKey(select,button);
		SelectMakeOrPlayGame(button,x,y,select);
	}
}

//メニューのデータを表示する
void MenuShow(int select) {
	int red = GetColor(255, 0, 0);//赤色
	int white = GetColor(-1, -1, -1);//白色
	int black = GetColor(0, 0, 0);//黒色
	int yellow = GetColor(255, 255, 0);//黄色
	int background = LoadGraph("画像/背景.jpg");//背景の画像

	ClearDrawScreen();

	DrawExtendGraph(-2, -1, 650, 500, background, FALSE);
	SetFontSize(60);

	// タイトルと、選択の描画
	DrawString(80, 100, "スーパーマリオ", red);
	SetFontSize(15);
	DrawString(80, 80, "中学生が作った", red);
	DrawString(380, 160, "＋ステージ設計", red);
	DrawBox(230, 290, 370, 320, yellow, TRUE);
	DrawString(240, 300, "あそび方の説明", black);
	DrawBox(230, 340, 370, 370, yellow, TRUE);
	DrawString(240, 350, "ステージづくり", black);
	DrawBox(230, 390, 370, 420, yellow, TRUE);
	DrawString(240, 400, "プレイステージ", black);

	//選択している四角の描画
	DrawBox(230, 240 + select * 50, 370, 270 + select * 50, red, FALSE);

	ScreenFlip();
}


//やることを選択した後
//　　　　　　　　　　　（ボタンが押されたかどうか、選択している座標、選ばれているもの）
void SelectMakeOrPlayGame(int &button, int &x, int &y, int &select) {
	if (button == 1) {
		SetFontSize(16);
		if (select == 1) {
			Manual();//マニュアルを開く
		}
		else if (select == 2) {
			while (1) {
				if (ProcessMessage() != 0) { // メッセージ処理
					break;//ウィンドウの×ボタンが押されたらループを抜ける
				}
				MakeStage();//ステージづくりをする
				gpUpdatekey();
				if (key[KEY_INPUT_ESCAPE] >= 1)break;//エスケープキーが押されていれば、やめる
				PlayingGame();//ゲームをする
			}
		}
		else if (select == 3) {
			PlayingGame();//ゲームをする
		}
	}
}


//マウスで、やることを選ぶ
//　　　　　　　　（ボタンが押されたかどうか、選択している座標、選ばれているもの）
void SelectByMouce(int &button, int &x, int &y, int &select) {
	button = 0;
	GetMouseInputLog(&button, &x, &y, TRUE);
	if (button == 1 && x >= 230 && x <= 370) {
		if (y >= 290 && y <= 320) {//一番上を選んだ時
			select = 1;
		}
		else if (y >= 340 && y <= 370) {//真ん中を選んだ時
			select = 2;
		}
		else if (y >= 390 && y <= 420) {//一番下を選んだ時
			select = 3;
		}
		else button = 0;
	}
	else button = 0;
}


//ボタンで、やることを選ぶ
//            （選ばれているもの、ボタンが押されたかどうか）
void SelectByKey(int &select, int &button) {
	gpUpdatekey();
	if (key[KEY_INPUT_UP] %3 == 1 && select > 1) {//上のほうを選ぶ
		select--;
	}
	if (key[KEY_INPUT_DOWN] %3 == 1 && select < 3) {//下のほうを選ぶ
		select++;
	}
	if (key[KEY_INPUT_RETURN] == 1) {//選択する
		button = 1;
	}
}
