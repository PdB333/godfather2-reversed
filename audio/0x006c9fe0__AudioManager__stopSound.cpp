// FUNC_NAME: AudioManager::stopSound
void __fastcall AudioManager::stopSound(int this)
{
    if ((*(int *)(this + 0x6c) != -1) && (DAT_00e50fb5 != '\0')) {
        // +0x6c: soundId (index into active sound table)
        // 0x8000 = STOP_FLAG, 3 = STOP_MODE_IMMEDIATE
        FUN_00410280(*(undefined1 *)(this + 0x6c), 0x8000, 3);
    }
}