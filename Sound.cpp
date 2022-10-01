#include "DxLib.h"

static int opening_handle;
static int enter_handle;

void Sound_Initialize() {
    opening_handle = LoadSoundMem("sounds/���[��������o��.mp3");
    enter_handle = LoadSoundMem("sounds/����A�{�^������1.mp3");
}

void Opening_Sound() {
    PlaySoundMem(opening_handle, DX_PLAYTYPE_BACK);
}

void Enter_Sound() {
    PlaySoundMem(enter_handle, DX_PLAYTYPE_BACK);
}