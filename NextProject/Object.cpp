#include"Object.h"
#include"Math.h"
ObjectClass::ObjectClass() {

}
ObjectClass::ObjectClass(VECTOR ScanPosition, VECTOR ScanDirection, float ScanMoveSpeed, float ScanJumpSpeed, TypeEnum ScanType) {
	Position = ScanPosition;
	Direction = ScanDirection;
	MoveSpeed = ScanMoveSpeed;
	JunpSpeed = ScanJumpSpeed;
	Scale = 10;
	Type = ScanType;
	ATK = 5;
	DeliteFlg = false;

}
void ObjectClass::Move(VECTOR MapMaxPosition, VECTOR MapMinPosition) {
	if (Type == Arrow) {
		Position = VAdd(Position, VScale(Direction, MoveSpeed));
	}
	if (Type == HealPotion) {
		Position = VAdd(Position, VScale(VGet(0, 0, 1), JunpSpeed));
		JunpSpeed -= 0.1f;
	}
	if (OutOfStage(Position, Scale, MapMaxPosition, MapMinPosition))DeliteFlg=true;
}
void ObjectClass::Show() {
	if (Type == Arrow) {
		DrawSphere3D(Position, Scale, 16, GetColor(250, 250, 0), GetColor(250, 250, 250), true);
	}
	if (Type == HealPotion) {
		DrawSphere3D(Position, Scale, 16, GetColor(250, 250, 0), GetColor(250, 250, 0), true);
	}
}
void ObjectClass::HitInvestigate(std::list<Villager*> Villagers, std::list<Zonbie*> Zonbies, std::list<Effect*> Effects, MusicManagerClass& MusicManager, MouseClass& Mouse, int Hundle) {
	bool Flg = false;
	VECTOR HitPosition = Position;
	if (Position.z > 0) {
		for (auto NextMob = Villagers.begin(); NextMob != Villagers.end(); NextMob++) {
			auto NextVillager = *NextMob;
			VECTOR NextPosition = NextVillager->GetPosition();
			VECTOR SubVector = VSub(NextPosition, Position);
			float ScanScale = NextVillager->IsScale();
			float AddScale = Scale + ScanScale;
			if (VSize(SubVector) <= AddScale) {
				if (Type == Arrow) {
					//Effects.push_back(new Effect(NextPosition, VNorm(VGet(0, 0, 0)), 1, Hundle));
					if (NextVillager->IsDamageFPSCount() <= 0 && NextVillager->IsLive()) {
						NextVillager->SetNockBack(Mouse,Direction);
						NextVillager->Damage(ATK);
						MusicManager.PlayHitAroowSound();
					}
				}
				Flg = true;
				break;
			}
		}
		if (!Flg) {
			for (auto NextMob = Zonbies.begin(); NextMob != Zonbies.end(); NextMob++) {
				auto NextZonbie = *NextMob;
				VECTOR NextPosition = NextZonbie->GetPosition();
				VECTOR SubVector = VSub(NextPosition, Position);
				float ScanScale = NextZonbie->IsScale();
				float AddScale = Scale + ScanScale;
				if (VSize(SubVector) <= AddScale) {
					if (Type == Arrow) {
						if (NextZonbie->IsDamageFPSCount() <= 0 && NextZonbie->IsLive()) {
							//Effects.push_back(new Effect(NextPosition, VNorm(VGet(0, 0, 0)), 1, Hundle));
							NextZonbie->SetNockBack(Mouse,Direction);
							NextZonbie->Damage(ATK);
							MusicManager.PlayHitAroowSound();
						}
					}
					Flg = true;
					break;
				}
			}
		}
	}
	if (Flg || Position.z <= 0) {
		if (Type == HealPotion) {
			if (Position.z <= 0)Position.z = 0;
			for (auto NextMob = Villagers.begin(); NextMob != Villagers.end(); NextMob++) {
				auto NextVillager = *NextMob;
				VECTOR NextPosition = NextVillager->GetPosition();
				VECTOR SubVector = VSub(NextPosition, Position);
				float ScanScale = NextVillager->IsScale();
				float AddScale = (Scale * 5.0f) + ScanScale;
				if (VSize(SubVector) <= AddScale) {
					VECTOR Direction = VNorm(SubVector);
					NextVillager->Heal(ATK);
				}
			}
			for (auto NextMob = Zonbies.begin(); NextMob != Zonbies.end(); NextMob++) {
				auto NextZonbie = *NextMob;
				VECTOR NextPosition = NextZonbie->GetPosition();
				VECTOR SubVector = VSub(NextPosition, Position);
				float ScanScale = NextZonbie->IsScale();
				float AddScale = (Scale * 5.0f) + ScanScale;
				if (VSize(SubVector) <= AddScale) {
					VECTOR Direction = VNorm(SubVector);
					if (NextZonbie->IsDamageFPSCount() <= 0 && NextZonbie->IsLive()) {
						NextZonbie->SetNockBack(Mouse,Direction);
						NextZonbie->Damage(ATK);
					}

				}
			}
			
		}
		DeliteFlg = true;
	}
}