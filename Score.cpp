#include "Score.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Func.h"
#include <iostream>
#include <string>

using namespace std;

static int cr1 = GetColor(255, 255, 255);
//�X�V
void Score_Update() {
    ScoreV_Update();
    //sleep(100);

    /*
    if (CheckHitKey(KEY_INPUT_RETURN) != 0) { //�G���^�[�L�[��������Ă�����
        SceneChangeFlag_Forbid();
        AllPlayData_Update();
        Enter_Sound();
        SceneMgr_ChangeScene(eScene_Ranking);//�V�[���������L���O�ɕύX
    }    
    */

    if (get_buf_h8maikon() == 'a') {
        SceneMgr_ChangeScene(eScene_Ranking);
    }
}

//�`��
void Score_Draw() {
    DrawString(0, 0, "�X�R�A��ʂł��B", cr1);
    DrawString(0, 20, "Enter�L�[�������ƃ����L���O��ʂɈڂ�", cr1);
    DrawFormatString(0, 40, cr1, "�o�ߎ���(�~���b): %d", Time_Get());
    DrawFormatString(0, 60, cr1, "�X�R�A: %d", ScoreV_Get());
}