// FUNC_NAME: AudioManager::setAuxSendVolume
// Address: 0x005f4760
// This function searches for a sound instance by a float key (likely frequency or pitch),
// then sets its volume and applies auxiliary send volumes (AuxSend1, AuxSend3).
// It uses a critical section for thread safety.

bool __thiscall AudioManager::setAuxSendVolume(int thisPtr, float key, float volume)
{
    int index;
    float* slotEntry;
    int soundInstanceAddr;
    int handleIndex;
    int handle;
    float auxSend3Vol;
    float auxSend1Vol;
    float scaledVolume;
    bool result;

    result = false;
    index = 0;
    slotEntry = (float*)(thisPtr + 0x82ac); // mSoundSlotMap: array of SoundSlotEntry (size 0x5c)

    // Search for a slot where the float key matches and the integer field is non-negative
    while ( ((int)slotEntry[1] < 0) || (slotEntry[0] != key) )
    {
        index++;
        slotEntry += 0x5c / sizeof(float); // stride 0x5c (92 bytes)
        if (index > 9)
        {
            return false;
        }
    }

    if (index < 0)
    {
        return false;
    }

    // Compute address of the sound instance data (array at 0x8210, stride 0x170)
    soundInstanceAddr = thisPtr + 0x8210 + index * 0x170;

    enterCriticalSection(&gAudioCriticalSection); // FUN_00ab4db0

    // Get handle index from sound instance (offset 0x9c)
    handleIndex = *(int*)(soundInstanceAddr + 0x9c); // mHandleIndex
    handleIndex *= 0x10; // each handle entry is 0x10 bytes

    // Get handle from array at 0x81c4 (offset by handleIndex)
    handle = *(int*)(thisPtr + 0x81c4 + handleIndex); // mHandleArray

    if (handle != 0)
    {
        // Get auxiliary send volumes
        auxSend3Vol = getAuxSendVolume("AuxSend3", &key); // FUN_004dafd0 + FUN_005e9d90
        auxSend1Vol = getAuxSendVolume("AuxSend1", &key);

        // Check threshold and aux send 3 activity
        if ( (gAuxSendThreshold <= *(float*)(soundInstanceAddr + 0x134)) && (auxSend3Vol != 0.0f) )
        {
            // Set volume in sound instance (offset 0x98)
            *(float*)(soundInstanceAddr + 0x98) = volume; // mVolume

            // Scale volume by factor at offset 0x90
            scaledVolume = *(float*)(soundInstanceAddr + 0x90) * volume; // mVolumeScale

            beginAudioUpdate(); // FUN_00c9eac0

            if (auxSend1Vol != 0.0f)
            {
                float finalVolume = scaledVolume;
                // Check mute flag at offset 0x9089
                if (*(char*)(thisPtr + 0x9089) == '\0') // mMuteAll
                {
                    finalVolume = 0.0f;
                }
                setChannelVolume(0, finalVolume); // FUN_00ca4e90
            }

            setChannelVolume(0, scaledVolume); // FUN_00ca4e90
            endAudioUpdate(); // FUN_00c9eae0

            result = true;
        }

        // Apply changes to the sound handle
        applySoundHandleChanges(thisPtr, *(int*)(thisPtr + 0x81c0 + handleIndex), handle); // FUN_005ebfa0
    }

    leaveCriticalSection(&gAudioCriticalSection); // FUN_00ab4e70
    return result;
}