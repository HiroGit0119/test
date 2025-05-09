#pragma once
#include <DxLib.h>
#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include <EffekseerForDXLib.h>
#include <iostream>

class Effect {
private:
	VECTOR Position;
	VECTOR Direction;
	float MoveSpeed;
	int Time;
	float Scale;
	int playingEffectHandle;
public:
	Effect();
	Effect(VECTOR Position, VECTOR Direction, float ScanScale, int ScanHandle);
	~Effect() {}
	void Show();
	void Move();
	int IsTime() { return Time; }
};
