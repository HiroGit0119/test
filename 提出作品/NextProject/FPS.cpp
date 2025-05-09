#include "FPS.h"
#include <windows.h>
#include"DxLib.h"
//コンストラクタ
FPSClass::FPSClass() {
    BeforeFPSTime = GetNowCount();
}
// FPSのコントロール
void FPSClass::Controll() {
    int NowFPSTime = GetNowCount();                                //今の経過時間を入手
    int WhileFPSTime = NowFPSTime - BeforeFPSTime;               //ひとつ前のフレームからどれだけ経過したか
    int AdjustmentFPSTime = int(TagetFPSTime) - WhileFPSTime;    //このフレームがどれだけ早いか
    if (AdjustmentFPSTime > 0) WaitTimer(AdjustmentFPSTime);          //早い場合休ませて調整する
    BeforeFPSTime = GetNowCount();                                  //調整後の経過時間を前の経過時間として記録
}