// FUNC_NAME: AudioManager::playSoundForEvent
void __fastcall AudioManager::playSoundForEvent(int thisPtr)
{
    char isSoundEnabled;
    int *audioManagerPtr;
    int soundEventId;
    undefined4 soundHandle;
    undefined4 unusedParam;

    audioManagerPtr = (int *)getAudioManager(); // FUN_007ab710 - singleton getter
    isSoundEnabled = (**(code **)(*audioManagerPtr + 0x10))(0x369ac561); // virtual check: isSoundEnabled?
    if ((isSoundEnabled != '\0') && (/* stack check artifact */)) {
        soundEventId = *(int *)(thisPtr + 0x78); // +0x78: current sound event ID
        if (soundEventId == 0x53) { // 83 decimal - likely "menu_select"
            unusedParam = 0;
            soundHandle = createSoundInstance(0, 0); // FUN_006fbc40
            playSound(0xba0e3ecb, 0, soundHandle, unusedParam); // FUN_007f96a0 - hash for select sound
            releaseSoundInstance(); // FUN_006fbc70
        }
        else if (soundEventId == 0x55) { // 85 decimal - "menu_back"
            unusedParam = 0;
            soundHandle = createSoundInstance(0, 0);
            playSound(0x10426350, 0, soundHandle, unusedParam);
            releaseSoundInstance();
            return;
        }
        else {
            soundEventId = soundEventId - 0x57; // 87 decimal - "menu_confirm"
            if (soundEventId == 0) {
                soundHandle = createSoundInstance(0, 0);
                playSound(0x238c4928, 0, soundHandle, soundEventId);
                releaseSoundInstance();
                return;
            }
        }
    }
    return;
}