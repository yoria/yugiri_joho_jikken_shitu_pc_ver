#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Menu.h"
#include "Score.h"
#include "Ranking.h"
#include "End.h"
#include "SceneMgr.h"

static eScene Scene = eScene_Menu;    //�V�[���Ǘ��ϐ�

//�X�V
void SceneMgr_Update() {
    switch (Scene) {       //�V�[���ɂ���ď����𕪊�
    case eScene_Menu:    //���݂̉�ʂ����j���[�Ȃ�
        Menu_Update();   //���j���[��ʂ̍X�V����������
        break;//�ȉ���
    case eScene_Game:
        Game_Update();
        break;
    case eScene_Score:
        Score_Update();
        break;
    case eScene_Ranking:
        Ranking_Update();
        break;
    case eScene_End:
        End_Update();
        break;
    case eScene_Config:
        Config_Update();
        break;
    }
}

//�`��
void SceneMgr_Draw() {
    switch (Scene) {      //�V�[���ɂ���ď����𕪊�
    case eScene_Menu:   //���݂̉�ʂ����j���[��ʂȂ�
        Menu_Draw();    //���j���[��ʂ̕`�揈��������
        break;//�ȉ���
    case eScene_Game:
        Game_Draw();
        break;
    case eScene_Score:
        Score_Draw();
        break;
    case eScene_Ranking:
        Ranking_Draw();
        break;
    case eScene_End:
        End_Draw();
        break;
    case eScene_Config:
        Config_Draw();
        break;
    }
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr_ChangeScene(eScene NextScene) {
    Scene = NextScene;
}
