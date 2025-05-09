#pragma once
#include"DxLib.h"
class MusicManagerClass {
private:
	int NormalMusic = LoadSoundMem("../Music/NormleMusic.mp3");
	int BlowSound = LoadSoundMem("../Music/Blow.mp3");
	int PotionSound = LoadSoundMem("../Music/Potion.mp3");
	int ShotAroowSound = LoadSoundMem("../Music/ShotAroow.mp3");
	int HitAroowSound = LoadSoundMem("../Music/HitAroow.mp3");
	int DwonSound = LoadSoundMem("../Music/Down.mp3");
	int CountDwonSound = LoadSoundMem("../Music/CountDown.mp3");
	int StartSound = LoadSoundMem("../Music/Start.mp3");
	bool IsPlayindMusic();
public:
	MusicManagerClass();
	void PlayMusic();
	void StopMusic();
	void PlayBlowSound();
	void PlayPotionSound();
	void PlayShotAroowSound();
	void PlayHitAroowSound();
	void PlayDwonSound();
	void PlayCountDwonSound();
	void PlayStartSound();
};
