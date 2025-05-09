#include"Villager.h"
#include"Zombie.h"

Villager::Villager(int ScanModel,int Animation) {
	Position = VGet(rand() % 600 - 300.0f, rand() % 600 - 300.0f, 0.0f);
	Direction = VGet(1, 0, 0);
	SetStartStatus(ScanModel, Animation);
}
Villager::Villager(VECTOR ScanPosition, VECTOR ScanDirection, int ScanModel, int Animation) {
	Position = ScanPosition;
	Direction = ScanDirection;
	SetStartStatus(ScanModel, Animation);
}

void Villager::SetStartStatus(int ScanModel, int Animation) {
	ViewDirection = Direction;
	MoveSpeed = 1.5;
	RecognitionRange = 200;
	Scale = 20;
	NockBackSpeed = 1.2f;
	JunpSpeed = 0;
	DamageFPSCount = 0;
	Hight = 100;
	MaxHP = 100;
	HP = MaxHP;
	Live = true;
	LiveCount = 60;
	NoRecognitionCount = 0;
	NoRecognitionTargetPosition = VGet(0, 0, 0);
	PickUpFlg = false;
	Model = MV1DuplicateModel(ScanModel);
	StandAnimation = MV1AttachAnim(Model, 1, Animation, FALSE);
	StandAnimationTotalTime = MV1GetAttachAnimTotalTime(Model, StandAnimation);
	StandAnimationNowTime = 0;
	StandAnimationBlend = 1;
	RunAnimation = MV1AttachAnim(Model, 0, Animation, FALSE);
	RunAnimationTotalTime = MV1GetAttachAnimTotalTime(Model, RunAnimation);
	RunAnimationNowTime = 0;
	RunAnimationBlend = 0;
	HitAnimation = MV1AttachAnim(Model, 3, Animation, FALSE);
	HitAnimationTotalTime = MV1GetAttachAnimTotalTime(Model, HitAnimation);
	HitAnimationNowTime = 0;
	HitAnimationBlend = 0;
	DeathAnimation = MV1AttachAnim(Model, 2, Animation, FALSE);
	DeathAnimationTotalTime = MV1GetAttachAnimTotalTime(Model, DeathAnimation);
	DeathAnimationNowTime = 0;
	DeathAnimationBlend = 0;
	MV1SetAttachAnimTime(Model, RunAnimation, RunAnimationNowTime);
	MV1SetAttachAnimTime(Model, StandAnimation, StandAnimationNowTime);
	MV1SetAttachAnimTime(Model, HitAnimation, HitAnimationNowTime);
	MV1SetAttachAnimTime(Model, DeathAnimation, DeathAnimationNowTime);
	MV1SetScale(Model, VGet(0.5f, 0.5f, 0.5f));
}
void Villager::VillagerMove(std::list<Zonbie*> Zonbies, VECTOR MapMaxPosition, VECTOR MapMinPosition, VECTOR MouseWorldPosition) {
	VECTOR AddDirection = VScale(VNorm(Position), 0.1f);
	bool RecognitionFlg = false;
	float AnimationBlendCount = 0.05f;
	if (PickUpFlg) {
		Position = MouseWorldPosition;
		Position.z -= PickLength - 2;
		RunAnimationBlend += AnimationBlendCount;
		HitAnimationBlend -= AnimationBlendCount;
		StandAnimationBlend -= AnimationBlendCount;
	}
	else {
		if (NockBackSpeed == 1) {
			if (Live) {
				for (auto ScanMob = Zonbies.begin(); ScanMob != Zonbies.end(); ScanMob++) {
					auto ScanZonbie = *ScanMob;
					VECTOR SubVECTOR = VSub(ScanZonbie->GetPosition(), Position);
					if (VSize(SubVECTOR) <= RecognitionRange) {
						AddDirection = VAdd(AddDirection, VNorm(SubVECTOR));
						RecognitionFlg = true;
					}
				}
				if (RecognitionFlg) {
					NoRecognitionCount = 0;
					AddDirection.z = 0;
					AddDirection = VNorm(AddDirection);
					AddDirection = VScale(AddDirection, -1);
					SetDirection(AddDirection);
					Move();
					HitAnimationBlend -= AnimationBlendCount;
					StandAnimationBlend -= AnimationBlendCount;
					RunAnimationBlend += AnimationBlendCount;
				}
				else {
					if (NoRecognitionCount < 120) {
						NoRecognitionCount++;
						if (NoRecognitionCount >= 120) {
							int MapSize = int(MapMaxPosition.x) * 2;
							NoRecognitionTargetPosition = VGet((rand() % MapSize) / 2.0f, (rand() % MapSize) / 2.0f, 0.0f);
						}
						HitAnimationBlend -= AnimationBlendCount;
						StandAnimationBlend += AnimationBlendCount;
						RunAnimationBlend -= AnimationBlendCount;
					}
					else {
						VECTOR NoRecognition = VSub(NoRecognitionTargetPosition, Position);
						NoRecognition = VNorm(NoRecognition);
						SetDirection(NoRecognition);
						Move();
						if (VSize(VSub(NoRecognitionTargetPosition, Position)) <= 10)NoRecognitionCount = 0;
						HitAnimationBlend -= AnimationBlendCount;
						StandAnimationBlend -= AnimationBlendCount;
						RunAnimationBlend += AnimationBlendCount;
					}
				}
			}
			else {
				DeathAnimationBlend += AnimationBlendCount;
				RunAnimationBlend -= AnimationBlendCount;
				StandAnimationBlend -= AnimationBlendCount;
				HitAnimationBlend -= AnimationBlendCount;
			}
		}
		else {
			Move();
			if (Live) {
				HitAnimationBlend += AnimationBlendCount;
			}
			else {
				DeathAnimationBlend += AnimationBlendCount;
				HitAnimationBlend -= AnimationBlendCount;
			}
			RunAnimationBlend -= AnimationBlendCount;
			StandAnimationBlend -= AnimationBlendCount;
		}
	}
	if (!(Direction.x == ViewDirection.x && Direction.y == ViewDirection.y)&&NockBackSpeed==1) {
		ViewDirection = SetViewDirection(Direction, ViewDirection);
	}
	BackStage(MapMaxPosition, MapMinPosition);
}
void Villager::VillagerShow() {
	MV1SetPosition(Model, Position);
	VECTOR ShowDirection = ViewDirection;
	MATRIX ShowMatrix = MGetRotZ(-90 * MPIRadian);
	ShowDirection = VTransform(ShowDirection, ShowMatrix);
	float radian = atan2(ShowDirection.y , ShowDirection.x);
	MV1SetRotationXYZ(Model, VGet(90 * MPIRadian, 0, radian));
	if (StandAnimationBlend > 1)StandAnimationBlend = 1;
	if (StandAnimationBlend <= 0) {
		StandAnimationBlend = 0;
		StandAnimationNowTime = 0;
	}
	if (RunAnimationBlend > 1)RunAnimationBlend = 1;
	if (RunAnimationBlend <= 0) {
		RunAnimationBlend = 0;
		RunAnimationNowTime = 0;
	}
	if (DeathAnimationBlend > 1)DeathAnimationBlend = 1;
	if (DeathAnimationBlend <= 0) {
		DeathAnimationBlend = 0;
		DeathAnimationNowTime = 0;
	}
	if (HitAnimationBlend > 1)HitAnimationBlend = 1;
	if (HitAnimationBlend <= 0) {
		HitAnimationBlend = 0;
		HitAnimationNowTime = 0;
	}
	if (LiveCount < 20) {
		float Scale = LiveCount * 0.025f;
		MV1SetScale(Model, VGet(Scale, Scale, Scale));
	}
	MV1SetAttachAnimBlendRate(Model, StandAnimation, StandAnimationBlend);
	MV1SetAttachAnimBlendRate(Model, RunAnimation, RunAnimationBlend);
	MV1SetAttachAnimBlendRate(Model, DeathAnimation, DeathAnimationBlend);
	MV1SetAttachAnimBlendRate(Model, HitAnimation, HitAnimationBlend);
	StandAnimationNowTime += 1.0f;
	RunAnimationNowTime += 1.0f;
	DeathAnimationNowTime += 1.0f;
	HitAnimationNowTime += 0.9f;
	if (StandAnimationTotalTime <= StandAnimationNowTime)StandAnimationNowTime -= StandAnimationTotalTime;
	if (RunAnimationTotalTime <= RunAnimationNowTime)RunAnimationNowTime -= RunAnimationTotalTime;
	if (DeathAnimationTotalTime <= DeathAnimationNowTime)DeathAnimationNowTime -= DeathAnimationTotalTime;
	if (HitAnimationTotalTime <= HitAnimationNowTime)HitAnimationNowTime = HitAnimationTotalTime;
	if (NockBackSpeed == 1)HitAnimationNowTime = 0;
	MV1SetAttachAnimTime(Model, StandAnimation, StandAnimationNowTime);
	MV1SetAttachAnimTime(Model, RunAnimation, RunAnimationNowTime);
	MV1SetAttachAnimTime(Model, DeathAnimation, DeathAnimationNowTime);
	MV1SetAttachAnimTime(Model, HitAnimation, HitAnimationNowTime);
	MV1DrawModel(Model);
	//DrawFormatString(100, 150, GetColor(250, 250, 250), "%d", MV1GetAnimNum(Model));
	
	//DrawFormatString(100, 100, GetColor(250, 250, 250), "%f", MV1GetAttachAnimBlendRate(Model, RunAnimation));
}
void Villager::HitInvestigate(std::list<Villager*> Villagers, std::list<Zonbie*> Zonbies, std::list<Effect*> Effects, MusicManagerClass& MusicManager, MouseClass& Mouse, int Number, int ScanHandle) {
	if (Number != Villagers.size()) {
		int Count = 0;
		for (auto NextMob = Villagers.begin(); NextMob != Villagers.end(); NextMob++) {
			Count++;
			auto NextVillager = *NextMob;
			VECTOR NextPosition = NextVillager->GetPosition();
			VECTOR SubVector = Is2DSubVector(NextPosition, Position);
			float ScanScale = NextVillager->IsScale();
			float AddScale = Scale + ScanScale;
			bool Flg = false;
			if (Position.z <= NextPosition.z) {
				if (Position.z + Hight > NextPosition.z)Flg = true;
			}
			else {
				if (NextPosition.z + NextVillager->IsHight() > Position.z)Flg = true;
			}
			if (VSize(SubVector) <= AddScale && Number != Count && Flg) {
				VECTOR HarfPosition = VAdd(Position, VScale(SubVector, 0.5));
				VECTOR Direction = VNorm(SubVector);
				OverlapCover(HarfPosition, VScale(Direction, -1), AddScale);
				HarfPosition.z = NextPosition.z;
				NextVillager->OverlapCover(HarfPosition, Direction, AddScale);
			}
		}
	}
	for (auto NextMob = Zonbies.begin(); NextMob != Zonbies.end(); NextMob++) {
		auto NextZonbie = *NextMob;
		VECTOR NextPosition = NextZonbie->GetPosition();
		VECTOR SubVector = Is2DSubVector(NextPosition, Position);
		float ScanScale = NextZonbie->IsScale();
		float AddScale = Scale + ScanScale;
		bool Flg = false;
		if (Position.z <= NextPosition.z) {
			if (Position.z + Hight > NextPosition.z)Flg = true;
		}
		else {
			if (NextPosition.z + NextZonbie->IsHight() > Position.z)Flg = true;
		}
		if (VSize(SubVector) <= AddScale && Flg) {
			VECTOR HarfPosition = VAdd(Position, VScale(SubVector, 0.5));
			VECTOR Direction = VNorm(SubVector);
			OverlapCover(HarfPosition, VScale(Direction, -1), AddScale);
			HarfPosition.z = NextPosition.z;
			NextZonbie->OverlapCover(HarfPosition, Direction, AddScale);
			if (DamageFPSCount <= 0) {
				//Effects.push_back(new Effect(Position, VGet(0, 0, 0), 1, ScanHandle));
				MusicManager.PlayBlowSound();
				SetNockBack(Mouse,VScale(Direction, -1));
				
				Damage(NextZonbie->IsATK());
				HitAnimationNowTime = 0;
				NextZonbie->AttackAnimationStart();
			}
		}
	}
}
