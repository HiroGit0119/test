#include "FPS.h"
#include <windows.h>
#include"DxLib.h"
//�R���X�g���N�^
FPSClass::FPSClass() {
    BeforeFPSTime = GetNowCount();
}
// FPS�̃R���g���[��
void FPSClass::Controll() {
    int NowFPSTime = GetNowCount();                                //���̌o�ߎ��Ԃ����
    int WhileFPSTime = NowFPSTime - BeforeFPSTime;               //�ЂƂO�̃t���[������ǂꂾ���o�߂�����
    int AdjustmentFPSTime = int(TagetFPSTime) - WhileFPSTime;    //���̃t���[�����ǂꂾ��������
    if (AdjustmentFPSTime > 0) WaitTimer(AdjustmentFPSTime);          //�����ꍇ�x�܂��Ē�������
    BeforeFPSTime = GetNowCount();                                  //������̌o�ߎ��Ԃ�O�̌o�ߎ��ԂƂ��ċL�^
}