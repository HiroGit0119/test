#pragma once
#include"DxLib.h"
#include <iostream>
#include<list>
#include"Villager.h"
#include"Zombie.h"
enum TrapTypeEnum {
	HealDispenser, ArrowDispenser
};
class TrapClass {
protected:
	
	VECTOR Position; //位置
	VECTOR Direction; //方向ベクトル
	int Color;
	int Scale;
	bool StepFlg;
	TrapTypeEnum TrapType;
	int ProgressTime;
	int ProgressCount;
public:
	TrapClass() {
		Position = VGet(500, -500, 0);
		Direction = VGet(0, 0, 0);
		StepFlg = false;
		Scale = 20;
		Color = 0;
		ProgressCount = 0;
		ProgressTime = 0;
		TrapType = HealDispenser;
	}
	TrapClass(VECTOR, VECTOR, int, TrapTypeEnum);
	void Show();
	void Progress();
	void CoolDwon();
	bool IsHitInvestigate(std::list<Villager*> Villagers, std::list<Zonbie*> Zonbies);
	void SetArrowStatus(VECTOR& Position1, VECTOR& Position2, VECTOR& Direction1, VECTOR& Direction2);
	void SetProgressTime(int Scan) { ProgressTime = Scan; }
	void SetStepFlg(bool Scan) { StepFlg = Scan; }
	void SetDirection(VECTOR Scan) { Direction = Scan; }
	bool IsStepFlg() { return StepFlg; }
	VECTOR GetPosition() { return Position; }
	VECTOR IsDirection() { return Direction; }
	int IsScale() { return Scale; }
	TrapTypeEnum IsTrapType() { return TrapType; }
	int IsProgressCount() { return ProgressCount; }
};
