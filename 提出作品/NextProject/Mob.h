#pragma once
#include"DxLib.h"
#include <iostream>
#include<list>
#include"Math.h"
#include"Mouse.h"
class MouseClass;
class Mob {
protected:
	Mob() {
		Position = VGet(float(rand() % 600) - 300.0f, float(rand() % 600) - 300.0f, 0.0f);
		Direction = VGet(0.0f, 0.0f, 0.0f);
		DamageFPSCount = 0;
		Hight = 0;
		HP = 0;
		JunpSpeed = 0;
		Live = false;
		LiveCount = 0;
		MaxHP = 0;
		Model = 0;
		MoveSpeed = 0;
		NockBackSpeed = 0;
		Scale = 0;
		ViewDirection = VGet(0, 0, 0);
		PickUpFlg = false;
	}
	VECTOR Position; //位置
	VECTOR Direction; //方向ベクトル
	VECTOR ViewDirection;
	int MaxHP;
	int HP;
	float MoveSpeed;//移動スピード
	float NockBackSpeed;//ノックバックのスピード
	float JunpSpeed;
	int DamageFPSCount;
	float Scale;
	int Hight;
	bool Live;
	int LiveCount;
	bool PickUpFlg;
	int Model;
public:
	void Show(bool ModelFlg);
	void Move();
	void BackStage(VECTOR, VECTOR);
	void OverlapCover(VECTOR, VECTOR, float);
	void SetNockBack(MouseClass&,VECTOR);
	void Heal(int Scan);
	void DeathProgress();
	VECTOR GetPickMidPosition();
	void Damage(int Scan) { HP -= Scan; }
	void SetPickUpFlg(bool Scan) { PickUpFlg = Scan; }
	void SetDirection(VECTOR Scan) { Direction = Scan; }
	void SetNockBackSpeed(float Scan) { NockBackSpeed = Scan; }
	float IsNockBackSpeed() { return NockBackSpeed; }
	VECTOR GetPosition() { return Position; }
	float IsScale() { return Scale; }
	int IsHight() { return Hight; }
	int IsLiveCoune() { return LiveCount; }
	bool IsLive() { return Live; }
	int IsDamageFPSCount() { return DamageFPSCount; }
};
