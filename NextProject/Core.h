#pragma once

#include"EffekseerForDXLib.h"
#include"FPS.h"
#include"Villager.h"
#include"Zombie.h"
#include"Camera.h"
#include"Trap.h"
#include"Object.h"
#include"Effect.h"
#include"Math.h"
#include"Mouse.h"
#include"Music.h"
enum GameStatusEnum {
	Title,Playing
};
class GameCore {
private:
	std::list<Villager*> Villagers;
	std::list<Zonbie*> Zonbies;
	std::list<TrapClass*> Traps;
	std::list<ObjectClass*> Objects;
	std::list<Effect*>Effects;
	CameraClass Camera;
	FPSClass FPS;
	MouseClass Mouse;
	GameStatusEnum GameStatus;
	MusicManagerClass MusicManager;
	VECTOR MapMaxPosition = VGet(500, 500, 0);
	VECTOR MapMinPosition = VGet(-500, -500, 0);
	VECTOR MapPosition1 = VGet(WorldLength, WorldLength, 0);
	VECTOR MapPosition2 = VGet(WorldLength, -WorldLength, 0);
	VECTOR MapPosition3 = VGet(-WorldLength, WorldLength, 0);
	VECTOR MapPosition4 = VGet(-WorldLength, -WorldLength, 0);
	bool PlayFlg = true;
	bool VillagerWinFlg = false;
	bool BackTitleFlg = true;
	bool InfoFlg = false;
	int FinishCount = -1;
	int ScreenChangeTime = 0;
	float CountDown = 0.0f;
	int VillagerCountBerPercent;
	int ZonbieCountBerPercent;
	int MariaModel = MV1LoadModel("../Model/Maria.mv1");
	int MariaAnim = MV1LoadModel("../Model/NewMaria.mv1");
	int ZonbieModel = MV1LoadModel("../Model/Zonbie2.mv1");
	int ZonbieAnim = MV1LoadModel("../Model/Zonbie.mv1");
	int Skyaset= MV1LoadModel("../Model/Sky.mv1");
	int SkyModel = MV1DuplicateModel(Skyaset);

	int PotionEffect = LoadEffekseerEffect("../Effect/Blow.efk", 20.0f);
	int HitEffect = LoadEffekseerEffect("../Effect/Hit.efk", 20.0f);
	int ArrowEffect = LoadEffekseerEffect("../Effect/Gun.efk", 20.0f);
	int TitleImage = LoadGraph("../Image/Title.png");
	int GoImage = LoadGraph("../Image/Go.png");
	int OneImage = LoadGraph("../Image/One.png");
	int TwoImage = LoadGraph("../Image/Two.png");
	int ThreeImage = LoadGraph("../Image/Three.png");
	int PlayImage = LoadGraph("../Image/Play.png");
	int InfoImage = LoadGraph("../Image/Info.jpg");
	int ExitImage = LoadGraph("../Image/Exit.png");
	int Count0Image = LoadGraph("../Image/Count0.png");
	int Count1Image = LoadGraph("../Image/Count1.png");
	int Count2Image = LoadGraph("../Image/Count2.png");
	int Count3Image = LoadGraph("../Image/Count3.png");
	int Count4Image = LoadGraph("../Image/Count4.png");
	int Count5Image = LoadGraph("../Image/Count5.png");
	int Count6Image = LoadGraph("../Image/Count6.png");
	int Count7Image = LoadGraph("../Image/Count7.png");
	int Count8Image = LoadGraph("../Image/Count8.png");
	int Count9Image = LoadGraph("../Image/Count9.png");
	int Count10Image = LoadGraph("../Image/Count10.png");
	int InfoUIImage = LoadGraph("../Image/InfoUI.png");
	int MariaNameImage = LoadGraph("../Image/MariaName.png");
	int MonsterNameImage = LoadGraph("../Image/MonsterName.png");
	int MariaWinsImage = LoadGraph("../Image/MariaWins.png");
	int MonsterWinsImage = LoadGraph("../Image/MonsterWins.png");
public:
	GameCore();
	void Play();
	void StageUpdate();
	void Move();		//移動プログラム
	void Overlap();		//重なり対応プログラム
	void Delete();		//消滅プログラム
	void Decision();	//判定プログラム
	void Show();		//表示プログラム
	void GameReset();
	void AllClear();
	void TitleShow();
	void ShowMobCount(BOX Box, size_t Size);
	void UpdateCountBer();
};
