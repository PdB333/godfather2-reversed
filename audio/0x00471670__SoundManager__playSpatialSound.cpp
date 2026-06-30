// FUNC_NAME: SoundManager::playSpatialSound
int __thiscall SoundManager::playSpatialSound(int* thisPtr, int* positionVec, undefined4* outHandle)
{
    int soundInstance;
    float volume;
    undefined4 localBuffer[8]; // 32 bytes, zero-initialized if outHandle is null

    soundInstance = 0;
    // Check if position is non-zero (all components)
    if ((positionVec[0] != 0) || (positionVec[1] != 0) || (positionVec[2] != 0) || (positionVec[3] != 0))
    {
        if (outHandle == (undefined4*)0x0)
        {
            outHandle = localBuffer;
            memset(localBuffer, 0, 32);
        }
        else if (thisPtr[0x5b] != 0) // vtable? or function pointer at +0x16C
        {
            ((void (*)(int*, undefined4*))thisPtr[0x5b])(thisPtr, outHandle);
        }

        // Create sound instance from global sound system singleton (DAT_012234bc)
        soundInstance = FUN_005e4950(DAT_012234bc, outHandle);
        if (soundInstance != 0)
        {
            // Call vtable method at index 0x2E (0xB8/4) - likely "play" or "start"
            (*(void (**)(int))(*(int*)thisPtr + 0xB8))(soundInstance);

            // Get some value from a vtable method at index 0x44 (0x110/4) - maybe "getRandomVolume" or "getVolume"
            double randomVal = (*(double (**)(void))(*(int*)thisPtr + 0x110))();
            volume = DAT_00e2cb90; // Default volume threshold
            if ((DAT_00e2cb90 < randomVal) && (randomVal < 1.0))
            {
                randomVal = (*(double (**)(void))(*(int*)thisPtr + 0x110))(); // Re-query? Possibly another random
                volume = (float)randomVal;
            }
            // Set volume on the sound instance
            FUN_005e6750(soundInstance, volume);
        }
    }
    return soundInstance;
}