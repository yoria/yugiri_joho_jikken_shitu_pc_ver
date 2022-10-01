#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"
#include "Game.h"
#include "Func.h"
#include "Sound.h"
// #include "erslib19.h" //�V���A���ʐM���ȒP�ɂ��Ă����w�b�_�t�@�C��


//�V���A���ʐM�̂��߂ɕK�{�ȕϐ�4��
/*
#define BUFSIZE 5000
static int com = 1;
static char buf[1000];
static int r;
*/

static int yello = GetColor(255, 241, 0);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    int MouseInput;

    ChangeWindowMode(FALSE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    serial_initialize();
    Game_Initialize(); //�V���A���ʐM�̏���    

    Sound_Initialize(); //�T�E���h�ǂݍ��݁i���ł��g�����Ԃɂ��Ă����j
    Opening_Sound();
    
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        Keyboard_Update();
        SceneMgr_Update();
        SceneMgr_Draw();
        /*
        DrawString(200, 100, "test", yello);
        int i = 100;
        if (ERS_CheckRecv(com) > 0) {  // �V���A���ʐM�̎�M�f�[�^����
            
            DrawString(200, i, "��M�f�[�^����", yello);
            r = ERS_Recv(com, buf, 1);
            set_buf(buf[0]);
            r = get_buf();
            DrawFormatString(200, i + 20, GetColor(255, 255, 255), "r�̒l�F%d", r);
            DrawFormatString(200, i + 40, GetColor(255, 255, 255), "buf[0]�̒l�F%c", buf[0]);
            DrawFormatString(200, i + 60, GetColor(255, 255, 255), "buf[1]�̒l�F%c", buf[1]);
            if (buf[0] < 920) {
                DrawString(200, 100, "buf[0]�͐��l�f�[�^�ł�", GetColor(254, 247, 240));
            }
            if (buf[0] == 'a') {
                DrawString(250, i, "a����������������������������������������", yello);
            }
        }          
        */
      
    }
    DxLib_End();
    return 0;
}