#pragma once
#include"DxLib.h"
#include<list>
#include"Math.h"
class Villager;
class Zonbie;
class MouseClass {
private:
	VECTOR ScreenPosition;
	VECTOR WorldPosition;
	VECTOR PickPosition;
	VECTOR OverPickPosition;
	VECTOR SaveCameraPosition;
	bool LeftInput = false;
	bool LeftBeforeInput;
	bool RightInput = false;
	bool RightBeforeInput;
	bool PickFlg;
	float MaxPickUpCount = 1000.0f;
	float NowPickUpCount;
	int PickUpCountUp = 1;
	int PickUpCountDwon = 3;
public:
	MouseClass();
	void Move(VECTOR CameraPosition);
	void Show();
	bool IsInTitlePlayBer();
	bool IsInTitleInfoBer();
	bool IsInTitleExitBer();
	bool IsLeftInput();
	bool IsRightKric();
	void HitInvestigate(std::list<Villager*> Villagers, std::list<Zonbie*> Zonbies, VECTOR CameraPosition);
	VECTOR IsWorldPosition() { return WorldPosition; }
	VECTOR IsPickPosition() { return PickPosition; }
	void PickUpCountReSet() { NowPickUpCount = MaxPickUpCount; }
	void ReleasePickFlg();
	bool IsPickFlg() { return PickFlg; }
	bool IsPotionFall();
	void ActPotionFall() { NowPickUpCount -= PotionFallCost; }
	bool IsWorldPositionInStage();
	
};
