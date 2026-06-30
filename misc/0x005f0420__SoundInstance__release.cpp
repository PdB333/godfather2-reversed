// FUNC_NAME: SoundInstance::release
void SoundInstance::release() {
    // Offset +0x0C: pointer to audio resource handle (e.g., stream or bank)
    // Offset +0x14: pointer to some associated data (e.g., buffer or decoder)
    if (this->audioHandle != nullptr && this->associatedData != nullptr) {
        // Global singleton at DAT_01223518: pointer to AudioManager (or similar) structure
        // *(DAT_01223518 + 4) yields the AudioManager instance with a vtable
        // vtable index 1 (offset 4) is releaseSound(audioHandle, flags)
        AudioManager* mgr = *(AudioManager**)(DAT_01223518 + 4);
        if (mgr != nullptr) {
            typedef void (*ReleaseFunc)(void*, int);
            ReleaseFunc release = (ReleaseFunc)(*((void***)mgr)[1]);
            release(this->audioHandle, 0);
        }
    }
    // Additional cleanup (likely frees memory or marks for deletion)
    FUN_009c8eb0();
}