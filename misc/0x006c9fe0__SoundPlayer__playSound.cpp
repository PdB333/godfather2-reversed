// FUNC_NAME: SoundPlayer::playSound
void __fastcall SoundPlayer::playSound(int thisPtr)
{
    // +0x6c: soundId (int) - sound resource identifier, -1 means not set
    // Global flag DAT_00e50fb5: probably g_soundEnabled or g_audioReady
    if ((*(int *)(thisPtr + 0x6c) != -1) && (DAT_00e50fb5 != '\0')) {
        // 0x8000 = SOUND_FLAG_LOOP or SOUND_PRIORITY, 3 = channel index
        FUN_00410280(*(byte *)(thisPtr + 0x6c), 0x8000, 3);
    }
    return;
}