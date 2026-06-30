// FUNC_NAME: SoundManager::initiateSoundSlots
void __thiscall SoundManager::initiateSoundSlots(int **soundInstanceArray, byte soundType, float durationScale)
{
    int soundInstance;
    float scaledDuration;
    byte numSlots;
    int slotIndex;
    int extraParam; // coming from EDI (unknown purpose, maybe priority or userData)

    if (this != 0) {
        // Calculate number of slots: based on a config byte (0 -> 1 slot? 1 -> 2 slots? maybe stereo/mono)
        numSlots = (*(byte *)(*(int *)(this + 8) + 8) & 1) + 1;
        if (numSlots != 0) {
            for (slotIndex = 0; slotIndex < numSlots; slotIndex++) {
                soundInstance = *soundInstanceArray;
                if (soundInstance != 0) {
                    // Set flags: bit 5 (0x20) and bit 8 (0x100) - might indicate active, looping etc.
                    *(ushort *)(soundInstance + 0x10) |= 0x120;
                    // Store sound type (e.g., SFX, dialogue, etc.)
                    *(byte *)(soundInstance + 0x1C) = soundType;
                    // Clear a flag/state byte
                    *(byte *)(soundInstance + 0x1D) = 0;
                    // Store extra parameter (likely priority or identifier)
                    *(int *)(soundInstance + 0x20) = extraParam;
                    // Scale duration by global factor (sample rate or pitch adjustment)
                    scaledDuration = durationScale * gSoundDurationScale; // DAT_00e445e0
                    *(int *)(soundInstance + 0x14) = (int)(longlong)ROUND(scaledDuration);
                    // Call lower-level function to start the sound playback
                    FUN_005dbc10(*(ushort *)(soundInstance + 8),  // sound ID or handle
                                 soundType,
                                 (int)scaledDuration,
                                 ~(byte)*(ushort *)(soundInstance + 0x10) & 1); // invert bit0 as interrupt flag
                }
                soundInstanceArray++;
            }
        }
    }
    return;
}