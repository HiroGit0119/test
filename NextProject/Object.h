#pragma once
#include"DxLib.h"
#include <iostream>
#include"Villager.h"
#include"Zombie.h"
#include"Effect.h"
#include"Music.h"
#include"Mouse.h"
enum TypeEnum {
	NoType,HealPotion,Arrow
};
class MouseClass;
class ObjectClass {
protected:
	TypeEnum Type;
	VECTOR Position; //位置
	VECTOR Direction; //方向ベクトル
	int Color;
	float Scale;
	float MoveSpeed;
	float JunpSpeed;
	int ATK;
	bool DeliteFlg;
public:
	ObjectClass();
	ObjectClass(VECTOR ScanPosition, VECTOR ScanDirection, float ScanMoveSpeed,float ScanJumpSpeed, TypeEnum ScanType);
	~ObjectClass(){}
	void Move(VECTOR MapMaxPosition,VECTOR MapMinPosition);
	void Show();
	void HitInvestigate(std::list<Villager*> Villagers, std::list<Zonbie*> Zonbies, std::list<Effect*> Effects, MusicManagerClass& MusicManager, MouseClass& Mouse, int Hundle);
	int IsATK() { return ATK; }
	void SetDirection(VECTOR Scan) { Direction = Scan; }
	VECTOR GetPosition() { return Position; }
	VECTOR IsDirection() { return Direction; }
	float IsScale() { return Scale; }
	TypeEnum IsType() { return Type; }
	bool IsDeliteFlg() { return DeliteFlg; }
};
