#include "Func.h"
#include "DxLib.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "SerialClass.h"
#include "erslib19.h" //�V���A���ʐM���ȒP�ɂ��Ă����w�b�_�t�@�C��


//using std::this_thread::sleep_for;

static int sceneChangeFlag = 0; //0:��ʑJ�ڂ��֎~ 1:��ʑJ�ڂ�����

static SaveData currentPlayData;

static int imageHandle = LoadGraph("images/1.png");

static SaveData allPlayData[100] = {};

static int playDataNumber = 0; //allPlayData�̗v�f�����Ǘ�����ϐ�

#define BUFSIZE 5000

static int com_h8maikon = 1;
static char buf_h8maikon[1000];
static int r_h8maikon;

static int com_shogeki_tebo = 7;
static char buf_shogeki_tebo[1000];
static int r_shogeki_tebo;

static int com_shogeki_hira = 6;
static char buf_shogeki_hira[1000];
static int r_shogeki_hira;

static char buf_current_equipment[1000];

/*
void sleep(int ms) {
	sleep_for(std::chrono::milliseconds(ms));
}
*/

static int yello = GetColor(255, 241, 0);


void timer(int second) {
    int timediff = 1;
    LONGLONG timelimit = GetNowHiPerformanceCount() + second * 1000000;
    while (timediff > 0) {
        timediff = int(timelimit - GetNowHiPerformanceCount());
        ClearDrawScreen();
        DrawFormatString(5, 5, GetColor(255, 255, 255), "%02d'%02d'%d%d", timediff / 60000000, (timediff % 60000000) / 1000000, ((timediff % 60000000) % 1000000) / 100000, (((timediff % 60000000) % 1000000) % 100000) / 10000);
        ScreenFlip();
    }
}




int Time_Get() {
    return(currentPlayData.time);
}

void Time_Draw(int x, int y, int cr) {
    //DrawFormatString(x, y, cr, "�o�ߎ���(�~���b): %d", currentPlayData.time);
    DrawFormatString(x, y+100, cr, "�o�ߎ���(h:m:s): %02d:%02d:%02d", (currentPlayData.time / 1000) /3600, ((currentPlayData.time / 1000) % 3600) / 60, (currentPlayData.time/1000) % 60);
}

void Time_Update() {
    currentPlayData.time = GetNowCount() - currentPlayData.startTime;
}



void ScoreV_Update() {
    switch (currentPlayData.equipment) {
    case tebo:
        currentPlayData.score = 10000 - currentPlayData.time + 10;
        break;
    case hirazaru:
        currentPlayData.score = 10000 - currentPlayData.time + 100;
        break;
    }
    if (currentPlayData.score < 1) {
        currentPlayData.score = 1;
    }
}

int ScoreV_Get() {
    return(currentPlayData.score);
}

void ScoreV_Finalize() {
    currentPlayData.score = 0;
}




int UseEquipment_Get() {
    return(currentPlayData.equipment);
}

void UseEquipment_Update(eKind kind) {
    currentPlayData.equipment = kind;
}

void UseEquipment_Draw(int x, int y, int cr) {
    switch (currentPlayData.equipment) {
    case tebo:
        DrawString(x, y, "�Ăڃ��[�h", cr);
        break;
    case hirazaru:
        DrawString(x, y, "�Ђ炴�郂�[�h", cr);
        break;
    }
}



int SceneChangeFlag_Get() {
    return(sceneChangeFlag);
}

void SceneChangeFlag_Allow() {
    sceneChangeFlag = 1;
}

void SceneChangeFlag_Forbid() {
    sceneChangeFlag = 0;
}




SaveData CurrentPlayData_Get() {
    return(currentPlayData);
}

void CurrentPlayData_Initialize() {
    currentPlayData = {
        GetNowCount(),
        0,
        0,
        init
    };
}




void AllPlayData_Update() {
    allPlayData[playDataNumber] = currentPlayData;
    playDataNumber = playDataNumber + 1;
}





int compar(const void* a, const void* b) {
    if (((SaveData*)a)->score < ((SaveData*)b)->score) {
        return 1;
    }
    else {
        return -1;
    }
}

void AllPlayData_Draw(int x, int y) {
    static int cr;
    qsort(allPlayData, 10, sizeof(SaveData), compar);
    DrawString(x, y-20, "���ʁ@���ԁ@�X�R�A�@���", GetColor(255, 255, 255));
    for (int i = 0; i < 10; i++) {
        if (currentPlayData.time == allPlayData[i].time) { //�����̔�r���@���܂�ǂ��Ȃ�����
            cr = GetColor(255, 255, 0);
        }
        else {
            cr = GetColor(255, 255, 255);
        }
        switch (allPlayData[i].equipment) {
        case tebo:
            DrawFormatString(x, y + i * 20, cr, "%d�� %d %d �Ă�", i + 1, allPlayData[i].time, allPlayData[i].score);
            break;
        case hirazaru:
            DrawFormatString(x, y + i * 20, cr, "%d�� %d %d �Ђ炴��", i + 1, allPlayData[i].time, allPlayData[i].score);
            break;   
        }
    }
}



void File_Output() {
    FILE* fp = fopen("savedata.dat", "wb");//�o�C�i���t�@�C�����J��
    fwrite(&currentPlayData, sizeof(SaveData), sizeof(currentPlayData) / sizeof(currentPlayData), fp); // SaveData_t�\���̂̒��g���o��
    fclose(fp);
}



void serial_initialize() {
    r_h8maikon = ERS_Open(com_h8maikon, BUFSIZE, BUFSIZE);    // rs232c�̃|�[�g���I�[�v������
    ERS_Config(com_h8maikon, ERS_9600);		// �ʐM���x��9600bps�ɂ���(�f�t�H���g)

    r_shogeki_tebo = ERS_Open(com_shogeki_tebo, BUFSIZE, BUFSIZE);
    ERS_Config(com_shogeki_tebo, ERS_9600);

    r_shogeki_hira = ERS_Open(com_shogeki_hira, BUFSIZE, BUFSIZE);
    ERS_Config(com_shogeki_hira, ERS_9600);
}


char get_buf_h8maikon() {
    DrawString(200, 100, "get_buf_h8maikon�֐����s��", yello);
    if (ERS_CheckRecv(com_h8maikon) > 0) {  // �V���A���ʐM�̎�M�f�[�^����
        r_h8maikon = ERS_Recv(com_h8maikon, buf_h8maikon, 1);
        DrawString(200, 100, "��M�f�[�^����", yello);
        return(buf_h8maikon[0]);
    } else {
        return('z');
    }
}

char get_buf_shogeki() {
    DrawString(200, 100, "get_buf_shogeki�֐����s��", yello);
    switch (currentPlayData.equipment) {
    case tebo:
        if (ERS_CheckRecv(com_shogeki_tebo) > 0) {  // �V���A���ʐM�̎�M�f�[�^����
            r_shogeki_tebo = ERS_Recv(com_shogeki_tebo, buf_shogeki_tebo, 1);
            DrawString(200, 100, "��M�f�[�^����", yello);
            return(buf_shogeki_tebo[0]);
        }        
        break;
    case hirazaru:
        if (ERS_CheckRecv(com_shogeki_hira) > 0) {  // �V���A���ʐM�̎�M�f�[�^����
            r_shogeki_hira = ERS_Recv(com_shogeki_hira, buf_shogeki_hira, 1);
            DrawString(200, 100, "��M�f�[�^����", yello);
            return(buf_shogeki_hira[0]);
        }
        break;
    default:
        return('z');
    }
    
}

void send_current_equipment() {
    buf_current_equipment[0] = 't';
    r_shogeki_tebo = ERS_Send(com_shogeki_tebo, buf_current_equipment, 1);
    buf_current_equipment[0] = 't';

}

void print_test() {
    DrawString(200, 100, "print_test", yello);
}
