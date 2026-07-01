// FUNC_NAME: AudioDataManager::assignSoundToSpeaker
void __thiscall AudioDataManager::assignSoundToSpeaker(int thisPtr, int speakerId, int soundHandle)
{
    // Check if flag bit 0 is clear (not disabled) and that the speaker array has elements
    if (((*(uint *)(thisPtr + 0x6f4) & 1) == 0) && (*(int *)(thisPtr + 0x33c) != 0))
    {
        uint index = 0;
        int **speakerArray = *(int ***)(thisPtr + 0x338);  // +0x338: pointer to array of speaker struct pointers

        // Search for a speaker with matching ID (offset +0x5c in each speaker struct)
        while ((*speakerArray)[0x5c / 4] != speakerId)
        {
            index++;
            speakerArray++;
            if (*(uint *)(thisPtr + 0x33c) <= index)  // +0x33c: number of speakers
            {
                return;
            }
        }

        int *speakerStruct = *(int **)(*(int **)(thisPtr + 0x338) + index);  // Get the speaker struct pointer at found index
        if ((speakerStruct != 0) && (isSoundValid(soundHandle) != 0))
        {
            speakerStruct[0x10 / 4] = soundHandle;  // +0x10: sound handle associated with speaker
            if (*(int *)(thisPtr + 0xdc) != 3)      // +0xdc: current state ID
            {
                *(int *)(thisPtr + 0xc4) = 0;       // +0xc4: clear some flag or state
            }
            *(uint *)(thisPtr + 0x6f4) |= 4;        // Set flag bit 2 on the manager
            registerSoundWithSpeaker(soundHandle, speakerId);  // Associate sound and speaker globally
        }
    }
}