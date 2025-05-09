#include"Effect.h"

Effect::Effect() {
	Direction = VGet(0, 0, 0);
	MoveSpeed = 0;
	playingEffectHandle = 0;
	Position = VGet(0, 0, 0);
	Scale = 0;
	Time = 0;
}
Effect::Effect(VECTOR ScanPosition, VECTOR ScanDirection, float ScanMoveSpeed, int ScanHandle) {
	Position = ScanPosition;
	Direction = ScanDirection;
	Time = 0;
	Scale = 10;
	
	playingEffectHandle = PlayEffekseer3DEffect(ScanHandle);
	MoveSpeed = ScanMoveSpeed;
	
}
void Effect::Move() {
	Time++;
	
}
void Effect::Show() {
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, Position.x, Position.y, Position.z);
}