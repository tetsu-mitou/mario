#include "Dxlib.h"

static int make = 1;

//画像の名前のセット
static int backgroundImg;//背景
static int beforeHalfFlagImg;//中間の旗とる前
static int AfterHalfFlagImg;//中間の旗とる後
static int halfFlagImg;//中間の旗とる前
static int marioImg;//マリオ
static int upkinokoImg;//ワンナップキノコ
static int kinokoImg;//スーパーキノコ
static int fireflowerImg;//ファイヤーフラワー
static int siroImg;//白
static int brickImg;//レンガ
static int hatenablockImg;//ハテナブロック
static int normalblockImg;//空のハテナブロック
static int floarImg;//地面
static int floarupImg;//草のある地面
static int dokanupImg;//上の土管
static int dokandownImg;//下の土管
static int skyImg;//空の画像
				  //普通マリオ
static int jumpmarioImg;//ジャンプのマリオ
static int deathmarioImg;//死んだマリオ
						 //スーパーマリオ
static int RjumpsupermarioImg;//ジャンプのスーパーマリオ右
static int LjumpsupermarioImg;//ジャンプのスーパーマリオ左
static int RsupermarioImg;//右のスーパーマリオ
static int LsupermarioImg;//左のスーパーマリオ
static int RmovemarioImg1;
static int LmovemarioImg1;
static int RmovemarioImg2;
static int LmovemarioImg2;

						  //スーパーマリオ
static int RjumpfiremarioImg;//ジャンプのスーパーマリオ右
static int LjumpfiremarioImg;//ジャンプのスーパーマリオ左
static int RfiremarioImg;//右のスーパーマリオ
static int LfiremarioImg;//左のスーパーマリオ

						 //マリオ終わり
static int coinImg;//コイン
static int kuriImg;//クリボー
static int RnokoImg;//ノコノコ右
static int LnokoImg;//ノコノコ左
static int koraImg;//甲羅
static int RtogezoImg;//トゲゾー右
static int LtogezoImg;//トゲゾー左
static int packunImg;//パックンフラワー
static int spineImg;//トゲ
static int dosunImg;//ドッスン
static int RteresaImg;//テレサ右
static int LteresaImg;//テレサ左
static int RtereteresaImg;//照れテレサ右
static int LtereteresaImg;//照れテレサ左
static int blackpackunImg;//黒パックンフラワー
static int hodaiImg;//砲台
static int RkillerImg;//キラー右
static int LkillerImg;//キラー左
static int flagImg;//ゴールの旗
static int castleImg;//ゴールの城
static int fireballImg;//ファイヤーボール


int MakeStage();//ステージづくり
void PlayingGame();//プレイゲーム
void Manual();//マニュアル


