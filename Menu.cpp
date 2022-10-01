#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "Func.h"

const static int PLAY_Y = 240;
const static int TEBO_Y = 260;
const static int HIRAZARU_Y = 280;
const static int EXPLANATION_Y = 300;
const static int RANKING_Y = 320;


typedef enum {
    eMenu_TEBO,
    eMenu_HIRAZARU,
    eMenu_EXPLANATION,    //�������
    eMenu_RANKING,
    eMenu_Num,        //�{���ڂ̐�
} eMenu;

int imageHandle = LoadGraph("images/1.png");

static int NowSelect = eMenu_TEBO;    //���݂̑I�����(�����̓Q�[���I��)
//static i
//�X�V
void Menu_Update() {
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {//���L�[��������Ă�����
        NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
    }
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
        NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
    }       
    print_test();
 

    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
        switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
        case eMenu_TEBO:
            CurrentPlayData_Initialize();
            UseEquipment_Update(tebo);
            Enter_Sound();
            SceneMgr_ChangeScene(eScene_Game);
            break;
        case eMenu_HIRAZARU:
            CurrentPlayData_Initialize();
            UseEquipment_Update(hirazaru);
            Enter_Sound();
            SceneMgr_ChangeScene(eScene_Game);
            break;
        case eMenu_EXPLANATION:
            Enter_Sound();
            SceneMgr_ChangeScene(eScene_Config);
            break;
        case eMenu_RANKING:
            Enter_Sound();
            SceneMgr_ChangeScene(eScene_Ranking);
        }
    }
}

//�`��
void Menu_Draw() {
    int imageHandle = LoadGraph("images/1.png");
    DrawGraph(0, 0, imageHandle, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��

    DrawString(200, 150, "���j���[��ʂł��B", GetColor(255, 255, 255));
    DrawString(200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor(255, 255, 255));
    DrawString(280, PLAY_Y, "�v���C", GetColor(255, 255, 255));
    DrawString(280, TEBO_Y, "�Ă�", GetColor(255, 255, 255));
    DrawString(280, HIRAZARU_Y, "���U��", GetColor(255, 255, 255));
    DrawString(280, EXPLANATION_Y, "�������", GetColor(255, 255, 255));
    DrawString(280, RANKING_Y, "�����L���O", GetColor(255, 255, 255));
    DrawFormatString(0, 400, GetColor(255, 255, 255), "%d", NowSelect);
    int y = 0;
    switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
    case eMenu_TEBO:
        y = TEBO_Y;
        break;
    case eMenu_HIRAZARU:
        y = HIRAZARU_Y;
        break;
    case eMenu_EXPLANATION:
        y = EXPLANATION_Y;
        break;
    case eMenu_RANKING:
        y = RANKING_Y;
        break;
    }
    DrawString(250, y, "��", GetColor(255, 255, 255));
}
