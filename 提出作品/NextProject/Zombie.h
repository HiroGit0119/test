#pragma once
#include<list>
#include"Mob.h"
#include"Villager.h"
class Mob;
class Zonbie : public Mob {
private:
	void SetStartStatus(int ScanModel, int Animation);
	int ATK;
	int StandAnimation;
	float StandAnimationTotalTime;
	float StandAnimationNowTime;
	float StandAnimationBlend;
	int RunAnimation;
	float RunAnimationTotalTime;
	float RunAnimationNowTime;
	float RunAnimationBlend;
	int HitAnimation;
	float HitAnimationTotalTime;
	float HitAnimationNowTime;
	float HitAnimationBlend;
	int DeathAnimation;
	float DeathAnimationTotalTime;
	float DeathAnimationNowTime;
	float DeathAnimationBlend;
	int AttackAnimation;
	float AttackAnimationTotalTime;
	float AttackAnimationNowTime;
	float AttackAnimationBlend;
	bool AttackFlg;
	bool StandFlg;
public:
	Zonbie(int ScanModel, int Animation);
	Zonbie(VECTOR Position, VECTOR Direction, int ScanModel, int Animation);
	void ZonbieMove(std::list<Villager*> Villagers, VECTOR MapMaxPosition, VECTOR MapMinPosition, VECTOR MouseWorldPosition);
	void ZonbieShow();
	void HitInvestigate(std::list<Zonbie*> Zonbies, int Number);
	int IsATK() { return ATK; }
	void AttackAnimationStart() {
		AttackFlg = true;
		AttackAnimationNowTime = 0;
	}
};
