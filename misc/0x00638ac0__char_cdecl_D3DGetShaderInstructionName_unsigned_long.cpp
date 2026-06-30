// Xbox PDB: char * __cdecl D3DGetShaderInstructionName(unsigned long)
// FUNC_NAME: AudioChannelManager::initChannels

void AudioChannelManager::initChannels(void)
{
    // External table of 21 channel name strings (e.g., "Music", "SFX", "Voice", etc.)
    extern const char* g_channelNames[21];
    // Offset 0x00 in data section

    for (int32_t i = 0; i < 21; ++i)
    {
        const char* name = g_channelNames[i];

        // Compute string length (likely used for validation or logging; result discarded here)
        const char* p = name;
        while (*p != '\0')
            ++p;

        // Allocate a channel slot (returns a handle/pointer to a channel structure)
        int32_t handle = FUN_00638920();  // possibly AudioChannelManager::allocateChannel()
        ChannelSlot* slot = reinterpret_cast<ChannelSlot*>(handle);

        // Set flags byte at offset +5: OR with 0x10 (bit 4) – e.g., enable active state
        slot->flags |= 0x10;

        // Set index byte at offset +6: 1-based channel index
        slot->index = static_cast<uint8_t>(i + 1);
    }
}