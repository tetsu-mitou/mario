#include "DxLib.h"
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

#define ITEM (10)

#define MONSTER (10000)//モンスターの限界数





int Key[256]; // キーが押されているフレーム数を格納する

// キーの入力状態を更新する
int gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
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

static int stage[100][25];//プレイ中のステージの、判定用。
//１はレンガ、2は空の？ブロック、３はコイン、4は上の土管、5は下の土管、6は地面、7は草がある地面、20以上100未満は？ブロック、100以上は移動の土管

static int dstage[26][100][25];//全ステージを保存する

static int bulletY[200];//弾のY座標
static int bulletX[200];//弾のX座標
static int Bside[200];//弾の向き
static double Bnuton[200];//弾の重力
static int Btype[200];//弾の種類


static int Mtype[MONSTER];//モンスターの種類
//-3はファイヤーフラワー、-2はワンナップキノコ、-1はスーパーキノコ、0はコイン、1はクリボー、2はノコノコ、3は止まっている甲羅、4は動く甲羅、
//5はトゲゾー、6はパックンフラワー、7は黒パックンフラワー、８は動かないとげ、9は落ちてこないドッスン、10は普通のテレサ、20は上がっていくとげ、
//21は落ちてくるドッスン、22は照れテレサ、100以上は砲台

static int monMove[MONSTER];//モンスターの動く距離
static int monY[MONSTER];//モンスターのY座標
static int monX[MONSTER];//モンスターのX座標
static int crol[MONSTER];//微調整
static int monSide[MONSTER];//モンスターの向き
static int monTime[MONSTER];//モンスターの移動
static int monEnd[MONSTER];//モンスターが死んでいるかどうか
static int monHP[MONSTER];//モンスターのHP
//モンスターの表示


int black = GetColor(0, 0, 0);//黒
int white = GetColor(-1, -1, -1);//白





//プロトタイプ宣言始まり



//画像のデータのセット
void ImageDataSetToMakeStage();

//すべての変数の初期化
void FirstPlayDataSet(int &, int &, int &, long &, int &, int &, int &, int &, int &, double &, double &, double &,
	int &,int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, 
	int &, int &, int &,int &, int &, int &, int &, int &, int &, int &);


//モンスターのデータの初期化
void MonsterPlayDataSet(int &);

//弾の初期化
void BulletPlayDataSet(int &);

//ステージデータの総数
void StagePlayDataSet(int &, int , int , int );

//モンスターを出現させる
void MonsterAppear(int &, int , int , int , int);

//ステージ上にモンスターを出現させる
void MonsterAppearOnStage(int &);

//土管に入って移動する
void DokanMove(int , int &, int &, int &, int &, int &, int &, int &, int );

//マリオが、土管によって移動する
void MarioMovedByDokan(int &, int &, int &, int &, int &, int &, int &, int &, int &,
	int &, int , int );

//プレイするときのスタート画面
int GameStartShow(int , int &, int &, int &, int &, int &, int &, int &, int &,int &, int &, int&);

//クリアしたときのデータの初期化
void DataSetByClear(int , int &, int &, int &, int &, int &, int &);

//死んだことによってする初期化
void DataSetByDeath(int &, int , int &, int &, int &, int &, int &);

//中間の旗によって移動する
void MoveByFlag(int , int , int , int , int , int , int &, int &, int &, int &);

//初期状態のマリオの場所の設定
void MarioPointDataSet(int , int , int , int , int &, int &, int &, int &);


//ステージのデータをセットする
void StageDataSet(int &, int , int , int , int );


//死んだ後の初期化
int SecondPlayDataSet(int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &,
	int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, 
	int &, int &, int &, int &, int &, int &);

//マリオがコインに触れたとき
void CoinGet(int , int , int , int , int , int &, int &);

//マリオが中間の旗に触れたとき
void FlagGet(int &, int &, int &, int , int &, int ,
	int &, int &, int &, int &, int &);


//弾を消す
void BulletDisappear(int , int &, int );

//弾が移動する
void BulletMove(int , int &, int );


//ファイヤーボールがモンスターに当たった時
int FireTouchMonster(int , int , long &, int &, int );

//ファイヤーボールが地面に当たった時
int FireTouchFloor(int , double , int );

//ファイヤーボールが動かなくなる時
int FireMoveStop(int, int , int , int , int &, int &, int , long &, double );

//ファイヤーボールが動く
void FireMove(int , int , int &, long &, int &);

//弾の処理全部
void BulletDataChange(long &, int &, int &, int &);

//モンスターを消すとき
int MonsterDelete(int &, int &);

//弾がモンスターに当たった時
void BulletAttackMonster(int , int &, int );

//モンスターが落ちるとき
int MonsterFall(int , int , int );

//キラーを移動させる
void KillerGo(int );

//とげが、停止中か動き中かを変える
void SpineChange(int , int , int ,int);

//とげが上に上がる
void SpineUp(int , int , int , int , int , int &);


//ドッスンの頭にドッスンがあるかどうか
int DossunHeadTouch(int , int );

//ドッスンが、上に上がるか、下に落ちるように変わるか
void DossunUpOrChange(int , int , int , int );

//ドッスンが落ちるとき
void DossunFall(int , int );

//砲台がモンスターを出現させる
void MosterAppearByHodai(int , int &, int );


//砲台がモンスターを出現させる時間など
void HodaiCreate(int , int , int , int , int , int , int &, int &, int );


//移動している甲羅にブロックが当たった時
void KoraTouchBlock(long &, int &, int &, int &, int , int , int , int );



//モンスターがブロックに当たった時
void MonsterTouchBlock(int , long &, int &, int &, int &, int &);


//モンスターがほかのモンスターに当たった時
int MonterTouchOtherMonster(int , int , long &, int &);

//砲台に当たった時、向きを変える
int MonsterTouchHodai(int , int);

//モンスターが動くとき
void MonsterMove(int , int &, int , int ,int,int);

//甲羅が消えるとき
void KoraDisappear(int , int );

//マリオがアイテムを獲得したとき
void MarioLevelUp(int , int &, int &, int &, int &, int &, int &, int &, long &);

//モンスターがマリオに当たった時
void MonsterTouchMario(int , int &, int &, int &, int &, int &, int &, int &, int &, long &);

//マリオがモンスターを踏んだ時
int  MarioStampMonster(long &, double , double , double , int & , int &, int &, int &,
	int &, int &, int &, int &, int &, int &, int , int );

//テレサがテレサに当たった時
int TeresaTouchTeresa(int , int &, int , int , int , int );

//テレサが横に動く
void TeresaMoveX(int , int , int , int , int &, int &, int , int , int &);


//テレサが縦に移動する
void TeresaMoveY(int , int , int , int , int , int , int &, int &, int &);


//テレサが動く
void TeresaMoveToMario(int , int , int , int , int &, long&, int &);


//テレサが、動くか照れている状態になるか
void TeresaTypeChange(int , int , int );

//テレサについてのこと
void AboutTeresa(int , int , int , int , int &, long&, int &);


//モンスターについての全部の処理
void MonsterDataSet(int &, int &, int &, int &, int &, int &, int &, int &, int &, int &, int &,
	int &, int &, int &, int &, double &, double &,
	double &, long &, int &, int &, int &, int &, int ,int);
//ここまで敵の処理




//マリオの右側に障害物がなく進むとき
void MarioRightMoveSafely(int , int , int &, int &);

//マリオの右側にブロックがあるかどうか
int  MarioRightMoveStopByBlock(int , int , int , int , int );


//マリオの右側に砲台があるかどうか
int MarioRightMoveStopByHodai(int , int , int , int , int );


//マリオが右に動けるかどうか
void MarioRightMoveStop(long &, int &, int &, int &, int &, int &, int &, int , int &,
	int , int , int , int , int &, int &, int &, int &, int &);

//右に動く動作のまとめ
void MarioRightMove(long &, int &, int &, int &, int &, int &,
	int , int &, int, int &, int &, int , int &, int &, int , int , int ,
	int , int , int , int , int &, int &, int &, int &);

//右へ進む動作



//左に、障害物がなく進むとき
void MarioLeftMoveSafely(int &, int , int );

//マリオに左にブロックがあるかどうか
int  MarioLeftMoveStopByBlock(int , int , int , int , int );

//マリオの左側に砲台があるかどうか
int MarioLeftMoveStopByHodai(int , int , int , int , int );

//マリオが左に動けるかどうか
void MarioLeftMoveStop(int &, int &, int &, int &, int &, int , int &, int , int &,
	int &, int &, int &, int &, int &, int &, int &);

//マリオが左に動く動作のまとめ

//右に動く動作と左に動く動作のまとめ
void LeftAndRightMove(long &, int &, int &, int &, int &, int &,
	int , int &, int , int &, int &, int , int &, int &, int , int , int , int , int , int , int &,
	int &, int &, int &);


//マリオが砲台に立っているかどうか
int  MarioTouchToHodai(int , int , int , int , int , int );


//マリオが地面に立っているかどうか
int MarioTouchFloor(int , int , int , int , int );

//マリオが落ちるとき
void MarioFall(int , int &, int , int &, int &, int , int , int &, int &, int &, int &,
	int &, int &, long &, double & , double & , double &, int &, int , int , int &, int &,
	int &, int &);

//マリオがジャンプするときの、データをセットする
void MarioJumpStartDataSet(double &, double &, double &, int &, int &, int &, double );

//マリオが、モンスターを踏むことでジャンプするとき
int MarioJumpStartOnMonster(long &, double &, double &, double &, int &, int &, int &, int &,
	int &, int &, int &, int &, int &, int &, int , int );


//マリオがジャンプを始める
void MarioJumpStart(long &, int &, int &, int &, int &, double &, double &, double &, int &,
	int &, int , int &, int &, int &, int , int &, int , int , int , int &,
	int &, int &, int &, int );


//地面について、ジャンプをやめるとき
int MarioJumpStop(int , int &, int , int , int , int &, int &);


//１フレーム分のジャンプをし終わったとき
int OneFrameJumpEnd(int , int , int , double , double );


//ジャンプ中の最初のデータ処理
void MarioJumpDataSet(double &, double , double , int &, int &, int &, int &, int , int );


//マリオのジャンプ中の処理のまとめ
void MarioJumping(long &, int &, int & , int &, int , int &, int &, int &, double &, double &,
	double &, int &, int &, int &, int &, int &, int &,
	int &, int &, int , int &, int &, int , int , int &, int , int , int , int &,
	int &, int &, int &);

//移動工程終わり


//土管に入るかどうか
void DokanGetIntoStart(int &, int &, int &, int &, int &, int , int , int , int , int ,
	int , int );


//マリオが土管にはいり中の時
int DokanGettingInto(int &, int &, int , int , int );

//土管に入るときの処理のまとめ
int  DokanGetInto(int &, int &, int &, int &, int &, int &, int , int , int , int , int ,
	int , int , int , int );


//土管から出る
void DokanGetOut(int &, int&, int &, int );


//ボタンを押して、ステージを変えたり、やめたりする
int StageChange(int &, int &, int &, int &, int &, int &, int &, int &, int &, int & ,int &);

//ボタンを押して、自滅する
void MarioKillMyself(int &, int &);

//ボタンを押して、スコアを消費して、時間を止めたかどうか
void TimeStop(int &, long &);

//マリオが死んでいるとき
int  MarioDying(int &, int , int &, int , int &);


//マリオがダメージを受けたとき
int MarioDamage(int &, int &, int &, double &, int &, int &, int &, int &, int &, int &,
	int );
//ハテナブロックの上にいる邪魔なモンスターをどかす
void MonsterUpByBlock(int,int,int);

//マリオの頭がブロックに当たった時
void MarioHeadHitBlock(int , int , int , int , int , int &, int &);

//マリオがクリアしたとき
int  MairoGameClear(long &, double &, int &, int &, int &, int &, int &, int , int , int ,
	int &, int , int , int , int );



//セーブデータを読み込む
void SaveInput();

//弾を出現させる
void BulletAppear(long &, int &, int , int , int , int , int , int , int );



//モンスターとアイテムを表示する
void PlayStageMonsterShow(int , int );

//ブロックを表示する
void PlayStageBlockShow(int , int , int);

//マリオと、ゴールの旗と、城の表示
void PlayStageMarioShow(int ,int , int , int , int , int , int , int , int , int , int ,int );

//その他のものを表示する
void PlayStageOtherShow(int , int , int , int , int , int , int , int ,
	int , int , int );

//表示についてのまとめ
void PlayStageShow(int , int , int , int , int , int , int , int , int , int , int ,
	int , int , int , int , int ,int);
//死ぬまでの、ゲームのループ
void PlayingGameByDeath(int &, int &, int &, int &, int &, int &, int &, int &, int &, int & , int &, int &, int &, long &,
	int &, int &, int &, int &, int &, double &, double &, double &, int &, int &, int &, int &, int &, int &,
	int &, int &, int &, int &, int &, int &, int &, int &, int &,
	int &, int &, int &);




//プロトタイプ宣言終わり








//全体のまとめ
void PlayingGame() {
	int mario;//マリオの残基
	int coin;//コイン数
	int mon;//モンスターの総数
	long score;//スコア
	int flagpoint;//ゴールの旗の場所
	int count ;//時間
	int clear;//クリアしたかどうか
	int dpla;//今いる場所がメインステージかサブステージか
	int stmove;//どれほどスクロールしているか
	double nuton;//重力加速度によって変更していって、一回分のジャンプの高さを表す
	double nutonLV;//重力加速度
	double nutonmax;//重力加速度の、初めの値
	int stop;//時間が止まっているかどうか
	int last;//いろいろな、判定
	int place;//今プレイしているステージ
	int dokanchange;//土管で移動しているかどうか
	int dokan;//移動先の土管の番号
	int black;//黒
	int white;//白
	int marioLV;//マリオの状態。１の時、ちびマリオ、２の時、スーパーマリオ、３の時、ファイヤーマリオ
	int moving;//スクロールするかどうか
	int superplus;//ちびマリオが、スーパーマリオや、ファイヤーマリオになった時に、マリオのY座標の幅を追加する
	int bullet;//今、ステージにある弾の総数 - 1
	int num;//今、ステージにいるモンスターの総数 - 1
	int jump;//ジャンプしているかどうか
	int marioDirection;//マリオの向き
	int MariowideX;//マリオの横の幅
	int MariowideY;//マリオの縦の幅
	int move;//移動できるかどうか
	int end;//マリオが、ダメージを受けたかどうか
	int marioY;//マリオの上側のY座標
	int marioX;//マリオの左側のX座標
	int monWide;//モンスターの幅
	int monstop;//モンスターが動いているかどうか
	int Ydokan;//移動先の土管のX座標
	int Xdokan;//移動先の土管のY座標
	int dying;//マリオが死んでいるかどうか
	int suke;//マリオの無敵時間
	int jumping;//モンスターによってジャンプしたかどうか,存在理由は、普通のジャンプは、上ボタンを押してないと、ジャンプをやめてしまうから
	int flag;//中間の旗を獲得したかどうか
	int flagStage;//中間の旗を獲得したところの場所,メインステージか、サブステージか
	int flagX;//中間の旗を獲得したところの、X座標
	int flagY;//中間の旗を獲得したときの、Y座標
	

	ImageDataSetToMakeStage();//画像データを読み込む

	SaveInput();//セーブデータを読み込む

	FirstPlayDataSet(mario, coin, mon,  score, flagpoint, count, clear, dpla, stmove, nuton, nutonLV, nutonmax, stop, last,  place,
		dokanchange, dokan, black, white, marioLV, moving, superplus, bullet, num, jump, marioDirection, MariowideX, MariowideY, move, end, monWide,
		flag,flagStage,flagX,flagY);//最初の初期化

	//死んだときのループ
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
		}

		int check = SecondPlayDataSet(dying, count, stop, move, dokanchange, dokan, coin, superplus, clear, monstop, flagpoint, marioLV, num, bullet, end, mario, place,
			marioImg, marioY, marioX, stmove, moving, dpla, Xdokan, Ydokan, suke ,jumping, MariowideX,flag,flagStage,flagX,flagY);
		//データのセット

		if (check == 1)break;//バックスペースを押されてた時、ゲームをやめる
		else if (check == 2)continue;//ステージを移動してた時、ゲームをやり直す

		PlayingGameByDeath(mario,num,bullet,dpla,flagpoint,stmove,dying,marioY,marioX, marioDirection,jump,marioLV,suke,score,
			coin,place,Ydokan,Xdokan,superplus,nutonmax,nutonLV,nuton,stop,MariowideX,MariowideY,moving,move,monWide,
			monstop,last,jumping,end,dokan,dokanchange,count,clear, flag,flagStage, flagX, flagY);//死ぬまでゲームをする

		if (Key[KEY_INPUT_BACK] >= 1) {//やめるとき
			break;
		}
		//ゲーム内のループ
		Sleep(1000);
	}
	//死んだ時のためのループ
	ClearDrawScreen();
	DrawFormatString(250, 200, white, "GAME OVER");
	Sleep(1000);
	WaitKey();
}




//画像の初期化
void ImageDataSetToMakeStage() {
	beforeHalfFlagImg = LoadGraph("画像/中間の旗前.png");
	AfterHalfFlagImg = LoadGraph("画像/中間の旗後.png");
	backgroundImg = LoadGraph("画像/背景.jpg");
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
	RmovemarioImg1 = LoadGraph("画像/歩く１右.png");
	LmovemarioImg1 = LoadGraph("画像/歩く１左.png");
	RmovemarioImg2 = LoadGraph("画像/歩く２右.png");
	LmovemarioImg2 = LoadGraph("画像/歩く２左.png");
	deathmarioImg = LoadGraph("画像/やられマリオ.png");
	//スーパーマリオ
	RjumpsupermarioImg = LoadGraph("画像/スーパーマリオジャンプ右.png");
	LjumpsupermarioImg = LoadGraph("画像/スーパーマリオジャンプ左.png");
	RsupermarioImg = LoadGraph("画像/スーパーマリオふつう右.png");
	LsupermarioImg = LoadGraph("画像/スーパーマリオふつう左.png");

	//スーパーマリオ
	RjumpfiremarioImg = LoadGraph("画像/ファイヤーマリオジャンプ右.png");
	LjumpfiremarioImg = LoadGraph("画像/ファイヤーマリオジャンプ左.png");
	RfiremarioImg = LoadGraph("画像/ファイヤーマリオふつう右.png");
	LfiremarioImg = LoadGraph("画像/ファイヤーマリオふつう左.png");

	//マリオ終わり
	coinImg = LoadGraph("画像/コイン.png");
	kuriImg = LoadGraph("画像/クリボー.png");
	RnokoImg = LoadGraph("画像/ノコノコ右.png");
	LnokoImg = LoadGraph("画像/ノコノコ左.png");
	koraImg = LoadGraph("画像/甲羅.png");
	RtogezoImg = LoadGraph("画像/トゲゾー右.png");
	LtogezoImg = LoadGraph("画像/トゲゾー左.png");
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

//すべての変数の初期化
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


//モンスターのデータの初期化
//　　　　　　　　　　（モンスターの番号）
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

//弾の初期化
//　　　　　　　　　　（弾の番号）
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

//ステージデータの総数
//　　　　　　　　　（土管に入っているかどうか）
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

//モンスターを出現させる
//                (モンスターの番号, モンスターの種類, 座標, 向き(1～2))
void MonsterAppear(int &num, int AppearType, int AppearX, int AppearY, int AppearDirection) {
	if (num < MONSTER) {
		num++;
		Mtype[num] = AppearType;//モンスターの種類
		monX[num] = AppearX + 2;//モンスターのX座標
		monY[num] = AppearY;//モンスターのY座標
		monMove[num] = 1;//モンスターの動く速さ
		if (Mtype[num] == MOVE_KORA)monMove[num] = 5;//動く甲羅は早く動く
		else if (Mtype[num] == FIREFLOWER || Mtype[num] == STOP_KORA || (Mtype[num] >= PAKKUN && Mtype[num] <= STOP_DOSSUN) || Mtype[num] >= HODAI) {
			monMove[num] = 0;//動かない
		}
		crol[num] = 0;
		monSide[num] = AppearDirection;//モンスターの向き
		monMove[num] = abs(monMove[num]) * monSide[num];
		monTime[num] = 0;//モンスターの特別な行動をするまでの時間
		monEnd[num] = 0;//モンスターの生死
		monHP[num] = 3;//モンスターのHP
	}
}

//ステージ上にモンスターを出現させる
//　　　　　　　　　　　　（モンスターの総数）
void MonsterAppearOnStage(int &num) {
	int i, h;
	for (h = 0; h <= 24; h++) {
		for (i = 0; i <= 99; i++) {
			if (stage[i][h] < 0) {
				int Direction = -1;
				if (stage[i][h] == -MOVE_KORA)Direction = 1;//動く	甲羅が出現するとき、右に移動する
				MonsterAppear(num, stage[i][h] * -1, 30 * i, (20 - h) * 30 + 2, Direction);//モンスターを出現させる
				stage[i][h] = 0;//出現させたところは消す
			}
		}
	}
}

//土管に入って移動する
//　　　　　　（今のステージの番号,土管に入ったかどうか,移動先の土管の座標,Y,マリオのY座標,スクロール,行先のステージの番号,移動先の土管の番号）
void DokanMove(int place, int &dokanchange, int &Xdokan, int &Ydokan, int &marioX, int &marioY, int &stmove, int &dpla, int dokan) {
	int last = 0;
	for (int g = place * 2 - 1; g <= place * 2; g++) {
		for (int h = 0; h <= 25; h++) {
			for (int i = 0; i <= 99; i++) {
				if (dstage[g][i][h] >= 101 &&
					dstage[g][i][h] % 100 / 10 == dokan) {//移動先の土管が見つかった時
					//どこに移動するかを設定する
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
		//移動先の土管に、マリオとスクロールをセットする
		marioY = (20 - Ydokan) * 30;
		marioX = Xdokan * 30 + 5;
		stmove = Xdokan * 30 - 300;
		if (stmove >= 78 * 30 - 10)stmove = 78 * 30 - 10;
		else if (stmove <= 0)stmove = 0;
	}

	dokanchange = 2;
}

//マリオが、土管によって移動する
//　　　　　　　　　　（スクロール数,マリオの座標,追加のマリオのY座標,ゴールの旗の位置,スクロールするかどうか,場所の番号、土管の座標,土管に入ったかどうか,ステージの番号、移動先の土管の番号）
void MarioMovedByDokan(int &stmove, int &marioX, int &marioY, int &superplus, int &flagpoint, int &moving, int &dpla, int &Xdokan, int &Ydokan, int &dokanchange, int place, int dokan) {
	if (dokanchange == 1) {
		DokanMove(place, dokanchange, Xdokan, Ydokan, marioX, marioY, stmove, dpla, dokan);//土管に入って移動する
	}
}

//プレイするときのスタート画面
//               （土管で移動するかどうか、ステージの番号、マリオの残基、スクロール数、中間の旗をとったかどうか、中間の旗の座標、
//　　　　　　　　マリオの追加のY座標、マリオの状態、マリオの横の幅、マリオのダメージ）
int GameStartShow(int dokanchange, int &place, int &mario, int &stmove, int &flag, int &flagStage, int &flagX, int &flagY, int &superplus, 
	int &marioLV ,int &MariowideX,int &end) {
	if (dokanchange == 0) {
		ClearDrawScreen();
		DrawFormatString(280, 200, white, "%dー%d", (place - 1) / 3 + 1, (place - 1) % 3 + 1);//何面にいるかを表示
		DrawFormatString(300, 250, white, "×%d", mario);//マリオの残基を表示
		DrawRotaGraph(280, 260, 0.20, 0.0, marioImg, TRUE);//マリオの残基を表示
		ScreenFlip();
		gpUpdateKey();
		WaitKey();
		gpUpdateKey();

		//キー操作
		if (Key[KEY_INPUT_BACK] >= 1) {//ゲームをやめる
			return 1;
		}
		else if (Key[KEY_INPUT_INSERT] >= 1 && place < 12) {//ステージを進める
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
		else if (Key[KEY_INPUT_DELETE] >= 1 && place > 1) {//ステージを戻す
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


//クリアしたときのデータの初期化
//　　　　　　　（クリアしたかどうか、マリオの残基、中間の旗をとったかどうか、旗の場所の番号、中間の旗の座標）
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

//死んだことによってする初期化
//　　　　　　　　（死んだかどうか、土管で移動するかどうか、マリオの追加のY座標、マリオの残基、マリオの状態、マリオの横の幅）
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

//中間の旗によって移動する
//             (旗で移動するかどうか、クリアしたかどうか、土管で移動するかどうか、中間の旗の座標、旗の場所の番号、マリオの座標、スクロール数、場所の番号)
void MoveByFlag(int flag,int clear,int dokanchange,int flagX,int flagY,int flagStage,int &marioX,int &marioY,int &stmove,int &dpla) {
	if (flag == 1 && clear == 0 && dokanchange == 0) {
		marioX = flagX * 30;
		marioY = (20 - flagY) * 30;
		stmove = (flagX - 8) * 30;
		dpla = flagStage;
		if (stmove < 0)stmove = 0;
		dstage[dpla][flagX][flagY] = HALFFLAG2;//移動先の中間の旗を、取った後の旗に変える
	}
}

//初期状態のマリオの場所の設定
//　　　　　　　　　　（土管で移動するかどうか、中間の旗で移動するかどうか、マリオの追加のY座標、マリオの座標、クリアの旗の座標、スクロールするかどうか）
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


//ステージのデータをセットする
//　　　　　　　（場所の番号、クリアしたかどうか、土管で移動するかどうか、中間の旗で移動するかどうか）
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


//死んだ後の初期化
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

	

	suke = 0;//無敵時間を０にする
	jumping = 0;//ジャンプしてないようにする
	count = 0;//時間を０にする
	stop = 0;//時間が止まってないようになる
	move = 0;//動けるようになる
	monstop = 0;//モンスターは動ける
	flagpoint = 90;//ゴールの旗の位置の設定

	MonsterPlayDataSet(num);//モンスターのデータを初期化する

	BulletPlayDataSet(bullet);//弾のデータを初期化する

	StagePlayDataSet(dying,clear,flag,dokanchange);//ステージデータを初期化する

	DataSetByClear(clear, mario, flag, flagStage, flagX, flagY, stmove);//クリアしたことでのデータを初期化する

	DataSetByDeath(end, dokanchange, superplus, mario, marioLV, MariowideX,stmove);//死んだことでのデータを初期化する

	if (mario <= 0)return 1;//残基がないとき、やめる


	int check = GameStartShow(dokanchange, place, mario, stmove, flag, flagStage, flagX, flagY, superplus,marioLV, MariowideX, end);
	//ゲームの始まりを表示する

	if (check != 0) {
		return check;
	}

	MarioMovedByDokan(stmove, marioX, marioY, superplus, flagpoint, moving, dpla, Xdokan, Ydokan, dokanchange, place, dokan);
	//土管で移動するとき

	MoveByFlag(flag, clear, dokanchange, flagX, flagY, flagStage, marioX, marioY, stmove, dpla);
	//中間の旗によって移動するとき

	MarioPointDataSet(dokanchange, flag, stmove, superplus, marioX, marioY, flagpoint, moving);
	//マリオの場所をセットする

	StageDataSet(dpla, clear, dokanchange, place, flag);
	//ステージのデータをセットする

	MonsterAppearOnStage(num);
	//ステージの上にモンスターを出す
	
	if(dpla %2 == 1)stage[flagpoint][6] = HATENA_KNOCKED;//旗の部分のブロック

	clear = 0;

	return 0;
}

//マリオがコインに触れたとき
//          （マリオの座標、マリオの幅、マリオの追加のY座標、コインの数、マリオの残基）
void CoinGet(int marioX, int marioY, int MariowideX, int MariowideY, int superplus, int &coin, int &mario) {
	for (int i = marioX - 1; i <= marioX + MariowideX + 1; i++) {
		for (int h = (marioY - 1) / 30; h <= (marioY + MariowideY + superplus + 5) / 30; h++) {
			if (stage[i / 30][20 - h] == COINBLOCK) {
				stage[i / 30][20 - h] = EMPTY;
				coin++;
				if (coin >= 100) {//コインが１００個になったら、残基が一つ増える
					coin = 0;
					if (mario < 99) {
						mario++;
					}
				}
			}//マリオがコインに触れているときのif

		}//マリオのX座標でのループ

	}//マリオのY座標でのループ
}

//マリオが中間の旗に触れたとき
//　　　　　（マリオの座標、マリオの幅、マリオの追加のY座標、場所の番号,中間の旗の判定、中間の旗の場所、中間の旗の座標、マリオの状態）
void FlagGet(int &marioX, int &marioY, int &MariowideX, int MariowideY, int &superplus,int dpla,int &flag,int &flagStage,int &flagX, int &flagY,int &marioLV) {
	for (int i = marioX - 1; i <= marioX + MariowideX + 1; i++) {
		for (int h = (marioY - 1) / 30; h <= (marioY + MariowideY + superplus + 5) / 30; h++) {
			if (stage[i / 30][20 - h] == HALFFLAG1) {
				stage[i / 30][20 - h] = HALFFLAG2;
				//中間の旗の場所を代入する
				flag = 1;
				flagStage = dpla;
				flagX = i / 30;
				flagY = 20 - h;
				if (marioLV == 1) {//ちびマリオなら、スーパーマリオになる
					marioLV = 2;
					superplus = 15;
					marioY -= 16;
					MariowideX = 25;
					marioX -= 10;
				}
			}//マリオが旗に触れているときのif

		}//マリオのX座標でのループ

	}//マリオのY座標でのループ
}


//弾を消す
//                  （処理している弾の番号、弾の総数、スクロール数）
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

//弾が移動する
//　　　　（現在処理している弾の番号、弾の総数、スクロール数）
void BulletMove(int i, int &bullet, int stmove) {
	for (int h = 0; h != 10 * Bside[i]; h += Bside[i]) {//弾が壁に当たってないとき移動する
		if (stage[(bulletX[i] + Bside[i] * 5) / 30][20 - (bulletY[i] + Bside[i] * 5) / 30] == EMPTY) {
			bulletX[i] += Bside[i];//弾を、弾の向きのほうに動かす
		}
		else {
			BulletDisappear(i, bullet, stmove);//弾を消す
			break;
		}
	}
}


//ファイヤーボールがモンスターに当たった時
//　　　　（処理している弾の番号、モンスターの総数、スコア、弾の総数、スクロール数）
int FireTouchMonster(int i, int num, long &score, int &bullet, int stmove) {
	//弾とモンスターのあたり
	int last = 0;
	for (int h = 0; h <= num; h++) {
		if (monEnd[h] == 1)continue;
		if (bulletX[i] <= monX[h] + 25 && bulletX[i] >= monX[h] &&
			bulletY[i] <= monY[h] + 25 && bulletY[i] >= monY[h]) {//弾がモンスターに当たった時
			if (Mtype[h] != COIN)Btype[i] = 0;//当たったのが、コインでないとき、弾は消える
			BulletDisappear(i, bullet, stmove);//弾を消す

			//ファイヤーボールで死ぬモンスターだったとき
			if (Mtype[h] >= KURIBO && Mtype[h] <= PAKKUN  || Mtype[h] == KILLER || Mtype[h] == STOP_TERESA || Mtype[h] == MOVE_TERESA) {
				monHP[h] -= 3;
				if (monHP[h] <= 0) {//モンスターを消す
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
	//弾とモンスターのあたり判定
}

//ファイヤーボールが地面に当たった時
//             （処理している弾の番号、弾の重力加速度の上限、弾が上下に動く向き）
int FireTouchFloor(int i, double Bnutonmax, int plus) {
	//弾と床のあたり判定

	bulletY[i] -= plus;
	if (stage[bulletX[i] / 30][20 - (bulletY[i] + 10) / 30] > EMPTY && stage[(bulletX[i]) / 30][20 - (bulletY[i] + 10) / 30] > EMPTY) {
		//地面に当たった時、重力加速度をリセットする
		Bnuton[i] = 0;
		return 1;
	}
	else return 0;
	//弾と床のあたり判定
}

//ファイヤーボールが動かなくなる時
int FireMoveStop(int plus, int h, int i, int BaseBulletY, int &num, int &bullet, int stmove, long &score, double Bnutonmax) {
	if (plus == -1) {//１回分のファイヤーボールの下がりが終わった時
		if (h < BaseBulletY + Bnutonmax - Bnuton[i]) {
			return 1;
		}
	}
	else if (plus == 1) {//１回分のファイヤーボールの上りが終わった時
		if (h > BaseBulletY + Bnutonmax + Bnuton[i]) {
			return 1;
		}
	}
	if (FireTouchFloor(i, Bnutonmax, plus) == 1) {//ファイヤーボールが地面に触れたとき
		return 1;
	}

	if (FireTouchMonster(i, num, score, bullet, stmove) == 1) {//ファイヤーボールがモンスターにあたった時
		return 1;
	}
	return 0;
}

//ファイヤーボールが動く
//　　　　　（処理している弾の番号、モンスターの総数、弾の総数、スコア、スクロール数）
void FireMove(int i, int num, int &bullet, long &score, int &stmove) {
	//炎の玉の時のif
	double BnutonLV = 3;
	double Bnutonmax = 5;
	if (Btype[i] == 2) {
		BulletMove(i, bullet, stmove);
		Bnuton[i] += BnutonLV;//弾の上下の速さを変化させる
		int h = bulletY[i];
		int plus;
		if (Bnutonmax - Bnuton[i] > 0) {//弾は上に上がる
			plus = 1;
		}
		else plus = -1;//弾は下に下がる
		int BaseBulletY = bulletY[i];
		Bnuton[i] += BnutonLV;
		for (;;) {
			if (FireMoveStop(plus, h, i, BaseBulletY, num, bullet, stmove, score, Bnutonmax) == 1) {//ファイヤーボールが動けるとき
				break;
			}
			h += plus;
		}

	}
	//炎の玉の時のif
}

//弾の処理全部
//　　　　　　　　　（スコア、弾の総数、スクロール数、モンスターの総数）
void BulletDataChange(long &score, int &bullet, int &stmove, int &num) {
	for (int i = 0; i <= bullet; i++) { //弾の処理
		BulletDisappear(i, bullet, stmove);//弾が消える

		BulletMove(i, bullet, stmove);//弾が動く

		FireMove(i, num, bullet, score, stmove);//ファイヤーボールが動く
	}
}


//モンスターを消すとき
//        (処理しているモンスターの番号、モンスターの総数)
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
		//消す
		i--;
		num--;
		return 1;
	}
	else return 0;
}

//弾がモンスターに当たった時
//　　　　　　　　（処理している弾の番号、弾の総数）
void BulletAttackMonster(int i, int &bullet,int stmove) {
	int h;
	for (h = 0; h <= bullet; h++) {
		if (Btype[h] == 1 && Mtype[i] != BLACK_PAKKUN && abs(bulletY[h] - monY[i]) < 25 && abs(bulletX[h] - monX[i]) < 25) {//弾がモンスターの当たった時
			Btype[h] = 0;
			if (Mtype[i] >= KURIBO && Mtype[i] <= PAKKUN)monHP[i]--;//モンスターのHPを減らす
			if (monHP[i] == 0)monEnd[i] = 1;//HPが０なら、消える
			BulletDisappear(i, bullet, stmove);//当たった弾は消える
		}
	}
}

//モンスターが落ちるとき,おちるとき１、おちないとき０
//　　　　（処理しているモンスターの番号、時間が止まっているかどうか、モンスターの総数）
int MonsterFall(int i, int stop, int num) {
	int h;
	int g;

	int a;// モンスターの左下の場所
	int b;//モンスターの右下の場所
	int last = 0;
	for (h = 0; h <= num; h++) {
		a = stage[(monX[i] - 1) / 30][20 - (monY[i] + 25) / 30];//モンスターの左下の場所
		b = stage[(monX[i] + 25 + 1) / 30][20 - (monY[i] + 25) / 30];//モンスターの右下の場所
		if (Mtype[i] != MOVE_TERESA && Mtype[i] != STOP_TERESA && Mtype[i] != STOP_DOSSUN && Mtype[i] != KILLER //下に落ちるモンスターで、
			&& (stop == 0 || Mtype[i] <= SUPER_KINOKO) && (a == EMPTY || a == COINBLOCK) && (b == EMPTY || b == COINBLOCK)) {//下がコインか、空の時
			if (Mtype[h] != STOP_TERESA && Mtype[h] != MOVE_TERESA && monX[i] + 24 >= monX[h] && monX[i] <= monX[h] + 24 &&
				monY[i] + 25 == monY[h]) {//下にモンスターがいるとき
				if (Mtype[i] == MOVE_KORA && Mtype[h] < HODAI && Mtype[i] != BLACK_PAKKUN) {//動く甲羅が上にいるとき
					monEnd[h] = 1;//下のモンスターは消える
				}
				last = 1;
				return 0;
			}
		}
		else {//下がブロックの時
			last = 1;//落ちられない
			return 0;
		}
	}
	if (last == 0) {
		monY[i]++;//下にモンスターがいないとき
		return 1;
	}
	else return 0;;
	//下に落ちれるとき
	
}

//キラーを移動させる
//           (処理しているモンスターの番号)
void KillerGo(int i) {
	int h;
	if (Mtype[i] == KILLER) {
		for (h = 0; h<5; h++) monX[i] += monSide[i];
	}
}

//とげが、停止中か動き中かを変える
//　　　　　　　（処理しているモンスターの番号、マリオの座標、マリオの縦の幅）
void SpineChange(int i, int marioX, int marioY,int MwideY) {
	if (Mtype[i] == STOP_SPINE && marioY + MwideY <= monY[i] && abs(marioX - monX[i]) <= 25 + 5) {
		Mtype[i] = MOVE_SPINE;
	}
}


//とげが上に上がる
//　　　　　（処理しているモンスターの番号、マリオの横幅、マリオの座標、マリオの追加の座標、マリオのダメージ）
void SpineUp(int i, int MariowideX, int marioX, int marioY, int superplus, int &end) {
	int h;
	if (Mtype[i] == MOVE_SPINE) {
		for (h = 0; h<3; h++) {
			monY[i] -= 5;
			if (marioY + superplus >= monY[i] && marioY <= monY[i] + 25 &&
				marioX + MariowideX + 1>= monX[i] && marioX <= monX[i] + 25 - 1) {//とげがマリオに当たったらダメージを受ける
				end = 1;
			}
		}
	}
}


//ドッスンの頭にドッスンがあるかどうか
//　　　　　　　　　（処理しているモンスターの番号、モンスターの総数）
int DossunHeadTouch(int i,int num) {
	for (int h = 0; h <= num; h++) {
		if (i != h && Mtype[h] == STOP_DOSSUN && abs(monX[i] - monX[h]) < 23 && abs(monY[i] - monY[h]) < 30) {//ドッスンの頭にドッスンがいるかどうか
			return 1;
		}
	}
	return 0;
}

//ドッスンが、上に上がるか、下に落ちるように変わるか
//                  (処理しているモンスターの番号、マリオの座標、モンスターの総数)
void DossunUpOrChange(int i, int marioX, int marioY,int num) {
	if (Mtype[i] == STOP_DOSSUN) {

		int a = stage[(monX[i] + 1)/ 30][20 - (monY[i] / 30)];//ドッスンの左上の場所
		int b = stage[(monX[i] + 25 - 1) / 30][20 - (monY[i]) / 30];//ドッスンの右上の場所

		if ((a == EMPTY || a == COINBLOCK) && (b == EMPTY || b == COINBLOCK) && DossunHeadTouch(i, num) == 0) {//ドッスンの上にドッスンかブロックがないとき
			monY[i]--;
		}
		if (marioY >= monY[i] && abs(marioX - monX[i]) <= 25 &&( b != COINBLOCK && b > EMPTY || DossunHeadTouch(i, num) == 1)) {//マリオが下にいる時
			Mtype[i] = FALL_DOSSUN;//下に向かっていくようになる
		}
	}
}

//ドッスンが落ちるとき
//　　　　　　（処理しているモンスターの番号、モンスターの総数）
void DossunFall(int i,int num) {

	int x1 = monX[i] / 30;//モンスターの左のX座標

	int x2 = (monX[i] + 25) / 30;//モンスターの右のX座標

	int y = 20 - (monY[i] + 30) / 30;//モンスターの下のY座標
	if (Mtype[i] == FALL_DOSSUN) {
		if (stage[x1][y] == BRICK) {
			stage[x1][y] = EMPTY;
		}
		//ドッスンの左下にレンガブロックがあるとき	

		if (stage[x2][y] == BRICK) {
			stage[x2][y] = EMPTY;
		}
		//ドッスンの右下にレンガブロックがあるとき

		//ドッスンの下に、コインでないブロックがないとき
		if ((stage[x1][y] == EMPTY || stage[x1][y] == COINBLOCK) && (stage[x2][y] == EMPTY || stage[x2][y] == COINBLOCK)) {
			monY[i] += 5;//下に落ちる
		}
		else {//ドッスンの下がコインでないブロックの時
			Mtype[i] = STOP_DOSSUN;//ドッスンが、上に上がるようになる
		}
	}
}


//砲台がモンスターを出現させる
//　　　　　　　　　　　（処理しているモンスターの番号、モンスターの総数砲台の向き）
void MosterAppearByHodai(int i, int &num, int hodaiDirection) {
	int last = 0;//出現できるかどうか
	int kora = 1;//甲羅を出現させるときの向き
	for (int h = 0; h <= num; h++) {
		if (abs(monX[i] + 30 * hodaiDirection - monX[h]) < 25 && abs(monY[i] - 5 - monY[h]) < 25) {//砲台の隣にモンスターがいるとき
			last = 1;
			break;
		}
	}
	if (last == 0) {//砲台から出現させるときのデータの処理
		int AppearType;
		if (Mtype[i] % 100 < ITEM) {//アイテムを出現させるとき
			AppearType = Mtype[i] % 100 * -1;
		}
		else {//モンスターを出現させるとき
			AppearType = Mtype[i] % 100 - ITEM;
			if (AppearType == 4)kora = -1;//甲羅なら。向きが変わる
		}
		MonsterAppear(num, AppearType, monX[i] + 30 * hodaiDirection, monY[i] - 5, hodaiDirection * kora);//モンスターを出現させる
	}
}


//砲台がモンスターを出現させる時間など
//　　　　　　　（処理しているモンスターの番号、マリオの幅、マリオの座標、マリオの追加のY座標、マリオが移動しているかどうか、モンスターの総数スクロール数）
void HodaiCreate(int i, int MariowideX, int MariowideY, int marioX, int marioY, int superplus, int &move, int &num ,int stmove) {
	if (Mtype[i] >= 100) {
		monTime[i] ++;//時間の分増やしていく
		if (monTime[i] % 50 == 0 && monX[i] - stmove < 600) {//モンスターを出現させるタイミングになり、砲台が画面上にあるとき
			int x1 = (monX[i] + 40) / 30;//砲台の右のほうの座標
			int x2 = (monX[i] - 10) / 30;//砲台の左のほうの座標
			int y1 = 20 - (monY[i] + 1) / 30;//砲台の上の座標
			int y2 = 20 - (monY[i] + 25 - 1) / 30;//砲台の下の座標

			if (marioX > monX[i] + 30 && stage[x1][y1] == EMPTY && stage[x1][y2] == EMPTY) {//隣にブロックがなく、左側にマリオがいるとき
				MosterAppearByHodai(i, num, 1);//モンスターの出現
			}
			else if (marioX + MariowideX < monX[i] && stage[x2][y1] == EMPTY && stage[x2][y2] == EMPTY) {//隣にブロックがなく、右にマリオがいるとき
				MosterAppearByHodai(i, num, -1);//モンスターの出現
			}
		}
	}
}


//移動している甲羅にブロックが当たった時
//　　　　　　　　（スコア、コイン数、マリオの残基、モンスターの総数処理しているモンスターの番号、モンスターの座標、マリオの向き）
void KoraTouchBlock(long &score, int &coin, int &mario, int &num, int i, int x, int y, int marioDirection) {
	if (Mtype[i] == MOVE_KORA && stage[x][y] > EMPTY) {
		if (stage[x][y] == BRICK) {//レンガに当たった時、破壊する
			stage[x][y] = EMPTY;
		}
		else if (stage[x][y] >= HATENA && stage[x][y] < DOKANUP_MOVE) {//？ブロックに当たった時、？ブロックから中身を出現させる
			int AppearType;
			if ((stage[x][y] - HATENA) < ITEM) {//アイテムを出すとき
				AppearType = (stage[x][y] - HATENA) * -1;
			}
			else {//モンスターを出すとき
				AppearType = (stage[x][y] - HATENA) - ITEM;
			}
			MonsterAppear(num, AppearType, x * 30, (20 - y - 1) * 30, marioDirection);//モンスターを出現させる
			stage[x][y] = HATENA_KNOCKED;

		}
		else if (stage[x][y] == COINBLOCK) {//甲羅がコインに当たった時、回収する
			stage[x][y] = EMPTY;
			score += 100;
			coin++;
			if (coin == 100)coin = 0, mario++;
		}

	}
}



//モンスターがブロックに当たった時
//　　　　　　　　　　（処理しているモンスターの番号、スコア、コイン数、マリオの残基、モンスターの幅、モンスターの総数）
void MonsterTouchBlock(int i, long &score, int &coin, int &mario, int &monWide, int &num) {
	if (monMove[i] > 0)monWide = 24; else monWide = 0;//モンスターが右に動いているとき、モンスターの幅を考慮する
	int x = (monX[i] + monWide + monMove[i]) / 30;//モンスターが移動する先のX座標
	int y1 = 20 - monY[i] / 30;//モンスターの上のY座標
	int y2 = 20 - (monY[i] + 25 - 1) / 30;//モンスターの下のY座標

	if (stage[x][y1] > EMPTY) {//上側がブロックに当たった時
		if (stage[x][y1] != COINBLOCK && Mtype[i] != KILLER)monMove[i] *= -1, monSide[i] *= -1;//向きを反転する
	}
	else if (stage[x][y2] > EMPTY) {//下側がブロックに当たった時
		if (stage[x][y2] != COINBLOCK && Mtype[i] != KILLER)monMove[i] *= -1, monSide[i] *= -1;//向きを反転する
	}

	KoraTouchBlock(score, coin, mario, num, i, x, y1, 1);//甲羅の上の部分がブロックに当たった時

	KoraTouchBlock(score, coin, mario, num, i, x, y2, -1);//甲羅の下の部分がブロックに当たった時

}


//モンスターがほかのモンスターに当たった時
//　　　　　　　　　　　　（処理しているモンスターの番号、モンスターの総数スコア、モンスターが止まっているかどうか）
int MonterTouchOtherMonster(int i, int num, long &score, int &monstop) {
	int touch = 0;
	for (int h = 0; h <= num; h++) {
		if (monEnd[h] == 1)continue;//当たられた側が死んでいた時、戻る
		if (i != h&&monY[i] + 24 >= monY[h] && monY[i] <= monY[h] + 24 &&
			monX[i] + 25 + monMove[i] >= monX[h] && monX[i] + monMove[i] <= monX[h] + 25) {//モンスターがほかのモンスターに当たった時
			if (Mtype[i] != MOVE_KORA && Mtype[i] != KILLER && Mtype[h] != KILLER) {//当たる側が甲羅、キラー、当たる側がキラーでないとき
				touch = 1;
				monMove[i] *= -1;//向きを反転する
				monSide[i] *= -1;
				monstop++;
			}
			else if (Mtype[i] == 4) {//当たる側が甲羅の時
				if (Mtype[h] == STOP_KORA || Mtype[h] == MOVE_KORA) {//甲羅が甲羅に当たってどっちも消える
					monEnd[i] = 1;
					monEnd[h] = 1;
					score += 100;
				}
				else if (Mtype[h] >= KURIBO  && Mtype[h] <= PAKKUN || Mtype[h] == KILLER) {//甲羅に当たられたモンスターは消える
					monEnd[h] = 1;
					score += 100;
				}
				else if (Mtype[h] > HODAI) {//砲台に当たった時は甲羅は向きを変える
					monMove[i] *= -1;
					monSide[i] *= -1;
				}
				//そうでないときは、甲羅はモンスターを通過する
			}
		}
	}
	return 0;
}

//砲台に当たった時、向きを変える
int MonsterTouchHodai(int i,int num) {
	for (int h = 0; h <= num; h++) {
		if (Mtype[h] >= HODAI && abs(monX[i] - monX[h]) < 25 && abs(monY[i] - monY[h]) < 25) {//砲台に当たった時
			monMove[i] *= -1;//向きを変える
			monSide[i] *= -1;//向きを変える
			monX[i] += monSide[i];//砲台に触れていないようにずらす
			return 1;
		}
	}
	return 0;
}

//モンスターが動くとき
//　　　　　　　（処理しているモンスターの番号、モンスターの幅、モンスターが止まっているかどうか、時間が止まっているかどうか,モンスターの総数、
//              マリオが落ちたことがあるかどうか）
void MonsterMove(int i, int &monWide, int monstop, int stop,int num,int fall) {
	int x1;//モンスターの移動先のX座標
	int x2;
	int y1 = 20 - (monY[i] + 1) / 30;//モンスターの上側のY座標
	int y2 = 20 - (monY[i] + 25 - 1) / 30;//モンスターの下側のY座標

	

	//普通のモンスターが移動するときで、移動先にブロックがないとき
	if (monstop <= 1 && (stop == 0 || Mtype[i] <= SUPER_KINOKO)) {
		for (int h = 1; h <= abs(monMove[i]); h++) {
			if (monSide[i] > 0)monWide = 24; else monWide = 0;//モンスターが右に動いているとき、モンスターの幅を考慮する
			x1 = (monX[i] + monWide + monSide[i]) / 30;//モンスターの移動先のX座標

			if(fall == 0)MonsterFall(i, stop, num);//まだ落ちたことがないとき、モンスターが下に落ちるかどうかを判断

			if (Mtype[i] != KILLER && Mtype[i] != MOVE_TERESA && Mtype[i] != STOP_TERESA &&//動くモンスターで、ブロックに当たらず動けるとき
				(stage[x1][y1] == EMPTY || stage[x1][y1] == COINBLOCK) && (stage[x1][y2] == EMPTY || stage[x1][y2] == COINBLOCK)) {

				if (MonsterTouchHodai(i, num) == 0) {//砲台に当たらなかったとき
					monX[i] += monSide[i];//動く
				}
			}
			else break;
		}
	}
}

//甲羅が消えるとき
//                (処理しているモンスターの番号、スクロール数)
void KoraDisappear(int i, int stmove) {
	if (Mtype[i] == MOVE_KORA && (monX[i] - stmove < -100 || monX[i] - stmove > 660)) {//甲羅が、画面外に出たとき
		//消える
		monEnd[i] = 1;
		monMove[i] = 0;
	}
}

//マリオがアイテムを獲得したとき
//              (処理しているモンスターの番号、コイン数、マリオの残基、マリオの座標、マリオの追加のY座標、マリオの横の幅、スコア)
void MarioLevelUp(int i, int &coin, int &mario, int &marioLV, int &marioX,int &marioY, int &superplus, int &MariowideX, long &score) {
	if (monEnd[i] == 0) {//アイテムが消えてないとき
		if (Mtype[i] == COIN) {//コインを獲得したとき
			monEnd[i] = 1;//コインを消し
			score += 100;
			coin++;//コインを増やす
			if (coin == 100)mario++, coin = 0;
		}
		else if (Mtype[i] == SUPER_KINOKO) {//スーパーキノコを獲得したとき
			monEnd[i] = 1;//スーパーキノコを消し、
			score += 1000;
			if (marioLV == 1) {
				marioLV = 2;//マリオをスーパーマリオにする
				marioY -= 20;
				superplus = 15;
				MariowideX = 25;
				marioX -= 10;
			}
		}
		else if (Mtype[i] == ONE_UP_KINOKO) {//ワンナップキノコを獲得したとき
			monEnd[i] = 1;
			score += 1000;
			if (mario < 100)mario++;//マリオの残基を一つ増やす
		}
		else if (Mtype[i] == FIREFLOWER) {//ファイヤーフラワーを獲得したとき
			monEnd[i] = 1;
			score += 1000;
			if (marioLV == 1) {//ちびマリオなら大きさを変更する
				marioY -= 20;
				superplus = 15;
				MariowideX = 25;
				marioX -= 10;
			}
			marioLV = 3;
		}
	}
}

//モンスターがマリオに当たった時
//(処理しているモンスターの番号、マリオの座標、マリオの追加のY座標、マリオのダメージ、コイン数、マリオの状態、マリオの横幅、スコア)
void MonsterTouchMario(int i,int &marioX,int &marioY,int &superplus,int &end,int &coin,int &mario,int &marioLV,int &MariowideX,long &score) {
	if (Mtype[i] < HODAI && marioY + superplus + 5 >= monY[i] && marioY + superplus <= monY[i] + 25 &&
		marioX + 19 >= monX[i] && marioX <= monX[i] + 18) {

		MarioLevelUp(i, coin, mario, marioLV, marioX,marioY, superplus, MariowideX,score);//マリオがアイテムを獲得したとき

		if (Mtype[i] == STOP_KORA) {//動いていない甲羅が当たった時
			Mtype[i] = MOVE_KORA;//動くようにする

			//向きを決める
			if ((marioX + 19) / 5 == monX[i] / 5) {//右向き
				monMove[i] = 10;
				monSide[i] = 1;
			}
			else if(marioX / 5 == (monX[i]+ 18) / 5){//左向き
				monMove[i] = -10;
				monSide[i] = -1;
			}
		}
		else if (Mtype[i] >= KURIBO && Mtype[i] < HODAI) {//マリオがその他のモンスターに当たったなら、マリオはダメージを受ける
			end = 1;
		}

	}
}

//マリオがモンスターを踏んだ時
//　（スコア、マリオのジャンプの速さ、マリオの重力加速度、重力加速度の上限、ジャンプしているかどうか、
//   マリオのダメージ、マリオの座標、マリオの横の幅、コイン数、マリオの残基数、マリオの追加のY座標、マリオの状態、
//  今処理しているモンスターの番号、マリオの向き）

int  MarioStampMonster(long &score, double nuton, double nutonLV, double nutonmax, int & jumping, int &jump, int &end, int &marioX, 
	int &marioY, int &MariowideX, int &coin,int &mario, int &superplus, int &marioLV, int i, int marioDirection) {
	if (((marioY + superplus + 20) / 5 == monY[i] / 5) &&
		marioX + 23 >= monX[i] + 5 - monX[i] % 5 && marioX <= monX[i] + 5 - monX[i] % 5 + 18) {
		jumping = 0;
		if (Mtype[i] >= TOGEZO && Mtype[i] <= STOP_TERESA && Mtype[i] != KILLER) {//踏むとダメージを受けるモンスターを踏んだ時
			end = 1;
		}
		if ((Mtype[i] >= KURIBO && Mtype[i] <= MOVE_KORA) || Mtype[i] == KILLER) {//踏むとジャンプできるモンスターを踏んだ時
			jump = 1;
			jumping = 1;
		}
		if (Mtype[i] == KURIBO || Mtype[i] == KILLER) {//クリボーかキラーを踏んだ時
			monEnd[i] = 1;//モンスターが消える
			score += 100;
		}
		else if (Mtype[i] == MOVE_KORA) {//動く甲羅を踏んだ時
			Mtype[i] = STOP_KORA;//甲羅が動かなくなる
			monMove[i] = 0;
			score += 100;
		}
		else if (Mtype[i] == 3) {//止まってる甲羅を踏んだ時
			Mtype[i] = MOVE_KORA;//甲羅が動くようになる
			if (marioX + MariowideX <= monX[i] + 25) {
				monSide[i] = 1;
			}
			else monSide[i] = -1;
			monMove[i] = 10 * monSide[i];
		}
		else if (Mtype[i] == NOKONOKO) {//ノコノコを踏んだ時
			Mtype[i] = STOP_KORA;//甲羅になる
			crol[i] = 10;
			monMove[i] = 0;
			score += 100;
		}
		MarioLevelUp(i, coin, mario, marioLV, marioX,marioY, superplus, MariowideX, score);//マリオがアイテムを獲得したとき

		return jumping;
	}
	else {
		return 0;
	}
}

//テレサがテレサに当たった時
//　　　　　　　　（今処理しているモンスターの番号、モンスターの総数、テレサの座標）
int TeresaTouchTeresa(int i, int &num,int x1,int x2,int y1 ,int y2) {
	for (int h = 0; h <= num; h++) {
		if (monEnd[h] == 1)continue;
		if (i != h &&  y2 >= monY[h] && y1 <= monY[h] + 25 &&
			x2  >= monX[h] && x1 <= monX[h] + 25)  {//テレサがモンスターに当たっているとき
			if (Mtype[h] == MOVE_TERESA) {//テレサが当たっているのがテレサの時
				return 1;
			}
		}
	}
	return 0;
}

//テレサが横に動く
//           (今処理しているモンスターの番号、マリオのX座標、マリオの向き、モンスターの総数、テレサの座標、テレサが移動するかどうか)
void TeresaMoveX(int i,int marioX,int marioDirection,int num,int &x1,int &x2,int y1,int y2,int &moveX) {
	if (monX[i] > marioX) {//マリオがテレサより左にいるとき
		x1 -= 2;//調べるX座標を移動先にする
	}
	else if (monX[i] < marioX) {//マリオがテレサより右にいるとき
		x2 += 2;//調べるX座標を移動先にする
	}
	if (TeresaTouchTeresa(i, num, x1, x2, y1, y2) == 0) {//テレサがテレサに当たってないとき
		moveX = 1;//横に動くことができる
	}
	else {//テレサがテレサに当たっていたら、X座標を元に戻す
		x1 = monX[i];
		x2 = monX[i] + 25;
	}
	if (moveX == 1) {//テレサが移動できるとき
		if (monX[i] > marioX) {//マリオがテレサより左にいるとき
			monSide[i] = -1;
			monX[i] -= 2;//テレサを左に移動させる
		}
		else if (monX[i] < marioX) {//マリオがテレサより右にいるとき
			monSide[i] = 1;
			monX[i] += 2;//テレサを右に移動させる
		}
		else monSide[i] = marioDirection;//テレサとマリオのX座標が同じくらいの時、テレサとマリオの向きを同じにする
	}
	else {
		monSide[i] = marioDirection;//マリオと同じ向きを向く

	}
}


//テレサが縦に移動する
//            (今処理しているモンスターの番号、マリオのY座標、マリオの向き、モンスターの総数、テレサの座標、テレサが移動できるかどうか)
void TeresaMoveY(int i, int marioY, int marioDirection, int num, int x1, int x2, int &y1, int &y2, int &moveY) {
	if (monY[i] > marioY) {//マリオがテレサより上にいるとき
		y1--;//テレサのY座標を移動先にする
	}
	else if (monY[i] < marioY) {//マリオがテレサより下にいるとき
		y2++;//テレサのY座標を移動先にする
	}
	if (TeresaTouchTeresa(i, num, x1, x2, y1, y2) == 0) {//テレサがテレサに当たってないとき
		moveY = 1;//縦に動くことができる
	}
	else {//テレサがテレサに当たっていた時
		//テレサのY座標を元に戻す
		y1 = monY[i];
		y2 = monY[i] + 25;
	}

	if (moveY == 1) {//もしテレサが移動できるとき
		if (monY[i] > marioY) {//マリオがテレサより上にいるとき
			monY[i] --;//テレサを上に移動させる
		}
		else if (monY[i] < marioY) {//マリオがテレサより下にいるとき
			monY[i] ++;//テレサを下に移動させる
		}
	}
}


//テレサが動く
//                (今処理しているモンスターの番号、マリオの座標、マリオの向き、モンスターの総数、スコア、モンスターが止まっているかどうか)
void TeresaMoveToMario(int i, int marioX, int marioY, int marioDirection,int &num,long&score,int &monstop) {
	//テレサ
	if (Mtype[i] == MOVE_TERESA) {
		int x1 = monX[i];
		int x2 = monX[i] + 25;
		int y1 = monY[i];
		int y2 = monY[i] + 25;
		int moveX = 0;
		int moveY = 0;
		
		TeresaMoveX(i, marioX, marioDirection, num, x1, x2, y1, y2, moveX);//横に動く

		TeresaMoveY(i, marioY, marioDirection, num, x1, x2, y1, y2, moveY);//縦に動く
		
	}
}


//テレサが、動くか照れている状態になるか
//　　　　　　　　　（今処理しているモンスターの番号、マリオの向き、マリオのX座標）
void TeresaTypeChange(int i, int marioDirection, int marioX) {
	if (Mtype[i] == MOVE_TERESA) {//普通に動けるとき
		if ((marioDirection == 1 && monX[i] >= marioX) || (marioDirection == -1 && monX[i] < marioX)) {//マリオがテレサのほうを向いたとき
			Mtype[i] = STOP_TERESA;//照れる
		}
	}
	if (Mtype[i] == STOP_TERESA) {//テレサが照れているとき
		if (monX[i] > marioX) {//マリオがテレサより左にいるとき
			monSide[i] = -1;//左を向く
		}
		else if (monX[i] < marioX) {//マリオがテレサより右にいるとき
			monSide[i] = 1;//右を向く
		}
		else monSide[i] = 1;
		if ((marioDirection == 1 && monX[i] <= marioX) || (marioDirection == -1 && monX[i] > marioX)) {//マリオがテレサのほうを向いてないとき
			Mtype[i] = 10;//テレサが不通に動けるようになる
		}
	}
}

//テレサについてのこと
//　　　　　　　（今処理しているモンスターの番号、マリオの座標、マリオの向き、マリオの総数、スコア、モンスターが止まっているかどうか）
void AboutTeresa(int i, int marioX, int marioY, int marioDirection, int &num, long&score, int &monstop) {
	TeresaMoveToMario(i, marioX, marioY, marioDirection,num, score, monstop);//テレサが、マリオのほうへ動く

	TeresaTypeChange(i, marioDirection, marioX);//テレサが、動くか照れている状態になるか
}



//モンスターについての全部の処理
void MonsterDataSet(int &jumping, int &num, int &marioLV, int &end, int &bullet, int &stmove, int &coin, int &mario, int &jump, int &last, int &marioX,
	int &marioY, int &monstop, int &monWide, int &move, double &nuton, double &nutonLV,
	double &nutonmax, long &score, int &marioDirection, int &stop, int &superplus, int &MariowideX,int dying,int MariowideY) {

	int fall;//落ちたかどうか、落ちてたなら、移動中には落ちない

	for (int i = 0; i <= num; i++) {//敵の処理  敵の処理　　　　　敵の処理　　　敵の処理
		if (dying == 1)break;
		if (MonsterDelete(i, num) == 1) {
			continue;
		}
		//死んだモンスターのデータを消去する処理

		fall = 0;//落ちたかどうか、落ちてたなら、移動中には落ちない

		BulletAttackMonster(i, bullet,stmove);//弾がモンスターに当たったかどうかを見る処理

		for (int g = 0; g<5; g++) {//５の分だけ落ちる
			if (MonsterFall(i, stop, num) == 1) {//モンスターが落ちる処理
				fall = 1;//落ちたとき、落ちたと設定する
			}
			else break;//落ちなかったとき、やめる
		}
		


		//モンスターが画面外(右側を除く)に出たとき、消える
		if (monX[i] + 25 - stmove < 0) {
			monEnd[i] = 1;
		}
		if (monY[i] >= 500)monEnd[i] = 1;


		KillerGo(i);//キラーが動く

		SpineChange(i, marioX, marioY,MariowideY);//とげが、上にマリオがいれば上に上がるように変わる

		SpineUp(i, MariowideX, marioX, marioY, superplus, end);//とげが上に上がる

		DossunUpOrChange(i, marioX, marioY,num);//ドッスンが上がるか、下にマリオがいれば下に落ちてくるように変わる

		DossunFall(i,num);//ドッスンが落ちてくる

		HodaiCreate(i, MariowideX, MariowideX, marioX, marioY, superplus, move, num, stmove);//砲台がモンスターを出す

		MonsterTouchBlock(i, score, coin, mario, monWide, num);//モンスターが障害物に当たった時

		monstop = 0;//モンスターが動ける

		MonterTouchOtherMonster(i, num, score, monstop);//敵が、違う敵に触れたとき


		MonsterMove(i, monWide, monstop, stop,num,fall);//モンスターを動かす


		KoraDisappear(i, stmove);//甲羅が、行き過ぎちゃったときに消す

		MonsterTouchMario(i, marioX, marioY, superplus, end, coin, mario, marioLV, MariowideX,score);//モンスターがマリオに当たった時


		MarioStampMonster(score, nuton, nutonLV, nutonmax, jumping, jump, end, marioX, marioY, MariowideX, coin, mario, superplus, marioLV, 
			i, marioDirection);//マリオがモンスターを踏んだ時

		AboutTeresa(i, marioX, marioY, marioDirection, num, score, monstop);//テレサについての処理
	}
	//敵の処理終わり
}
//ここまで敵の処理








//マリオの右側に障害物がなく進むとき
//　　　　　　　　　　　（動けるかどうか、スクロールするかどうか、マリオのX座標、マリオの追加のY座標）
void MarioRightMoveSafely(int move, int moving, int &marioX, int &stmove) {

	if (move != 1) {
		marioX += 5;//右に進む
	}
	if (marioX <= 2590 && marioX - stmove >= 300) {//マリオが画面の端のほうでないとき
		if (moving == 1) {
			if (move != 1)stmove += 5;//スクロールする
		}
	}
}

//マリオの右側にブロックがあるかどうか
//　　　　　　　　　　　　　　（マリオの座標、マリオの幅、マリオの追加のY座標）
int  MarioRightMoveStopByBlock(int marioX, int marioY, int MariowideX, int MariowideY, int superplus) {
	int x = (marioX + MariowideX + 1) / 30;//マリオの右側のX座標
	int y;//マリオのY座標
	int last = 0;//動けるかどうか
	for (int i = marioY + 1; i <= marioY + MariowideY + superplus - 1; i++) {
		y = 20 - i / 30;
		if (stage[x][y] > EMPTY && stage[x][y] != HALFFLAG1 && stage[x][y] != HALFFLAG2) {//マリオの横に中間の旗でない障害物があるとき
			last = 1;//動けない
			break;
		}
	}//マリオの右側に障害物があるかどうか
	return last;
}


//マリオの右側に砲台があるかどうか
//                           (モンスターの総数、マリオの座標、マリオの横の幅、マリオの追加のY座標)
int MarioRightMoveStopByHodai(int num, int marioX, int marioY, int MariowideX, int superplus) {
	for (int i = 0; i <= num; i++) {
		if (Mtype[i] >= 100) {//砲台の時

			//マリオの右側がおおよそ砲台に触れているとき
			if ((marioX + MariowideX) / 5 == monX[i] / 5 && marioY - 1 <= monY[i] + 25 && marioY + MariowideX + superplus + 1 >= monY[i]) {
				return 1;//動けない
			}
		}

	}//モンスター全部の呼び出し

	return 0;
}


//マリオが右に動けるかどうか
//           (スコア、スクロール数、マリオの残基、コイン数、マリオの座標、マリオの幅、マリオの追加のY座標、　動けるかどうか、
//   　　　　スクロールするかどうか、モンスターの総数、今の場所、旗をとったかどうか、旗の場所、旗の座標、マリオの状態)
void MarioRightMoveStop(long &score, int &stmove, int &mario, int &coin, int &marioX, int &marioY, int &MariowideX, int MariowideY, int &superplus,
	int move, int moving, int num,int dpla,int &flag,int &flagStage,int &flagX,int &flagY,int &marioLV) {

	
	CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);//コインを獲得する
	FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY,marioLV);//中間の旗を獲得する

	if (MarioRightMoveStopByBlock(marioX, marioY, MariowideX, MariowideY, superplus) == 0 &&
		MarioRightMoveStopByHodai(num, marioX, marioY, MariowideX, superplus) == 0) {//動けるとき

		MarioRightMoveSafely(move, moving, marioX, stmove);//右に動く
	}

}

//右に動く動作のまとめ
void MarioRightMove(long &score, int &mario, int &coin, int &marioX, int &marioY, int &move,
	int clear, int &marioLV, int end, int &marioDirection, int &MariowideX, int MariowideY, int &superplus, int &stmove, int moving, int jump, int speed, 
	int num, int dying, int dokanchange,int dpla, int &flag,int &flagStage, int &flagX, int &flagY) {

	if (dokanchange == 0 && clear == 0 && dying == 0 && Key[KEY_INPUT_RIGHT] >= 1) {//右ボタンを押したとき
		marioDirection = 1;
		for (int h = 0; h < speed; h++) {//速さの分だけ進む

			MarioRightMoveStop(score, stmove, mario, coin, marioX, marioY, MariowideX, MariowideY, superplus, move, moving, num ,dpla, flag,flagStage, 
				flagX, flagY,marioLV);//右に進めるかどうか

		}//速さの分の繰り返し
		move = 1;
	}//右ボタンを入力したかどうか
}

//右へ進む動作




//左に、障害物がなく進むとき
//　　　　　　　　　　（マリオのX座標、スクロール数、動けるかどうか）
void MarioLeftMoveSafely(int &marioX, int stmove, int move) {
	if (marioX >= 5 + stmove) {
		if (move != -1) {
			marioX -= 5;//左に進む
		}
	}
}
//マリオに左にブロックがあるかどうか
//　　　　　　　　　　　　（マリオの座標、マリオの幅、マリオの追加のY座標）
int  MarioLeftMoveStopByBlock(int marioX, int marioY, int MariowideX, int MariowideY, int superplus) {
	int x = (marioX - 1) / 30;//マリオの左側のX座標
	int y;//マリオのY座標
	int last = 0;//障害物に触れたかどうか
	for (int i = marioY + 1; i <= marioY + MariowideY + superplus - 1; i++) {
		y = 20 - i / 30;
		if (stage[x][y] > EMPTY && stage[x][y] != HALFFLAG1 && stage[x][y] != HALFFLAG2) {//マリオの左側に中間の旗以外の障害物があるかどうか
			last = 1;
			break;
		}
	}
	return last;
}


//マリオの左側に砲台があるかどうか
//                       (モンスターの総数、マリオの座標、マリオの横の幅、マリオの追加のY座標)
int MarioLeftMoveStopByHodai(int num, int marioX, int marioY, int MariowideX, int superplus) {
	for (int i = 0; i <= num; i++) {
		if (Mtype[i] >= 100) {//砲台のとき

			//マリオの左側がおおよそ砲台に触れているとき
			if ((marioX - 1)/ 5 == (monX[i] + 25) / 5 && marioY - 1 <= monY[i] + 25 && marioY + MariowideX + superplus + 1 >= monY[i]) {
				return 1;
			}
		}

	}//モンスター全部の呼び出し

	return 0;
}


//マリオが左に動けるかどうか
//　　　　　（スクロール数、移動できるかどうか、マリオの座標、マリオの幅、マリオの追加のY座標、モンスターの総数、コイン数、
//　　　　　　マリオの残基、今のステージの場所、中間の旗をとったかどうか、中間の旗の座標、マリオの状態）
void MarioLeftMoveStop( int &stmove, int &move, int &marioX,int &marioY, int &MariowideX, int MariowideY, int &superplus, int num,int &coin,
	int &mario,int &dpla,int &flag,int &flagStage,int &flagX,int &flagY,int &marioLV) {
	
	CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);//コインを獲得する
	FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY, marioLV);//中間の旗を獲得する

	if (MarioLeftMoveStopByBlock(marioX, marioY, MariowideX, MariowideY, superplus) == 0 &&
		MarioLeftMoveStopByHodai(num, marioX, marioY, MariowideX, superplus) == 0) {//左に動けるとき

		MarioLeftMoveSafely(marioX, stmove, move);//左に動く
	}
}

//マリオが左に動く動作のまとめ
void MarioLeftMove(long &score, int &mario, int &coin, int &marioX, int &marioY, int &move, int clear, int &marioLV, int end,int &marioDirection,
	int &MariowideX, int MariowideY, int &superplus, int stmove, int moving, int jump, int speed, int num, int dying, int dokanchange,  int &dpla,
	int &flag, int &flagStage, int &flagX,int &flagY) {
	if (dokanchange == 0 && clear == 0 && dying == 0 && Key[KEY_INPUT_LEFT] >= 1) {//左ボタンが押されたとき
		marioDirection = -1;
		for (int h = 0; h < speed; h++) {
			MarioLeftMoveStop( stmove, move,marioX, marioY, MariowideX, MariowideY, superplus, num, coin, mario, dpla, flag, flagStage, flagX,flagY, 
				marioLV);//左に動ければ動く

		}//速さの分の繰り返し
		move = -1;
	}//左キーが押されたかどうか
}


//右に動く動作と左に動く動作のまとめ
void LeftAndRightMove(long &score, int &mario, int &coin, int &marioX, int &marioY, int &move,
	int clear, int &marioLV, int end, int &marioDirection, int &MariowideX, int MariowideY, int &superplus, int &stmove, int moving, int jump, int num, 
	int dying, int dokanchange, int dpla, int &flag,int &flagStage, int &flagX, int &flagY) {

	//ジャンプ中でないときに左シフトキーを押すと、マリオが早くなる
	int speed;//移動する速さ
	if (jump == 0 && Key[KEY_INPUT_LSHIFT] >= 1) {
		speed = 2;
	}
	else {
		speed = 1;
	}

	
	MarioRightMove(score, mario, coin, marioX, marioY, move, clear, marioLV, end, marioDirection, MariowideX, MariowideY, superplus, stmove, moving, jump, speed, num,
		dying, dokanchange, dpla, flag,flagStage, flagX, flagY);//右に移動する

	MarioLeftMove(score, mario, coin, marioX, marioY, move, clear, marioLV, end, marioDirection, MariowideX, MariowideY, superplus, stmove, moving, jump, speed, num, 
		dying, dokanchange, dpla, flag, flagStage,flagX, flagY);//左に移動する
}
//左右の移動の終わり


//マリオが砲台に立っているかどうか
//　　　　　　　　　（モンスターの総数、マリオの座標、マリオの幅、マリオの追加のY座標）
int  MarioTouchToHodai(int num, int marioX, int marioY, int MariowideX, int MariowideY, int superplus) {
	for (int i = 0; i <= num; i++) {
		if (Mtype[i] >= 100) {
			if (marioX - 1 <= monX[i] + 25 && marioX + MariowideX - 1 >= monX[i]) {//マリオと砲台のX座標が触れているとき
				if (marioY - 1 <= monY[i] + 25 && marioY + MariowideY + superplus - 1 >= monY[i]) {//マリオと砲台のY座標が触れているとき
					return 1;//マリオは砲台に立ってている
				}
			}
		}
	}
	return 0;//マリオは砲台に立っていない
}


//マリオが地面に立っているかどうか
//　　　　　　　　（マリオの座標、マリオの幅、マリオの追加のY座標）
int MarioTouchFloor(int marioX, int marioY, int MariowideX, int MariowideY, int superplus) {
	int x1 = (marioX + 1) / 30;//マリオの左のX座標
	int x2 = (marioX + MariowideX - 5) / 30;//マリオの右のX座標
	int y = 20 - (marioY + MariowideY + superplus) / 30;//マリオの下側のY座標

	if ((stage[x1][y] == EMPTY || stage[x1][y] == HALFFLAG2) && (stage[x2][y] == EMPTY || stage[x2][y] == HALFFLAG2)) {//マリオが中間の旗でない地面に立っていないとき
		return 0;
	}
	else {//立っているとき
		return 1;
	}
}

//マリオが落ちるとき
//　　　　（土管で移動するかどうか、ジャンプしているかどうか、マリオの追加のY座標、マリオの幅、クリアしたかどうか、マリオの状態、マリオのダメージ、
//　　　　マリオの座標、マリオの残基、コイン数、スコア、）
void MarioFall(int dokanchange, int &jump, int num, int &superplus, int &MariowideX, int MariowideY, int clear, int &marioLV, int &end, int &marioX, int &marioY, 
	int &mario,int &coin, long &score, double & nuton, double & nutonmax, double &nutonLV, int &jumping, int marioDirection, int dpla, int &flag, int &flagStage,
	int &flagX, int &flagY) {


	if (clear == 0 && !(marioLV == 1 && end == 1) && jump == 0 && dokanchange == 0) {
		int last = 0;
		for (int i = 0; i < 15; i++) {

			CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);//コインを獲得する
			FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY,marioLV);//中間の旗を獲得する

			for (int h = 0; h <= num; h++) {
				if (MarioStampMonster(score, nuton, nutonLV, nutonmax, jumping, jump, end, 
					marioX, marioY, MariowideX, coin, mario, superplus, marioLV, h,marioDirection) == 1) {//マリオがモンスターを踏んだ時
					last = 1;
					break;//マリオは落ちない
				}
			}
			if (last == 1)break;
			if (MarioTouchFloor(marioX, marioY, MariowideX, MariowideY, superplus) == 0) {//マリオが床にいなくて、
				if (MarioTouchToHodai(num, marioX, marioY, MariowideX, MariowideY, superplus) == 0) {//マリオが砲台の上にもいないとき、
					marioY++;//マリオは落ちる
				}
			}

		}
	}
}

//マリオがジャンプするときの、データをセットする
//                    (ジャンプの上下する速さ、重力加速度、重力加速度の上限、ジャンプしているかどうか、モンスターによってジャンプするかどうか、
//　　　　　　　　　　　マリオのY座標、ジャンプの速さや高さの調整)
void MarioJumpStartDataSet(double &nuton, double &nutonLV, double &nutonmax, int &jump, int &jumping, int &marioY, double control) {
	jump = 1;
	nuton = 0;
	nutonLV = 1.5;
	nutonmax = 19 + control;
	marioY -= 3;
}

//マリオが、モンスターを踏むことでジャンプするとき
//         (スコア、ジャンプの上下する速さ、重力加速度、重力加速度の上限、モンスターによってジャンプしているかどうか、ジャンプしているかどうか、
//       マリオのダメージ、マリオの座標、マリオの横の幅、コイン数、マリオの残基、マリオの追加のY座標、マリオの状態、モンスターの総数、マリオの向き)
int MarioJumpStartOnMonster(long &score, double &nuton, double &nutonLV, double &nutonmax, int &jumping, int &jump, int &end, int &marioX,
	int &marioY, int &MariowideX, int &coin, int &mario,int &superplus, int &marioLV, int num, int marioDirection) {
	int last = 0;
	for (int i = 0; i <= num; i++) {//モンスター全部を呼び出す

		//マリオがモンスターを踏んだ時
		if (MarioStampMonster(score,nuton,nutonLV,nutonmax,jumping,jump,end,marioX,marioY,MariowideX,coin,mario,superplus,marioLV,i,marioDirection) == 1) {
			last = 1;//ジャンプする
			break;
		}
	}
	return last;
}


//マリオがジャンプを始める
//           (スコア、コイン数、マリオの残基、モンスターによってジャンプしたとき、ジャンプしているかどうか、ジャンプの上下の速さ、重力過速度の上限、
//　　　　　重力加速度、マリオの状態、マリオの座標、マリオの幅、マリオの追加のY座標、モンスターの総数、マリオの向き、ステージの場所、
//　　　　　中間の旗をとったかどうか、中間の旗の場所、中間の旗の座標、マリオが死んでいるかどうか)
void MarioJumpStart(long &score, int &coin, int &mario, int &jumping, int &jump, double &nuton, double &nutonmax, double &nutonLV, int &clear,
	int &marioLV,int end, int &marioX,int &marioY,  int &MariowideX, int MariowideY, int &superplus, int num, int marioDirection, int dpla, int &flag, 
	int &flagStage, int &flagX, int &flagY,int dying) {

	int x1 = (marioX + 1) / 30;//マリオの左のX座標
	int x2 = (marioX + MariowideX - 1) / 30;//マリオの右のX座標
	int y = 20 - (marioY + superplus + MariowideY + 2) / 30;//マリオの下側のY座標

	CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);//マリオがコインを獲得する
	FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY,marioLV);//マリオが中間の旗を獲得する


	if (clear == 0 && dying == 0) {//死んでなくて、クリアもしてないとき

		//地面に立っていて、ジャンプをするとき
		if (Key[KEY_INPUT_UP] == 1 && jump == 0 && ((stage[x1][y] >= 1 && stage[x1][y] != 8 && stage[x1][y] != 9 )|| 
			(stage[x2][y] >= 1 && stage[x2][y] != 8 && stage[x2][y] != 9))){
			MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, 0);
		}
		//砲台の上にいて、ジャンプするとき
		else if (MarioTouchToHodai(num, marioX, marioY, MariowideX, MariowideY, superplus) == 1 && clear == 0 
			&& Key[KEY_INPUT_UP] == 1 && jump == 0) {//
			MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, 0);
		}
		//モンスターを踏んでジャンプするとき
		else if (MarioJumpStartOnMonster(score, nuton, nutonLV, nutonmax, jumping, jump, end, marioX, marioY, MariowideX, coin, mario, superplus, marioLV, num, marioDirection) == 1) {
			if (Key[KEY_INPUT_UP] == 0) {//上ボタンが押されなかったとき
				MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, -4);//小さいジャンプを始める
			}
			else {//上ボタンを押したとき
				MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, 2);//大きいジャンプを始める
			}
		}
	}
	if (jump != 1)Key[KEY_INPUT_UP] = 0;

}


//地面について、ジャンプをやめるとき
//              (マリオの座標、マリオの追加のY座標、マリオの幅、ジャンプしているかどうか、モンスターによってジャンプしているかどうか)
int MarioJumpStop(int marioX, int &marioY, int superplus, int MariowideX, int MariowideY, int &jump, int &jumping) {
	int x1 = (marioX + 1) / 30;//マリオの左側のX座標
	int x2 = (marioX + MariowideX - 1) / 30;//マリオの右側のX座標
	int y = 20 - (marioY + superplus + MariowideY + (jump - 1)) / 30;//マリオの下側のY座標


	//マリオが地面に立っているとき
	if (stage[x1][y] > EMPTY && stage[x1][y] != HALFFLAG1 && stage[x1][y] != HALFFLAG2 
		|| stage[x2][y] > EMPTY && stage[x2][y] != HALFFLAG1 && stage[x2][y] != HALFFLAG2) {
		//ジャンプをやめる
		jump = 0;
		jumping = 0;
		return 1;
	}
	else {
		return 0;
	}
}


//１フレーム分のジャンプをし終わったとき
//               (ジャンプ中のマリオのY座標、ジャンプする向き、ジャンプする前のマリオのY座標、ジャンプの速さ、重力加速度の上限)
int OneFrameJumpEnd(int h, int plus, int basemarioY, double nuton, double nutonmax) {
	if (plus == 1) {//ジャンプで、上昇中
		if (h > (basemarioY + nutonmax - nuton)) {
			return 1;
		}
	}
	else if (plus == -1) {//ジャンプで、落下中
		if (h < (basemarioY + nutonmax - nuton)) {
			return 1;
		}
	}
	return 0;
}


//ジャンプ中の最初のデータ処理
//                 (ジャンプの速さ、重力加速度、重力加速度の上限、ジャンプしているかどうか、ジャンプの向き、ジャンプする前のマリオのY座標、
//                ジャンプ中のマリオのY座標、マリオのY座標、モンスターによってジャンプしているかどうか)
void MarioJumpDataSet(double &nuton, double nutonLV, double nutonmax, int &jump, int &plus, int &basemarioY, int &h, int marioY, int jumping) {
	nuton += nutonLV;//重力加速度を足す
	if (jump == 1 && Key[KEY_INPUT_UP] == 0 && jumping == 0) {//ジャンプ中に上ボタンが押されてないとき
		jump = 2;//ジャンプが、落下に代わる
		nuton = (nutonmax + nutonmax - nuton) / 2 + 5;
	}
	if (jump == 1) {//ジャンプが上昇中の時、
		plus = 1;
	}
	else if (jump == 2) {//ジャンプが落下中の時
		plus = -1;
	}
	basemarioY = marioY;
	h = marioY;
}


//マリオのジャンプ中の処理のまとめ
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

		//ジャンプによる、移動の始まり
		for (;;) {

			CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);//マリオがコインを獲得する
			FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY,marioLV);//マリオが中間の旗を獲得する

			//1フレーム分のジャンプが終わった時、ジャンプを中断する
			if (OneFrameJumpEnd(h, plus, basemarioY, nuton, nutonmax) == 1) {
				break;
			}

			//マリオが、砲台の上に立った時、ジャンプをやめる
			if (jump == 2 && MarioTouchToHodai(num, marioX, marioY, MariowideX, MariowideY, superplus) == 1) {
				jump = 0;
				jumping = 0;
				break;
			}

			//マリオが、地面についてジャンプをやめるとき
			if (MarioJumpStop(marioX, marioY, superplus, MariowideX, MariowideY, jump, jumping) == 1) {
				break;
			}
			else {
				marioY -= plus;//マリオが、ジャンプで移動する
			}
			
			//ジャンプによる上昇が、とても小さくなった時、ジャンプを落下に変える
			if (jump == 1 && nutonmax - nuton < 2) {
				jump = 2;
				nuton += 4;
			}


			MarioRightMove(score, mario, coin, marioX, marioY, move, clear, marioLV, end, marioDirection, MariowideX, MariowideY, superplus, stmove, moving, jump, 1, num, dying, 
				dokanchange, dpla, flag,flagStage,flagX, flagY);//ジャンプ中、右に動く

			MarioLeftMove(score, mario, coin, marioX, marioY, move, clear, marioLV, end, marioDirection, MariowideX, MariowideY, superplus, stmove, moving, jump, 1, num, dying,
				dokanchange, dpla, flag, flagStage,flagX, flagY);//ジャンプ中、左に動く

			//マリオが、モンスターを踏んだ時
			if (MarioJumpStartOnMonster(score, nuton, nutonLV, nutonmax, jumping, jump, end, marioX, marioY, MariowideX, coin, mario, superplus, marioLV, num, marioDirection) == 1) {
				if (Key[KEY_INPUT_UP] == 0) {//上ボタンを押さなかったとき
					MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, -1);//小さいジャンプを始める
				}
				else {//上ボタンを押したとき
					MarioJumpStartDataSet(nuton, nutonLV, nutonmax, jump, jumping, marioY, 3);//大きいジャンプを始める
				}
				break;
			}

			h += plus;
		}
	}
	//ジャンプの処理が終了いたしました
}

//移動工程終わり



//土管に入るかどうか
//　　　　　　　　　（土管で移動する先、土管で移動するかどうか、土管で移動中の時間、移動先の土管の座標、マリオの座標、マリオの幅、クリアしたかどうか、
//　　　　　　　　　　マリオが死んだかどうか）
void DokanGetIntoStart(int &dokan, int &dokanchange, int &count, int &Xdokan, int &Ydokan, int marioX, int marioY, int MariowideY, int superplus, int MariowideX, 
	int clear, int dying) {

	int x1 = marioX  / 30;//マリオの左のX座標
	int x2 = (marioX + MariowideX - 10) / 30;//マリオの右のX座標
	int y = 20 - (marioY + MariowideY + superplus + 1) / 30;//マリオの下側のY座標

	if (dokanchange == 0 && clear == 0 && dying == 0 && Key[KEY_INPUT_DOWN] == 1 && stage[x1][y] >= DOKANUP_MOVE && stage[x2][y] >= DOKANUP_MOVE) {//土管には入れるとき
		//土管による移動のデータをセットする
		dokan = stage[x1][y] % 10;
		dokanchange = 1;
		count = 0;
		Xdokan = x1;
		Ydokan = y;
	}
}


//マリオが土管にはいり中の時
//　　　　　　　　（マリオが土管にはいっている時間、マリオのY座標、土管で移動するかどうか、マリオの追加のY座標、今のステージの場所）
int DokanGettingInto(int &count, int &marioY, int dokanchange, int superplus, int dpla) {
	if (dokanchange == 1) {//土管で移動するとき
		count++;//時間を進める
		marioY += 5;//マリオを下に移動させる
		if (count >= 8 + superplus / 4) {//マリオが、土管に入り切った時
			for (int h = 0; h <= 24; h++) {
				for (int i = 0; i <= 99; i++) {
					if (dstage[dpla][i][h] >= EMPTY) {//今のステージデータを保存する
						dstage[dpla][i][h] = stage[i][h];
					}
				}
			}
			count = 0;
			return 1;//土管での移動先へ行く
		}
	}

	return 0;
}

//土管に入るときの処理のまとめ
int  DokanGetInto(int &dokanchange, int &count, int &dokan, int &Xdokan, int &Ydokan, int &marioY, int marioX, int clear, int marioLV, int end, int MariowideX, 
	int MariowideY, int superplus, int dpla, int dying) {

	DokanGetIntoStart(dokan, dokanchange, count, Xdokan, Ydokan, marioX, marioY, MariowideY, superplus, MariowideX, clear, dying);
	//土管に入れるかどうか

	return DokanGettingInto(count, marioY, dokanchange, superplus, dpla);
	//土管にはいり中、終わったら、移動先へ行く
}


//土管から出る
//           (土管から出る時間、マリオのY座標、土管で移動してきたかどうか、マリオの追加のY座標)
void DokanGetOut(int &count, int&marioY, int &dokanchange, int superplus) {
	if (dokanchange == 2) {//マリオが、土管で移動してきたとき
		count++;//時間を進める
		marioY -= 5;//マリオが、上に上がってくる
		if (count >= 5 + superplus / 4) {//十分に上がった時
			//データをセットする
			dokanchange = 0;
			count = 0;
		}
	}
}


//ボタンを押して、ステージを変えたり、やめたりする
//　　　　　　　（場所、マリオの残基、スクロール数、中間の旗をとったかどうか、中間の旗の場所、中間の旗の座標、マリオの追加のY座標、
//　　　　　　　マリオの横の幅、マリオのダメージ）
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

//ボタンを押して、自滅する
//                 (マリオの状態、マリオがダメージを受けたかどうか)
void MarioKillMyself(int &marioLV, int &end) {
	if (Key[KEY_INPUT_ESCAPE] == 1) {
		marioLV = 1;
		end = 1;
	}
}

//ボタンを押して、スコアを消費して、時間を止めたかどうか
//           (時間を止めたかどうか、スコア)
void TimeStop(int &stop, long &score) {
	if (Key[KEY_INPUT_LCONTROL] == 1 || Key[KEY_INPUT_RCONTROL] == 1) {//コントロールキーを押したとき
		if (stop >= 1)stop = 0;//時間が止まっていた時、進める
		else if (score >= 10000 && stop == 0)stop = 1, score -= 10000;//スコアが１０００以上あって、時間が止まっていないとき、時間を止める
	}
	if (stop >= 1) {//時間を止められる制限時間の処理
		stop++;
		if (stop >= 100)stop = 0;
	}
}

//マリオが死んでいるとき
//             （マリオが死んでいる時間、無敵時間、マリオのY座標、マリオが死んでいるかどうか、マリオのダメージ）
int  MarioDying(int &count,int suke,int &marioY,int dying,int &end) {
	if (dying == 1 && suke == 0) {//死んでいて、無敵時間でもないとき
		count++;//時間を進める
		if (count <= 10) {//時間が１０以内なら
			marioY -= 20 - count * 2;//上に移動する
		}
		else {//時間が１０より大きいなら
			marioY += count * 2 - 20;//下に移動する
		}
		if (marioY >= 520 + count * 2 - 20) {//ある程度下に行ったら、
			count = 0;//ゲームをやめる
			return 1;
		}
	}
	else end = 0;

	return 0;
}


//マリオがダメージを受けたとき
//　　　　　　（マリオがダメージを受けたかどうか、無敵時間かどうか、ジャンプをしているかどうか、マリオが死んでいるかどうか、マリオの追加のY座標、
//　　　　　　　マリオの状態、マリオの横の幅、時間、マリオのY座標、土管で移動しているかどうか）
int MarioDamage(int &end, int &suke, int &jump, double &nuton, int &dying, int &superplus, int &marioLV, int &MariowideX, int &count, int &marioY, 
	int dokanchange) {
	if (end == 1 && suke == 0 && dokanchange == 0) {
		if (marioLV == 1) {//ちびマリオなら
			//死ぬ
			jump = 0;
			nuton = 0;
			dying = 1;
		}
		if (marioLV == 2) {//スーパーマリオなら
			//ちびマリオになる
			marioLV = 1;
			superplus = 0;
			MariowideX = 20;
			suke = 1;//無敵時間の始まり
		}
		else if (marioLV >= 3) {//ファイヤーマリオなら
			marioLV = 2;//スーパーマリオになる
			suke = 1;//無敵時間の始まり
		}
	}

	return  MarioDying(count, suke, marioY, dying, end);//マリオが死んでいるとき
}


//下でハテナブロックからモンスターが出て、そこのモンスターが上に上がる
//　　　　　　　　　　（モンスターの総数、ハテナブロックから出現するモンスターの座標）
void MonsterUpByBlock(int num,int x,int y) {

	int MX1;
	int MX2;
	int MY1;
	int MY2;
	for (int i = 0; i <= num; i++) {
		MX1 = (monX[i] + 2) / 30;//上がる方のモンスターの左のX座標
		MX2 = (monX[i] + 25 - 2) / 30;//上がる方のモンスターの右のX座標
		MY1 = 20 - (monY[i] + 2)/ 30;//上がる方のモンスターの上のY座標
		MY2 = 20 - (monY[i] + 25 - 2) / 30;//あがる方のモンスターの下のY座標
		if ((abs(x - monX[i]) < 25 && abs(y - monY[i]) < 25  )|| //出現するモンスターに触ってた時か、上がる方のモンスターがブロック内にいるとき
			!(stage[MX1][MY1] == EMPTY &&stage[MX1][MY2] == EMPTY &&stage[MX2][MY1] == EMPTY &&stage[MX2][MY2] == EMPTY)) {
			monY[i] -= 5;//上のモンスターは上に上がって、
			i--;
			continue;//重ならなくなるまで上に上がる
		}
	}
}



//マリオの頭がブロックに当たった時
//　　　　　　　　マリオのX座標、マリオの横の幅、マリオのY座標、マリオが死んでいるかどうか、マリオの状態、モンスターの総数、ジャンプしているかどうか）
void MarioHeadHitBlock(int marioX, int MariowideX, int marioY, int dying, int marioLV, int &num, int &jump) {
	int x1 = (marioX + 1) / 30;//マリオの左側のX座標
	int x2 = (marioX + MariowideX - 1) / 30;//マリオの右側のX座標
	int y = 20 - (marioY - 5) / 30;//マリオの上側のY座標


	//死んでなくて、ジャンプ中で、中間の旗でないブロックにぶつかった時
	if (dying == 0 && jump >= 1 && 
		(stage[x1][y] > EMPTY && stage[x1][y] != HALFFLAG1 && stage[x1][y] != HALFFLAG2 ||
			stage[x2][y] > EMPTY && stage[x2][y] != HALFFLAG1 && stage[x2][y] != HALFFLAG2)) {
		jump = 0;
		if (stage[x1][y] == 1 && marioLV >= 2) {//スーパーマリオでレンガにぶつかった時(左)
			stage[x1][y] = EMPTY;//壊す
		}
		else if (stage[x2][y] == 1 && marioLV >= 2) {//スーパーマリオでレンガにぶつかった時(右)
			stage[x2][y] = EMPTY;//壊す
		}
		else if (stage[x1][y] >= HATENA && stage[x1][y] < DOKANUP_MOVE) {//ハテナブロックにぶつかった時(左)
			//ハテナブロックに入っているモンスターを出現させる
			int AppearType;
			if (stage[x1][y] - HATENA < ITEM) {//アイテムが出るとき
				AppearType = (stage[x1][y] - HATENA) * -1;
			}
			else {//モンスターが出るとき
				AppearType = stage[x1][y] - HATENA - ITEM;
			}
			MonsterUpByBlock(num, x1 * 30, (20 - y - 1) * 30);//ハテナブロックの上にいる邪魔なモンスターをどかす
			MonsterAppear(num, AppearType, x1 * 30, (20 - y - 1) * 30, 1);
			stage[x1][y] = HATENA_KNOCKED;//ハテナブロックを空にする
		}
		else if (stage[x2][y] >= HATENA && stage[x2][y] < DOKANUP_MOVE) {//ハテナブロックにぶつかった時(右)
			//ハテナブロックに入っているモンスターを出現させる
			int AppearType;
			if (stage[x2][y] - HATENA < ITEM) {//アイテムが出るとき
				AppearType = (stage[x2][y] - HATENA) * -1;
			}
			else {//モンスターが出るとき
				AppearType = stage[x2][y] - HATENA - 10;
			}
			MonsterUpByBlock(num, x2 * 30, (20 - y - 1) * 30);//ハテナブロックの上にいる邪魔なモンスターをどかす
			MonsterAppear(num, AppearType, x2 * 30, (20 - y - 1) * 30, 1);
			stage[x2][y] = HATENA_KNOCKED;//ハテナブロックを空にする
		}
	}
}

//マリオがクリアしたとき
//　　　　　　　　（スコア、ジャンプの速さ、クリアしたかどうか、ジャンプしているかどうか、時間、場所、マリオのY座標、スクロール数、
//　　　　　　　今のステージの場所、モンスターの総数、マリオのX座標、マリオの追加のY座標、マリオの幅、ゴールの旗の場所）
int  MairoGameClear(long &score, double &nuton, int &clear, int &jump, int &count, int &place, int &marioY, int stmove, int dpla, int num, 
	int &marioX, int superplus, int MariowideX, int MariowideY, int flagpoint) {

	if (dpla % 2 == 1 && clear == 0 && marioX / 30 >= flagpoint) {//クリアしたとき
		//クリアしたときのデータのセット
		for (int i = 0; i <= num; i++) {//モンスターを全部消す
			monEnd[i] = 1;
			score += 100;
		}
		clear = 1;
		jump = 0;
		nuton = 0;
		count = 0;
	}
	if (clear == 1) {//クリアしているとき
		count++;
		int x1 = marioX / 30;//マリオの左のX座標
		int x2 = (marioX + MariowideX) / 30;//マリオの右のX座標
		int y;//マリオの下の部分のY座標
		int last = 0;
		for (int h = 0; h < 10; h++) {
			y = 20 - (marioY + MariowideY + superplus + 1) / 30;
			if (stage[x1][y] == 0 && stage[x2][y] == 0 && marioY <= 430) {//地面に立っていないとき
				marioY++;//下に落ちる
				y++;
			}
			else {//地面に立っているとき
				marioX++;//右に移動する
				Key[KEY_INPUT_RIGHT]++;
				break;
			}
		}
		if (count == 201) {//完全にクリアしたとき、キーが押されるまで動かなくなる
			DrawFormatString(250, 200, GetColor(0, 0, 0), "GAME CLEAR!");
			ScreenFlip();
			WaitKey();
			return 1;
		}
		if (marioX  / 30 >= flagpoint + 5 || count >= 200) {//クリアしきった時
			//クリアの表示をする
			count = 200;
			if(place < 12)place++;//ステージを一つ進める
			else place = 1;
		}
	}
	return 0;
}








//セーブデータを読み込む
void SaveInput() {
	int i, h, g;
	FILE *fp = fopen("セーブデータ.dat", " r b");
	if (fp == NULL) {
		DrawFormatString(250, 250, GetColor(0, 0, 0), "セーブできませんでした。");
		ScreenFlip();
		WaitKey();
	}
	fread(&Data, sizeof(Data), 1, fp);
	fclose(fp);

	//ステージデータを読み込む
	for (g = 0; g <= 25; g++) {
		for (i = 0; i <= 99; i++) {
			for (h = 0; h <= 24; h++) {
				dstage[g][i][h] = Data.makesta[g][i][h];
			}
		}
	}
	//ステージデータ読み込み
}

//弾を出現させる
//　　　　　　　　（スコア、弾の総数、クリアしたかどうか、マリオの座標、マリオの追加のY座標、マリオの状態、マリオのダメージ、マリオの向き）
void BulletAppear(long &score, int &bullet, int clear, int marioX, int marioY, int superplus, int marioLV, int end, int marioDirection) {
	if (clear == 0 && !(marioLV == 1 && end == 1)) {//クリアしてなくて、死んでもないとき
		if (score >= 200 && marioLV == 2 && Key[KEY_INPUT_RSHIFT] % 20 == 1) {//スーパーマリオで、スコアが２００以上あって、シフトを押したとき
			score -= 200;//スコアを２００消費し、
			//マリオ弾を出す
			bullet++;
			bulletY[bullet] = marioY + 20;
			bulletX[bullet] = marioX + 5;
			Btype[bullet] = 1;
			Bside[bullet] = marioDirection;
			Bnuton[bullet] = EMPTY;
		}
		if (marioLV == 3 && Key[KEY_INPUT_RSHIFT] % 5 == 2) {//ファイヤーマリオで、シフトを押したとき
			//ファイヤーボールを出す
			bullet++;
			bulletY[bullet] = marioY + 20;
			bulletX[bullet] = marioX + 5;
			Btype[bullet] = 2;
			Bside[bullet] = marioDirection;
			Bnuton[bullet] = EMPTY;
		}
	}
}



//モンスターとアイテムを表示する
//                       （スクロール数、モンスターの総数）
void PlayStageMonsterShow(int stmove, int num) {
	int i;
	for (i = 0; i <= num; i++) {
		int x1 = monX[i] - stmove;
		int x2 = x1 + 25;
		int y1 = monY[i];
		int y2 = y1 + 25;
		if (monEnd[i] == 1)continue;
		if (monX[i] - stmove < 660) {

			if (Mtype[i] == COIN) 	DrawExtendGraph(x1, y1, x2, y2, coinImg, TRUE);//コイン
			else if (Mtype[i] == KURIBO)	DrawExtendGraph(x1, y1, x2, y2, kuriImg, TRUE);//クリボー
			else if (Mtype[i] == NOKONOKO) DrawExtendGraph(x1, y1, x2, y2, (monMove[i] == 1 ? RnokoImg : LnokoImg), TRUE);//ノコノコ
			else if (Mtype[i] == STOP_KORA || Mtype[i] == MOVE_KORA) DrawExtendGraph(x1, y1, x2, y2, koraImg, TRUE);//甲羅
			else if (Mtype[i] == TOGEZO) DrawExtendGraph(x1, y1, x2, y2, (monMove[i] == 1 ? RtogezoImg : LtogezoImg), TRUE);//トゲゾー
			else if (Mtype[i] == PAKKUN) DrawExtendGraph(x1, y1, x2, y2, packunImg, TRUE);//パックンフラワー
			else if (Mtype[i] == BLACK_PAKKUN) DrawExtendGraph(x1, y1, x2, y2, blackpackunImg, TRUE);//黒パックンフラワー
			else if (Mtype[i] == STOP_SPINE || Mtype[i] == MOVE_SPINE) DrawExtendGraph(x1, y1, x2, y2, spineImg, TRUE);//とげ
			else if (Mtype[i] == STOP_DOSSUN || Mtype[i] == FALL_DOSSUN) DrawExtendGraph(x1, y1, x2, y1 + 30, dosunImg, TRUE);//ドッスン
			else if (Mtype[i] == MOVE_TERESA) DrawExtendGraph(x1, y1, x2, y2, (monSide[i] == 1 ? RteresaImg : LteresaImg), TRUE);//テレサ
			else if (Mtype[i] == STOP_TERESA) DrawExtendGraph(x1, y1, x2, y2, (monSide[i] == 1 ? RtereteresaImg : LtereteresaImg), TRUE);//照れテレサ
			else if (Mtype[i] == KILLER) DrawExtendGraph(x1, y1, x2, y2, (monSide[i] == 1 ? RkillerImg : LkillerImg), TRUE);//キラー
			else if (Mtype[i] >= HODAI) 	DrawExtendGraph(x1, y1, x2, y2, hodaiImg, TRUE);//砲台
			
			//アイテムの表示
			else if (Mtype[i] == SUPER_KINOKO) DrawExtendGraph(x1, y1, x2, y2, kinokoImg, TRUE);//スーパーキノコ
			else if (Mtype[i] == ONE_UP_KINOKO) DrawExtendGraph(x1, y1, x2, y2, upkinokoImg, TRUE);//ワンナップキノコ
			else if (Mtype[i] == FIREFLOWER) DrawExtendGraph(x1, y1, x2, y2, fireflowerImg, TRUE);//ファイヤーフラワー
		}
	}
}



//ブロックを表示する
//                      (スクロール数)
void PlayStageBlockShow(int stmove,int dpla,int flagpoint) {
	int i, h;
	for (h = 0; h <= 20; h++) {
		for (i = stmove / 30; i <= stmove / 30 + 22; i++) {
			if (stage[i][h] == 0)continue;
			int x1 = i * 30 - stmove;//左端のX座標
			int x2 = x1 + 30;//右端のX座標
			int y1 = (20 - h) * 30;//上側のY座標
			int y2 = y1 + 30;//下側のY座標

			if (stage[i][h] >= HATENA && stage[i][h] < DOKANUP_MOVE) DrawExtendGraph(x1, y1, x2, y2, hatenablockImg, FALSE);//ハテナブロック
			else if (stage[i][h] == HATENA_KNOCKED) DrawExtendGraph(x1, y1, x2, y2, normalblockImg, FALSE);//空のハテナブロック
			else if (stage[i][h] == BRICK) 	DrawExtendGraph(x1, y1, x2, y2, brickImg, FALSE);//レンガ
			else if (stage[i][h] == COINBLOCK) DrawExtendGraph(x1, y1, x2, y2, coinImg, TRUE);//コイン
			else if (stage[i][h] == FLOOR) DrawExtendGraph(x1, y1, x2, y2, floarImg, TRUE);//地面
			else if (stage[i][h] == GRASS) 	DrawExtendGraph(x1, y1, x2, y2, floarupImg, TRUE);//草の生えた地面
			else if (stage[i][h] >= DOKANUP_MOVE || stage[i][h] == DOKANUP) DrawExtendGraph(x1 - 2, y1, x1 + 32, y2, dokanupImg, TRUE);//土管の上側
			else if (stage[i][h] == DOKANDOWN) DrawExtendGraph(x1, y1, x2, y2, dokandownImg, TRUE);//土管の下側
			else if (stage[i][h] == HALFFLAG1) DrawExtendGraph(x1, y1, x2, y2, beforeHalfFlagImg, TRUE);//触れる前の中間の旗
			else if (stage[i][h] == HALFFLAG2) DrawExtendGraph(x1, y1, x2, y2, AfterHalfFlagImg, TRUE);//触れた後の中間の旗
		}
	}

	if (dpla % 2 == 1) {//ゴールの旗の表示
		DrawRotaGraph(100 + (flagpoint - 2) * 30 - stmove, 300, 1, 0.0, flagImg, TRUE);
	}

}


//マリオと、ゴールの旗と、城の表示
//                    (スクロール数、マリオが死んでいるかどうか、マリオの座標、マリオの向き、マリオの状態、マリオがジャンプしているかどうか
//                   無敵時間、今のステージの場所、ゴールの旗の場所、クリアしているかどうか)
void PlayStageMarioShow(int stmove, int dying, int marioY, int marioX, int marioDirection, int marioLV, int jump, int suke, int dpla, int flagpoint,
	int clear,int count) {

	if (dpla % 2 == 1) {//ゴールの城の表示
		DrawRotaGraph(70 + (flagpoint + 3) * 30 - stmove, 360, 1, 0.0, castleImg, TRUE);
	}
	int x = marioX - stmove;
	int y = marioY;
	int right = Key[KEY_INPUT_RIGHT];//右の入力数
	int left = Key[KEY_INPUT_LEFT];//左の入力数
	if (right > left)left = 0;
	else right = 0;
	if (dying == 0 && !(clear == 1 && count == 200)) {//土管に入ってなくて、クリアもしていない時
		if (marioLV == 1) {//ちびマリオの表示
			if (jump == 0 && (right >= 1 || left >= 1))
				DrawExtendGraph(x, y, x + 15 , y + 20,
				(right >= 1 ? (right / 5 % 2 == 1?RmovemarioImg1:RmovemarioImg2) : (left / 5 % 2 == 1 ? LmovemarioImg1 : LmovemarioImg2)), TRUE);
			else DrawExtendGraph(x, y, (jump == 0 ? x + 15 : x + 20), y + 20,
				(jump == 0 ? (marioDirection == 1 ? RsupermarioImg : LsupermarioImg) :
				(marioDirection == 1 ? RjumpsupermarioImg : LjumpsupermarioImg)), TRUE);
		}
		else if (marioLV == 2) {//スーパーマリオの表示
			if (jump == 0 && (right >= 1 || left >= 1))
				DrawExtendGraph(x, y, x + 20, y + 35,
				(right >= 1 ? (right / 5 % 2 == 1 ? RmovemarioImg1 : RmovemarioImg2) : (left / 5 % 2 == 1 ? LmovemarioImg1 : LmovemarioImg2)), TRUE);
			else DrawExtendGraph(x, y, (jump == 0 ? x + 20 : x + 25), y + 35,
				(jump == 0 ? (marioDirection == 1 ? RsupermarioImg : LsupermarioImg) :
				(marioDirection == 1 ? RjumpsupermarioImg : LjumpsupermarioImg)), TRUE);
		}
		else if (marioLV == 3) {//ファイヤーマリオの表示
			DrawExtendGraph(x, y, (jump == 0 ? x + 20 : x + 25), y + 35,
				(jump == 0 ? (marioDirection == 1 ? RfiremarioImg : LfiremarioImg) : (marioDirection == 1 ? RjumpfiremarioImg : LjumpfiremarioImg)), TRUE);
		}
	}

}

//その他のものを表示する
//                 (スコア、コイン数、マリオの残基、弾の総数、今のステージの場所、ゴールの旗の場所、スクロール数、死んでいるかどうか、マリオの座標
//　　　　　　　　　クリアしたかどうか)
void PlayStageOtherShow(int score, int coin, int mario, int bullet, int dpla, int flagpoint, int stmove, int dying,
	int marioX, int marioY,int clear) {
	int i;
	int black = GetColor(0, 0, 0);
	int x = marioX - stmove;
	int y = marioY;

	for (i = 0; i <= bullet; i++) {//弾の表示
		if (Btype[i] == 1) {//マリオ弾
			DrawRotaGraph(bulletX[i] - stmove, bulletY[i], 0.1, 0, marioImg, TRUE);
		}
		if (Btype[i] == 2) {//ファイヤーボール
			DrawExtendGraph(bulletX[i] - stmove, bulletY[i], bulletX[i] - stmove + 10, bulletY[i] + 10, fireballImg, TRUE);
		}
	}
	if (dying == 1) DrawExtendGraph(x, y, x + 20, y + 20, deathmarioImg, TRUE);//マリオが死んでいるとき

	//データの表示
	DrawFormatString(500, 0, black, "score %d", score);
	DrawFormatString(60, 0, black, "×%d", coin);//コイン
	DrawExtendGraph(45, -2, 65, 18, coinImg, TRUE);
	DrawFormatString(20, 0, black, "×%d", mario);//マリオの残機
	DrawRotaGraph(15, 10, 0.15, 0.0, marioImg, TRUE);
}



//表示についてのまとめ
void PlayStageShow(int num, int bullet,int dpla, int flagpoint, int stmove, int dying, int marioY, int marioX, int marioDirection, int marioLV, int jump, 
	int suke, int score, int coin, int mario,int clear,int count) {
	ClearDrawScreen(); // 画面を消す
	DrawExtendGraph(-210,-5,650,600,backgroundImg,FALSE);//背景の表示

	PlayStageMarioShow(stmove, dying, marioY, marioX, marioDirection, marioLV, jump, suke, dpla, flagpoint,clear,count);//マリオの表示
	PlayStageBlockShow(stmove, dpla, flagpoint);//ブロックの表示
	PlayStageMonsterShow(stmove, num);//モンスターの表示
	PlayStageOtherShow(score, coin, mario, bullet, dpla, flagpoint, stmove, dying, marioX, marioY,clear);//その他の表示
	ScreenFlip();
}





//死ぬまでの、ゲームのループ
void PlayingGameByDeath(int &mario, int &num, int &bullet, int &dpla, int &flagpoint, int &stmove, int &dying, int &marioY, int &marioX, int & marioDirection, int &jump, 
	int &marioLV, int &suke, long &score,int &coin, int &place, int &Ydokan, int &Xdokan, int &superplus, double &nutonmax, double &nutonLV, double &nuton, int &stop, int &MariowideX,
	int &MariowideY, int &moving, int &move, int &monWide,int &monstop, int &last, int &jumping, int &end, int &dokan, int &dokanchange, int &count, int &clear,int &flag,
	int &flagStage, int &flagX, int &flagY) {

	while (ProcessMessage() == 0 ) {
		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
		}

		if (mario >= 100)mario = 99;//残基が１００以上になった時、９９に直す

		if (clear == 0) gpUpdateKey();//クリアしてないときに、キーの出力状態を計算する

		//ここから、座標の移動など
		if (StageChange(place, mario,stmove,flag,flagStage,flagX,flagY,superplus,marioLV,MariowideX,end) == 1) {//ボタンにタッチして、ステージが変わるとき
			break;
		}

		//土管に入って、入りきったらbreakする。
		if (DokanGetInto(dokanchange, count, dokan, Xdokan, Ydokan, marioY, marioX, clear, marioLV, end, MariowideX, MariowideY, superplus, dpla, dying) == 1) {
			break;
		}

		//土管から出るとき
		DokanGetOut(count, marioY, dokanchange, superplus);


		//マリオがジャンプを始めるとき
		MarioJumpStart(score, coin, mario, jumping, jump, nuton, nutonmax, nutonLV, clear, marioLV,  end, marioX, marioY, MariowideX, MariowideY, superplus, 
			num, marioDirection, dpla, flag,flagStage, flagX, flagY,dying);

		//マリオが自害するとき
		MarioKillMyself(marioLV, end);

		//マリオが時間を止める時
		TimeStop(stop, score);

		//弾が消える
		BulletAppear(score, bullet, clear, marioX, marioY, superplus, marioLV, end, marioDirection);

		//弾の処理
		BulletDataChange(score, bullet, stmove, num);
		
		//クリアしたとき
		if (MairoGameClear(score, nuton, clear, jump, count, place, marioY, stmove, dpla, num, marioX, superplus, MariowideX, MariowideY, flagpoint) == 1) {
			break;
		}

		//モンスターについての処理
		MonsterDataSet(jumping, num, marioLV, end, bullet, stmove, coin, mario, jump, last, marioX, marioY, monstop, monWide, move, nuton, nutonLV, nutonmax,score,
			marioDirection, stop, superplus, MariowideX,dying,MariowideY);

		//マリオがダメージを受けたとき
		if (MarioDamage(end, suke, jump, nuton, dying, superplus, marioLV, MariowideX, count, marioY, dokanchange) == 1) break;

		//コインを獲得する
		CoinGet(marioX, marioY, MariowideX, MariowideY, superplus, coin, mario);

		//中間の旗を獲得する
		FlagGet(marioX, marioY, MariowideX, MariowideY, superplus, dpla, flag, flagStage, flagX, flagY,marioLV);

		//マリオの頭がブロックに当たった時
		MarioHeadHitBlock(marioX, MariowideX, marioY, dying, marioLV, num, jump);


		//左右に動くとき
		LeftAndRightMove(score, mario, coin, marioX, marioY, move, clear, marioLV, end, marioDirection, MariowideX, MariowideY, superplus, stmove, moving, jump, num, dying,
			dokanchange, dpla, flag,flagStage, flagX, flagY);

		//マリオが落ちるとき
		MarioFall(dokanchange, jump, num, superplus, MariowideX, MariowideY, clear, marioLV, end, marioX, marioY, mario, coin, score,
			nuton, nutonmax, nutonLV, jumping, marioDirection, dpla, flag, flagStage, flagX, flagY);

		//マリオがジャンプしているとき
		MarioJumping(score, bullet, monWide, monstop, stop, jump, marioX, marioY, nutonmax, nuton, nutonLV, superplus, marioDirection, move, stmove, coin, mario,
			MariowideX, MariowideY, clear, marioLV, end, num, moving, jumping, dying, dokanchange, dpla, flag, flagStage, flagX, flagY);

		
		if (marioY >= 460 && dokanchange == 0) {//マリオが落ちたとき
			//死ぬ
			marioLV = 1;
			end = 1;
			dying = 1;
		}
		move = 0;

		//無敵時間について
		if (suke >= 1)suke++;
		if (suke == 50)suke = 0;

		//画像を表示する
		PlayStageShow(num, bullet, dpla, flagpoint, stmove, dying, marioY, marioX, marioDirection, marioLV, jump, suke, score, coin, mario, clear,count);

		Sleep(33);
	}
}