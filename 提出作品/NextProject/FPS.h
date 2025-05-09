#pragma once

//fps管理クラス
class FPSClass {
private:
    const float TagetFPSTime = 1000 / 60;
    int BeforeFPSTime;  //1フレーム前の時間
public:
    FPSClass();              // コンストラクタ
    void Controll();    //FPSのコントロール
};
