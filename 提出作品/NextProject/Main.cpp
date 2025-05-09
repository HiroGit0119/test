
#include <DxLib.h>
#include"DxLib.h"
#include <Windows.h>
#include <stdio.h>
#include"EffekseerForDXLib.h"
#include"Core.h"
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	using namespace std;
	srand(static_cast<unsigned int>(time(0)));
	SetBackgroundColor(100, 100, 200);
	SetGraphMode(int(WindowSize.x), int(WindowSize.y), 32);
	ChangeWindowMode(true);
	
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	
	if (Effkseer_Init(8000) == -1) { 
		DxLib_End(); 
		return -1;
	}
	SetUseLighting(true);
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	GameCore* Core = new GameCore();
	Core->Play();
	Effkseer_End();
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
