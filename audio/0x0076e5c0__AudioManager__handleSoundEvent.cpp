// FUNC_NAME: AudioManager::handleSoundEvent
void __thiscall AudioManager::handleSoundEvent(AudioManager* thisPtr, uint soundId, char playFlag)
{
    // thisPtr is the AudioManager object
    // soundId: the sound event ID to handle
    // playFlag: non-zero to play, zero to stop? (based on argument pattern)
    
    // +0x50: pointer to sound data (SoundData*)
    SoundData* soundData = *(SoundData**)(thisPtr + 0x50);
    
    // +0x1b8c: flag indicating if sound is enabled (e.g., not muted)
    bool isSoundEnabled = *(char*)(soundData + 0x1b8c) == '\x01';
    
    // The sound data contains arrays of sound IDs at offsets 0x660-0x6b4 (22 entries)
    // These are grouped into categories. Each group has a different sound effect.
    
    // Group 1: IDs at offsets 0x68c, 0x6b4, 0x674
    if ((soundId == *(uint*)(soundData + 0x68c) >> 2) ||
        (soundId == *(uint*)(soundData + 0x6b4) >> 2) ||
        (soundId == *(uint*)(soundData + 0x674) >> 2))
    {
        if (playFlag != '\0')
        {
            // Play sound with ID based on isSoundEnabled
            uint soundEffectId = (isSoundEnabled ? 0xa96a17c9 : 0) + 0xf5cf680f;
            (*(void (__thiscall**)(AudioManager*, uint))(*thisPtr + 0x2c))(thisPtr, soundEffectId);
            return;
        }
        // Stop sound
        uint soundEffectId = (isSoundEnabled ? 0x462665f7 : 0) + 0xeac4423f;
        (*(void (__thiscall**)(AudioManager*, uint, int, int, int, float, float))(*thisPtr + 0x2c))
            (thisPtr, soundEffectId, 1, 1, 0, 1.0f, 1.0f);
    }
    // Group 2: IDs at offsets 0x678, 0x67c, 0x680, 0x684, 0x688
    else if ((soundId == *(uint*)(soundData + 0x678) >> 2) ||
             (soundId == *(uint*)(soundData + 0x67c) >> 2) ||
             (soundId == *(uint*)(soundData + 0x680) >> 2) ||
             (soundId == *(uint*)(soundData + 0x684) >> 2) ||
             (soundId == *(uint*)(soundData + 0x688) >> 2))
    {
        if (playFlag != '\0')
        {
            uint soundEffectId = (isSoundEnabled ? 0xda82c77 : 0) + 0x7b6c9b97;
            (*(void (__thiscall**)(AudioManager*, uint))(*thisPtr + 0x2c))(thisPtr, soundEffectId);
            return;
        }
        uint soundEffectId = (isSoundEnabled ? 0x64b245c9 : 0) + 0xcd26ad67;
        (*(void (__thiscall**)(AudioManager*, uint, int, int, int, float, float))(*thisPtr + 0x2c))
            (thisPtr, soundEffectId, 1, 1, 0, 1.0f, 1.0f);
        return;
    }
    // Group 3: IDs at offsets 0x6a0, 0x6a4, 0x6a8, 0x6ac, 0x6b0
    else if ((soundId == *(uint*)(soundData + 0x6a0) >> 2) ||
             (soundId == *(uint*)(soundData + 0x6a4) >> 2) ||
             (soundId == *(uint*)(soundData + 0x6a8) >> 2) ||
             (soundId == *(uint*)(soundData + 0x6ac) >> 2) ||
             (soundId == *(uint*)(soundData + 0x6b0) >> 2))
    {
        if (playFlag != '\0')
        {
            uint soundEffectId = (isSoundEnabled ? 0x88d9f149 : 0) + 0x4d68d42c;
            (*(void (__thiscall**)(AudioManager*, uint))(*thisPtr + 0x2c))(thisPtr, soundEffectId);
            return;
        }
        uint soundEffectId = (isSoundEnabled ? 0xda82c77 : 0) + 0x7c03365c;
        (*(void (__thiscall**)(AudioManager*, uint, int, int, int, float, float))(*thisPtr + 0x2c))
            (thisPtr, soundEffectId, 1, 1, 0, 1.0f, 1.0f);
        return;
    }
    // Group 4: IDs at offsets 0x670, 0x66c, 0x69c, 0x668, 0x698, 0x664, 0x694, 0x660, 0x690
    else if ((soundId == *(uint*)(soundData + 0x670) >> 2) ||
             (soundId == *(uint*)(soundData + 0x66c) >> 2) ||
             (soundId == *(uint*)(soundData + 0x69c) >> 2) ||
             (soundId == *(uint*)(soundData + 0x668) >> 2) ||
             (soundId == *(uint*)(soundData + 0x698) >> 2) ||
             (soundId == *(uint*)(soundData + 0x664) >> 2) ||
             (soundId == *(uint*)(soundData + 0x694) >> 2) ||
             (soundId == *(uint*)(soundData + 0x660) >> 2) ||
             (soundId == *(uint*)(soundData + 0x690) >> 2))
    {
        if (playFlag != '\0')
        {
            uint soundEffectId = (isSoundEnabled ? 0x2ab10ef7 : 0) + 0x1e6846d8;
            (*(void (__thiscall**)(AudioManager*, uint))(*thisPtr + 0x2c))(thisPtr, soundEffectId);
            return;
        }
        uint soundEffectId = (isSoundEnabled ? 0x92db9549 : 0) + 0x10aa9ae0;
        (*(void (__thiscall**)(AudioManager*, uint, int, int, int, float, float))(*thisPtr + 0x2c))
            (thisPtr, soundEffectId, 1, 1, 0, 1.0f, 1.0f);
        return;
    }
    // If soundId doesn't match any known group, do nothing
    return;
}