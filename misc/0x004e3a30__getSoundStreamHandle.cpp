// FUNC_NAME: getSoundStreamHandle
// Address: 0x004e3a30
// Role: Returns the current sound stream handle from the sound manager instance, or a default handle if no instance exists.
uint32 getSoundStreamHandle(void)
{
    // g_pSoundManager is a global pointer to the active sound manager (DAT_012054dc)
    // g_defaultSoundStreamHandle is a global default handle (DAT_012058a4)
    if (g_pSoundManager != NULL) {
        // Stream handle stored at offset 0x16C from the sound manager instance
        return *(uint32*)((uint8*)g_pSoundManager + 0x16C);
    }
    return g_defaultSoundStreamHandle;
}