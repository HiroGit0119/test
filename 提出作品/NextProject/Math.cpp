#include"Math.h"
VECTOR Is2DSubVector(VECTOR Scan1, VECTOR Scan2) {
	VECTOR Vector1 = Scan1;
	VECTOR Vector2 = Scan2;
	Vector1.z = 0;
	Vector2.z = 0;
	return VSub(Vector1, Vector2);
}
bool OutOfStage(VECTOR ScanPosition, float ScanScale, VECTOR MapMaxPosition, VECTOR MapMinPosition) {
	if (ScanPosition.x > MapMaxPosition.x - ScanScale)return true;
	else if (ScanPosition.x < MapMinPosition.x + ScanScale)return true;
	else if (ScanPosition.y > MapMaxPosition.y - ScanScale)return true;
	else if (ScanPosition.y < MapMinPosition.y + ScanScale)return true;
	else return false;
}
const VECTOR SetViewDirection(VECTOR ScanDirection, VECTOR ScanViewDirection) {
	VECTOR TargetDirection = ScanDirection;
	VECTOR ViewDirection = ScanViewDirection;
	bool LeftFlg = IsLeftRotate(ViewDirection, TargetDirection);
	if (LeftFlg) {
		ViewDirection = VTransform(ViewDirection, LeftRotationMatrix);
	}
	else {
		ViewDirection = VTransform(ViewDirection, RightRotationMatrix);
	}
	if (LeftFlg != IsLeftRotate(ViewDirection, TargetDirection))ViewDirection = TargetDirection;
	return ViewDirection;
}
const bool IsLeftRotate(VECTOR ViewDirection, VECTOR TargetDirection) {
	if (ViewDirection.x >= 0) {
		if (ViewDirection.y >= 0) {
			if (TargetDirection.y >= 0) {
				if (ViewDirection.x >= TargetDirection.x)return true;
			}
			else {
				if (-ViewDirection.x >= TargetDirection.x)return true;
			}
		}
		else {
			if (TargetDirection.y >= 0) {
				if (-ViewDirection.x <= TargetDirection.x)return true;
			}
			else {
				if (ViewDirection.x <= TargetDirection.x)return true;
			}
		}
	}
	else {
		if (ViewDirection.y >= 0) {
			if (TargetDirection.y >= 0) {
				if (ViewDirection.x >= TargetDirection.x)return true;
			}
			else {
				if (-ViewDirection.x >= TargetDirection.x)return true;
			}
		}
		else {
			if (TargetDirection.y >= 0) {
				if (-ViewDirection.x <= TargetDirection.x)return true;
			}
			else {
				if (ViewDirection.x <= TargetDirection.x)return true;
			}
		}
	}
	return false;
}
bool WithinMarginError(float Angle1, float Angle2) {
	if (Angle1 >= Angle2) {
		if (Angle1 - Angle2 <= RotationLength)return true;
		if (Angle1 - Angle2 >= 360 - RotationLength)return true;
	}
	else {
		if (Angle2 - Angle1 <= RotationLength)return true;
		if (Angle2 - Angle1 >= 360 - RotationLength)return true;
	}
	return false;
}
void MyDrawBox(BOX Box, int Color) {
	DrawBox(int(Box.Left), int(Box.Up), int(Box.Right), int(Box.Down), Color, true);
}
void MyDrawGraph(BOX Box, int Image) {
	DrawExtendGraph(int(Box.Left), int(Box.Up), int(Box.Right), int(Box.Down), Image, true);
}
