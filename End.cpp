#include "End.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Func.h"

//�X�V
void End_Update() {
    /*
    if (CheckHitKey(KEY_INPUT_RETURN) == 0 && SceneChangeFlag_Get() == 0) {
        SceneChangeFlag_Allow();
    }
    if (CheckHitKey(KEY_INPUT_RETURN) != 0 && SceneChangeFlag_Get() == 1) { //�G���^�[�L�[��������Ă�����
        SceneChangeFlag_Forbid();
        Enter_Sound();
        SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
    }    
    */

    if (get_buf_h8maikon() == 'a') {
        SceneMgr_ChangeScene(eScene_Menu);
    }

}

//�`��
void End_Draw() {
    DrawString(0, 0, "End��ʂł��B", GetColor(255, 255, 255));
    DrawString(0, 20, "�G���^�[�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
}