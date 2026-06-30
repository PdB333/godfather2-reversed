// FUNC_NAME: AudioStreamManager::shutdown
// Address: 0x005f1cc0
// Role: Shuts down and resets audio stream state, releasing pending resources and zeroing global audio state variables.

// Global audio state structure (offsets relative to base at 0x011a0ef0)
struct AudioStreamState {
    /* +0x00 (0x011a0ef0) */ uint32_t field_0;
    /* +0x04 (0x011a0ef4) */ uint32_t field_4;
    /* +0x08 (0x011a0ef8) */ uint8_t  field_8;   // Set to 0x80 (default volume?)
    /* +0x0A (0x011a0efa) */ uint16_t field_A;
    /* +0x0C (0x011a0efc) */ uint32_t field_C;
    /* +0x10 (0x011a0f00) */ char*    pStreamBuf;
    /* +0x14 (0x011a0f04) */ uint32_t field_14;
    /* +0x18 (0x011a0f08) */ uint32_t field_18;
    /* +0x1C (0x011a0f0c) */ uint32_t field_1C;
    /* +0x20 (0x011a0f10) */ uint32_t flags;      // Bit 0 indicates streaming active
} g_audioState __attribute__((section(".bss"), used));

// Pointer to audio manager instance (0x01223518)
int32_t** g_ppAudioMgrBase __attribute__((section(".bss"), used));

void AudioStreamManager::shutdown()
{
    // Release the stream if it is currently active and the manager object exists
    if (g_audioState.pStreamBuf != nullptr &&
        (g_audioState.flags & 1) != 0)
    {
        int32_t* pAudioMgrObj = g_ppAudioMgrBase[1]; // dereference offset 4 of base (object pointer)
        if (pAudioMgrObj != nullptr)
        {
            // Call virtual function at vtable+4 (second entry)
            void (*releaseFunc)(void*, int32_t) = (void (*)(void*, int32_t))(*(int32_t*)(*(int32_t*)pAudioMgrObj + 4));
            releaseFunc(pAudioMgrObj, 0);
        }
    }

    // Reset all global state fields
    g_audioState.pStreamBuf = nullptr;
    g_audioState.field_14 = 0;
    g_audioState.field_18 = 0;
    g_audioState.field_1C = 0;
    g_audioState.field_C = 0;
    g_audioState.flags = 0;
    g_audioState.field_0 = 0;
    g_audioState.field_4 = 0;
    g_audioState.field_A = 0;
    g_audioState.field_8 = 0x80;
}