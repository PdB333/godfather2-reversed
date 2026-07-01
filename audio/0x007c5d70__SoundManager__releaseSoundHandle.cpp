// FUNC_NAME: SoundManager::releaseSoundHandle
void __fastcall SoundManager::releaseSoundHandle(int thisPtr)
{
    int *soundHandlePtr = (int *)(thisPtr + 0x8c); // +0x8c: pointer to sound handle (or instance)
    int soundHandle = *soundHandlePtr;

    if (soundHandle != 0 && soundHandle != 0x48) // 0x48 = sentinel for invalid/uninitialized
    {
        int baseOffset;
        if (soundHandle == 0)
        {
            baseOffset = 0;
        }
        else
        {
            baseOffset = soundHandle - 0x48; // subtract size of sound instance to get base
        }

        // FUN_006dc860 likely returns a float (easing/random value)
        float result = (float)FUN_006dc860(*(undefined4 *)(&DAT_00002494 + *(int *)(thisPtr + 0x58)), // +0x58: index into global table
                                           baseOffset + 0x68);

        if (soundHandle == 0)
        {
            baseOffset = 0;
        }
        else
        {
            baseOffset = soundHandle - 0x48;
        }

        // FUN_00424df0 likely plays/stops a sound with given parameters
        FUN_00424df0(*(undefined4 *)(&DAT_00002494 + *(int *)(thisPtr + 0x58)),
                     baseOffset,
                     result,
                     1, 0, 0);

        // Call virtual destructor/release on the sound instance (if valid)
        if (soundHandle != 0)
        {
            int *soundInstance = (int *)(soundHandle - 0x48);
            if (soundInstance != (int *)0x0)
            {
                (**(code **)*soundInstance)(1); // vtable call with arg 1 (stop/release)
            }
        }

        // Free the handle memory
        if (soundHandle != 0)
        {
            FUN_004daf90(soundHandlePtr); // likely operator delete or memory free
            *soundHandlePtr = 0;
        }
    }
    return;
}