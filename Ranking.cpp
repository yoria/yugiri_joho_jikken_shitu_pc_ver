#include "Ranking.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Func.h"
//�X�V

void Ranking_Update() {
    //sleep(100);
    /*
    if (CheckHitKey(KEY_INPUT_RETURN) == 0 && SceneChangeFlag_Get() == 0) {
        SceneChangeFlag_Allow();
    }
    if (CheckHitKey(KEY_INPUT_RETURN) != 0 && SceneChangeFlag_Get() == 1) {
        SceneChangeFlag_Forbid();
        Enter_Sound();
        SceneMgr_ChangeScene(eScene_End);//�V�[�����I����ʂɕύX
    }    
    */
    if (get_buf_h8maikon() == 'a') {
        SceneMgr_ChangeScene(eScene_End);
    }

}

//�`��
void Ranking_Draw() {
    DrawString(0, 0, "�����L���O��ʂł��B", GetColor(255, 255, 255));
    DrawString(0, 20, "Enter�L�[�������ƏI����ʂɈڂ�", GetColor(255, 255, 255));
    AllPlayData_Draw(0, 80);
}