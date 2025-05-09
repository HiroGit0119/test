#include"Music.h"
MusicManagerClass::MusicManagerClass() {
	ChangeVolumeSoundMem(200, NormalMusic);
	SetFrequencySoundMem(33000, CountDwonSound);
}
void  MusicManagerClass::PlayMusic() {
	PlaySoundMem(NormalMusic, DX_PLAYTYPE_LOOP);
}
void MusicManagerClass::StopMusic() {
	StopSoundMem(NormalMusic);
}
void MusicManagerClass::PlayBlowSound() {
	if(IsPlayindMusic())PlaySoundMem(BlowSound, DX_PLAYTYPE_BACK);
}
bool MusicManagerClass::IsPlayindMusic() {
	if (CheckSoundMem(NormalMusic))return true;
	else return false;
}
void MusicManagerClass::PlayPotionSound() {
	if (IsPlayindMusic())PlaySoundMem(PotionSound, DX_PLAYTYPE_BACK);
}
void MusicManagerClass::PlayShotAroowSound() {
	if (IsPlayindMusic())PlaySoundMem(ShotAroowSound, DX_PLAYTYPE_BACK);
}
void MusicManagerClass::PlayHitAroowSound() {
	if (IsPlayindMusic())PlaySoundMem(HitAroowSound, DX_PLAYTYPE_BACK);
}
void MusicManagerClass::PlayDwonSound() {
	if (IsPlayindMusic())PlaySoundMem(DwonSound, DX_PLAYTYPE_BACK);
}
void MusicManagerClass::PlayCountDwonSound() {
	PlaySoundMem(CountDwonSound, DX_PLAYTYPE_BACK);
}
void MusicManagerClass::PlayStartSound() {
	PlaySoundMem(StartSound, DX_PLAYTYPE_BACK);
}