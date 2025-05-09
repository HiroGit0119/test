#include"Mob.h"
#include"Math.h"
void Mob::Show(bool ModelFlg) {
	MV1SetPosition(Model, Position);
	float radian = atan(Direction.y / Direction.x);
	radian *= MPIAngle;
	radian += 90;
	radian *= MPIRadian;
	MV1SetRotationXYZ(Model, VGet(90 * MPIRadian, 0, radian));
	MV1DrawModel(Model);
}
void Mob::Move() {
	if (VSize(Direction) > 0)Position = VAdd(Position, VScale(Direction, MoveSpeed * NockBackSpeed));
	Position.z += JunpSpeed;
	JunpSpeed -= 0.1f;
	if (Position.z <= 0) {
		if (JunpSpeed < -0.11)Direction = ViewDirection;
		JunpSpeed = 0;
		Position.z = 0;
		NockBackSpeed = 1;
		DamageFPSCount = 0;
	}
	if (DamageFPSCount > 0)DamageFPSCount -= 1;
}
void Mob::BackStage(VECTOR MaxStagePosition, VECTOR MinStagePosition) {
	if (Position.x > MaxStagePosition.x - Scale)Position.x = MaxStagePosition.x - Scale;
	else if (Position.x < MinStagePosition.x + Scale)Position.x = MinStagePosition.x + Scale;
	if (Position.y > MaxStagePosition.y - Scale)Position.y = MaxStagePosition.y - Scale;
	else if (Position.y < MinStagePosition.y + Scale)Position.y = MinStagePosition.y + Scale;
}
void Mob::OverlapCover(VECTOR ScanPosition,VECTOR ScanDirection, float ScanScale) {
	VECTOR SetPosition = VAdd(ScanPosition, VScale(ScanDirection, ScanScale / 2.0f));
	Position = SetPosition;
}
void Mob::SetNockBack(MouseClass& Mouse,VECTOR ScanDirection) {
	if (DamageFPSCount <= 0) {
		DamageFPSCount = 60;
		JunpSpeed = 2;
		NockBackSpeed = 2;
		Direction = ScanDirection;
		if (PickUpFlg) {
			PickUpFlg = false;
			Mouse.ReleasePickFlg();
			bool Flg;
			Flg = Mouse.IsPickFlg();
		}
		
	}
}
void Mob::Heal(int Scan) {
	if (Live) {
		HP += Scan;
		if (MaxHP > HP)HP = MaxHP;
	}
}
void Mob::DeathProgress() {
	if (Live) {
		if (HP <= 0)Live = false;
	}
	else {
		LiveCount -= 1;
	}
}
VECTOR Mob::GetPickMidPosition() {
	VECTOR ReturnPosition = Position;
	ReturnPosition.z += PickLength;
	return ReturnPosition;
}
	