// FUNC_NAME: Entity::updateAudioFlagState
void __fastcall Entity__updateAudioFlagState(Entity* thisPtr) // param_1 = this
{
    uint32_t flags = *(uint32_t*)((uint8_t*)thisPtr + 0x11c); // +0x11c: audio/state flags
    uint32_t bit26 = flags >> 26 & 1; // bit 26 (0x4000000) from flags
    // Check bit22 (0x400000) and global threshold
    if (((flags >> 22) & 1) == 0 || g_audioThreshold < *(uint32_t*)((uint8_t*)thisPtr + 0x1a8)) // +0x1a8: some threshold value
    {
        if (bit26 != 0)
        {
            stopAudio(); // FUN_00949850: deactivate audio
            *(uint32_t*)((uint8_t*)thisPtr + 0x11c) = flags & 0xFBFFFFFF; // clear bit 26
        }
    }
    else
    {
        if (bit26 == 0)
        {
            startAudio(); // FUN_00949800: activate audio
            *(uint32_t*)((uint8_t*)thisPtr + 0x11c) = flags | 0x4000000; // set bit 26
        }
    }
}