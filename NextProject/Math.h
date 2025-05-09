#pragma once
#include"DxLib.h"
#include <iostream>
#include<math.h> 
typedef struct BOX {
	float Left, Right, Up, Down;
} BOX;
__inline BOX BoxGet(VECTOR Position,float Wight,float Height)
{
	BOX Result;
	Result.Left = Position.x - Wight;
	Result.Right = Position.x + Wight;
	Result.Up = Position.y - Height;
	Result.Down = Position.y + Height;
	return Result;
}
const float WorldLength = 500.0f;
const int BrackColor = GetColor(10, 10, 10);
const int WhiteColor = GetColor(250, 250, 250);
const int VillagerColor = GetColor(250, 0, 0);
const int ZonbieColor = GetColor(0, 250, 0);
const int GrayColor = GetColor(100, 100, 100);
const VECTOR WindowSize = VGet(1500, 700, 0);
const VECTOR PickBerMidPosition = VGet(WindowSize.x * 0.5f, WindowSize.y * 0.90f, 0);
const BOX PickBerBack = BoxGet(PickBerMidPosition, WindowSize.x * 0.31f, WindowSize.y * 0.06f);
const BOX PickBerFront = BoxGet(PickBerMidPosition, WindowSize.x * 0.30f, WindowSize.y * 0.05f);
const float PickBerFrontMaxLength = PickBerFront.Right - PickBerFront.Left;
const float PotionFallLength = PickBerFrontMaxLength / 10;
const VECTOR TitleImageMidPosition = VGet(WindowSize.x * 0.50f, WindowSize.y * 0.25f, 0);
const float TitleImageLength = WindowSize.y * 0.3f;
const BOX TitleImageBox = BoxGet(TitleImageMidPosition, TitleImageLength, TitleImageLength);
const float TitleBerPositionY = WindowSize.y * 0.75f;
const float TitleBerHitWight= WindowSize.x * 0.10f;
const float TitleBerHitHeight = WindowSize.x * 0.05f;
const float TitleBerImageWight = WindowSize.x * 0.15f;
const float TitleBerImageHeight = WindowSize.x * 0.10f;
const VECTOR TitleBerPositionLeft = VGet(WindowSize.x * 0.25f, TitleBerPositionY, 0);
const VECTOR TitleBerPositionMid = VGet(WindowSize.x * 0.50f, TitleBerPositionY, 0);
const VECTOR TitleBerPositionRight = VGet(WindowSize.x * 0.75f, TitleBerPositionY, 0);
const BOX TitleBerHitLeft = BoxGet(TitleBerPositionLeft, TitleBerHitWight, TitleBerHitHeight);
const BOX TitleBerHitMid = BoxGet(TitleBerPositionMid, TitleBerHitWight, TitleBerHitHeight);
const BOX TitleBerHitRight = BoxGet(TitleBerPositionRight, TitleBerHitWight, TitleBerHitHeight);
const BOX TitleBerImageLeft = BoxGet(TitleBerPositionLeft, TitleBerImageWight, TitleBerImageHeight);
const BOX TitleBerImageMid = BoxGet(TitleBerPositionMid, TitleBerImageWight, TitleBerImageHeight);
const BOX TitleBerImageRight = BoxGet(TitleBerPositionRight, TitleBerImageWight, TitleBerImageHeight);
const VECTOR ScreenMidPosition = VGet(WindowSize.x * 0.5f, WindowSize.y * 0.5f, 0);
const float InfoUILength = WindowSize.y * 0.4f;
const BOX InfoBox = BoxGet(ScreenMidPosition, InfoUILength, InfoUILength);
const float CountPositionY = WindowSize.y * 0.15f;
const float CountLength = WindowSize.x * 0.05f;
const float MariaPositionX = WindowSize.x * 0.1f;
const float ZonbiePositionX = WindowSize.x * 0.9f;
const BOX MariaCountBox = BoxGet(VGet(MariaPositionX, CountPositionY, 0), CountLength, CountLength);
const BOX ZonbieCountBox = BoxGet(VGet(ZonbiePositionX, CountPositionY, 0), CountLength, CountLength);
const float CountCircleLength = WindowSize.x * 0.2f;
const VECTOR CountBerMidPosition = VGet(WindowSize.x * 0.5f, CountPositionY, 0);
const float NamePositionY = WindowSize.y * 0.05f;
const VECTOR MariaNamePosition = VGet(MariaPositionX, NamePositionY, 0);
const VECTOR ZonbieNamePosition = VGet(ZonbiePositionX, NamePositionY, 0);
const float NameHeight = WindowSize.y * 0.05f;
const float NameWight = NameHeight * 2;
const BOX MariaNameBox = BoxGet(MariaNamePosition, NameWight, NameHeight);
const BOX ZonbieNameBox = BoxGet(ZonbieNamePosition, NameWight, NameHeight);
const float CountBerOutWight = WindowSize.x * 0.31f;
const float CountBerOutHeight = WindowSize.y * 0.06f;
const float CountBerInWight = WindowSize.x * 0.3f;
const float CountBerInHeight = WindowSize.y * 0.05f;
const float CountBerLength = CountBerInWight * 2.0f;
const BOX CountBerOut = BoxGet(CountBerMidPosition, CountBerOutWight, CountBerOutHeight);
const BOX CountBerIn = BoxGet(CountBerMidPosition, CountBerInWight, CountBerInHeight);
const float WinsLength = WindowSize.y * 0.30f;
const BOX WinsBox = BoxGet(ScreenMidPosition, WinsLength, WinsLength);
const int CountBerPercentPlas = 3;

const float MyPI = 3.14159265358979323846264338327950288f;
const float MPIRadian = MyPI / 180.0f;
const float MPIAngle = 180.0f / MyPI;
const float RotationLength = 5.0f;
const MATRIX LeftRotationMatrix= MGetRotZ(RotationLength * MPIRadian);
const MATRIX RightRotationMatrix = MGetRotZ(-RotationLength * MPIRadian);
const VECTOR MidPosition = VGet(WindowSize.x / 2, WindowSize.y / 2, 0);
const float PercentLength = WindowSize.x / 400.0f;
const float PickLength = 50.0f;
const float PickScale = 20.0f;
const float MobHeight = 100.0f;
const float PotionFallCost = 100.0f;
VECTOR Is2DSubVector(VECTOR, VECTOR);
bool OutOfStage(VECTOR, float, VECTOR, VECTOR);
const VECTOR SetViewDirection(VECTOR ScanDirection, VECTOR ScanViewDirection);
const bool IsLeftRotate(VECTOR ViewDirection, VECTOR TargetDirection);
bool WithinMarginError(float Angle1, float Angle2);
void MyDrawBox(BOX Box, int Color);
void MyDrawGraph(BOX Box, int Image);