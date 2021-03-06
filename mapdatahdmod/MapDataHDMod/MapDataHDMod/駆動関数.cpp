#define  _CRT_SECURE_NO_WARNINGS

#include <string>

#include <sys/types.h>
#include <sys/stat.h>

#include "TimerMessageBox.h"
#include "ゲームデータ構造.h"

using namespace std;
using namespace 関数;


// 004D2CB8  41 3A 4D 41 50 44 41 54 41 2E 4E 36 50 00 00 00  A:MAPDATA.N6P...
#define GAMEDATASTRUCT_MAPDATAN6P_NAME_ADDRESS	0x4D2CB8	// mapdata.n6pという名前のアドレス。｢004D2CB8  A:MAPDATA.N6P...｣というNULLが３つあるので、２文字までなら簡単に長く出来る。
// それ以上長くしたい場合には、この場所のアドレスを参照している所の参照先を変更すること。

#define GAMEDATASTRUCT_MAPDATAN6P_REF_ADDRESS1	0x490B60	// 「mapdata.n6pという名前のアドレス」を参照している場所１つ目
#define GAMEDATASTRUCT_MAPDATAN6P_REF_ADDRESS2	0x490C79	// 「mapdata.n6pという名前のアドレス」を参照している場所２つ目


char szMapDataFileName[32] = "A:MAPDATAHD.N6P"; // 他のプログラムが、再再度、名前を変更を可能とするため、十分なバッファを確保しておく。
// TSMODは、常に上記２つの場所で参照しているアドレスから、名前の場所を得て計算するため、
// どこに名前が存在しても問題なく追従する。

// Obgkマップはあるのか無いのか？
bool isExistMapDataFileName = true;

void WINAPI On_初期化(HANDLE 呼び出し元ハンドル) {

	HANDLE hCurProcess = GetCurrentProcess();

	// ファイルの存在のチェックして存在しなければエラーを出す。
	struct stat  st;
	if (!stat(szMapDataFileName + 2, &st) == 0) { // +2==最初の２文字は無視

		// 無いということで…
		isExistMapDataFileName = false;

	}

	// 覚書マップが存在していなかったのならばエラーメッセージ。
	if (!isExistMapDataFileName) {

		// エラーメッセージ処理
		string error = string(szMapDataFileName + 2) + "が見つかりません。\n｢標準化モード｣で起動します。";

		TimedMessageBox(NULL, error.c_str(), "エラー", NULL, 4000); // 自動で消えるミリ秒。(この場合3秒)

		// 覚書マップが存在するならば…
	}
	else {

		// TENSHOU.EXE内の"A:MAPDATA.N6P"を参照している箇所を、このDLLのszMapDataFilenameポインタに置き換える。
		// 即ち、4D2CB8を指し示すニーモニックを、szMapDataFileNameを指し示すニーモニックへと書き換える
		int Address = (int)szMapDataFileName;
		WriteProcessMemory(hCurProcess, (LPVOID)GAMEDATASTRUCT_MAPDATAN6P_REF_ADDRESS1, (LPCVOID)&Address, 4, NULL);
		WriteProcessMemory(hCurProcess, (LPVOID)GAMEDATASTRUCT_MAPDATAN6P_REF_ADDRESS2, (LPCVOID)&Address, 4, NULL);
	}
}

void WINAPI On_シナリオ大名選択直前() {
}

void WINAPI On_メインゲーム開始() {
	// デフォルトの位置へと移動
	Set_城位置(9, 163, 4);	// 徳山
	Set_城位置(10, 6, 6);	// 平戸
	Set_城位置(12, 32, 6);	// 三本松
	Set_城位置(15, 82, 6);	// 北ノ庄
	Set_城位置(16, 86, 6);	// 大聖寺
	Set_城位置(18, 131, 6);	// 尾浦
	Set_城位置(23, 45, 7);	// 尾高
	Set_城位置(24, 50, 7);	// 八橋
	Set_城位置(26, 126, 7);	// 本庄
	Set_城位置(28, 145, 7);	// 横手
	Set_城位置(29, 150, 7);	// 角館
	Set_城位置(31, 11, 9);	// 勢福寺
	Set_城位置(33, 20, 9);	// 城井谷
	Set_城位置(39, 82, 9);	// 一乗谷
	Set_城位置(44, 36, 10);	// 小倉山
	Set_城位置(45, 48, 10);	// 高田
	Set_城位置(47, 97, 10);	// 魚津
	Set_城位置(49, 123, 10);	// 新発田
	Set_城位置(50, 136, 10);	// 米沢
	Set_城位置(55, 16, 12);	// 古処山
	Set_城位置(59, 61, 12);	// 此隅
	Set_城位置(66, 130, 12);	// 黒川
	Set_城位置(67, 140, 12);	// 白石
	Set_城位置(72, 21, 13);	// 府内
	Set_城位置(73, 28, 13);	// 鞍掛山
	Set_城位置(79, 8, 15);	// 日野江
	Set_城位置(82, 52, 15);	// 天神山
	Set_城位置(84, 61, 15);	// 竹田
	Set_城位置(96, 136, 16);	// 三春
	Set_城位置(97, 140, 16);	// 小高
	Set_城位置(99, 35, 18);	// 来島
	Set_城位置(104, 78, 18);	// 今浜
	Set_城位置(105, 81, 18);	// 大垣
	Set_城位置(107, 96, 18);	// 林
	Set_城位置(118, 111, 19);	// 厩橋
	Set_城位置(120, 136, 19);	// 大館
	Set_城位置(125, 57, 21);	// 三木
	Set_城位置(127, 66, 21);	// 室町
	Set_城位置(139, 111, 22);	// 平井
	Set_城位置(140, 116, 22);	// 忍
	Set_城位置(149, 82, 24);	// 清洲
	Set_城位置(151, 123, 24);	// 古河
	Set_城位置(154, 28, 25);	// 中村
	Set_城位置(160, 116, 25);	// 河越
	Set_城位置(163, 6, 27);	// 一宇治
	Set_城位置(164, 36, 27);	// 岡豊
	Set_城位置(166, 51, 27);	// 洲本
	Set_城位置(170, 82, 27);	// 那古野
	Set_城位置(173, 120, 27);	// 岩付
	Set_城位置(174, 12, 28);	// 加治木
	Set_城位置(175, 17, 28);	// 飫肥
	Set_城位置(183, 38, 30);	// 安芸
	Set_城位置(193, 52, 31);	// 岸和田
	Set_城位置(203, 88, 33);	// 岡崎
	Set_城位置(205, 5, 34);	// 種子島
	Set_城位置(210, 113, 34);	// 稲村
	Set_城位置(211, 117, 34);	// 久留里
	Set_城位置(212, 98, 36);	// 高天神

}



