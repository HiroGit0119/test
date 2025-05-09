#pragma once
#include"Mob.h"
#include"Effect.h"
#include"Music.h"
#include<list>
class MouseClass;
class Zonbie;
class Villager : public Mob {
private:
	void SetStartStatus(int ScanModel, int Animation);
	float RecognitionRange; //認識範囲
	int NoRecognitionCount;
	VECTOR NoRecognitionTargetPosition;
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

public:
	Villager(int Model, int Animation);
	Villager(VECTOR Position,VECTOR Direction,int Model, int Animation);
	~Villager(){ MV1DeleteModel(Model); }
	void VillagerMove(std::list<Zonbie*> Zonbies, VECTOR MapMaxPosition, VECTOR MapMinPosition, VECTOR MouseWorldPosition);
	void VillagerShow();
	void HitInvestigate(std::list<Villager*> Villagers, std::list<Zonbie*> Zonbies,std::list<Effect*> Effects,MusicManagerClass& MusicManager, MouseClass& Mouse, int Number, int ScanHandle);
	float IsRecognitionRange() { return RecognitionRange; }
	
};
