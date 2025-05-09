#include"Camera.h"
#include<cmath>
#include "EffekseerForDXLib.h"
CameraClass::CameraClass() {
	PlayPosition = VGet(0, 1000, 800);
	PlayViewPosition = VGet(0, 0, 0);
	TitleStartPosition = VGet(0, 500,400);
	Position = VGet(0, 0, 0);
	ViewPosition = VGet(0, 0, 0);
}
void CameraClass::SetPosition() {
	VECTOR Direction = VNorm(VSub(ViewPosition, Position));
	AngleY = atan2f(Direction.x, Direction.z);
	AngleX = sqrtf(Direction.x * Direction.x + Direction.z * Direction.z);
	AngleX = atan2f(-Direction.y, AngleX);
	AngleZ = atan2f(Direction.x, Direction.y);
	SetCameraPositionAndAngle(Position, AngleX, AngleY, AngleZ);
	SetCameraNearFar(10, 10000);
	Effekseer_Sync3DSetting();
}
void CameraClass::SetPlayPosition() {
	Position = PlayPosition;
	ViewPosition = PlayViewPosition;
}
void CameraClass::SetTitlePosition() {
	Position = TitleStartPosition;
	ViewPosition = PlayViewPosition;
}
void CameraClass::MoveTitlePosition() {
	Position = VTransform(Position, TitleTransformMatrix);
}
void CameraClass::MoveCountDwon(float CountDwon) {
	if (CountDwon > 120.0f) {
		Position = VGet(100.0f, -300.0f + ((CountDwon - 120.0f)) * 10.0f,50.0f);
		ViewPosition= VGet(200.0f, -300.0f + ((CountDwon - 120.0f)) * 10.0f, 50.0f);
	}
	else if (CountDwon > 60.0f) {
		Position = VGet(-100.0f, 300.0f - ((CountDwon - 60.0f)) * 10.0f, 50.0f);
		ViewPosition = VGet(-200.0f, 300.0f - ((CountDwon - 60.0f)) * 10.0f, 50.0f);
	}
	else if (CountDwon == 60.0f) {
		Position = PlayPosition;
		Position.z += 1000.0f;
		ViewPosition = PlayViewPosition;
		ViewPosition.z += 1500.0f;
	}
	else if (CountDwon > 10.0f) {
		Position.z -= (Position.z - PlayPosition.z) / (CountDwon - 10.0f);
		ViewPosition.z -= (ViewPosition.z - PlayViewPosition.z) / (CountDwon - 10.0f);
	}
}
void CameraClass::MoveGameOver() {
	ViewPosition.z += 20;
}
void CameraClass::DebagBiew() {
	DrawFormatString(10, 20, GetColor(250, 250, 250), "[%f,%f,%f]", AngleX, AngleY, AngleZ);
	DrawFormatString(10, 120, GetColor(250, 250, 250), "[%f,%f,%f]", Position.x, Position.y, Position.z);
	DrawFormatString(10, 220, GetColor(250, 250, 250), "[%f,%f,%f]", ViewPosition.x, ViewPosition.y, ViewPosition.z);
}