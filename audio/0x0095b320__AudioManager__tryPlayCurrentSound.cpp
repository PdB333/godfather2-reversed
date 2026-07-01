// FUNC_NAME: AudioManager::tryPlayCurrentSound
// Function at 0x0095b320 - Attempts to play a sound based on current index stored in object
void __thiscall AudioManager::tryPlayCurrentSound(int param_2)
{
    // +0xC0: current sound index (-1 = invalid)
    uint currentSoundIndex = *(uint *)(this + 0xC0);
    if (currentSoundIndex != 0xFFFFFFFF && currentSoundIndex < *(uint *)(this + 0x68)) // +0x68: number of sounds
    {
        // +0x64 (base 100): pointer to array of sound object pointers
        int* pSoundList = *(int **)(this + 100);
        int soundObject = FUN_006b0ee0(pSoundList[currentSoundIndex]); // ResolveSoundObject
        if (soundObject != 0)
        {
            char isAudioActive = FUN_006b4440(); // Global audio enabled check
            if (isAudioActive != 0)
            {
                // +0x48 in sound object: handle/ID used to get component
                int soundComponent = FUN_00849cf0(*(int *)(soundObject + 0x48)); // GetSoundComponent
                if (soundComponent != 0)
                {
                    byte flags = *(byte *)(soundComponent + 0x58); // +0x58 flags byte
                    if ((~flags & 1) == 0) // Bit0 clear means component is not disabled
                    {
                        FUN_0097b440(*(int *)(soundObject + 0x48), soundObject + 0x10, param_2, DAT_00d5e288); // PlaySoundInternal(handle, param2, globalVolume)
                    }
                }
            }
        }
    }
    return;
}