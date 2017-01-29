#include "DxLib.h"
#include "PlayAndMakeGame.h"

static int key[256]; // キーが押されているフレーム数を格納する
#define FontSize  20
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

int MoveToManual(int &);//マニュアルを移動する

void ShowMoveToManual(int);//マニュアルの移動の説明

void MakeStageAboutKey();//ステージづくりのキーの説明

void MakeStageHowTo();//ステージづくりのやり方の説明

void PlayStageAboutKey();//プレイ時のキーについての説明

void PlayStageHowTo();//プレイ時のやり方の説明


//マニュアルのまとめ
void Manual() {
	key[KEY_INPUT_RETURN] = 2;
	int red = GetColor(255, 0, 0);//赤
	int white = GetColor(-1, -1, -1);//白
	int black = GetColor(0, 0, 0);//黒
	int yellow = GetColor(255, 255, 0);//黄色
	int select = 1;//選ばれているマニュアル
	while (ScreenFlip() == 0  ) {
		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
		}

		ClearDrawScreen();

		DrawBox(0, 0, 650, 500, white, TRUE);
		SetFontSize(20);

		// 文字列の描画

		if (MoveToManual(select) == 1) {//マニュアルの移動
			break;
		}

		if (select == 1) {
			MakeStageHowTo();//ステージの作り方
		}
		else if (select == 2) {
			MakeStageAboutKey();//ステージを作るときの、キーについて
		}
		else if (select == 3) {
			PlayStageHowTo();//ゲームのやり方
		}
		else if (select == 4) {
			PlayStageAboutKey();//遊ぶ時のキーについて
		}

		ShowMoveToManual(select);//マニュアルの移動についてを見せる

		ScreenFlip();//表示する
	}
}


//マニュアルの移動についてのことを見せる
//　　　　　　　　（今のマニュアル）
void ShowMoveToManual(int select) {
	int black = GetColor(0, 0, 0);//黒
	DrawString(10, 450, "←ＢＡＣＫ", black);//戻りかたの表示
	if(select == 1)DrawString(120, 450, "タイトルへ", black);//タイトルに戻れるときの表示
	DrawFormatString(300,450,black,"%dP",select);//ページ数の表示
	DrawString(500, 450, "ＥＮＴＥＲ→", black);//進み方の表示
}


//マニュアルを移動する
//　　　　　　（今のマニュアル）
int MoveToManual(int &select) {
	gpUpdatekey();
	if (key[KEY_INPUT_RETURN] == 1 && select < 5) {//エンターキーが押されたとき
		select++;//マニュアルを一つ進める
		if (select > 4)select = 1;//限界まで進めたら、最初に戻る
	}
	if (key[KEY_INPUT_BACK] == 1 && select > 0) {//バックスペースキーが押されたとき
		select--;//マニュアルを一つ戻す
		if (select < 1)return 1;//限界まで戻ったら、メニュー画面に戻る
	}
	return 0;
}

//ステージづくりの説明
void MakeStageHowTo() {
	SetFontSize(FontSize);
	int x = 10;//表示するX座標
	int y = 20;//表示するY座標
	int black = GetColor(0, 0, 0);//黒
	int blue = GetColor(0, 0, 255);//青
	DrawString(x, 5, "ステージづくりの方法", GetColor(255, 0, 0));
	DrawString(x, y += FontSize + 5, "中央の画面・・・作り中のステージを表示する。", blue);
	DrawString(x, y += FontSize + 5, "右端の画面・・・ステージ上に置くものを表示する。", blue);
	DrawString(x, y += FontSize + 5, "　　　　　　　　そこでクリックしたものを置けるようになる。", blue);
	DrawString(x, y += FontSize + 5, "モンスター・・・ステージ上に置くと、ゲーム開始後に出現する。", black);
	DrawString(x, y += FontSize + 5, "アイテム・・・そのままステージに置くことができないが、", black);
	DrawString(x, y += FontSize + 5, "　　　　　　　ハテナブロックなどに入れることができる。", black);
	DrawString(x, y += FontSize + 5, "ブロックなど・・・ステージ上に置くとゲーム開始後に出現する。", black);
	DrawString(x, y += FontSize + 5, "？ブロック・・・モンスターかアイテムをその上に置くと、", black);
	DrawString(x, y += FontSize + 5, "　　　　　　　　モンスターかアイテムを入れることができる。", black);
	DrawString(x, y += FontSize + 5, "　　　　　　　　何もはいってないとき、コインを入れる", black);
	DrawString(x, y += FontSize + 5, "砲台・・・モンスターかアイテムを入れると、", black);
	DrawString(x, y += FontSize + 5, "　　　　　ゲーム中にそれが砲台から出現する。", black);
	DrawString(x, y += FontSize + 5, "　　　　　何も入ってないとき、コインが出現する", black);
	DrawString(x, y += FontSize + 5, "土管・・・上に表示されるのがその土管の番号で、", black);
	DrawString(x, y += FontSize + 5, "　　　　　下に表示されるのが移動先の番号で、", black);
	DrawString(x, y += FontSize + 5, "　　　　　右シフトキーで移動先は変更できる。", black);
}

//ステージづくりの時のキーのやり方
void MakeStageAboutKey() {
	SetFontSize(FontSize);
	int x = 10;//表示の時のX座標
	int y = 20;//表示の時のY座標
	int black = GetColor(0,0,0);//黒
	int blue = GetColor(0, 0, 255);//青
	DrawString(x, 5, "ステージづくりの時のキーの説明", GetColor(255, 0, 0));
	DrawString(x, y += FontSize + 5, "ＥＳＣＡＰＥキー・・・タイトルに戻る", blue);
	DrawString(x, y += FontSize + 5, "エンターキー・・・ゲームのプレイ画面に移動する", blue);
	DrawString(x, y += FontSize + 5, "インサートキー(INS)・・・作るステージを一つ進める", black);
	DrawString(x, y += FontSize + 5, "デリートキー(DEL)・・・作るステージを一つ戻す", black);
	DrawString(x, y += FontSize + 5, "スペースキー・・・クリックと同じ", black);
	DrawString(x, y += FontSize + 5, "ＢＡＣＫキーキー・・・選択している場所のものを消す", blue);
	DrawString(x, y += FontSize + 5, "　　　　土管の上に何か置くときは、消してからじゃないと無理", blue);
	DrawString(x, y += FontSize + 5, "矢印キー・・・矢印の方向に移動する", black);
	DrawString(x, y += FontSize + 5, "左コントロールキー＋矢印キー・・・早く移動する", black);
	DrawString(x, y += FontSize + 5, "右コントロールキー＋矢印キー・・・ゆっくり移動する", black);
	DrawString(x, y += FontSize + 5, "Ｓキー・・・今のステージデータを保存する", blue);
	DrawString(x, y += FontSize + 5, "左シフトキー・・・ステージ画面か、選択画面に移動する。", black);
	DrawString(x, y += FontSize + 5, "右シフトキー・・・土管の移動する先を変更する", black);
	DrawString(x, y += FontSize + 5, "Ctrl + Alt + Back・・・今のステージを全部消す", blue);
	DrawString(x, y += FontSize + 5, "Ctrl + Alt + C・・・今のステージをコピーする", black);
	DrawString(x, y += FontSize + 5, "Ctrl + Alt + P・・・コピーしたステージを張り付ける", black);
}


//どうやって遊ぶか
void PlayStageHowTo() {

	SetFontSize(FontSize);
	int x = 10;//表示するX座標
	int y = 20;//表示するX座標
	int black = GetColor(0, 0, 0);//黒
	int blue = GetColor(0, 0, 255);//青
	DrawString(x, 5, "プレイ方法", GetColor(255, 0, 0));
	DrawString(x, y += FontSize + 5, "最初・・・何かしらのキーを押すとゲームが始まります。", blue);
	y += FontSize;
	DrawString(x, y += FontSize + 5, "クリア条件・・・ステージ右端にある、", blue);
	DrawString(x, y += FontSize + 5, "　　　　　　　　ゴールの旗まで行くとゴールです。", blue);
	DrawString(x, y += FontSize + 5, "クリア後・・・何かしらのキーを押すと次に進みます", blue);
	DrawString(x, y += FontSize + 5, "失敗条件・・・地面の穴に落ちるか、", blue);
	DrawString(x, y += FontSize + 5, "　　　　　　　ちびマリオの時にモンスターに当たった時です。", blue);
	DrawString(x, y += FontSize + 5, "ゲームオーバー条件・・・左上の残基が０になった時", blue);
	DrawString(x, y += FontSize + 5, "レンガ・・・スーパーマリオ以上の時、頭をぶつけると消えます。", black);
	DrawString(x, y += FontSize + 5, "？ブロック・・・頭をぶつけると、入ってるものが出てきます。", black);
	DrawString(x, y += FontSize + 5, "　　　　　　　　ただ、動く甲羅は普通より遅いです。", black);
	DrawString(x, y += FontSize + 5, "土管・・・その上で下矢印を押すと、違う場所に移動します。", black);
	DrawString(x, y += FontSize + 5, "砲台・・・一定間隔で何かが発射されます。", black);
	DrawString(x, y += FontSize + 5, "　　　　　ただ、動く甲羅は普通より遅いです。", black);
	DrawString(x, y += FontSize + 5, "しゃがむ・・・しゃがむことはできません。", black);
	DrawString(x, y += FontSize + 5, "ジャンプ・・・床の上か、モンスターを踏むとできます。", black);
	y += FontSize + 5;

}


//ゲームをするときの、キーのやり方
void PlayStageAboutKey() {
	SetFontSize(FontSize);
	int x = 10;//表示するX座標
	int y = 40;//表示するY座標
	int black = GetColor(0, 0, 0);//黒
	int blue = GetColor(0, 0, 255);//青
	
	DrawString(x, 5, "プレイ時のキーの説明", GetColor(255, 0, 0));
	DrawString(x, y += FontSize + 5, "移動・・・左右矢印キー", blue);
	DrawString(x, y += FontSize + 5, "ジャンプ・・・上矢印キー", blue);
	DrawString(x, y += FontSize + 5, "左シフトキー＋矢印キー・・・ダッシュ(不完全)", black);
	DrawString(x, y += FontSize + 5, "右シフトキー・・・スーパーマリオならマリオ弾、", black);
	DrawString(x, y += FontSize + 5, "　　　　　　　　ファイヤーマリオならファイヤーボールを出す", blue);
	DrawString(x, y += FontSize + 5, "左右コントロールキー・・・時間を止められる。", black);
	DrawString(x, y += FontSize + 5, "　　　　　　　　　　　　　ただし、１０００スコアを消費", black);
	DrawString(x, y += FontSize + 5, "エスケープキー・・・自害する(ステージづくりと違う)", blue);
	DrawString(x, y += FontSize + 5, "バックスペースキー・・・ゲームをやめる(ステージづくりと違う)", blue);
	
}



