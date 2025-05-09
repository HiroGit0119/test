#include"Mouse.h"
#include"Villager.h"
#include"Zombie.h"
MouseClass::MouseClass() {
	ScreenPosition = VGet(0, 0, 0);
	PickFlg = false;
}
void MouseClass::Move(VECTOR CameraPosition) {
	int X, Y;
	GetMousePoint(&X, &Y);
	ScreenPosition = VGet(float(X), float(Y), 0.0f);
	WorldPosition = ConvScreenPosToWorldPos(ScreenPosition);
	VECTOR SubDirection = VNorm(VSub(CameraPosition, WorldPosition));
	VECTOR SubVector = VScale(SubDirection, 1 / SubDirection.z * WorldPosition.z);
	WorldPosition = VSub(WorldPosition, SubVector);
	PickPosition = VAdd(WorldPosition, VScale(SubDirection, PickLength * (1 / SubDirection.z)));
	OverPickPosition = VAdd(PickPosition, VScale(SubDirection, PickLength));
	LeftBeforeInput = LeftInput;
	if (GetMouseInput() == MOUSE_INPUT_LEFT)LeftInput = true;
	else LeftInput = false;
	RightBeforeInput = RightInput;
	if (GetMouseInput() == MOUSE_INPUT_RIGHT)RightInput = true;
	else RightInput = false;
}
void MouseClass::Show() {
	DrawCircle(int(ScreenPosition.x), int(ScreenPosition.y), 2, WhiteColor, true);
	float PickUpCountPercent = NowPickUpCount / 10.0f;
	MyDrawBox(PickBerBack, BrackColor);
	BOX NowPickBerFront = PickBerFront;
	NowPickBerFront.Right = PickBerFront.Left + (PickBerFrontMaxLength * PickUpCountPercent / 100.0f);
	MyDrawBox(NowPickBerFront, WhiteColor);
	BOX PotionFallBox = NowPickBerFront;
	PotionFallBox.Left = PotionFallBox.Right-PotionFallLength;
	if (PotionFallBox.Left < NowPickBerFront.Left)PotionFallBox.Left = NowPickBerFront.Left;
	MyDrawBox(PotionFallBox, GrayColor);
}
bool MouseClass::IsInTitlePlayBer() {
	if (ScreenPosition.x < TitleBerHitLeft.Left) return false;
	if (ScreenPosition.x > TitleBerHitLeft.Right) return false;
	if (ScreenPosition.y < TitleBerHitLeft.Up) return false;
	if (ScreenPosition.y > TitleBerHitLeft.Down) return false;
	return true;
}
bool MouseClass::IsInTitleInfoBer() {
	if (ScreenPosition.x < TitleBerHitMid.Left) return false;
	if (ScreenPosition.x > TitleBerHitMid.Right) return false;
	if (ScreenPosition.y < TitleBerHitMid.Up) return false;
	if (ScreenPosition.y > TitleBerHitMid.Down) return false;
	return true;
}
bool MouseClass::IsInTitleExitBer() {
	if (ScreenPosition.x < TitleBerHitRight.Left) return false;
	if (ScreenPosition.x > TitleBerHitRight.Right) return false;
	if (ScreenPosition.y < TitleBerHitRight.Up) return false;
	if (ScreenPosition.y > TitleBerHitRight.Down) return false;
	return true;
}
bool MouseClass::IsLeftInput() {
	if (!LeftInput && LeftBeforeInput)return true;
	else return false;
}
bool MouseClass::IsRightKric() {
	if (RightInput && !RightBeforeInput)return true;
	else return false;
}
void MouseClass::HitInvestigate(std::list<Villager*> Villagers, std::list<Zonbie*> Zonbies, VECTOR CameraPosition) {
	if (!LeftInput) {
		PickFlg = false;
	}
	else {
		if (PickFlg)NowPickUpCount -= PickUpCountDwon;
		if (NowPickUpCount <= 0) {
			NowPickUpCount = 0;
			PickFlg = false;
		}
	}
	if (!PickFlg) {
		if (NowPickUpCount < MaxPickUpCount&& !LeftInput) {
			NowPickUpCount += PickUpCountUp;
			if (NowPickUpCount > MaxPickUpCount)NowPickUpCount = MaxPickUpCount;
		}
	}
	if (!PickFlg) {
		for (auto NextMob = Villagers.begin(); NextMob != Villagers.end(); NextMob++) {
			auto Scan = *NextMob;
			VECTOR ScanPosition = Scan->GetPosition();
			VECTOR ScanTopPosition = ScanPosition;
			ScanTopPosition.z += MobHeight;
			if (Segment_Segment_MinLength(WorldPosition,OverPickPosition,ScanPosition,ScanTopPosition) <= PickScale && LeftInput && Scan->IsNockBackSpeed() == 1) {
				Scan->SetPickUpFlg(true);
				Scan->SetNockBackSpeed(1);
				PickFlg = true;
				break;
			}
			else Scan->SetPickUpFlg(false);
		}
	}
	if (!PickFlg) {
		for (auto NextMob = Zonbies.begin(); NextMob != Zonbies.end(); NextMob++) {
			auto Scan = *NextMob;
			VECTOR ScanPosition = Scan->GetPosition();
			VECTOR ScanTopPosition = ScanPosition;
			ScanTopPosition.z += MobHeight;
			if (Segment_Segment_MinLength(WorldPosition, OverPickPosition, ScanPosition, ScanTopPosition) <= PickScale && LeftInput && Scan->IsNockBackSpeed() == 1) {
				Scan->SetPickUpFlg(true);
				Scan->SetNockBackSpeed(1);
				PickFlg = true;
				break;
			}
			else Scan->SetPickUpFlg(false);
		}
	}
}
void MouseClass::ReleasePickFlg() {
	PickFlg = false;
}
bool MouseClass::IsPotionFall() {
	if (NowPickUpCount >= PotionFallCost)return true;
	else return false;
}
bool MouseClass::IsWorldPositionInStage() {
	if (WorldPosition.x > WorldLength)return false;
	if (WorldPosition.x < -WorldLength)return false;
	if (WorldPosition.y > WorldLength)return false;
	if (WorldPosition.y < -WorldLength)return false;
	return true;
}