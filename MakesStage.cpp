#include "Dxlib.h"
#include "PlayAndMakeGame.h"

//ブロック
#define EMPTY (0)//空
#define BRICK (1)//レンガ
#define HATENA_KNOCKED (2)//空のハテナブロック
#define COINBLOCK (3)//コインブロック
#define DOKANUP (4)//上の土管
#define DOKANDOWN (5)//下の土管
#define FLOOR (6)//地面
#define GRASS (7)//草のある地面
#define HALFFLAG1 (8)//取られてない旗
#define HALFFLAG2 (9)//取られた旗
#define HATENA (20)//ハテナブロック
#define DOKANUP_MOVE (100)//移動できる土管

//モンスター
#define FIREFLOWER (-3)//ファイヤーフラワー
#define ONE_UP_KINOKO (-2)//ワンナップキノコ
#define SUPER_KINOKO (-1)//スーパーキノコ
#define COIN (0)//コイン
#define KURIBO (1)//クリボー
#define NOKONOKO (2)//ノコノコ
#define STOP_KORA (3)//止まってる甲羅
#define MOVE_KORA (4)//動いてる甲羅
#define TOGEZO (5)//トゲゾー
#define PAKKUN (6)//パックンフラワー
#define BLACK_PAKKUN (7)//黒パックンフラワー
#define STOP_SPINE (8)//動いてないトゲ
#define MOVE_SPINE (20)//動いてるトゲ
#define STOP_DOSSUN (9)//止まってるドッスン
#define FALL_DOSSUN (21)//落ちてるドッスン
#define MOVE_TERESA (10)//動いてるテレサ
#define STOP_TERESA (22)//止まってるテレサ
#define KILLER (11)//キラー
#define HODAI (100)//砲台

#define ITEM (10)//アイテムをハテナブロックかなんかに入れるときの、アイテム分の猶予

#define MONSTER (10000)




//今作っているステージ

int makesta[26][100][25];//ステージ全部

int dempty[26][10];//どの土管が空か
int dokango[26];//どの土管を置いていいか

int choicestage[100][25];//コピーするステージ

int flagpoint = 90;

int key[256]; // キーが押されているフレーム数を格納する

			  // キーの入力状態を更新する
int gpUpdatekey() {
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

struct StageData {
	int makesta[26][100][25];
	int dempty[26][10];
	int dokango[26];
};
StageData Data;

//画像のデータのセット
void ImageDataSetToPlayGame();


//ステージデータを開いて、代入する
void OpenSave();

//ステージデータをセーブデータに記憶する
void Save();



//ステージに置かれたブロックや敵の表示

//モンスターを選ぶとき
void SelectMonster(int &, int &, int , int , int , int );

//ブロックを選んだ時
void SelectBlock(int &, int &, int , int , int , int );

//何を置くのかを選ぶ物のまとめ
void SelectItem(int &, int &, int , int , int , int );

//土管の上に何か置くとき
void PutOnDokan(int , int , int , int );

//土管を置くとき
void PutDokan(int , int , int );

//ハテナブロックの上に置くとき
void PutOnHatenaBlock(int , int , int , int );

//砲台の上に置くとき
void PutOnHodai(int , int , int , int );

//普通に何かを置くとき
void PutOther(int , int , int , int );

//ブロックや敵を置く時のデータの計算
void PutItemData(int &, int &, int &, int &, int &, int );

//選択している場所を、右に移動するとき
void MoveRight(int , int &, int &, int &);

//選択している場所を、左に移動するとき
void MoveLeft(int , int &, int &, int &);


//マリオが、左右に移動する
void MoveRightAndLeft(int &, int &, int &, int &);


//選択しているところを、ステージか、、何を置くかを選ぶ画面かに移動する
void MoveToSelectMonitor(int &, int &, int );

//上下に移動する
void MoveUpAndDown(int &, int &, int );

//土管の移動先を移動する
void ChangeDokan(int &, int , int , int );

//ステージ上のものを消すとき
void BlockDisappear(int &, int , int );

//ステージ上の全部について、変える
void ChangeAllByKey();

//ステージを変えるとき
void ChangeStage(int &, int &, int &);

//クリックをキーでできるとき）
void PutThing(int &, int &);

//キーボードを入力したときの動作の計算
int KeyInputData(int &, int &, int &, int &, int &, int &, int &, int &);

//マウスの計算
void MouseInputData(int &, int &, int &, int &, int &, int &, int &, int &, int );

//ステージにあるものを表示する
void MakeStageImageShow(int , int );

//モンスターや、アイテムの表示
void MakeStageMonsterShow(int , int , int , int , int );


//置くためのブロックや、敵などを選ぶ部分の表示
void MakePutItemShow(int , int );

//ステージづくりの時のデータを表示する
void MakeStageDataShow(int , int , int , int , int );

//画像や文字の全体の表示
void MakeStageShow(int , int , int , int , int , int );






//主な変数の始まりと、初期化と、全体のまとめ
int MakeStage() {
	int choice = 0;//何を選んでいるか
	int button = 0;//クリックしたかどうか
	int touch = 0;//クリックもしくは、クリックと同意味のキーを入力したかどうか
	int touchX = 30;//選択されているX座標
	int touchY = 120;//選択されているY座標
	int mon = 0;//選択されているのが、モンスターかどうか
	int flagpoint = 90;//ゴールの旗の位置
	int tate = 410;//マリオのY座標
	int yoko = 25;//マリオのX座標
	int pace = 2;//キーを動かせるペース
	int p = 0;//マウスをクリックしたときのX座標
	int r = 0;//マウスをクリックしたときのY座標
	int dselect = 0;//土管の移動先の番号
	int dchosing = 0;//土管の移動先の番号を変えているかどうか、
	int black = GetColor(0, 0, 0);//黒
	int white = GetColor(-1, -1, -1);//白
	int stmove = 0;//スクロールしている長さ
	key[KEY_INPUT_RETURN] = 2;

	for (int h = 0; h <= 25; h++) {
		for (int i = 0; i <= 99; i++) {
			choicestage[i][h] = EMPTY;
		}
	}

	OpenSave();//セーブを開く

	ImageDataSetToPlayGame();//画像のデータをセットする

	while (ProcessMessage() == 0 && gpUpdatekey() == 0) {
		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
		}
		MakeStageShow(choice, touchX, touchY, dchosing,stmove, mon);//表示の全般

		MouseInputData(p, r, button, touch, dchosing, touchX, touchY, dselect,stmove);//マウスのデータを読み込む

		if (KeyInputData(dchosing, dselect, touch, touchX, touchY,stmove,make,pace) == 1) {//キーのデータを読み込む
			break;
		}

		PutItemData(touch, touchX, touchY, choice, mon,stmove);//モンスターや、ブロックを置く

		Sleep(30);
	}
	return 0;
}





//画像のデータのセット
void ImageDataSetToPlayGame() {
	halfFlagImg = LoadGraph("画像/中間の旗前.png");
	marioImg = LoadGraph("画像/マリオ普通.png");
	upkinokoImg = LoadGraph("画像/ワンナップきのこ.png");
	kinokoImg = LoadGraph("画像/キノコ.png");
	fireflowerImg = LoadGraph("画像/ファイヤーフラワー.png");
	siroImg = LoadGraph("画像/四角.png");
	brickImg = LoadGraph("画像/ちゃんとレンガ.jpg");
	hatenablockImg = LoadGraph("画像/？ブロック.png");
	normalblockImg = LoadGraph("画像/壊れないブロック.png");
	floarImg = LoadGraph("画像/地面.png");
	floarupImg = LoadGraph("画像/床ブロック.png");
	dokanupImg = LoadGraph("画像/土管上.png");
	dokandownImg = LoadGraph("画像/土管下.png");
	skyImg = LoadGraph("画像/そら.jpg");
	//普通マリオ
	jumpmarioImg = LoadGraph("画像/マリオジャンプ.png");
	deathmarioImg = LoadGraph("画像/やられマリオ.png");
	//スーパーマリオ
	RjumpsupermarioImg = LoadGraph("画像/スーパーマリオジャンプ右.png");
	LjumpsupermarioImg = LoadGraph("画像/スーパーマリオジャンプ左.png");
	RsupermarioImg = LoadGraph("画像/スーパーマリオふつう右.png");
	LsupermarioImg = LoadGraph("画像/スーパーマリオふつう左.jpg");

	//スーパーマリオ
	RjumpfiremarioImg = LoadGraph("画像/ファイヤーマリオジャンプ右.png");
	LjumpfiremarioImg = LoadGraph("画像/ファイヤーマリオジャンプ左.png");
	RfiremarioImg = LoadGraph("画像/ファイヤーマリオふつう右.png");
	LfiremarioImg = LoadGraph("画像/ファイヤーマリオふつう左.png");

	//マリオ終わり
	coinImg = LoadGraph("画像/コイン.png");
	kuriImg = LoadGraph("画像/クリボー.png");
	RnokoImg = LoadGraph("画像/ノコノコ右.png");//ここから
	koraImg = LoadGraph("画像/甲羅.png");
	RtogezoImg = LoadGraph("画像/トゲゾー右.png");
	packunImg = LoadGraph("画像/パックン.png");
	spineImg = LoadGraph("画像/とげ.png");
	dosunImg = LoadGraph("画像/ドッスン.png");
	RteresaImg = LoadGraph("画像/テレサ右.png");
	LteresaImg = LoadGraph("画像/テレサ左.png");
	RtereteresaImg = LoadGraph("画像/照れテレサ右.png");
	LtereteresaImg = LoadGraph("画像/照れテレサ左.png");
	blackpackunImg = LoadGraph("画像/黒パックン.png");
	hodaiImg = LoadGraph("画像/キラー砲台.png");
	RkillerImg = LoadGraph("画像/キラー右.png");
	LkillerImg = LoadGraph("画像/キラー左.png");
	flagImg = LoadGraph("画像/マリオ旗.png");
	castleImg = LoadGraph("画像/城.png");
	fireballImg = LoadGraph("画像/ファイヤーボール.png");
}


//ステージデータを開いて、代入する
void OpenSave() {

	int i, h, g;
	//セーブデータを開く
	FILE *fp = fopen("セーブデータ.dat", " r b");
	if (fp == NULL) {
		DrawFormatString(250, 250, GetColor(0, 0, 0), "セーブデータを開けませんでした。");
		ScreenFlip();
		WaitKey();
	}
	fread(&Data, sizeof(Data), 1, fp);
	fclose(fp);



	for (g = 0; g <= 25; g++) {//保存されているステージデータを代入する
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
	//開いたセーブデータの値を代入する	
}


//ステージデータをセーブデータに記憶する
void Save() {
	int i, h, g;

	//ステージの床を設定する。

	for (g = 0; g <= 25; g++) {//データを保存するとき、地面のブロックを、データ上の、一番下まで同じにする
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

	//ステージのデータを構造体に入れる
	for (g = 0; g <= 25; g++) {
		for (h = 0; h <= 24; h++) {
			for (i = 0; i <= 99; i++) {
				Data.makesta[g][i][h] = makesta[g][i][h];
			}
		}
	}

	//土管の置く場所を構造体に入れる
	for (i = 0; i <= 24; i++) {
		Data.dokango[i] = dokango[i];
	}

	//土管の空き場所を構造体に入れる
	for (h = 0; h <= 24; h++) {
		for (i = 0; i <= 9; i++) {
			Data.dempty[h][i] = dempty[h][i];
		}
	}

	//構造体を保存し、保存が成功したかを表示する。
	ClearDrawScreen();
	DrawBox(0, 0, 650, 500, GetColor(-1, -1, -1), TRUE);
	FILE  *fp = fopen("セーブデータ.dat", "wb");
	if (fp == NULL) {
		DrawFormatString(250, 250, GetColor(0, 0, 0), "セーブできませんでした。");
	}
	fwrite(&Data, sizeof(Data), 1, fp);
	fclose(fp);
	DrawFormatString(250, 220, GetColor(0, 0, 0), "セーブしました。");
	ScreenFlip();
	Sleep(500);
}


//ステージに置かれたブロックや敵の表示


//モンスターを選ぶとき
//                (何を選んでるか、選んだのがモンスターかどうか、クリックしたか、選択している座標、スクロール数)
void SelectMonster(int &choice, int &mon, int touch, int touchX, int touchY, int stmove) {
	if (touch == 1 && (touchX - stmove + 30) / 30 == 19) {//アイテムかモンスターを選んだ時
		choice = touchY / 30 * -1 + 6;
		if (choice >= 0) {//アイテムを選んだ時
			choice = 3 - choice ;
		}
		else if (choice < - KILLER && choice >= - HODAI) {//何もないところを選んだ時
			choice = EMPTY;
		}
		mon = 1;//選ばれているのが、アイテムだということを表す
	}
}

//ブロックを選んだ時
//　　　　　　（選んだのがモンスターかどうか、何を選んだか、クリックしたかどうか、選択している座標、スクロール数）
void SelectBlock(int &mon, int &choice, int touch, int touchX, int touchY, int stmove) {
	if (touch == 1 && (touchX - stmove + 30) / 30 == 20) {//置くものとして、ブロックを選んだ時
		mon = 0;
		choice = touchY / 30 - 4 + 1;
		if (choice == 4) choice = HATENA;//ハテナブロックを選らんだとき
		if (choice == 6) choice = DOKANUP;//移動できない土管を選んだ時
		if (choice == 7) choice = DOKANUP_MOVE;//移動する土管を選んだ時
		if (choice == 8) choice = FLOOR;//地面を選んだ時
		if (choice == 9) choice = GRASS;//草のある地面を選んだ時
		if (choice == 10) choice = - HODAI;//砲台を選んだ時
		if (choice == 11) choice = HALFFLAG1;//中間の旗を選んだ時
		if ((choice > HALFFLAG1 && choice != HATENA && choice < DOKANUP_MOVE) || choice >= 1000) {//空白を選んだ時
			choice = 0;//何も選んでないことになる
		}
	}
}


//何を置くのかを選ぶ物のまとめ
//　　　　　　（選んだのがモンスターかどうか、何を選んだか、クリックしたかどうか、選択している座標、スクロール数）
void SelectItem(int &mon, int &choice, int touch, int touchX, int touchY, int stmove) {
	SelectMonster(choice, mon, touch, touchX, touchY, stmove);//モンスターを選んだ時
	SelectBlock(mon, choice, touch, touchX, touchY, stmove);//ブロックを選んだ時
}


//土管の上に何か置くとき
//　　　　　　（何を選んだか、選んだのがモンスターかどうか、置く座標）
void PutOnDokan(int choice, int mon, int x, int y) {
	if ((choice > 0 || mon == 1 && choice < 0) && makesta[make][x][y] >= DOKANUP_MOVE) {//土管の上に何かを置くとき
		dempty[(make - 1) / 2 + 1][makesta[make][x][y] % 100 / 10] = EMPTY;//その土管の番号を空にする
		for (int i = 0; i <= 9; i++) {//選べる土管を変える
			if (dempty[(make - 1) / 2 + 1][i] == EMPTY) {
				dokango[(make - 1) / 2 + 1] = i;//今、選択できる土管を決定
				break;
			}
			else if (i == 9)dokango[(make - 1) / 2 + 1] = 10;//土管が、１０個より多いとき、置けなくする
		}

	}
}


//土管を置くとき
//　　　　（何を選んだか、置く場所の座標）
void PutDokan(int choice, int x, int y) {
	if (choice == DOKANUP_MOVE) {//置くのが、土管の時
		if (dokango[(make - 1) / 2 + 1] >= 10) {//土管がすでに１０個以上あって、置けないとき
			makesta[make][x][y] = DOKANUP;//普通の土管になる
			choice = DOKANUP;//選んだのも、普通の土管になる
		}
		else {//土管が、１０個以下の時
			makesta[make][x][y] = DOKANUP_MOVE + dokango[(make - 1) / 2 + 1] * 10;//土管に、土管の番号を入れる
			dempty[(make - 1) / 2 + 1][dokango[(make - 1) / 2 + 1]] = 1;//置いた土管の番号を満たす
			for (int i = 0; i <= 9; i++) {
				if (dempty[(make - 1) / 2 + 1][i] == EMPTY) {
					dokango[(make - 1) / 2 + 1] = i;//次に置ける土管の番号を決める
					break;
				}
				else if (i == 9)dokango[(make - 1) / 2 + 1] = 10;//土管が全部埋まっていたら、土管を置けなくする
			}
		}
	}
}


//ハテナブロックの上に置くとき
//　　　　　　　　（置く場所の座標、選んだのがモンスターかどうか、何を選んだか）
void PutOnHatenaBlock(int x, int y, int mon, int choice) {
	if (makesta[make][x][y] >= HATENA && makesta[make][x][y] < DOKANUP_MOVE && mon == 1) {//ハテナブロックの上に置くとき,モンスターか、アイテムなら、ハテナブロックに入れる
		if (choice>0)makesta[make][x][y] = HATENA + choice;
		else if (choice<0)makesta[make][x][y] = HATENA + ITEM + choice*-1;
	}
}

//砲台の上に置くとき
//　　　　　　　（置く場所の座標、選んだのがモンスターかどうか、何を選んだか）
void PutOnHodai(int x, int y, int mon, int choice) {
	if (makesta[make][x][y] <= -HODAI && mon == 1) {//砲台の上に置くとき、モンスターか、アイテムなら、砲台の中に入れる
		if (choice > 0)makesta[make][x][y] = -HODAI - choice;
		else if (choice < 0)makesta[make][x][y] = -(HODAI + ITEM) + choice;
	}
}


//普通に何かを置くとき
//　　　　　　（置く場所の座標、選んだのがモンスターかどうか、何を選んだか）
void PutOther(int x, int y, int mon, int choice) {
	if (makesta[make][x][y] < HATENA && makesta[make][x][y] > - HODAI && choice != 0
		&& !(mon == 1 && choice > 0) && choice != -11) {//置く場所が、砲台でも、ハテナブロックでも、土管でもないとき
		makesta[make][x][y] = choice;//選んだものを、ステージに置く
	}
}

//ブロックや敵を置く時のデータの計算
//　　　　　　　（クリックしたかどうか、選択している座標、何を選んだか、選んだのがモンスターかどうか、スクロール数）
void PutItemData(int &touch, int &touchX, int &touchY, int &choice, int &mon, int stmove) {


	int x = touchX / 30;//選択しているX座標
	int y = 24 - touchY / 30;//選択しているY座標

	SelectItem(mon, choice, touch, touchX, touchY, stmove);//何を置くのかを選ぶ

	if (touch == 1 && x <= 17 + stmove / 30 - 1) {//ステージ上に何かしらを置くとき
		PutOnDokan(choice, mon, x, y);//土管の上に置くとき

		PutDokan(choice, x, y);//土管を置くとき

		PutOnHatenaBlock(x, y, mon, choice);//ハテナブロックの上に置くとき

		PutOnHodai(x, y, mon, choice);//砲台の上に置くとき

		PutOther(x, y, mon, choice);//普通にものを置くとき
	}
	if (touch == 1 && (touchX - stmove + 30) / 30 == 21 && touchY / 30 == 19) {
		choice = EMPTY;//何を置くのかを選ぶときに、空白の部分をクリックしたら、何も選んでないことになる
	}
}


//選択している場所を、右に移動するとき
//　　　　　　（移動するペース、選択しているX座標、土管の移動先の番号を変えているかどうか、スクロール数）
void MoveRight(int pace, int &touchX, int &dchosing, int &stmove) {
	if (key[KEY_INPUT_RIGHT] % pace == 0 && key[KEY_INPUT_RIGHT] != 0 && key[KEY_INPUT_LEFT] == 0) {//左ボタンは押されてなくて、右ボタンが押されたとき
		if ((touchX / 30 < 98 || (touchX - stmove) / 30 > 16 )&& (touchX - stmove) / 30  < 20) {//選択しているX座標が、右端になくて、何を置くかの選択画面にもないとき
			if ((touchX - stmove) / 30 > 7 && (touchX - stmove) / 30 < 17 && stmove / 30 < 98 - 16)stmove += 30;//選択しているX座標が真ん中くらいにあるとき、右にスクロールする
			touchX += 30;//選択しているX座標を右に移動する
			dchosing = 0;//土管の移動先の番号を変えていないとする
		}
	}
}

//選択している場所を、左に移動するとき
//          （移動するペース、選択しているX座標、土管の移動先の番号を変えているかどうか、スクロール数）
void MoveLeft(int pace, int &touchX, int &dchosing, int &stmove) {
	if (key[KEY_INPUT_LEFT] % pace == 0 && key[KEY_INPUT_LEFT] != 0 && key[KEY_INPUT_RIGHT] == 0) {//右ボタンは押されてなくて、左ボタンが押されたとき
		if (touchX > 0 && (touchX - stmove) / 30 != 17) {//選択しているX座標が、左端になくて、何を置くかの選択画面にもないとき
			if ((touchX - stmove) / 30 < 9 && stmove > 0)stmove -= 30;//
			touchX -= 30;
			dchosing = 0;
		}
	}
}


//マリオが、左右に移動する
//　　　　　　　　（選択しているX座標、土管の移動先の番号を変えているかどうか、移動するペース）
void MoveRightAndLeft(int &touchX, int &dchosing, int &stmove, int &pace) {
	pace = 2;
	if (key[KEY_INPUT_LCONTROL] >= 1) {//左のコントロールキーを押しているとき、早いペースで移動する
		pace = 1;
	}
	else if (key[KEY_INPUT_RCONTROL] >= 1) {//右のコントロールキーを押しているとき、ゆっくり移動する
		pace = 3;
	}
	MoveLeft(pace, touchX, dchosing, stmove);//左に移動する
	MoveRight(pace, touchX, dchosing, stmove);//右に移動する
}


//選択しているところを、ステージか、、何を置くかを選ぶ画面かに移動する
void MoveToSelectMonitor(int &touchX, int &touchY, int stmove) {
	if (key[KEY_INPUT_LSHIFT] == 1) {//左シフトキーが押されたとき
		if ((touchX - stmove) / 30 < 17) {//選択しているX座標が、ステージ上にいるとき
			touchX = 18 * 30 + stmove;//何を置くかを選ぶ画面に移動する
			touchY = 4 * 30;
		}
		else  {//選択しているX座標が、何を置くかを選ぶ画面にあるとき
			touchX = stmove;//ステージ画面に移動する
			touchY = 4 * 30;
		}
	}
}

//上下に移動する
//　　　　　　　　（選択しているy座標、土管の移動先の番号を変えているかどうか、移動するペース）
void MoveUpAndDown(int &touchY, int &dchosing, int pace) {
	if (key[KEY_INPUT_UP] %2 == 0 && key[KEY_INPUT_UP] != 0 && key[KEY_INPUT_DOWN] == 0 && touchY / 30 > 4) {//上ボタンを押したとき
		touchY -= 30;//上に移動する
		dchosing = 0;

		//上を押したとき、右ボタンと左ボタンも押せるようになる
		if (key[KEY_INPUT_LEFT] >= 1)key[KEY_INPUT_LEFT] = pace;
		else if (key[KEY_INPUT_RIGHT] >= 1)key[KEY_INPUT_RIGHT] = pace;
	}
	else if (key[KEY_INPUT_DOWN] %2 == 0 && key[KEY_INPUT_DOWN] != 0 && key[KEY_INPUT_UP] == 0 && touchY / 30 < 19) {//下ボタンを押したとき
		touchY += 30;//上に移動する
		dchosing = 0;

		//下を押したとき、右ボタンと左ボタンも押せるようになる
		if (key[KEY_INPUT_LEFT] >= 1)key[KEY_INPUT_LEFT] = pace;
		else if (key[KEY_INPUT_RIGHT] >= 1)key[KEY_INPUT_RIGHT] = pace;
	}
}


//土管の移動先を移動する
//　　　　　　　（移動する先の土管の番号、土管の移動先の番号を変えているかどうか、選択している座標）
void ChangeDokan(int &dselect, int dchosing, int touchX, int touchY) {

	if (dchosing == 1 && key[KEY_INPUT_RSHIFT] % 5 == 2) {//右シフトキーを教えているとき
		dselect++;//移動する先を一つ進める
		if (dselect >= 10)dselect = 0;//移動する先の番号が１０以上の時、移動先の番号０にする
		makesta[make][touchX / 30][24 - touchY / 30] = makesta[make][touchX / 30][24 - touchY / 30] / 10 * 10 + dselect;
	}
}

//ステージ上のものを消すとき
//　　　　　　　　（土管の移動先の番号を変えているかどうか、選択している座標）
void BlockDisappear(int &dchosing, int touchX, int touchY) {
	if (key[KEY_INPUT_BACK] >= 1) {//バックスペースを押したとき
		dchosing = 0;//土管の移動先の番号を変えていない
		if (makesta[make][touchX / 30][24 - touchY / 30] >= 100) {//土管を消すとき
			dempty[(make - 1) / 2 + 1][makesta[make][touchX / 30][24 - touchY / 30] % 100 / 10] = 0;//消す土管の番号を空にする
			for (int i = 0; i <= 9; i++) {
				if (dempty[(make - 1) / 2 + 1][i] == EMPTY) {
					dokango[(make - 1) / 2 + 1] = i;//選べるようになる土管を変える
					break;
				}
				else if (i == 9)dokango[(make - 1) / 2 + 1] = 10;
			}

		}
		makesta[make][touchX / 30][24 - touchY / 30] = EMPTY;//消す
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


//ステージを変えるとき
//　　　　　　　（クリックしたとき、土管の移動先の番号を変えているかどうか、今作っているステージ）
void ChangeStage(int &touch, int &dchosing,int &make) {
	if (key[KEY_INPUT_INSERT] == 1 && make < 24) {//インサートキーを押したとき
		make++;//ステージを一つ進める
		touch = 0;
		dchosing = 0;
	}
	else if (key[KEY_INPUT_DELETE] == 1 && make > 1) {//デリートキーを押したとき
		make--;//ステージを一つ戻す
		touch = 0;
		dchosing = 0;
	}
}

//クリックをキーでできるとき
//　　　　　　（クリックしたかどうか、土管の移動先の番号を変えているかどうか）
void PutThing(int &touch, int &dchosing) {
	if (key[KEY_INPUT_SPACE] >= 1) {
		touch = 1;
		dchosing = 0;
	}
}


//キーボードを入力したときの動作の計算
//　　　　　　　（土管の移動先の番号を変えているかどうか、移動先の土管の番号、クリックしたかどうか、選択している座標、スクロール数、今作っているステージ、移動するペース）
int KeyInputData(int &dchosing, int &dselect, int &touch, int &touchX, int &touchY, int &stmove,int &make,int &pace) {

	ChangeDokan(dselect, dchosing, touchX, touchY);//土管の移動先の番号を変える

	BlockDisappear(dchosing, touchX, touchY);//ブロックを消す

	ChangeStage(touch, dchosing,make);//ステージを変える

	MoveUpAndDown(touchY, dchosing, pace);//上下させる

	MoveRightAndLeft(touchX, dchosing, stmove,pace);//左右に動かす

	PutThing(touch, dchosing);//クリックする

	MoveToSelectMonitor(touchX, touchY, stmove);//やっているモニターを変える

	ChangeAllByKey();//ステージ全体についてやる

	if (key[KEY_INPUT_S] >= 1) {//セーブする
		Save();
	}
	else if (key[KEY_INPUT_ESCAPE] == 1 || key[KEY_INPUT_RETURN] == 1) {//ステージづくりをやめる
		return 1;
	}

	return 0;
}



//マウスの計算
//　　　　　　　　　（マウスによって獲得した座標、クリックしたかどうか、土管の移動先の番号を変えているかどうか、選択している座標、土管の移動先の番号、スクロール数）
void MouseInputData(int &p, int &r, int &button, int &touch, int &dchosing, int &touchX, int &touchY, int &dselect, int stmove) {
	button = 0;//クリックしたかどうか
	GetMouseInputLog(&button, &p, &r, TRUE);//マウスのデータを入れる
	if (button != 0) {//クリックされたとき
		dchosing = 0;//土管の移動先の番号を変えていない
		touch = 1;//タッチされた
		touchY = r + 120;//座標の調節
		touchX = p + stmove;
	}
	else if (button == 0) {//クリックされなかったとき
		touch = 0;//クリックされてない
	}

	//右のシフトボタンが押されたとき、土管の移動先を変更できるようになる
	if ((touch == 1 || key[KEY_INPUT_RSHIFT] == 1) && makesta[make][touchX / 30][24 - touchY / 30] >= 100 && dchosing == 0 && dokango[(make - 1) / 2 + 1]<10) {
		dselect = 0;
		dchosing = 1;
	}
}

//ステージにあるものを表示する
//　　　　　　　　　　（スクロール数、何を選んだか）
void MakeStageImageShow(int stmove,int choice) {


	int black = GetColor(0, 0, 0);//黒
	int white = GetColor(-1, -1, -1);//白

	int i, h;
	DrawBox(0, 0, 510, 480, white, TRUE);//白く塗りつぶす


	//城と旗とマリオの最初の場所の表示
	DrawRotaGraph(100 + (flagpoint - 2) * 30 - stmove, 300, 1, 0.0, flagImg, TRUE);//ゴールの旗の表示
	DrawRotaGraph(90 + (flagpoint + 3) * 30 - stmove, 360, 1, 0.0, castleImg, TRUE);//城の表示
	DrawExtendGraph(50 - stmove - 10, 430,	50 - stmove + 5, 430 + 20,	RsupermarioImg, TRUE);//最初のマリオの位置の表示

	//ステージの表示
	int x;//表示するときの右端のX座標
	int y;//表示するときの上側のY座標
	int a;//どこの場所を表示するか
	for (h = 0; h <= 24; h++) {
		for (i = stmove / 30; i <= 19 + stmove / 30; i++) {
			x = i * 30 - stmove;
			y = (20 - h) * 30;
			a = makesta[make][i][h];
			if (a == EMPTY) continue;//何もなかった時、戻る
			//ブロックの表示
			MakeStageMonsterShow(a, x, y ,0, 1);//モンスターを表示する
		}
	}
}

//モンスターや、アイテムの表示
//　　　　　　　　　　　（表示するかどうか調べるところ、そこのX座標、そこのY座標、モンスターを選んだかどうか、ステージに表示するかどうか）
void MakeStageMonsterShow(int a,int x,int y,int mon,int type) {
	int black = GetColor(0, 0, 0);

	//ブロックと砲台の表示
	if (a >= HATENA&&a < 100)DrawExtendGraph(x, y , x + 30, y + 30, hatenablockImg, FALSE);//ハテナブロック
	else if (a == HATENA_KNOCKED && mon == 0) DrawExtendGraph(x, y , x + 30, y + 30, normalblockImg, FALSE);//空のハテナブロック
	else if (a == BRICK && mon == 0) DrawExtendGraph(x, y , x + 30, y + 30, brickImg, FALSE);//レンガブロック
	else if (a == COINBLOCK && mon == 0) DrawExtendGraph(x, y , x + 30, y + 30, coinImg, TRUE);//コイン
	else if (a == FLOOR) DrawExtendGraph(x, y , x + 30, y + 30, floarImg, TRUE);//地面
	else if (a == GRASS) DrawExtendGraph(x, y , x + 30, y + 30, floarupImg, TRUE);//草のある地面
	else if (a >= DOKANUP_MOVE || a == DOKANUP) DrawExtendGraph(x - 2, y , x + 32, y + 31, dokanupImg, TRUE);//上の土管
	else if (a == DOKANDOWN) DrawExtendGraph(x, y , x + 30, y + 30, dokandownImg, TRUE);//下の土管
	else if (a == HALFFLAG1) DrawExtendGraph(x, y , x + 30, y + 30, halfFlagImg, TRUE);//中間の旗
	else if (a <= - HODAI) DrawExtendGraph(x, y , x + 30, y + 30, hodaiImg, TRUE);//砲台

	//敵などの表示
	int b;//ハテナブロックに入っている
	int c;//砲台に入っている

	if (a < HATENA + ITEM)b = a - HATENA;
	else b = -(a - HATENA - ITEM);
	if (a > -(HODAI + ITEM))c = -(a + HODAI);
	else c = a + HODAI + ITEM;

	if ((a == -SUPER_KINOKO && mon == 1) || b == -SUPER_KINOKO || c == -SUPER_KINOKO)
		DrawExtendGraph(x, y , x + 30, y + 30 , kinokoImg, TRUE);//スーパーキノコ
	else if ((a == -ONE_UP_KINOKO && mon == 1) || b == -ONE_UP_KINOKO || c == -ONE_UP_KINOKO)
		DrawExtendGraph(x, y , x + 30, y + 30, upkinokoImg, TRUE);//ワンナップキノコ
	else if ((a == -FIREFLOWER && mon == 1) || b == -FIREFLOWER || c == -FIREFLOWER)
		DrawExtendGraph(x, y , x + 30, y + 30, fireflowerImg, TRUE);//ファイヤーフラワー
	else if (a == - KURIBO || b == -KURIBO || c == -KURIBO) DrawExtendGraph(x, y , x + 30, y + 30, kuriImg, TRUE);//クリボー
	else if (a == - NOKONOKO || b == -NOKONOKO || c == -NOKONOKO) DrawExtendGraph(x, y, x + 30, y + 30, RnokoImg, TRUE);//ノコノコ
	else if (a == -STOP_KORA || b == -STOP_KORA || c == -STOP_KORA) DrawExtendGraph(x, y , x + 30, y + 30, koraImg, TRUE);//止まっている甲羅
	else if (a == -MOVE_KORA || b == -MOVE_KORA || c == -MOVE_KORA) DrawExtendGraph(x, y , x + 30, y + 30, koraImg, TRUE);//動いている甲羅
	else if (a == -TOGEZO || b == -TOGEZO || c == -TOGEZO) DrawExtendGraph(x, y , x + 30, y + 30, RtogezoImg, TRUE);//トゲゾー
	else if (a == -PAKKUN || b == -PAKKUN  || c == -PAKKUN) DrawExtendGraph(x, y , x + 30, y + 30, packunImg, TRUE);//パックンフラワー
	else if (a == -BLACK_PAKKUN || b == -BLACK_PAKKUN || c == -BLACK_PAKKUN) DrawExtendGraph(x, y , x + 30, y + 30, blackpackunImg, TRUE);//ブラックパックンフラワー
	else if (a == - STOP_SPINE|| b == -STOP_SPINE || c == - STOP_SPINE) DrawExtendGraph(x, y , x + 30, y + 30, spineImg, TRUE);//トゲ
	else if (a == - STOP_DOSSUN || b == - STOP_DOSSUN|| c == - STOP_DOSSUN) DrawExtendGraph(x, y , x + 30, y + 30, dosunImg, TRUE);//ドッスン
	else if (a == -MOVE_TERESA || b == - MOVE_TERESA || c == - MOVE_TERESA) DrawExtendGraph(x, y , x + 30, y + 30, RteresaImg, TRUE);//テレサ
	else if (a == -KILLER || b == - KILLER || c == - KILLER) DrawExtendGraph(x, y , x + 30, y + 30, RkillerImg, TRUE);//キラー

	//文字の表示
	if (a >= DOKANUP_MOVE && type == 1) {//土管の番号と、移動先の表示
		DrawFormatString(x + 11, y - 20, black, "%d", a % 100 / 10);//その土管の番号
		DrawFormatString(x + 7, y - 5, black, "↓");
		DrawFormatString(x + 11, y + 10, black, "%d", a % 10);//移動先の番号
	}
	else if (a >= DOKANUP_MOVE && type == 0) {//土管の、下の矢印
		DrawFormatString(x + 7, y + 10, black, "↓");
	}
	else if (a == -MOVE_KORA || b == - MOVE_KORA || c == - MOVE_KORA) {//移動する甲羅の、移動することを示す矢印
		DrawFormatString(x + 7, y + 5, black, "→");
	}
}




//置くためのブロックや、敵などを選ぶ部分の表示
//　　　　　　　　　（何を選んでいるか、選んでいるのがモンスターかどうか）
void MakePutItemShow(int choice ,int mon) {

	int black = GetColor(0, 0, 0);//黒
	int white = GetColor(-1, -1, -1);

	DrawBox(510, 0, 640, 500, white, TRUE);//選ばれる部分を白く塗りつぶす

	int x = 570;//左端の座標
	int a;//表示するもの
	for (int i = 1; i <= 11; i++) {
		if (i == 4) a = HATENA;//ハテナブロックを選らんだとき
		else if (i == 6) a = DOKANUP;//移動できない土管を選んだ時
		else if (i == 7) a = DOKANUP_MOVE;//移動する土管を選んだ時
		else if (i == 8) a = FLOOR;//地面を選んだ時
		else if (i == 9) a = GRASS;//草のある地面を選んだ時
		else if (i == 10) a = -HODAI;
		else if (i == 11) a = HALFFLAG1;//中間の旗を選んだ時
		else a = i;
		MakeStageMonsterShow(a, x, (i - 1) * 30 , 0,0);//選ぶものの表示
	}

	//置くものを選ぶところのブロックの表示

	
	
	x = 540;//左端の座標
	for (int i = -3; i <= 11; i++) {
		if (i <= 0) {//アイテムを選ぶ時
			a = 3 + i;
		}
		else if (i < -11 && i >= -100) {//モンスターを選ぶ時
			a = 0;
		}
		else a = -i;

		MakeStageMonsterShow(a, x, (i + 2) * 30, 1, 0);//選ぶものの表示
	}
	//置くものを選ぶところの敵などの表示


	//何を選択しているかの表示
	DrawString(20 * 30 - 3, 15 * 30 - 30, "選択", black);
	DrawBox(20 * 30 - 5, 15 * 30 - 5, 20 * 30 + 30 + 5, 15 * 30 + 30 + 5 , black, FALSE);//選択しているものを囲う四角
	if (choice == 0) {
		DrawLine(20 * 30 - 5, 15 * 30 - 5, 20 * 30 + 30 + 5, 15 * 30 + 30 + 5, black, 1);//何も選んでないとき、斜線を表示する
	}
	else {
		MakeStageMonsterShow(choice, 20 * 30, 15 * 30, mon,0);//選んだものの表示
	}

	DrawLine(510, 0, 510, 600, black);//ステージとの区切りの表示
}



//ステージづくりの時のデータを表示する
//　　　　　　　　　　（何を選んでいるか、選択している座標、土管の移動先の番号を変えているかどうか、スクロール数）
void MakeStageDataShow(int choice, int touchX, int touchY, int dchosing, int stmove) {
	int black = GetColor(0, 0, 0);

	DrawBox(touchX / 30 * 30 - stmove + 1, (touchY / 30 - 4) * 30 + 1, (touchX / 30 + 1) * 30 - stmove - 1, (touchY / 30 - 3) * 30 - 1, GetColor(0, 0, 255), FALSE);
	DrawBox(touchX / 30 * 30 - stmove, (touchY / 30 - 4) * 30, (touchX / 30 + 1) * 30 - stmove, (touchY / 30 - 3) * 30, GetColor(0, 0, 255), FALSE);
	DrawBox(touchX / 30 * 30 - stmove + 1, (touchY / 30 - 4) * 30 + 1, (touchX / 30 + 1) * 30 - stmove - 1, (touchY / 30 - 3) * 30 - 1, GetColor(0, 0, 255), FALSE);
	DrawFormatString(0, 0, black, "%d - %d 　%dステージ", ((make - 1) / 2) / 3 + 1, ((make - 1) % 6) / 2 + 1, 2 - make % 2);
}


//画像や文字の全体の表示
//　　　　　　　　（何を選んでいるか、選択している座標、土管の移動先の番号を変えているかどうか、スクロール数、選んでいるのがモンスターかどうか）
void MakeStageShow(int choice, int touchX, int touchY, int dchosing, int stmove, int mon) {

	ClearDrawScreen(); // 画面を消す

					   //ステージ上にある敵やブロックの表示
	MakeStageImageShow(stmove,choice);

	//ステージ上にこれから置くものを選ぶものの表示
	MakePutItemShow(choice ,mon);

	//ステージづくりの時の、データの表示
	MakeStageDataShow(choice, touchX, touchY, dchosing, stmove);

	ScreenFlip();
}

