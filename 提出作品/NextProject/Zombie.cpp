#include"Zombie.h"
#include<list>
#include"Math.h"
Zonbie::Zonbie(int ScanModel, int Animation) {
	Position = VGet(float(rand() % 600 - 300), float(rand() % 600 - 300), 0);
	Direction = VGet(1, 0, 0);
	SetStartStatus(ScanModel, Animation);
}
Zonbie::Zonbie(VECTOR ScanPosition, VECTOR ScanDirection, int ScanModel, int Animation) {
	Position = ScanPosition;
	Direction = ScanDirection;
	SetStartStatus(ScanModel, Animation);
}
void Zonbie::SetStartStatus(int ScanModel, int Animation) {
	ViewDirection = Direction;
	MoveSpeed = 1.5;
	Scale = 20;
	NockBackSpeed = 1.2f;
	JunpSpeed = 0;
	DamageFPSCount = 0;
	Hight = 100;
	ATK = 5;
	MaxHP = 100;
	HP = MaxHP;
	Live = true;
	LiveCount = 60;
	PickUpFlg = false;
	StandFlg = true;
	AttackFlg = false;
	Model = MV1DuplicateModel(ScanModel);
	StandAnimation = MV1AttachAnim(Model, 0, Animation, FALSE);
	StandAnimationTotalTime = MV1GetAttachAnimTotalTime(Model, StandAnimation);
	StandAnimationNowTime = 0;
	StandAnimationBlend = 1;
	RunAnimation = MV1AttachAnim(Model, 4, Animation, FALSE);
	RunAnimationTotalTime = MV1GetAttachAnimTotalTime(Model, RunAnimation);
	RunAnimationNowTime = 0;
	RunAnimationBlend = 0;
	HitAnimation = MV1AttachAnim(Model, 3, Animation, FALSE);
	HitAnimationTotalTime = MV1GetAttachAnimTotalTime(Model, HitAnimation);
	HitAnimationNowTime = 0;
	HitAnimationBlend = 0;
	DeathAnimation = MV1AttachAnim(Model, 1, Animation, FALSE);
	DeathAnimationTotalTime = MV1GetAttachAnimTotalTime(Model, DeathAnimation);
	DeathAnimationNowTime = 0;
	DeathAnimationBlend = 0;
	AttackAnimation = MV1AttachAnim(Model, 2, Animation, FALSE);
	AttackAnimationTotalTime = MV1GetAttachAnimTotalTime(Model, DeathAnimation);
	AttackAnimationNowTime = 0;
	AttackAnimationBlend = 0;
	MV1SetAttachAnimTime(Model, RunAnimation, RunAnimationNowTime);
	MV1SetAttachAnimTime(Model, StandAnimation, StandAnimationNowTime);
	MV1SetAttachAnimTime(Model, HitAnimation, HitAnimationNowTime);
	MV1SetAttachAnimTime(Model, DeathAnimation, DeathAnimationNowTime);
	MV1SetAttachAnimTime(Model, AttackAnimation, AttackAnimationNowTime);
	MV1SetScale(Model, VGet(0.5f, 0.5f, 0.5f));
}
void Zonbie::ZonbieMove(std::list<Villager*> Villagers, VECTOR MapMaxPosition, VECTOR MapMinPosition, VECTOR MouseWorldPosition) {
	float NearLength = 0;
	VECTOR NearVillagerPosition;
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
			Direction = VGet(0, 0, 0);
			if (Live && Villagers.size() > 0) {
				StandFlg = false;
				for (auto ScanMob = Villagers.begin(); ScanMob != Villagers.end(); ScanMob++) {
					auto ScanVillager = *ScanMob;
					if (ScanVillager->IsLive()) {
						VECTOR VillagerPosition = ScanVillager->GetPosition();
						float ScanLength = VSize(VSub(Position, VillagerPosition));
						if ((ScanLength < NearLength) || (ScanMob == Villagers.begin())) {
							NearLength = ScanLength;
							NearVillagerPosition = VillagerPosition;
						}
					}
				}
				VECTOR ReadDirection = VNorm(VSub(NearVillagerPosition, Position));
				ReadDirection.z = 0;
				Direction = ReadDirection;
				Move();
				RunAnimationBlend += AnimationBlendCount;
				HitAnimationBlend -= AnimationBlendCount;
				StandAnimationBlend -= AnimationBlendCount;
			}
			else {
				StandFlg = true;
				RunAnimationBlend -= AnimationBlendCount;
				HitAnimationBlend -= AnimationBlendCount;
				if (Live) {
					StandAnimationBlend += AnimationBlendCount;
				}
				else {
					StandAnimationBlend -= AnimationBlendCount;
					DeathAnimationBlend += AnimationBlendCount;
				}
				
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
	if (!(Direction.x == ViewDirection.x && Direction.y == ViewDirection.y) && NockBackSpeed == 1) {
		ViewDirection = SetViewDirection(Direction, ViewDirection);
	}
	BackStage(MapMaxPosition, MapMinPosition);
}
void Zonbie::HitInvestigate(std::list<Zonbie*> Zonbies, int Number) {
	if (Number != Zonbies.size()) {
		int Count = 0;
		for (auto NextMob = Zonbies.begin(); NextMob != Zonbies.end(); NextMob++) {
			Count++;
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
			if (VSize(SubVector) <= AddScale && Number != Count && Flg) {
				VECTOR HarfPosition = VAdd(Position, VScale(SubVector, 0.5));
				VECTOR Direction = VNorm(SubVector);
				OverlapCover(HarfPosition, VScale(Direction, -1.0f), AddScale);
				HarfPosition.z = NextPosition.z;
				NextZonbie->OverlapCover(HarfPosition, Direction, AddScale);
			}
		}
	}
}
void Zonbie::ZonbieShow() {
	float AnimationBlendCount = 0.05f;
	MV1SetPosition(Model, Position);
	VECTOR ShowDirection = ViewDirection;
	MATRIX ShowMatrix = MGetRotZ(-90 * MPIRadian);
	ShowDirection = VTransform(ShowDirection, ShowMatrix);
	float radian = atan2(ShowDirection.y, ShowDirection.x);
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
	if (AttackFlg) {
		if (AttackAnimationTotalTime <= AttackAnimationNowTime) {
			AttackAnimationBlend -= AnimationBlendCount;
			if (AttackAnimationBlend <= 0) {
				AttackFlg = false;
				AttackAnimationBlend = 0;
				AttackAnimationNowTime = 0;
			}
		}
		else {
			AttackAnimationBlend += AnimationBlendCount;
			if (AttackAnimationBlend > 1)AttackAnimationBlend = 1;
			AttackAnimationNowTime += 1.5f;
			if (AttackAnimationTotalTime <= AttackAnimationNowTime) {
				AttackAnimationNowTime = AttackAnimationTotalTime;
			}
		}
		
		
	}
	if (AttackAnimationBlend > 1)AttackAnimationBlend = 1;
	if (AttackAnimationBlend <= 0) {
		AttackAnimationBlend = 0;
		AttackAnimationNowTime = 0;
	}
	if (LiveCount < 20) {
		float Scale = LiveCount * 0.025f;
		MV1SetScale(Model, VGet(Scale, Scale, Scale));
	}
	MV1SetAttachAnimBlendRate(Model, StandAnimation, StandAnimationBlend);
	MV1SetAttachAnimBlendRate(Model, RunAnimation, RunAnimationBlend);
	MV1SetAttachAnimBlendRate(Model, DeathAnimation, DeathAnimationBlend);
	MV1SetAttachAnimBlendRate(Model, HitAnimation, HitAnimationBlend);
	MV1SetAttachAnimBlendRate(Model, AttackAnimation, AttackAnimationBlend);
	if (NockBackSpeed == 1)HitAnimationNowTime = 0;
	StandAnimationNowTime += 1.0f;
	RunAnimationNowTime += 1.0f;
	DeathAnimationNowTime += 3.0f;
	HitAnimationNowTime += 2.0f;
	
	if (StandAnimationTotalTime <= StandAnimationNowTime)StandAnimationNowTime -= StandAnimationTotalTime;
	if (RunAnimationTotalTime <= RunAnimationNowTime)RunAnimationNowTime -= RunAnimationTotalTime;
	if (DeathAnimationTotalTime <= DeathAnimationNowTime)DeathAnimationNowTime = DeathAnimationTotalTime;
	if (HitAnimationTotalTime <= HitAnimationNowTime)HitAnimationNowTime = HitAnimationTotalTime;
	
	MV1SetAttachAnimTime(Model, StandAnimation, StandAnimationNowTime);
	MV1SetAttachAnimTime(Model, RunAnimation, RunAnimationNowTime);
	MV1SetAttachAnimTime(Model, DeathAnimation, DeathAnimationNowTime);
	MV1SetAttachAnimTime(Model, HitAnimation, HitAnimationNowTime);
	MV1SetAttachAnimTime(Model, AttackAnimation, AttackAnimationNowTime);
	MV1DrawModel(Model);
}
