#include"Core.h"
GameCore::GameCore() {
	GameStatus = Title;
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	ScreenChangeTime = 30;
	MV1SetPosition(SkyModel, VGet(0, 0, 0));
	MV1SetRotationXYZ(SkyModel, VGet(90 * MPIRadian, 0, 0));
	VillagerCountBerPercent = 0;
	ZonbieCountBerPercent = 0;
}
void GameCore::Play() {
	GameReset();
	Camera.SetTitlePosition();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		if (GameStatus == Title) {
			MusicManager.StopMusic();
			if (!InfoFlg) {
				if (((Mouse.IsInTitlePlayBer() && Mouse.IsLeftInput()) || ScreenChangeTime > 0) && !BackTitleFlg) {
					if (ScreenChangeTime == 0)MusicManager.PlayStartSound();
					ScreenChangeTime++;
				}
				if (ScreenChangeTime > 0 && BackTitleFlg) {
					ScreenChangeTime--;
					if (ScreenChangeTime == 0)BackTitleFlg = false;
				}
				if (ScreenChangeTime >= 30) {
					GameStatus = Playing;
					AllClear();
					GameReset();
					MusicManager.PlayCountDwonSound();
				}
				if (Mouse.IsInTitleInfoBer() && Mouse.IsLeftInput() && !BackTitleFlg)InfoFlg = true;
				if (Mouse.IsInTitleExitBer() && Mouse.IsLeftInput() && !BackTitleFlg)break;
			}
			else {
				if (Mouse.IsLeftInput() && !BackTitleFlg)InfoFlg = false;
			}

		}
		else if (GameStatus == Playing) {
			if (!PlayFlg) {
				FinishCount--;
				if (FinishCount < 30)ScreenChangeTime++;
				if (FinishCount <= 0) {
					MusicManager.StopMusic();
					GameStatus = Title;
					AllClear();
					GameReset();
					Camera.SetTitlePosition();
					BackTitleFlg = true;
					
				}
			}
			else {
				if (ScreenChangeTime > 0) {
					ScreenChangeTime--;
				}
				if (CountDown > -60.0f) {
					CountDown -= 1.0f;
				}
				if (CountDown == 0) {
					MusicManager.PlayMusic();
				}
			}
			UpdateCountBer();
		}
		StageUpdate();
		Show();
		FPS.Controll();
	}
}
void GameCore::StageUpdate() {
	if (!(GameStatus == Playing && CountDown > 0)) {
		Move();
		Overlap();
		Delete();
		Decision();
	}
}
void GameCore::Move() {

	for (auto ScanMob = Villagers.begin(); ScanMob != Villagers.end(); ScanMob++) {
		auto ScanVillager = *ScanMob;
		ScanVillager->VillagerMove(Zonbies, MapMaxPosition, MapMinPosition, Mouse.IsPickPosition());
	}

	for (auto ScanMob = Zonbies.begin(); ScanMob != Zonbies.end(); ScanMob++) {
		auto ScanZonbie = *ScanMob;
		ScanZonbie->ZonbieMove(Villagers, MapMaxPosition, MapMinPosition, Mouse.IsPickPosition());
	}

	for (auto ScanMob = Traps.begin(); ScanMob != Traps.end(); ScanMob++) {
		auto ScanObject = *ScanMob;
		ScanObject->Progress();
	}

	for (auto ScanMob = Objects.begin(); ScanMob != Objects.end(); ScanMob++) {
		auto ScanObject = *ScanMob;
		ScanObject->Move(MapMaxPosition, MapMinPosition);
	}

	for (auto ScanMob = Effects.begin(); ScanMob != Effects.end(); ScanMob++) {
		auto ScanEffect = *ScanMob;
		ScanEffect->Move();
	}

	Mouse.Move(Camera.IsPosition());
	
}
void GameCore::Overlap() {
	for (auto ScanMob = Objects.begin(); ScanMob != Objects.end(); ScanMob++) {
		auto MyScan = *ScanMob;
		MyScan->HitInvestigate(Villagers, Zonbies, Effects,MusicManager,Mouse, ArrowEffect);
		
		if (MyScan->IsDeliteFlg() && MyScan->IsType() == HealPotion) {
			MusicManager.PlayPotionSound();
			Effects.push_back(new Effect(MyScan->GetPosition(), VNorm(VGet(0, 0, 0)), 1, PotionEffect));
		}
	}
	int Number = 0;
	for (auto ScanMob = Villagers.begin(); ScanMob != Villagers.end(); ScanMob++) {
		auto MyVillager = *ScanMob;
		Number++;
		MyVillager->HitInvestigate(Villagers, Zonbies, Effects,MusicManager,Mouse, Number, HitEffect);
		
	}

	Number = 0;
	for (auto ScanMob = Zonbies.begin(); ScanMob != Zonbies.end(); ScanMob++) {
		auto MyZonbie = *ScanMob;
		Number++;
		MyZonbie->HitInvestigate(Zonbies, Number);
	}
	for (auto ScanMob = Traps.begin(); ScanMob != Traps.end(); ScanMob++) {
		auto ScanTrap = *ScanMob;
		bool Flg = ScanTrap->IsHitInvestigate(Villagers, Zonbies);
		if (Flg && !ScanTrap->IsStepFlg()) {
			if (ScanTrap->IsTrapType() == HealDispenser) {
				Objects.push_back(new ObjectClass(ScanTrap->GetPosition(), VGet(0, 0, 1), 0, 1, HealPotion));
			}
			else if (ScanTrap->IsTrapType() == ArrowDispenser) {
				VECTOR Position1;
				VECTOR Position2;
				VECTOR Direction1;
				VECTOR Direction2;
				ScanTrap->SetArrowStatus(Position1, Position2, Direction1, Direction2);
				Objects.push_back(new ObjectClass(Position1, Direction1, 10, 0, Arrow));
				Objects.push_back(new ObjectClass(Position2, Direction2, 10, 0, Arrow));
				ScanTrap->SetProgressTime(ScanTrap->IsProgressCount());
				MusicManager.PlayShotAroowSound();
			}
			ScanTrap->SetStepFlg(Flg);
		}
		else if (!Flg && ScanTrap->IsStepFlg())ScanTrap->SetStepFlg(Flg);
		else if (!Flg) ScanTrap->CoolDwon();
	}
	if (Mouse.IsRightKric()&&Mouse.IsPotionFall()&&Mouse.IsWorldPositionInStage()) {
		VECTOR SetPosition = Mouse.IsWorldPosition();
		SetPosition.z += 2000;
		Objects.push_back(new ObjectClass(SetPosition, VGet(0, 0, 1), 0, -60, HealPotion));
		Mouse.ActPotionFall();
	}
	if (GameStatus == Playing)Mouse.HitInvestigate(Villagers, Zonbies, Camera.IsPosition());
}
	
void GameCore::Delete() {
	for (auto ScanMob = Villagers.begin(); ScanMob != Villagers.end(); ScanMob) {
		auto ScanVillager = *ScanMob;
		ScanVillager->DeathProgress();
		if (ScanVillager->IsLiveCoune() <= 0) {
			auto Delete = ScanMob;
			ScanMob++;
			Villagers.erase(Delete);
			MusicManager.PlayDwonSound();
		}
		else ScanMob++;
	}
	for (auto ScanMob = Zonbies.begin(); ScanMob != Zonbies.end(); ScanMob) {
		auto ScanZonbie = *ScanMob;
		ScanZonbie->DeathProgress();
		if (ScanZonbie->IsLiveCoune() <= 0) {
			auto Delete = ScanMob;
			ScanMob++;
			Zonbies.erase(Delete);
			MusicManager.PlayDwonSound();
		}
		else ScanMob++;
	}
	for (auto ScanMob = Objects.begin(); ScanMob != Objects.end(); ScanMob) {
		auto ScanObjects = *ScanMob;
		if (ScanObjects->IsDeliteFlg()) {
			auto Delete = ScanMob;
			ScanMob++;
			Objects.erase(Delete);
		}
		else ScanMob++;
	}
	for (auto ScanMob = Effects.begin(); ScanMob != Effects.end(); ScanMob) {
		auto ScanEffect = *ScanMob;
		if (ScanEffect->IsTime() >= 100) {
			auto Delete = ScanMob;
			ScanMob++;
			Effects.erase(Delete);
		}
		else ScanMob++;
	}
}
void GameCore::Decision() {
	if (PlayFlg) {
		if (Zonbies.size() <= 0) {
			PlayFlg = false;
			VillagerWinFlg = true;
		}
		else if (Villagers.size() <= 0)PlayFlg = false;
	}
}
void GameCore::Show() {
	if (GameStatus == Playing && CountDown > 10)Camera.MoveCountDwon(CountDown);
	else if (GameStatus == Playing && CountDown == 10)Camera.SetPlayPosition();

	ClearDrawScreen();
	if (GameStatus == Title)Camera.MoveTitlePosition();
	Camera.SetPosition();
	MV1DrawModel(SkyModel);
	int Color = GetColor(100, 100, 100);
	DrawTriangle3D(MapPosition1, MapPosition2, MapPosition3,Color , true);
	DrawTriangle3D(MapPosition4, MapPosition2, MapPosition3, Color, true);
	for (auto ScanMob = Traps.begin(); ScanMob != Traps.end(); ScanMob++) {
		auto ScanTrap = *ScanMob;
		ScanTrap->Show();
	}
	for (auto ScanMob = Villagers.begin(); ScanMob != Villagers.end(); ScanMob++) {
		auto Scan = *ScanMob;
		Scan->VillagerShow();
	}
	for (auto ScanMob = Zonbies.begin(); ScanMob != Zonbies.end(); ScanMob++) {
		auto Scan = *ScanMob;
		Scan->ZonbieShow();
	}
	for (auto ScanMob = Objects.begin(); ScanMob != Objects.end(); ScanMob++) {
		auto ScanObject = *ScanMob;
		ScanObject->Show();
	}
	for (auto ScanMob = Effects.begin(); ScanMob != Effects.end(); ScanMob++) {
		auto ScanObject = *ScanMob;
		ScanObject->Show();
	}
	UpdateEffekseer3D();
	DrawEffekseer3D();
	if (GameStatus == Playing && !PlayFlg) {
		if (VillagerWinFlg)MyDrawGraph(WinsBox, MariaWinsImage);
		else MyDrawGraph(WinsBox, MonsterWinsImage);
	}
	if (GameStatus==Title) {
		TitleShow();
	}
	if (GameStatus == Playing) {
		Mouse.Show();
		DrawCircle(0, 0, int(CountCircleLength), VillagerColor, true);
		DrawCircle(int(WindowSize.x), 0, int(CountCircleLength), ZonbieColor, true);
		ShowMobCount(MariaCountBox, Villagers.size());
		ShowMobCount(ZonbieCountBox, Zonbies.size());
		MyDrawGraph(MariaNameBox, MariaNameImage);
		MyDrawGraph(ZonbieNameBox, MonsterNameImage);
		MyDrawBox(CountBerOut, BrackColor);
		BOX NowVillagerBer = CountBerIn;
		NowVillagerBer.Right = NowVillagerBer.Left + (CountBerLength / 1000.0f * VillagerCountBerPercent);
		MyDrawBox(NowVillagerBer, VillagerColor);
		BOX NowZonbieBer = CountBerIn;
		NowZonbieBer.Left = NowZonbieBer.Right - (CountBerLength / 1000.0f * ZonbieCountBerPercent);
		MyDrawBox(NowZonbieBer, ZonbieColor);
	}
	if (CountDown > -60 && GameStatus == Playing) {
		float ImageSize = 100.0f;
		if (CountDown > 0) {
			float Few = float(int(CountDown) % 60);
			if (Few > 50.0f)ImageSize = (60.0f - Few) * 10.0f;
			else if (Few < 10.0f)ImageSize = Few * 10.0f;
		}
		else {
			ImageSize = -CountDown * 3.0f;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (60 - (-int(CountDown))) * 10);
		}
		
		float ImageLength = PercentLength * ImageSize;
		BOX ImageBox = BoxGet(MidPosition, ImageLength, ImageLength);
		if (CountDown > 120)MyDrawGraph(ImageBox, ThreeImage);
		else if (CountDown > 60)MyDrawGraph(ImageBox, TwoImage);
		else if (CountDown > 0)MyDrawGraph(ImageBox, OneImage);
		else MyDrawGraph(ImageBox, GoImage);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	if (ScreenChangeTime > 0) {
		float BrackLength = WindowSize.y / 50.0f * ScreenChangeTime;
		DrawBox(0, 0, int(WindowSize.x), int(BrackLength), BrackColor, true);
		DrawBox(0, int(WindowSize.y), int(WindowSize.x), int(WindowSize.y - BrackLength), BrackColor, true);
	}
	ScreenFlip();
	
}
void GameCore::GameReset() {
	FinishCount = 300;
	CountDown = 180;
	PlayFlg = true;
	for (int i = 0; i < 10; i++) {
		Villagers.push_back(new Villager(VGet(300.0f, -290.0f + (i * 60.0f), 0.0f), VGet(-1.0f, 0.0f, 0.0f), MariaModel, MariaAnim));
	}
	for (int i = 0; i < 10; i++) {
		Zonbies.push_back(new Zonbie(VGet(-300.0f, -290.0f + (i * 60.0f), 0.0f), VGet(1.0f, 0.0f, 0.0f), ZonbieModel, ZonbieAnim));
	}
	Mouse.PickUpCountReSet();
	Traps.push_back(new TrapClass(VGet(200, 200, 0), VGet(0, 0, 0), 20, HealDispenser));
	Traps.push_back(new TrapClass(VGet(-200, 200, 0), VGet(0, 0, 0), 20, HealDispenser));
	Traps.push_back(new TrapClass(VGet(200, -200, 0), VGet(0, 0, 0), 20, HealDispenser));
	Traps.push_back(new TrapClass(VGet(-200, -200, 0), VGet(0, 0, 0), 20, HealDispenser));
	Traps.push_back(new TrapClass(VGet(480, 480, 0), VNorm(VGet(-1, -1, 0)), 20, ArrowDispenser));
	Traps.push_back(new TrapClass(VGet(-480, 480, 0), VNorm(VGet(1, -1, 0)), 20, ArrowDispenser));
	Traps.push_back(new TrapClass(VGet(480, -480, 0), VNorm(VGet(-1, 1, 0)), 20, ArrowDispenser));
	Traps.push_back(new TrapClass(VGet(-480, -480, 0), VNorm(VGet(1, 1, 0)), 20, ArrowDispenser));
	VillagerCountBerPercent = 0;
	ZonbieCountBerPercent = 0;
	
}
void GameCore::AllClear() {
	Villagers.clear();
	Zonbies.clear();
	Traps.clear();
	Objects.clear();
	Effects.clear();

}
void GameCore::TitleShow() {
	if (!InfoFlg) {
		MyDrawGraph(TitleImageBox, TitleImage);
		MyDrawGraph(TitleBerImageLeft, PlayImage);
		MyDrawGraph(TitleBerImageMid, InfoImage);
		MyDrawGraph(TitleBerImageRight, ExitImage);
	}
	else {
		MyDrawGraph(InfoBox, InfoUIImage);
	}
}
void GameCore::ShowMobCount(BOX Box, size_t MobSize) {
	int Image = 0;
	switch (MobSize)
	{
	case 0:
		Image = Count0Image;
		break;
	case 1:
		Image = Count1Image;
		break;
	case 2:
		Image = Count2Image;
		break;
	case 3:
		Image = Count3Image;
		break;
	case 4:
		Image = Count4Image;
		break;
	case 5:
		Image = Count5Image;
		break;
	case 6:
		Image = Count6Image;
		break;
	case 7:
		Image = Count7Image;
		break;
	case 8:
		Image = Count8Image;
		break;
	case 9:
		Image = Count9Image;
		break;
	case 10:
		Image = Count10Image;
		break;
	default:
		break;
	}
	MyDrawGraph(Box, Image);
}
void GameCore::UpdateCountBer() {
	float VillagerSize = float(Villagers.size());
	float ZonbieSize = float(Zonbies.size());
	float MobSize = VillagerSize + ZonbieSize;
	int VillagerPercent = int(VillagerSize / MobSize * 1000) ;
	int ZonbiePercent = int(ZonbieSize / MobSize * 1000) ;
	if (VillagerCountBerPercent < VillagerPercent) {
		VillagerCountBerPercent += CountBerPercentPlas;
		if (VillagerCountBerPercent > VillagerPercent)VillagerCountBerPercent = VillagerPercent;
	}
	else if (VillagerCountBerPercent < VillagerPercent) {
		VillagerCountBerPercent -= CountBerPercentPlas;
		if (VillagerCountBerPercent < VillagerPercent)VillagerCountBerPercent = VillagerPercent;
	}
	if (ZonbieCountBerPercent < ZonbiePercent) {
		ZonbieCountBerPercent += CountBerPercentPlas;
		if (ZonbieCountBerPercent > ZonbiePercent)ZonbieCountBerPercent = ZonbiePercent;
	}
	else if (ZonbieCountBerPercent > ZonbiePercent) {
		ZonbieCountBerPercent -= CountBerPercentPlas;
		if (ZonbieCountBerPercent < ZonbiePercent)ZonbieCountBerPercent = ZonbiePercent;
	}
	
	
}
