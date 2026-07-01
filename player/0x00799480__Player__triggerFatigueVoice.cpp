// FUNC_NAME: Player::triggerFatigueVoice

// Reconstructed from Ghidra decompile at 0x00799480
// This function handles playing a fatigue vocalization for the player character
// Offset 0xb1c stores the current sound ID (likely a handle)
// Offset 0xb1d stores a flag indicating sound is playing

void __thiscall Player::triggerFatigueVoice(int* thisPtr, int soundId, int loadParam)
{
    int soundHandle;
    char buffer[16];          // Buffer for sound loading
    char* unusedPtr;          // Possibly used by called function
    int* localC;              // Unused in this path

    // Check if the provided soundId matches the current sound slot and loadParam is 0
    if ((soundId == thisPtr[0xb1c / 4]) && (loadParam == 0))
    {
        // If a sound is already playing (flag set), clear both sound ID and flag and return
        if (thisPtr[0xb1d / 4] != 0)  // Note: offset 0xb1d is byte, but stored as int? Assume int for simplicity
        {
            thisPtr[0xb1c / 4] = 0;
            *(char*)((int)thisPtr + 0xb1d) = 0;
            return;
        }

        // Initialize audio system (stop previous sounds, etc.)
        AudioSystem::reset();  // FUN_005e3070

        // Setup local variables (unused here but may be used by virtual call)
        unusedPtr = (char*)0x0079f030;  // Possible reference to a sound bank
        localC = thisPtr;

        // Call virtual function at vtable+0xac to load a sound file
        // This likely returns a handle to the loaded sound
        soundHandle = (thisPtr->vtable[0xac / 4])(thisPtr, "sx_vox_herc_fatigue_02.emx", buffer);

        // Store the sound handle and set the active flag
        thisPtr[0xb1c / 4] = soundHandle;
        *(char*)((int)thisPtr + 0xb1d) = 1;

        // If sound loaded successfully, play it at a specified volume/position
        if (soundHandle != 0)
        {
            AudioSystem::playSound(soundHandle, gFatigueSoundVolume);  // FUN_005e6700, _DAT_00d6a5cc is a global volume
        }
    }
    return;
}