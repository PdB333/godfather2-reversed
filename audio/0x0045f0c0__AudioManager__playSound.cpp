// FUNC_NAME: AudioManager::playSound
char __thiscall AudioManager::playSound(int this_ptr, int soundId, int volume, int pan, int priority, char isLooping, int param7, int param8)
{
    char result;

    if (*(int *)(this_ptr + 0x218) != 0) {
        result = FUN_00571fb0(soundId, priority, pan, param7, param8); // +0x218 = pointer to audio device or mixer
        if ((result != '\0') && (isLooping != '\0')) {
            FUN_005727f0(); // possibly loop start/stop callback
        }
        return result;
    }
    return '\0';
}