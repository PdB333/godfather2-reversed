// FUNC_NAME: SoundManager::stopSound
void __fastcall SoundManager::stopSound(uint this)
{
    uint soundStateIndex;

    // Check if there's an active sound resource at +0xa8
    if (*(uint *)(this + 0xa8) != 0)
    {
        soundStateIndex = *(uint *)(this + 0xa8) & 0xff;

        // If the channel state (indexed by m_channelIndex * 0x10) is non-zero, add 0x10 to index
        if (g_channelStateTable[*(int *)(this + 0x14) * 0x10] != '\0')
        {
            soundStateIndex = soundStateIndex + 0x10;
        }

        // Call engine mixer stop function
        mixerStop();

        // Clear the sound active flag at indexed position
        g_soundActiveFlags[soundStateIndex] = 0;
    }

    // Call engine mixer update to finalize state
    mixerUpdate();
}