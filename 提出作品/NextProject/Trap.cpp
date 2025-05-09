#include"Trap.h"
#include"Math.h"
TrapClass::TrapClass(VECTOR ScanPosition, VECTOR ScanDirection, int ScanScale, TrapTypeEnum ScanType) {
	Position = ScanPosition;
	Direction = ScanDirection;
	StepFlg = false;
	Scale = ScanScale;
	TrapType = ScanType;
	ProgressTime = 20;
	ProgressCount = 20;
}
void TrapClass::Show() {
	VECTOR Position1 = VGet(Position.x + Scale, Position.y + Scale, 1);
	VECTOR Position2 = VGet(Position.x - Scale, Position.y + Scale, 1);
	VECTOR Position3 = VGet(Position.x + Scale, Position.y - Scale, 1);
	VECTOR Position4 = VGet(Position.x - Scale, Position.y - Scale, 1);
	if (StepFlg) {
		DrawTriangle3D(Position1, Position2, Position3, GetColor(250, 250, 0), true);
		DrawTriangle3D(Position4, Position2, Position3, GetColor(250, 250, 0), true);
	}
	else {
		DrawTriangle3D(Position1, Position2, Position3, GetColor(0, 250, 250), true);
		DrawTriangle3D(Position4, Position2, Position3, GetColor(0, 250, 250), true);
	}
}
void TrapClass::Progress() {
	if (TrapType == ArrowDispenser) {
		ProgressTime--;
		if (ProgressTime <= 0) {
			StepFlg = false;
			ProgressCount++;
		}
	}
}
void TrapClass::CoolDwon() {
	if (TrapType == ArrowDispenser) {
		if (ProgressCount > 20)ProgressCount--;
	}
}
bool TrapClass::IsHitInvestigate(std::list<Villager*> Villagers, std::list<Zonbie*> Zonbies) {
	bool Flg = false;
	for (auto NextMob = Villagers.begin(); NextMob != Villagers.end(); NextMob++) {
		auto NextVillager = *NextMob;
		VECTOR NextPosition = NextVillager->GetPosition();
		VECTOR SubVector = VSub(NextPosition, Position);
		float ScanScale = NextVillager->IsScale();
		float AddScale = Scale + ScanScale;
		if (VSize(SubVector) <= AddScale && NextPosition.z <= 0) {
			Flg = true;
			break;
		}
	}
	if (!Flg) {
		for (auto NextMob = Zonbies.begin(); NextMob != Zonbies.end(); NextMob++) {
			auto NextZonbies = *NextMob;
			VECTOR NextPosition = NextZonbies->GetPosition();
			VECTOR SubVector = VSub(NextPosition, Position);
			float ScanScale = NextZonbies->IsScale();
			float AddScale = Scale + ScanScale;
			if (VSize(SubVector) <= AddScale && NextPosition.z <= 0) {
				Flg = true;
				break;
			}
		}
	}
	return Flg;
}
void TrapClass::SetArrowStatus(VECTOR& Position1, VECTOR& Position2, VECTOR& Direction1, VECTOR& Direction2) {
	MATRIX DirectionMatrix1 = MGetRotZ(45 * MPIRadian);
	Direction1 = VTransform(Direction, DirectionMatrix1);
	MATRIX DirectionMatrix2 = MGetRotZ(-45 * MPIRadian);
	Direction2 = VTransform(Direction, DirectionMatrix2);
	Position1 = VAdd(Position, VScale(Direction2, Scale * 2.5f));
	Position1.z += 20;
	Position2 = VAdd(Position, VScale(Direction1, Scale * 2.5f));
	Position2.z += 20;
}