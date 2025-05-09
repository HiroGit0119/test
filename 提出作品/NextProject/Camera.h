#pragma once
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include <EffekseerForDXLib.h>
#include <iostream>
#include"Math.h"
class CameraClass {
private:
	VECTOR Position;
	VECTOR ViewPosition;
	VECTOR PlayPosition;
	VECTOR PlayViewPosition;
	VECTOR UpVec = VGet(0, 1, 0);
	VECTOR TitleStartPosition;
	MATRIX TitleTransformMatrix = MGetRotZ(0.2 * MPIRadian);
	float AngleX = 0;
	float AngleY = 0;
	float AngleZ = 0;
public:
	CameraClass();
	void SetPosition();
	void SetPlayPosition();
	void SetTitlePosition();
	void MoveTitlePosition();
	void MoveCountDwon(float CountDwon);
	void MoveGameOver();
	void DebagBiew();
	VECTOR IsPosition() { return Position; }
};
